#ifndef CONSTRUCTION_H__
# define CONSTRUCTION_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/param.h>
#include "dico.h"

/**
 * The structure Grid is used as a 2D grid of char you can use to implement games like a wordsearch puzzle.
 * It contains moreover the grid 2 int which are the dimensions of the grid
 * and an third int for the number of words in the grid, a second char** is the list of the words present in the grid.
 */
typedef struct s_Grid
  {
    unsigned int width;
    unsigned int height;
    unsigned int inlist;
    char** tab;
    char** list;
  } Grid;

/**
 * Initialisation of structure Grid, allocates needed memory to add words in grid and list,
 * initialize other attributes with values passed in parameters
 * @param width
 * @param height
 * @param nbWords
 * @return Grid*
 */
Grid* grid_init(const int width, const int height, const int nbWords);

/**
 * Destroyer of structure Grid, deallocates memory previously allocated in the structure pointed to by g
 * @param g
 */
void grid_destroy(Grid* g);

/**
 * Add the string pointed to by str in the list of the structure Grid pointed to by g
 * and call function reverse(char* str) if it's previously added reversed in the grid
 * @param g
 * @param str
 * @param revstr
 */
void list_add(Grid* g, char* str, int revstr);

/**
 * In the grid of the structure Grid pointed to by g,
 * add the char passed in parameters at the coordinates also passed in parameters
 * @param g
 * @param x
 * @param y
 * @param c
 */
void add_char(Grid* g, unsigned int x, unsigned int y, char c);

/**
 * In the grid of the structure Grid pointed to by g,
 * add the string pointed to by str horizontally starting at the coordinates also passed in parameters.
 * Call function list_add(Grid* g, char* str, int revstr),
 * int revstr inform if the word is previously reversed (revstr = 1)
 * @param x
 * @param y
 * @param str
 * @param revstr
 */
void add_word_horizontal(Grid* g, unsigned int x, unsigned int y, char* str, int revstr);

/**
 * In the grid of the structure Grid pointed to by g,
 * add the string pointed to by str vertically starting at the coordinates also passed in parameters.
 * Call function list_add(Grid* g, char* str, int revstr),
 * int revstr inform if the word is previously reversed (revstr = 1)
 * @param x
 * @param y
 * @param str
 * @param revstr
 */
void add_word_vertical(Grid* g, unsigned int x, unsigned int y, char* str, int revstr);

/**
 * In the grid of the structure Grid pointed to by g,
 * add the string pointed to by str diagonally from the top left to the bottom right,
 * starting at the coordinates also passed in parameters.
 * Call function list_add(Grid* g, char* str, int revstr),
 * int revstr inform if the word is previously reversed (revstr = 1)
 * @param g
 * @param x
 * @param y
 * @param str
 * @param revstr
 */
void add_word_diagonal_tlbr(Grid* g, unsigned int x, unsigned int y, char* str, int revstr);

/**
 * In the grid of the structure Grid pointed to by g,
 * add the string pointed to by str diagonally from the top right to the bottom left,
 * starting at the coordinates also passed in parameters.
 * Call function list_add(Grid* g, char* str, int revstr),
 * int revstr inform if the word is previously reversed (revstr = 1)
 * @param g
 * @param x
 * @param y
 * @param str
 * @param revstr
 */
void add_word_diagonal_trbl(Grid* g, unsigned int x, unsigned int y, char* str, int revstr);

/**
 * Reverses the string pointed to by str
 * @param str
 * @return char*
 */
char* reverse(char* str);

/**
 * Checks if the string pointed to by str crosses an other string in the grid of the structure Grid pointed to by g.
 * It returns the char at the point of collision between a string previously added and the new string
 * or '0' if there is no crossing
 * @param g
 * @param str
 * @param x
 * @param y
 * @param orientation
 * @return char
 */
char cross(Grid* g, const char* str, int x, int y, unsigned const int orientation);

/**
 * Fills a new grid with strings from the grid of strings pointed to by dico.
 * The new structure Grid is created by calling function grid_init(const int width, const int height, const int nbWords).
 * Choose random coordinates and orientation for each new string added in the grid.
 * Call the function reverse(char* str) if the random test return 0.
 * Call the function cross(Grid* g, const char* str, int x, int y, unsigned const int orientation) for
 * the checklist which determine if a string can be added.
 * @param dico
 * @param width
 * @param height
 * @param nbMots
 * @return Grid*
 */
Grid* filling(char** dico, const unsigned int width, const unsigned int height, unsigned int nbMots);

/**
 * Display char by char the grid and string by string the list of the structure Grid pointed to by g
 * @param g
 */
void display_grid(Grid* g);

/**
 * Display char by char the grid of the structure Grid pointed to by g
 * @param g
 */
void display_grid_grid(Grid* g);

/**
 * Display string by string the list of the structure Grid pointed to by g
 * @param g
 */
void display_grid_words(Grid* g);

#endif /* !CONSTRUCTION_H__ */
