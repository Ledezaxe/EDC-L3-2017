#include "client_texte1.h"


char * buffer_id = NULL;
char * buffer_name = NULL;
char * commande = NULL;
bool game = true;
Client_data * client_data;

Socket_client * open_client_sockets( char * id )
{
  if ( id )
  {
    Socket_client * new = malloc( sizeof( Socket_client ));
    new -> socket_contex = zmq_ctx_new();
    new -> socket_port1 = zmq_socket( new -> socket_contex , ZMQ_DEALER );
    new -> socket_port2 = zmq_socket( new -> socket_contex , ZMQ_DEALER );
    new -> timeout = client_time_out;

    zmq_setsockopt( new -> socket_port1 , ZMQ_IDENTITY , id , strlen( id ));
    zmq_setsockopt( new -> socket_port1 , ZMQ_RCVTIMEO , &new -> timeout , sizeof( int ));
    zmq_setsockopt( new -> socket_port1 , ZMQ_SNDTIMEO , &new -> timeout , sizeof( int ));
    zmq_setsockopt( new -> socket_port2 , ZMQ_IDENTITY , id , strlen( id ));
    zmq_setsockopt( new -> socket_port2 , ZMQ_RCVTIMEO , &new -> timeout , sizeof( int ));
    zmq_setsockopt( new -> socket_port2 , ZMQ_SNDTIMEO , &new -> timeout , sizeof( int ));

    int socket_bind_output_1 = zmq_connect( new -> socket_port1 , "tcp://"CLIENT_ADRESSE":"CLIENT_PORT1 );
    int socket_bind_output_2 = zmq_connect( new -> socket_port2 , "tcp://"CLIENT_ADRESSE":"CLIENT_PORT2 );
    if ( socket_bind_output_1 != 0 && socket_bind_output_2 != 0 )
    {
      zmq_close( new -> socket_port1 );
      zmq_close( new -> socket_port2 );
      zmq_ctx_destroy( new -> socket_contex );
      printf( "Client:ERROR #1-1: MUTUAL PORT CONNECT ERROR\n" );
      free( new );
      exit( EXIT_FAILURE );
    }
    else if ( socket_bind_output_1 != 0 )
    {
      zmq_close( new -> socket_port1 );
      zmq_ctx_destroy( new -> socket_contex );
      printf( "Client:ERROR #1-2: PORT 1 CONNECT ERROR\n" );
      free( new );
      exit( EXIT_FAILURE );
    }
    else if ( socket_bind_output_2 != 0 )
    {
      zmq_close( new -> socket_port2 );
      zmq_ctx_destroy( new -> socket_contex );
      printf( "Client:ERROR #1-3: PORT 2 CONNECT ERROR\n" );
      free( new );
      exit( EXIT_FAILURE );
    }
    return new;
  }
  else
  {
    printf( "Client:ERROR #1-4: ID IS NULL FOR IDENTITY\n" );
    exit( EXIT_FAILURE );
  }
}

void close_client_socket( Socket_client * client_data )
{
  zmq_close( client_data -> socket_port1 );
  zmq_close( client_data -> socket_port2 );
  zmq_ctx_destroy( client_data -> socket_contex );
  free( client_data );
}

Client_data * create_client_data( char * id , char * name )
{
  if ( id == NULL)
  {
    printf( "Client:ERROR #2-1: ID IS NULL FOR CLIENT\n" );
    exit( EXIT_FAILURE );
  }
  if ( name == NULL)
  {
    printf( "Client:ERROR #2-1: NAME IS NULL FOR CLIENT\n" );
    exit( EXIT_FAILURE );
  }
  Client_data * new = malloc( sizeof( Client_data ));
  new -> socket = open_client_sockets( id );
  new -> id = id;
  new -> name = name;
  return new;
}


