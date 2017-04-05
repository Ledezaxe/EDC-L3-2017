#include "client_brute_force.h"


char * buffer_rcv = NULL;
char * buffer_id =NULL ;
char * buffer_name=NULL;
char * commande = NULL;
bool game = true;
Client_data * client_data;

Socket_client * open_client_sockets(char * id){
  if(id)
  {
    Socket_client * new = malloc( sizeof( Socket_client ));
    new -> socket_contex = zmq_ctx_new();
    new -> socket_port1 = zmq_socket( new -> socket_contex , ZMQ_DEALER );
    new -> socket_port2 = zmq_socket( new -> socket_contex , ZMQ_DEALER );
    new->timeout = client_time_out;

    zmq_setsockopt( new -> socket_port1 , ZMQ_IDENTITY , id , strlen( id ));
    zmq_setsockopt( new -> socket_port1 , ZMQ_RCVTIMEO , &new->timeout , sizeof( int ));
    zmq_setsockopt( new -> socket_port1 , ZMQ_SNDTIMEO , &new->timeout  , sizeof( int ));
    zmq_setsockopt( new -> socket_port2 , ZMQ_IDENTITY , id , strlen( id ));
    zmq_setsockopt( new -> socket_port2 , ZMQ_RCVTIMEO , &new->timeout  , sizeof( int ));
    zmq_setsockopt( new -> socket_port2 , ZMQ_SNDTIMEO , &new->timeout  , sizeof( int ));

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
  }else{
    printf( "Client:ERROR #1-4: ID IS NULL FOR IDENTITY\n" );
    exit( EXIT_FAILURE );
  }
}

void close_client_socket(Socket_client * client_data){
  zmq_close( client_data->socket_port1);
  zmq_close(client_data->socket_port2 );
  zmq_ctx_destroy(client_data->socket_contex);
  free(client_data);
}

Client_data * create_client_data(char * id , char * name){
  if(id == NULL){
    printf( "Client:ERROR #2-1: ID IS NULL FOR CLIENT\n" );
    exit(EXIT_FAILURE);
  }
  if(name == NULL){
    printf( "Client:ERROR #2-1: NAME IS NULL FOR CLIENT\n" );
    exit(EXIT_FAILURE);
  }
  Client_data * new = malloc( sizeof(Client_data));
  new->socket = open_client_sockets(id);
  new->id = id;
  new->name = name;
  new->k =0;
  new->x=0;
  new->y=0;
  return new;
}


void destroy_client_data(Client_data * client_data){

  if(client_data->id){
    free(client_data->id);
  }
  if(client_data->name){
    free(client_data->name);
  }
  if(client_data->word){
    for ( unsigned int i = 0; i <client_data->k ; ++ i )
    {
      free(client_data->word[i]);
    }
    free(client_data->word);
  }
  if(client_data->grid){
    for ( unsigned int i = 0; i <client_data->x ; ++ i )
    {
      free(client_data->grid[i]);
    }
    free(client_data->grid);
  }
  if(client_data->socket){
    close_client_socket(client_data->socket);
  }
  free(client_data);
}

