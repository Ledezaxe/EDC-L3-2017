//
// Created by nfoissac on 30/11/16.
//

#ifndef _SERVER_CLIENT_DATA_H
#define _SERVER_CLIENT_DATA_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 *
 */
typedef struct _Client_Data
{
  char * name;
  char * id;
  unsigned int score;
  unsigned int word_find;
} Client_Data;

/**
 *
 */
typedef struct _List_Client
{
  Client_Data ** list_client_data;
  unsigned int * list_client;
  unsigned int Maxclient;
  unsigned int length;
} List_Client;

/**
 *
 * @param name
 * @param id
 * @return
 */
Client_Data * server_create_client( char * name , char * id );

/**
 *
 * @return
 */
Client_Data * server_create_void( void );

/**
 *
 * @param client_limit
 * @return
 */
List_Client * server_create_list( unsigned int client_limit );

/**
 *
 * @param list_client
 * @param client_data
 * @return
 */
int server_list_add_client( List_Client * list_client , Client_Data * client_data );

/**
 *
 * @param list_client
 * @param id
 * @param score
 * @return
 */
int server_list_client_set_score( List_Client * list_client , char * id , unsigned int score );

/**
 *
 * @param list_client
 * @param id
 * @param word_find
 * @return
 */
int server_list_client_set_word( List_Client * list_client , char * id , unsigned int word_find );

/**
 *
 * @param list_client
 * @param id
 * @param score
 * @return
 */
int server_list_client_add_score( List_Client * list_client , char * id , unsigned int score );

/**
 *
 * @param list_client
 * @param id
 * @param word_find
 * @return
 */
int server_list_client_add_word( List_Client * list_client , char * id , unsigned int word_find );

/**
 *
 * @param list_client
 * @param id
 * @return
 */
int server_list_client_reset_score( List_Client * list_client , char * id );

/**
 *
 * @param list_client
 * @param id
 * @return
 */
int server_list_client_reset_word( List_Client * list_client , char * id );

/**
 *
 * @param list_client
 * @param id
 * @return
 */
int server_list_client_reset( List_Client * list_client , char * id );

/**
 *
 * @param list_client
 * @param client_data
 * @return
 */
int server_list_rem_client( List_Client * list_client , Client_Data * client_data );

/**
 *
 * @param list_client
 * @param id
 * @return
 */
int server_list_rem_client_id( List_Client * list_client , char * id );

/**
 *
 * @param client_data
 */
void server_client_reset_score( Client_Data * client_data );

/**
 *
 * @param client_data
 */
void server_client_reset_word( Client_Data * client_data );

/**
 *
 * @param client_data
 * @param score
 */
void server_client_set_score( Client_Data * client_data , unsigned int score );

/**
 *
 * @param client_data
 * @param word_find
 */
void server_client_set_word( Client_Data * client_data , unsigned int word_find );

/**
 *
 * @param client
 */
void destroy_client( Client_Data * client );

/**
 *
 * @param list_client
 */
void destroy_list_client( List_Client * list_client );

/**
 *
 * @param list_client
 */
void debug_list_client_print( List_Client * list_client );

#endif //MOT_MELÉE_SERVER_CLIENT_DATA_H