void destroy_client_data( Client_data * client_data )
{

  if ( client_data -> id )
  {
    free( client_data -> id );
  }
  if ( client_data -> name )
  {
    free( client_data -> name );
  }
  if ( client_data -> socket )
  {
    close_client_socket( client_data -> socket );
  }
  free( client_data );
}

void sig_handler( int signo )
{
  if ( signo == SIGINT || signo == SIGTERM )
  {
    zmq_send( client_data -> socket -> socket_port1 , "" , 0 , ZMQ_NOBLOCK );
    zmq_send( client_data -> socket -> socket_port1 , "LEAVE" , 5 , ZMQ_NOBLOCK );
    destroy_client_data( client_data );
    if ( buffer_id != NULL)
    {
      free( buffer_id );
    }
    if ( buffer_name != NULL)
    {
      free( buffer_name );
    }
    if ( commande != NULL)
    {
      free( commande );
    }

    exit( EXIT_FAILURE );
  }

}

void fgetstring( const unsigned int size , char * string )
{
  char * fgetreturn = fgets( string , sizeof( char ) * size , stdin );
  if ( fgetreturn == 0 )
  {
    exit( - 1 );
  }
  if ( strlen( string ) == size && string[ size - 1 ] == '\n' )
  {
    string[ size - 1 ] = '\0';
  }
  else
  {
    int s = strlen( string ) - 1;
    string[ s ] = '\0';
  }
}

void gen_random( char * s , const int len )
{
  srand(( 1 / ( time(NULL)) ^ rand()) * getpid());
  static const char alphanum[] = "0123456789"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz";

  for ( int i = 0; i < len; ++ i )
  {
    s[ i ] = alphanum[ rand() % ( sizeof( alphanum ) - 1 ) ];
  }

  s[ len ] = 0;
}


void rcv( Client_data * client_data)
{
  char * message = calloc(client_calloc_size,sizeof(char));
  int64_t more = 0x1;
  size_t more_size = sizeof more;
  zmq_recv( client_data -> socket -> socket_port2 , message , 1 , 0 );
  while ( more > 0 )
  {
    char * buffer = calloc( client_calloc_buffer , sizeof( char ));
    zmq_recv( client_data -> socket -> socket_port2 , buffer , client_calloc_buffer , 0 );
    strcat( message , buffer );
    zmq_getsockopt( client_data -> socket -> socket_port2 , ZMQ_RCVMORE , &more , &more_size );
    free( buffer );
  }
  if ( strlen( message ) == 0 )
  {
    printf( "Network Disconnected Or Fault\n" );
    zmq_send( client_data -> socket -> socket_port1 , "" , 0 , ZMQ_SNDMORE );
    zmq_send( client_data -> socket -> socket_port1 , "LEAVE" , 5 , 0 );
    exit( 1 );
  }
  if(message!=NULL)
  free(message);
}

char * rnb( Client_data * client_data , char * message )
{
  int64_t more = 0x1;
  size_t more_size = sizeof more;
  zmq_recv( client_data -> socket -> socket_port2 , message , 1 , ZMQ_NOBLOCK );
  if ( message == NULL)
  {
    return NULL;
  }
  while ( more > 0 )
  {
    char * buffer = calloc( client_calloc_buffer , sizeof( char ));
    zmq_recv( client_data -> socket -> socket_port2 , buffer , client_calloc_buffer , ZMQ_NOBLOCK );
    strcat( message , buffer );
    zmq_getsockopt( client_data -> socket -> socket_port2 , ZMQ_RCVMORE , &more , &more_size );
    free( buffer );
  }
  return message;
}


void client_join_game( char * name )
{
  char * sender = malloc( client_calloc_buffer * sizeof( char ));
  if ( strlen( name ) == 0 )
  {
    snprintf( sender , client_calloc_buffer , "JOIN ANONYMOUS" );
  }
  else
  {
    snprintf( sender , client_calloc_buffer , "JOIN %s" , name );
  }
  zmq_send( client_data -> socket -> socket_port1 , "" , 0 , ZMQ_SNDMORE );
  zmq_send( client_data -> socket -> socket_port1 , sender , strlen( sender ) , 0 );
  free( sender );
}

