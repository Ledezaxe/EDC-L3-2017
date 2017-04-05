//
// Created by nfoissac on 30/11/16.
//

#include "server_client_data.h"


Client_Data * server_create_client( char * name , char * id )
{
  Client_Data * this = malloc( sizeof( Client_Data ));
  this -> id = malloc( sizeof( char * ) * strlen( id ) + 1 );
  memcpy( this -> id , id , strlen( id ) + 1 );
  this -> name = malloc( sizeof( char * ) * strlen( name ) + 1 );
  memcpy( this -> name , name , strlen( name ) + 1 );
  this -> score = 0;
  this -> word_find = 0;
  return this;
}

Client_Data * server_create_void( void )
{
  Client_Data * this = malloc( sizeof( char * ) * 2 + sizeof( unsigned int ) * 2 );
  this -> name = NULL;
  this -> id = NULL;
  this -> score = 0;
  this -> word_find = 0;
  return this;
}

void server_client_reset_score( Client_Data * client_data )
{
  client_data -> score = 0;
}

void server_client_reset_word( Client_Data * client_data )
{
  client_data -> word_find = 0;
}

void server_client_set_score( Client_Data * client_data , unsigned int score )
{
  client_data -> score = score;
}
void server_client_set_word( Client_Data * client_data , unsigned int word_find )
{
  client_data -> word_find = word_find;
}

void destroy_client( Client_Data * client )
{
  if ( client )
  {
    free( client -> name );
    free( client -> id );
  }
  free( client );
}

void destroy_list_client( List_Client * list_client )
{
  for ( unsigned int i = 0; i < list_client -> Maxclient; ++ i )
  {
    if ( list_client -> list_client_data[ i ] != NULL)
    {
      destroy_client( list_client -> list_client_data[ i ] );
    }
  }
  free( list_client -> list_client_data );
  free( list_client -> list_client );
  free( list_client );
}

List_Client * server_create_list( unsigned int client_limit )
{
  List_Client * this = malloc( sizeof( List_Client ));
  this -> Maxclient = client_limit;
  this -> list_client_data = malloc( sizeof( Client_Data * ) * this -> Maxclient );
  this -> list_client = calloc( this -> Maxclient , sizeof( int * ));
  for ( unsigned int i = 0; i < this -> Maxclient; i ++ )
  {
    this -> list_client_data[ i ] = server_create_void();
  }
  return this;
}

int server_list_add_client( List_Client * list_client , Client_Data * client_data )
{
  if ( list_client -> length < list_client -> Maxclient )
  {
    for ( unsigned int i = 0; i < list_client -> Maxclient; ++ i )
    {
      if(list_client -> list_client[ i ] == 1 && strcmp( list_client -> list_client_data[ i ] -> id , client_data -> id ) == 0)
        return 2;
    }
    for ( unsigned int i = 0; i < list_client -> Maxclient; ++ i )
    {
      if ( list_client -> list_client[ i ] == 0 && list_client -> list_client_data[ i ] != NULL)
      {
        destroy_client( list_client -> list_client_data[ i ] );
        list_client -> list_client_data[ i ] = client_data;
        list_client -> list_client[ i ] = 1;
        list_client -> length += 1;
        return 0;
      }
    }
  }
  return 1;
}

int server_list_rem_client( List_Client * list_client , Client_Data * client_data )
{
  if ( list_client -> length > 0 )
  {
    for ( unsigned int i = 0; i < list_client -> Maxclient; ++ i )
    {
      if ( list_client -> list_client[ i ] == 1 && strcmp( list_client -> list_client_data[ i ] -> id , client_data -> id ) == 0 )
      {
        destroy_client( list_client -> list_client_data[ i ] );
        list_client -> list_client_data[ i ] = server_create_void();
        list_client -> list_client[ i ] = 0;
        list_client -> length -= 1;
        return 0;
      }
    }
  }

  return 1;
}
int server_list_rem_client_id( List_Client * list_client , char * id )
{
  if ( list_client -> length > 0 )
  {
    for ( unsigned int i = 0; i < list_client -> Maxclient; ++ i )
    {
      if ( list_client -> list_client[ i ] == 1 && strcmp( list_client -> list_client_data[ i ] -> id , id ) == 0 )
      {
        destroy_client( list_client -> list_client_data[ i ] );
        list_client -> list_client_data[ i ] = server_create_void();
        list_client -> list_client[ i ] = 0;
        list_client -> length -= 1;
        return 0;
      }
    }
  }

  return 1;
}
int server_list_client_set_score( List_Client * list_client , char * id , unsigned int score )
{
  for ( unsigned int i = 0; i < list_client -> Maxclient; ++ i )
  {
    if ( list_client -> list_client[ i ] == 1 && strcmp( list_client -> list_client_data[ i ] -> id , id ) == 0 )
    {
      server_client_set_score( list_client -> list_client_data[ i ] , score );
      return 0;
    }
  }
  return 1;
}

