

#ifndef _CLIENT_TEXTE1_H_H
#define _CLIENT_TEXTE1_H_H

#include <czmq.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>
#include <signal.h>
#include <pthread.h>


#define CLIENT_PORT1 "8000"
#define CLIENT_PORT2 "8001"
#define CLIENT_ADRESSE "127.0.0.1"

unsigned int client_time_out = 5000;
unsigned int client_id_size = 15;
unsigned int client_name_size = 20;
unsigned int client_calloc_size = 6260000;
unsigned int client_calloc_buffer =64;

/**
 *
 */
typedef struct _socket_client
{
  void * socket_contex;
  void * socket_port1;
  void * socket_port2;
  int timeout;
} Socket_client;

/**
 *
 */
typedef struct _client_data{
  Socket_client * socket;
  char * id;
  char * name;
}Client_data;

/**
 *
 * @param id
 * @return
 */
Socket_client * open_client_sockets(char * id);

/**
 *
 * @param socket_client
 */
void  close_client_socket(Socket_client * socket_client);

/**
 *
 * @param id
 * @param name
 * @return
 */
Client_data * create_client_data(char * id , char * name);

/**
 *
 * @param client_data
 */
void destroy_client_data(Client_data * client_data);

#endif //_CLIENT_TEXTE1_H_H
