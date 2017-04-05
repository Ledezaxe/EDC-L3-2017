//
// Created by nfoissac on 09/11/16.
//

#include "server_a.h"

bool gird_generated = false;
bool game_started = false;
bool game_wait_restart = false;

List_Client * test = NULL;
Socket_server * server = NULL;

unsigned int timer_time_score;

Socket_server * open_server_sockets()
{
  Socket_server * new = malloc( sizeof( Socket_server ));
  new -> socket_contex = zmq_ctx_new();
  new -> socket_port1 = zmq_socket( new -> socket_contex , ZMQ_ROUTER );
  new -> socket_port2 = zmq_socket( new -> socket_contex , ZMQ_ROUTER );
  int socket_bind_output_1 = zmq_bind( new -> socket_port1 , "tcp://"SERVER_ADRESSE":"SERVER_PORT1 );
  int socket_bind_output_2 = zmq_bind( new -> socket_port2 , "tcp://"SERVER_ADRESSE":"SERVER_PORT2 );
  if ( socket_bind_output_1 != 0 && socket_bind_output_2 != 0 )
  {
    zmq_close( new -> socket_port1 );
    zmq_close( new -> socket_port2 );
    zmq_ctx_destroy( new -> socket_contex );
    printf( "Server:ERROR #1-1: MUTUAL PORT BIND ERROR\n" );
    free( new );
    exit( EXIT_FAILURE );
  }
  else if ( socket_bind_output_1 != 0 )
  {
    zmq_close( new -> socket_port1 );
    zmq_ctx_destroy( new -> socket_contex );
    printf( "Server:ERROR #1-2: PORT 1 BIND ERROR\n" );
    free( new );
    exit( EXIT_FAILURE );
  }
  else if ( socket_bind_output_2 != 0 )
  {
    zmq_close( new -> socket_port2 );
    zmq_ctx_destroy( new -> socket_contex );
    printf( "Server:ERROR #1-3: PORT 2 BIND ERROR\n" );
    free( new );
    exit( EXIT_FAILURE );
  }
  return new;
}

void close_server_sockets( Socket_server * socketServer )
{
  zmq_close( socketServer -> socket_port1 );
  zmq_close( socketServer -> socket_port2 );
  zmq_ctx_destroy( socketServer -> socket_contex );
  free( socketServer );
}


void envoyer( void * socket_port , char * mot , char * id )
{
  int wordsize = strlen( mot );
  int decal = 0;
  int chunck = SERVER_BUFFER_CHUNK;

  zmq_send( socket_port , id , strlen( id ) , ZMQ_SNDMORE );
  zmq_send( socket_port , "" , 0 , ZMQ_SNDMORE );
  while ( wordsize >= 0 )
  {
    char * message = calloc( chunck , sizeof( char ));
    memmove( message , mot + decal , chunck );
    zmq_send( socket_port , message , chunck , ZMQ_SNDMORE );
    free( message );
    decal += chunck;
    wordsize = wordsize - chunck;
  }
  zmq_send( socket_port , "\0" , 1 , 0 );
}

char * recevoir( void * socket_port , char * message )
{
  int64_t more = 0x1;
  size_t more_size = sizeof more;
  zmq_recv( socket_port , message , SERVER_ID_CHUNK , ZMQ_NOBLOCK );
  if ( message == NULL)
  {
    return NULL;
  }
  strcat( message , " " );
  while ( more > 0 )
  {
    char * buffer = calloc( SERVER_BUFFER_CHUNK , sizeof( char ));
    zmq_recv( socket_port , buffer , SERVER_BUFFER_CHUNK , ZMQ_NOBLOCK );
    strcat( message , buffer );
    zmq_getsockopt( socket_port , ZMQ_RCVMORE , &more , &more_size );
    free( buffer );
  }
  if ( strlen( message ) == 0 )
  {
    return NULL;
  }
  return message;
}


pthread_t timer_th;

