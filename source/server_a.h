/**
 * @file server_textuel_beta.h
 * @brief Programme de tests.
 * @authors Nicola Foissac <nicola.foissac@etudiant.univ-lr.fr>
 * @authors Quentin Rouanet <quentin.rouanet@etudiant.univ-lr.fr>,
 * @authors Quentin Pouvreau <quentin.pouvreau@etudiant.univ-lr.fr>
 * @version 0.1
 * @date 11 septembre 2007
 *
 * Programme de test pour l'objet de gestion des chaînes de caractères Str_t.
 *
 */

#ifndef SOURCE_SERVER_H
#define SOURCE_SERVER_H

#include <czmq.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <pthread.h>
#include "construction.h"
#include "verif_mot.h"
#include "server_client_data.h"
#include "dico.h"
/**
 * @brief Macro de definition du port 1 de comunitation du server.
 */
#define SERVER_PORT1 "8000"
/**
 * @brief Macro de definition du port 1 de comunitation du server.
 */
#define SERVER_PORT2 "8001"
/**
 * @brief Macro de definition du port 1 de comunitation du server.
 */
#define SERVER_ADRESSE "127.0.0.1"
#define SERVER_ID_CHUNK 15
#define SERVER_BUFFER_CHUNK 64

bool gird_generated;
bool game_started;
bool game_wait_restart;
unsigned int timer_gen_grid;

typedef struct _Server_data
{
  unsigned int numberofgames;
  unsigned int numberofclient;
  unsigned int numberofword;
} Server_data;



/*

typedef struct _Server_Client_Data
{
  Server_data server_data;
  Client_Data ** client;
  unsigned int numberMaxclient;
  unsigned int numberofClient;
} Server_Client_Data;

*/
typedef struct _Socket_server
{
  void * socket_contex;
  void * socket_port1;
  void * socket_port2;
} Socket_server;


Socket_server * open_server_sockets();
void close_server_sockets( Socket_server * socketServer );



/**
 * @brief On peu voire la structure interne des donnée mais je pense qu'il faudrais certainememnt utiliser un liste qui qui peux se changer facilement example liste chainer.
 */


#endif //SOURCE_SERVER_H