int server_list_client_set_word( List_Client * list_client , char * id , unsigned int word_find )
{
  for ( unsigned int i = 0; i < list_client -> Maxclient; ++ i )
  {
    if ( list_client -> list_client[ i ] == 1 && strcmp( list_client -> list_client_data[ i ] -> id , id ) == 0 )
    {
      server_client_set_word( list_client -> list_client_data[ i ] , word_find );
      return 0;
    }
  }
  return 1;
}

int server_list_client_add_score( List_Client * list_client , char * id , unsigned int score )
{
  for ( unsigned int i = 0; i < list_client -> Maxclient; ++ i )
  {
    if ( list_client -> list_client[ i ] == 1 && strcmp( list_client -> list_client_data[ i ] -> id , id ) == 0 )
    {
      server_client_set_score( list_client -> list_client_data[ i ] , list_client -> list_client_data[ i ]->score+score );
      return 0;
    }
  }
  return 1;
}

int server_list_client_add_word( List_Client * list_client , char * id , unsigned int word_find )
{
  for ( unsigned int i = 0; i < list_client -> Maxclient; ++ i )
  {
    if ( list_client -> list_client[ i ] == 1 && strcmp( list_client -> list_client_data[ i ] -> id , id ) == 0 )
    {
      server_client_set_word( list_client -> list_client_data[ i ] , list_client -> list_client_data[ i ]->word_find+word_find );
      return 0;
    }
  }
  return 1;
}

int server_list_client_reset_score( List_Client * list_client , char * id )
{
  for ( unsigned int i = 0; i < list_client -> Maxclient; ++ i )
  {
    if ( list_client -> list_client[ i ] == 1 && strcmp( list_client -> list_client_data[ i ] -> id , id ) == 0 )
    {
      server_client_reset_score( list_client -> list_client_data[ i ] );
      return 0;
    }
  }
  return 1;
}

int server_list_client_reset_word( List_Client * list_client , char * id )
{
  for ( unsigned int i = 0; i < list_client -> Maxclient; ++ i )
  {
    if ( list_client -> list_client[ i ] == 1 && strcmp( list_client -> list_client_data[ i ] -> id , id ) == 0 )
    {
      server_client_reset_word( list_client -> list_client_data[ i ] );
      return 0;
    }
  }
  return 1;
}

int server_list_client_reset( List_Client * list_client , char * id )
{
  for ( unsigned int i = 0; i < list_client -> Maxclient; ++ i )
  {
    if ( list_client -> list_client[ i ] == 1 && strcmp( list_client -> list_client_data[ i ] -> id , id ) == 0 )
    {
      server_client_reset_word( list_client -> list_client_data[ i ] );
      server_client_reset_score( list_client -> list_client_data[ i ] );
      return 0;
    }
  }
  return 1;
}

void debug_list_client_print( List_Client * list_client )
{
  printf( "List client \n" );
  printf( "@%p\n" , ( void * ) &list_client );
  printf( "Max client :%d \n" , list_client -> Maxclient );
  for ( unsigned int i = 0; i < list_client -> Maxclient; ++ i )
  {
    if ( list_client -> list_client[ i ] == 1 && list_client -> list_client_data[ i ] != NULL)
    {
      printf( "[%d]@%p ->name :%s ,id :%s ,score :%d ,word find:%d \n" , i , ( void * ) &list_client -> list_client_data[ i ] , list_client -> list_client_data[ i ] -> name , list_client -> list_client_data[ i ] -> id , list_client -> list_client_data[ i ] -> score , list_client -> list_client_data[ i ] -> word_find );
    }
  }
}