void * game_timer()
{
  timer_gen_grid = 0;
  timer_time_score = 350;
  while ( timer_gen_grid != timer_time_score )
  {
    timer_time_score -= 1;
    sleep( 1 );
  }
  printf( "end game 1\n" );
  game_started = false;
  pthread_exit( 0 );

}

char * server_word_list( char ** word_list , unsigned int size_list )
{

  unsigned int lentgh = size_list * 28 + 6;
  char * this = calloc( lentgh , sizeof( char ));
  snprintf( this , lentgh , "WORD " );

  for ( unsigned int k = 0; k < size_list; ++ k )
  {
    snprintf( this + strlen( this ) , lentgh - strlen( this ) , "%s " , word_list[ k ] );
  }
  return this;
}

char * server_grid_list( char ** grid_list , unsigned int size_list_widt , unsigned int size_list_heigth )
{
  unsigned int size = size_list_heigth * size_list_widt + SERVER_BUFFER_CHUNK + 1;
  char * this = calloc( size , sizeof( char ));
  snprintf( this , size , "GRID %d %d " , size_list_widt , size_list_heigth );

  for ( unsigned int j = 0; j < size_list_widt; ++ j )
  {
    for ( unsigned int i = 0; i < size_list_heigth; ++ i )
    {
      snprintf( this + strlen( this ) , size - strlen( this ) , "%c" , grid_list[ j ][ i ] );
    }
  }
  return this;
}

void sig_handler( int signo )
{
  if ( signo == SIGINT || signo == SIGTERM )
  {

      for ( unsigned int j = 0; j < test -> Maxclient; ++ j )
      {
        if ( test -> list_client[ j ] == 1 && test -> list_client_data[ j ] != NULL)
        {
          printf("%s \n",test -> list_client_data[ j ] -> id);
          envoyer( server -> socket_port2 , "LEAVE@CLIENT" , test -> list_client_data[ j ] -> id );
        }
      }
    printf( "Server_offline\n" );
    sleep(10);
    exit(EXIT_FAILURE);
  }
}



