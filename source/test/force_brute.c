/*
** force_brute.c for  in /Utilisateurs/qrouanet/Rouanet_Pouvreau_Foissac_EDC2016/source/force_brute
** 
** Made by Rouanet Quentin
** Login   <qrouanet@etudiant.univ-lr.fr>
** 
** Started on  Wed Nov 16 09:00:31 2016 Rouanet Quentin
** Last update Fri Dec  9 11:49:53 2016 Rouanet Quentin
*/

#include "force_brute.h"

/* orientation X vers num

   4  3  2

   5  X  1

   6  7  8

 */

// fonction pavé césar, c'est un algo long et pas opti-z-oinion donc ça passe

int check_word(char **map, int x, int y, char *word, int xmax, int ymax)
{
  int i;
  int xi;
  int yi;

  if (x >= (int)strlen(word)) // orientation 4 3 2
    {
      if (y >= (int)strlen(word)) // orientation 4
	{
	  i = 0;
	  xi = x;
	  yi = y;
	  while (yi >= 0 && xi >= 0 && word[i] == map[xi][yi] && word[i] != '\0')
	    {
	      i++;
	      xi--;
	      yi--;
	    }
	  if (word[i] == '\0')
	    return (4);
	}
      // orientation 3
      i = 0;
      xi = x;
      while (xi >= 0 && word[i] == map[xi][y] && word[i] != '\0')
	{
	  i++;
	  xi--;
	}
      if (word[i] == '\0')
	return (3);

      // orientation 2
      i = 0;
      xi = x;
      yi = y;
      while (yi < ymax && xi >= 0 && word[i] == map[xi][yi] && word[i] != '\0')
	{
	  i++;
	  xi--;
	  yi++;
	}
      if (word[i] == '\0')
	return (2);
    }
  // orienatation 1
  i = 0;
  yi = y;
  while (yi < ymax && word[i] == map[x][yi] && word[i] != '\0')
    {
      i++;
      yi++;
    }
  if (word[i] == '\0')
    return (1);
  if (y >= (int)strlen(word)) // orientation 5 6
    {
      // orientation 5
      i = 0;
      yi = y;
      while (yi >= 0 && word[i] == map[x][yi] && word[i] != '\0')
	{
	  i++;
	  yi--;
	}
      if (word[i] == '\0')
	return (5);

      // orientation 6
      i = 0;
      xi = x;
      yi = y;
      while (yi >= 0 && xi < xmax && map[xi] != NULL && word[i] == map[xi][yi] && word[i] != '\0')
	{
	  i++;
	  xi++;
	  yi--;
	}
      if (word[i] == '\0')
	return (6);
    }

  // orientation 7
  i = 0;
  xi = x;
  while (xi < xmax && map[xi] != NULL && word[i] == map[xi][y] && word[i] != '\0')
    {
      i++;
      xi++;
    }
  if (word[i] == '\0')
    return (7);

  // orientation 8
  i = 0;
  xi = x;
  yi = y;
  while (yi < ymax && xi < xmax && map[xi] != NULL && word[i] == map[xi][yi] && word[i] != '\0')
    {
      i++;
      xi++;
      yi++;
    }
  if (word[i] == '\0')
    return (8);
  return (0);
}

/* orientation X vers num

   4  3  2

   5  X  1

   6  7  8

 */


char *format_msg(char *word, int x, int y, int ori, char *id)
{
  char *ret;
  int size;
  int xf = x;
  char s_xf[10];
  int yf = y;
  char s_yf[10];
  char s_x[10];
  char s_y[10];

  if (ori == 6 || ori == 7 || ori == 8)
    xf += strlen(word) - 1;
  if (ori == 2 || ori == 3 || ori == 4)
    xf -= strlen(word) - 1;
  if (ori == 2 || ori == 1 || ori == 8)
    yf += strlen(word) - 1;
  if (ori == 4 || ori == 5 || ori == 6)
    yf -= strlen(word) - 1;

  // "FOUND 'id' 'word' 'x' 'y' 'xf' 'yf'\0"

  size = strlen(id) + strlen(word) + sprintf(s_xf, "%d", xf) + sprintf(s_yf, "%d", yf) + sprintf(s_x, "%d", x) + sprintf(s_y, "%d", y) + 5 + 6 + 1 + 10;

  ret = calloc(size, sizeof(char));

  ret = strcat(ret, "FOUND ");
  ret = strcat(ret, id);
  ret = strcat(ret, " ");
  ret = strcat(ret, word);
  ret = strcat(ret, " ");
  ret = strcat(ret, s_x);
  ret = strcat(ret, " ");
  ret = strcat(ret, s_y);
  ret = strcat(ret, " ");
  ret = strcat(ret, s_xf);
  ret = strcat(ret, " ");
  ret = strcat(ret, s_yf);
  ret = strcat(ret, "\0");

  return (ret);
}

char *force_brute(char **map, char **words, char *id, int xmax, int ymax)
{
  static int x = 0; // init seulement
  static int y = 0;
  int i = 0;
  int found = 0; // mot trouve -> 1 ou plus

  while (!found && x < xmax)
    {
      while (!found && y < ymax)
	{
	  while (!found && words[i] != NULL)
	    {
		if (words[i][0] == map[x][y])
		{
		  found = check_word(map, x, y, words[i], xmax, ymax);
		  if (found != 0)
		    return (format_msg(words[i], x, y++, found, id));
		}
	      i++;
	    }
	  i = 0;
	  y++;
	}
      y = 0;
      if (!found)
	x++;
    }
  return (NULL);
}