void sig_handler( int signo )
{
  if ( signo == SIGINT || signo == SIGTERM )
  {
    zmq_send( client_data->socket->socket_port1 , "" , 0 , ZMQ_NOBLOCK );
    zmq_send( client_data->socket->socket_port1 , "LEAVE" , 5 , ZMQ_NOBLOCK );
    destroy_client_data(client_data);
    if(buffer_rcv != NULL){
      free(buffer_rcv);
    }
    if(buffer_id !=NULL){
      free(buffer_id);
    }
    if(buffer_name!=NULL){
      free(buffer_name);
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


char * recevoir( Client_data * client_data , char * message )
{

  int64_t more = 0x1;
  size_t more_size = sizeof more;
  zmq_recv( client_data->socket->socket_port2 , message , 1 , 0 );
  while ( more > 0 )
  {
    char * buffer = calloc( 64 , sizeof( char ));
    zmq_recv( client_data->socket->socket_port2 , buffer , 64 , 0 );
    strcat( message , buffer );
    zmq_getsockopt( client_data->socket->socket_port2 , ZMQ_RCVMORE , &more , &more_size );
    free( buffer );
  }
  if ( strlen( message ) == 0 )
  {
    printf( "Network Disconnected Or Fault\n" );
    zmq_send( client_data->socket->socket_port1 , "" , 0 , ZMQ_SNDMORE );
    zmq_send( client_data->socket->socket_port1 , "LEAVE" , 5 , 0 );
    exit( 1 );
  }
  return message;
}

char * rnb( Client_data * client_data , char * message )
{
  int64_t more = 0x1;
  size_t more_size = sizeof more;
  zmq_recv( client_data->socket->socket_port2 , message , 1 , ZMQ_NOBLOCK );
  if ( message == NULL)
  {
    return NULL;
  }
  while ( more > 0 )
  {
    char * buffer = calloc( 64 , sizeof( char ));
    zmq_recv( client_data->socket->socket_port2 , buffer , 64 , ZMQ_NOBLOCK );
    strcat( message , buffer );
    zmq_getsockopt( client_data->socket->socket_port2 , ZMQ_RCVMORE , &more , &more_size );
    free( buffer );
  }
  return message;
}

void unserialize_word_list()
{
  buffer_rcv = calloc( client_calloc_size , sizeof( char ));
  buffer_rcv = recevoir(client_data, buffer_rcv );
  char * messagesep = malloc( 64 * sizeof( char ));
  char * ptr2 = messagesep;
  char * ptr = calloc( client_calloc_size , sizeof( char ));
  char * ptr3 = ptr;
  char * buffer = buffer_rcv;
  ptr = strcpy( ptr ,buffer_rcv);
  unsigned int counter =0;
  while ( (messagesep = strsep( &buffer_rcv , " " ))!=NULL)
  {
    counter ++;
  }
  counter-=1;

  client_data->word = calloc(counter , sizeof( char ** ));
  messagesep = strsep( &ptr , " " );
  int k = 0;

  for ( int i = 0; i < counter; ++ i )
  {
    client_data->word[i] = calloc( 27, sizeof( char ));
  }

  while (( messagesep = strsep( &ptr , " " )) != NULL)
  {
    unsigned int size = strlen( messagesep );
    client_data->word[ k ] = memcpy( client_data->word[ k ] , messagesep ,size);
    client_data->word[ k ][ size ] = '\0';
    k ++;

  }
  client_data->word[ counter ] = NULL;
  client_data->word = client_data->word;
  client_data->k = counter;
  free(buffer);
  free(ptr3);
  free(ptr2);
}

void client_join_game( char * name )
{
  char * sender = malloc( 64 * sizeof( char ));
  if ( strlen( name ) == 0 )
  {
    snprintf( sender , 64 , "JOIN ANONYMOUS" );
  }
  else
  {
    snprintf( sender , 64 , "JOIN %s" , name );
  }
  zmq_send( client_data->socket->socket_port1 , "" , 0 , ZMQ_SNDMORE );
  zmq_send( client_data->socket->socket_port1 , sender , strlen( sender ) , 0 );
  free( sender );
}

void unserialize_grid( char * grid )
{

  char * fmessage = calloc( 64 , sizeof( char ));
  char * buffer_fmessage = fmessage;
  fmessage = strsep( &grid , " " );
  fmessage = strsep( &grid , " " );
  unsigned int x = atoi( fmessage );
  fmessage = strsep( &grid , " " );

  unsigned int y = atoi( fmessage );

  char ** serialise = malloc( y * sizeof( char * ));
  char * ret = calloc( 6250020 , sizeof( char ));
  char * buffer_ret =ret;
  ret = strsep( &grid , " " );
  for ( unsigned int k = 0; k < y; ++ k )
  {
    serialise[k]=calloc(x+1 ,sizeof(char));

  }

  int cpt = 0;
  for ( unsigned int i = 0; i < x; ++ i )
  {
    for ( unsigned int j = 0; j < y; ++ j )
    {
      serialise[i][j] = ret[ cpt ];
      cpt ++;
    }
  }
  client_data->grid =serialise;
  client_data->x = x;
  client_data->y = y;
  free(buffer_fmessage);
  free(buffer_ret);
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
        char * ret2 = calloc( client_calloc_size, sizeof( char ));
        do
        {
          ret2 = rnb( client_data , ret2 );
        }
        while ( ret2 == NULL);
        printf( "%s \n" , ret2 );
        printf( "Disconnected to the server\n" );
        game = false;
        free( ret );
        free( ret2 );
        zmq_send( client_data->socket->socket_port1 , "" , 0 , ZMQ_SNDMORE );
        zmq_send( client_data->socket->socket_port1 , "LEAVE" , 5 , 0 );
        destroy_client_data(client_data);
        if(buffer_rcv != NULL){
          free(buffer_rcv);
        }
        if(buffer_id !=NULL){
          free(buffer_id);
        }
        if(buffer_name!=NULL){
          free(buffer_name);
        }
        if ( commande != NULL)
        {
          free( commande );
        }
        exit(EXIT_SUCCESS);
      }
      else if ( strcmp( ret , "LEAVE@CLIENT" ) == 0 )
      {
        printf( "server off line\n" );
        game = false;
        destroy_client_data(client_data);
        if(buffer_rcv != NULL){
          free(buffer_rcv);
        }
        if(buffer_id !=NULL){
          free(buffer_id);
        }
        if(buffer_name!=NULL){
          free(buffer_name);
        }
        if ( commande != NULL)
        {
          free( commande );
        }
        exit(EXIT_FAILURE);
      }
      free( ret );
    }
  }

  pthread_exit( 0 );

}