bool game = true;
int main( void )
{

    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);


  test = server_create_list( 10 );
  server = open_server_sockets();


  while ( game == true )
  {

    Grid * server_grid;

    char ** dico = create_dictionary( "./dico/dictionary.dic" );

    server_grid = filling( dico , 5 , 5 , 1 );

    display_grid_grid( server_grid );
    display_grid_words( server_grid );
    char * word_list = server_word_list( server_grid -> list , server_grid -> inlist );
    char * grid_list = server_grid_list( server_grid -> tab , server_grid -> width , server_grid -> height );

    unsigned int * word_find = calloc( server_grid -> inlist , sizeof( unsigned int * ));
    unsigned int number_word_find = 0;
    gird_generated = true;
    if ( pthread_create( &timer_th , NULL , game_timer , NULL) == - 1 )
    {
      printf( "thread : erreur création\n" );
    }
    game_started = true;
     while ( 1 )
    {
      if ( game_started == false )
      {
        break;
      }

      char * retour = calloc( 500 , sizeof( char ));

      retour = recevoir( server -> socket_port1 , retour );
      if ( retour != NULL)
      {
        char * buffer_retour = retour;
        char * tok;
        char * id;
        char * command;
        id = strsep( &buffer_retour , " " );
        command = strsep( &buffer_retour , " " );
        tok = strsep( &buffer_retour , " " );
        if ( id != NULL && command != NULL && tok != NULL)
        {
          if (( strcmp( "JOIN" , command )) == 0 )
          {
            Client_Data * buffer = server_create_client( tok , id );
            unsigned int flag_add_client = server_list_add_client( test , buffer );
            if ( flag_add_client == 0 || flag_add_client == 2 )
            {
              envoyer( server -> socket_port2 , grid_list , id );
              envoyer( server -> socket_port2 , word_list , id );

              debug_list_client_print( test );
            }
          }
          else if (( strcmp( "FOUND" , command )) == 0 )
          {

            char * mot = tok;
            char * buffer_x = strsep( &buffer_retour , " " );
            char * buffer_y = strsep( &buffer_retour , " " );
            char * buffer_x1 = strsep( &buffer_retour , " " );
            char * buffer_y1 = strsep( &buffer_retour , " " );

            if ( buffer_x != NULL && buffer_x1 != NULL && buffer_y != NULL && buffer_y1 != NULL && mot != NULL)
            {
              unsigned int x = atoi( buffer_x );

              unsigned int y = atoi( buffer_y );

              unsigned int x1 = atoi( buffer_x1 );

              unsigned int y1 = atoi( buffer_y1 );

              if (x < server_grid -> width && x1 < server_grid -> width && y < server_grid -> height && y1 < server_grid -> height )
              {
                if (verif_mot( mot , server_grid -> tab , x , y , x1 , y1 ))
                {

                  for ( unsigned int i = 0; i < server_grid -> inlist; ++ i )
                  {
                    if ( strcmp( server_grid -> list[ i ] , mot ) == 0 && word_find[ i ] == 0 )
                    {
                      server_list_client_add_word( test , id , 1 );
                      server_list_client_add_score( test , id , timer_time_score );
                      debug_list_client_print( test );
                      word_find[ i ] = 1;
                      number_word_find += 1;
                      if ( number_word_find == server_grid -> inlist )
                      {
                        unsigned int size = SERVER_BUFFER_CHUNK * test -> length;
                        char * sender = calloc( size , sizeof( char ));
                        unsigned int counter_client = 0;
                        for ( unsigned int j = 0; j < test -> Maxclient; ++ j )
                        {
                          if ( counter_client == test -> length )
                          {
                            break;
                          }
                          if ( test -> list_client[ i ] == 1 && test -> list_client_data[ i ] != NULL)
                          {
                            snprintf( sender + strlen( sender ) , size - strlen( sender ) , "%s %s Score:%d Mot:%d \n" , test -> list_client_data[ j ] -> name , test -> list_client_data[ j ] -> id , test -> list_client_data[ j ] -> score , test -> list_client_data[ j ] -> word_find );
                            counter_client ++;
                          }
                        }
                        printf( "->%s\n" , sender );
                        for ( unsigned int j = 0; j < test -> Maxclient; ++ j )
                        {
                          if ( test -> list_client[ j ] == 1 && test -> list_client_data[ j ] != NULL)
                          {
                            envoyer( server -> socket_port2 , "SCORE" , test -> list_client_data[ j ] -> id );
                            envoyer( server -> socket_port2 , sender , test -> list_client_data[ j ] -> id );
                            server_list_rem_client_id( test , test -> list_client_data[ j ] -> id );
                          }
                        }
                        free( sender );
                        for ( unsigned int j = 0; j < test -> Maxclient; ++ j )
                        {
                          if ( test -> list_client[ j ] == 1 && test -> list_client_data[ j ] != NULL)
                          {
                            server_list_rem_client_id( test , test -> list_client_data[ j ] -> id );
                          }
                        }
                        game_started = false;
                      }
                    }
                  }
                }
              }
            }
          }
        }
        else if ( id != NULL && command != NULL && tok == NULL)
        {
          if (( strcmp( "LEAVE" , command )) == 0 )
          {
            server_list_rem_client_id( test , id );
            debug_list_client_print( test );
          }
        }
        free( retour );
      }
      sleep( 0.0001 );
    }

    grid_destroy( server_grid );
    destroy_dictionary( dico );
    free( grid_list );
    free( word_list );
    for ( unsigned int j = 0; j < test -> Maxclient; ++ j )
    {
      if ( test -> list_client[ j ] == 1 && test -> list_client_data[ j ] != NULL)
      {
        envoyer( server -> socket_port2 , "LEAVE@CLIENT" , test -> list_client_data[ j ] -> id );
      }
    }
    for ( unsigned int j = 0; j < test -> Maxclient; ++ j )
    {
      if ( test -> list_client[ j ] == 1 && test -> list_client_data[ j ] != NULL)
      {
        server_list_rem_client_id( test , test -> list_client_data[ j ] -> id );
      }
    }

  }
  close_server_sockets(server);
  return 0;
}