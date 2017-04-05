//
// Created by nfoissac on 18/11/16.
//

#ifndef _DICO_H
#define _DICO_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned int max_size_random_ln;

/**
 * Deallocates the char** pointed by dictionary
 * @param dictionary
 */
void destroy_dictionary( char ** dictionary );

/**
 * Allocates a new dictionary (char**) and build it by copying words from a text file,
 * location is the string pointed to by path
 * @param path
 * @return char**
 */
char ** create_dictionary( char * path );

/**
 * Returns a string randomly picked out from the char** pointed to by dictionary
 * @param dictionary
 * @return char*
 */
char * random_word_dictionary( char ** dictionary );

/**
 * Returns a char** of the number of string passed in parameters randomly picked out from the char** pointed to by dictionary
 * @param dictionary
 * @param number
 * @return char**
 */
char ** random_n_word_dictionary( char ** dictionary , unsigned int number );

/**
 * Returns a char** of the number of string passed in parameters randomly picked out from the char** pointed to by dictionary.
 * All the chosen strings have a length between min and max passed in parameters.
 * @param dictionary
 * @param number
 * @param min
 * @param max
 * @return char**
 */
char ** random_ln_word_dictionary( char ** dictionary , unsigned int number , unsigned int min , unsigned int max );

#endif //_DICO_H