pthread_t message_th;

void * game_timer()
{
  while ( game == true )
  {
    char * ret = calloc( client_calloc_size , sizeof( char ));
    ret = rnb( client_data , ret );
    if ( ret != NULL)
    {
      if ( strcmp( ret , "SCORE" ) == 0 )
      {
        char * ret2 = calloc( client_calloc_size , sizeof( char ));
        do
        {
          ret2 = rnb( client_data , ret2 );
        }
        while ( ret2 == NULL);
        printf( "%s \n" , ret2 );
        printf( "Disconnected to the server\n" );
        game = false;
        free(ret);
        free( ret2 );
        zmq_send( client_data -> socket -> socket_port1 , "" , 0 , ZMQ_SNDMORE );
        zmq_send( client_data -> socket -> socket_port1 , "LEAVE" , 5 , 0 );
        destroy_client_data( client_data );
        if ( buffer_id != NULL)
        {
          free( buffer_id );
        }
        if ( buffer_name != NULL)
        {
          free( buffer_name );
        }
        if ( commande != NULL)
        {
          free( commande );
        }
        exit( EXIT_SUCCESS );
      }
      else if ( strcmp( ret , "LEAVE@CLIENT" ) == 0 )
      {
        printf( "server off line\n" );
        game = false;
        free( ret );
        destroy_client_data( client_data );
        if ( buffer_id != NULL)
        {
          free( buffer_id );
        }
        if ( buffer_name != NULL)
        {
          free( buffer_name );
        }
        if ( commande != NULL)
        {
          free( commande );
        }
        exit( EXIT_FAILURE );
      }
      free( ret );
    }
  }

  pthread_exit( 0 );

}

int main( void )
{
  signal( SIGINT , sig_handler );
  signal( SIGTERM , sig_handler );

  buffer_id = calloc( client_id_size , sizeof( char ));
  buffer_name = calloc( client_name_size , sizeof( char ));
  gen_random( buffer_id , client_id_size );

  printf( "Connexion au serveur\nEntrée nom utilisateur ?<max 19 charactere>\n" );
  fgetstring( client_name_size , buffer_name );
  client_data = create_client_data( buffer_id , buffer_name );
  client_join_game( buffer_name );

  rcv(client_data);

  commande = calloc( client_calloc_buffer , sizeof( char ));
  if ( pthread_create( &message_th , NULL , game_timer , NULL) == - 1 )
  {
    printf( "thread : erreur création\n" );
  }
  game = true;
  while ( game != false )
  {
    commande[ 0 ] = '\0';
    fgetstring( client_calloc_buffer , commande );
    if ( strlen( commande ) != 0 )
    {
      if ( strcmp( commande , "LEAVE" ) == 0 )
      {
        zmq_send( client_data -> socket -> socket_port1 , "" , 0 , ZMQ_SNDMORE );
        zmq_send( client_data -> socket -> socket_port1 , "LEAVE" , client_calloc_buffer , 0 );
        game = false;
      }
      else
      {
        zmq_send( client_data -> socket -> socket_port1 , "" , 0 , ZMQ_SNDMORE );
        zmq_send( client_data -> socket -> socket_port1 , commande , client_calloc_buffer , 0 );
      }
    }
  }
  zmq_send( client_data -> socket -> socket_port1 , "" , 0 , ZMQ_SNDMORE );
  zmq_send( client_data -> socket -> socket_port1 , "LEAVE" , 5 , ZMQ_SNDMORE );

  printf( "Deconnextion du serveur" );

  destroy_client_data( client_data );
  if ( buffer_id != NULL)
  {
    free( buffer_id );
  }
  if ( buffer_name != NULL)
  {
    free( buffer_name );
  }
  if ( commande != NULL)
  {
    free( commande );
  }

  return 0;
}