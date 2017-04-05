/*
** force_brute.h for  in /Utilisateurs/qrouanet/Rouanet_Pouvreau_Foissac_EDC2016/source/force_brute
** 
** Made by Rouanet Quentin
** Login   <qrouanet@etudiant.univ-lr.fr>
** 
** Started on  Wed Nov 16 08:55:45 2016 Rouanet Quentin
** Last update Fri Dec  9 14:32:41 2016 Rouanet Quentin
*/

#ifndef FORCE_BRUTE_H__
# define FORCE_BRUTE_H__

#include "../construction.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * In case of occurance between the target box and the first character of a word the function check_word is called which is responsible for checking in the 8 possible directions.
 * @param word
 * @param x
 * @param y
 * @param ori
 * @param id
 * @return char*
 */
char *format_msg(char *word, int x, int y, int ori, char *id);

/**
 * This function returns a char* corresponding to a message formatted to correspond to a sending for the server or in the case where there is no longer any possible word it returns NULL
 * If the format_msg function returns a formatted message containing the required information, it basically returns a message ready to be sent to the server.
 * @param map
 * @param word
 * @param id
 * @return char*
 */
char *force_brute(char **map, char **word, char *id, int xmax, int ymax);

/**
 * This function looks for each box of each lign of the grid if the content character corresponds with a word of the word list. The location on the grid is maintained between calls of the function by two static variables
 * @param map
 * @param i
 * @param y
 * @param word
 * @return int
 */
int check_word(char **map, int i, int y, char *word, int xmax, int ymax);

#endif /* !FORCE_BRUTE_H__ */