void display_grid()
{
  unsigned int i, j;
  for (i = 0 ; i < client_data-> x ; i++)
  {
    for (j = 0 ; j < client_data-> y  ; j++)
    {
      printf("%c", client_data->grid[j][i]);
    }
    printf("\n");
  }
  printf("\n");
}

void display_words()
{
  unsigned int i;
  for (i = 0 ; i < client_data-> k ; i++)
  {
    printf("%s\n",client_data->word[i]);
  }
  printf("\n");
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
  client_data = create_client_data(buffer_id,buffer_name);
  client_join_game( buffer_name );


  buffer_rcv = calloc( client_calloc_size , sizeof( char ));
  buffer_rcv = recevoir( client_data, buffer_rcv );
  unserialize_grid( buffer_rcv );
  free( buffer_rcv );
  display_grid();

  unserialize_word_list();
  display_words();


  commande = calloc( 64 , sizeof( char ));
  if ( pthread_create( &message_th , NULL , game_timer , NULL) == - 1 )
  {
    printf( "thread : erreur création\n" );
  }
  game = true;
  while (game !=false)
  {

    char *res;

    res = strdup("DEBUT");
    while (res != NULL)
    {
      free(res);
      res = force_brute(client_data->grid, client_data->word, client_data->x-1, client_data->y-1);
      if (res != NULL)
      {
        printf( "%s\n" ,res);
        zmq_send( client_data -> socket -> socket_port1 , "" , 0 , ZMQ_SNDMORE );
        zmq_send( client_data -> socket -> socket_port1 , res , sizeof( res ) , 0 );
      }
      sleep(0.01);
    }
   break;

  }
  zmq_send( client_data->socket->socket_port1 , "" , 0 , ZMQ_SNDMORE );
  zmq_send( client_data->socket->socket_port1 , "LEAVE" , 5 , ZMQ_SNDMORE );

  printf( "Deconnextion du serveur" );

  destroy_client_data(client_data);
  if(buffer_rcv != NULL){
    free(buffer_rcv);
  }
  if(buffer_id !=NULL){
    free(buffer_id);
  }
  if(buffer_name!=NULL){
    free(buffer_name);
  }
  return 0;
}