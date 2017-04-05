#include "construction.h"

Grid* grid_init(const int width, const int height, const int nbWords)
{
  Grid* g = malloc(sizeof(Grid));

  g->width = width;
  g->height = height;
  g->inlist = 0;

  int i;

  g->tab = malloc(width * sizeof(char*));
  g->list = calloc(nbWords,sizeof(char*));

  for (i = 0 ; i < nbWords ; i++)
    g->list[i] = malloc(27 * sizeof(char));

  for (i = 0 ; i < width ; i++)
    g->tab[i] = malloc(height * sizeof(char));

  for (i = 0 ; i < width ; i++)
    memset(g->tab[i], '0', height);

  return g;
}

void grid_destroy(Grid* g)
{
  int i = g->width;

  while (i != 0)
    {
      i--;
      free(g->tab[i]);
    }

  i = g->inlist;

  while (i != 0)
    {
      i--;
      free(g->list[i]);
    }

  free(g->list);
  free(g->tab);
  free(g);
}

void list_add(Grid* g, char* str, int revstr)
{
  if (revstr == 0)
    {
      str = reverse(str);
      int sizeBuffer = strlen(str);
      memcpy(g->list[g->inlist], str, sizeBuffer);
      g->list[g->inlist][sizeBuffer]='\0';
      free(str);
    }
  else
    {
      int sizeBuffer = strlen(str);
      memcpy(g->list[g->inlist], str, sizeBuffer);
      g->list[g->inlist][sizeBuffer]='\0';
    }

  g->inlist++;
}

void add_char(Grid* g, unsigned int x, unsigned int y, char c)
{
  g->tab[x][y] = c;
}

void add_word_horizontal(Grid* g, unsigned int x, unsigned int y, char* str, int revstr)
{
  unsigned int i;
  list_add(g, str, revstr);

  for (i = 0 ; i < strlen(str) ; i++)
    {
      add_char(g, x, y, str[i]);
      x++;
    }
}

void add_word_vertical(Grid* g, unsigned int x, unsigned int y, char* str, int revstr)
{
  unsigned int i;
  list_add(g, str, revstr);

  for (i = 0 ; i < strlen(str) ; i++)
    {
      add_char(g, x, y, str[i]);
      y++;
    }
}

void add_word_diagonal_tlbr(Grid* g, unsigned int x, unsigned int y, char* str, int revstr)
{
  unsigned int i;
  list_add(g, str, revstr);

  for (i = 0 ; i < strlen(str) ; i++)
    {
      add_char(g, x, y, str[i]);
      x++;
      y++;
    }
}

void add_word_diagonal_trbl(Grid* g, unsigned int x, unsigned int y, char* str, int revstr)
{
  unsigned int i;
  list_add(g, str, revstr);

  for (i = 0 ; i < strlen(str) ; i++)
    {
      add_char(g, x, y, str[i]);
      x--;
      y++;
    }
}

char* reverse(char *str)
{
  char* ret = malloc(sizeof(char) * (strlen(str) + 1));
  int i;
  int j = 0;

  i = strlen(str) - 1;

  while (i)
      ret[j++] = str[i--];

  ret[j++] = str[i];
  ret[j] = '\0';

  return ret;
}

char cross(Grid* g, const char* str, int x, int y, const unsigned int orientation)
{
  unsigned int i = 0;
  unsigned int j;

  while(i < strlen(str) && x < (int)g->width && x >= 0 && y < (int)g->height && y >= 0)
    {
      for (j = 0 ; j < strlen(str) ; j++)
	{
	  //On corrige seulement si la case est déjà occupée par un carctère différent
	  //de celui du mot se situant (virtuellement) sur cette case
	  if (g->tab[x][y] != '0' && g->tab[x][y] != str[j])
	    return g->tab[x][y];
	}

      if (orientation == 0)
	{
	  x++;
	}
      else if (orientation == 1)
	{
	  y++;
	}
      else if (orientation == 2)
	{
	  x++;
	  y++;
	}
      else
	{
	  x--;
	  y++;
	}
    }

  return '0';
}

Grid* filling(char** tab, const unsigned int width, const unsigned int height, unsigned int nbWords)
{
  Grid* g = grid_init(width, height, nbWords);
  unsigned int i = 0;
  unsigned int cpt = 0;
  int cX, cY, rnd;

  char** dico = random_ln_word_dictionary(tab, nbWords, 3, MIN(height, width));

  //Tant qu'on a pas le nombre de mots requis
  while (cpt < nbWords && g->inlist < nbWords)
    {
      cpt++;

      char* str = dico[rand()%nbWords];

      //On tire les coordonnées d'une case de départ au hasard
      cX = rand()%width;
      cY = rand()%height;

      //On tire au hasard l'orientation et l'inversion du mot
      rnd = rand()%2;
      if (rnd == 0)
	  str = reverse(str);

      unsigned int orientation = rand()%4;
      //0 = horizontale ; 1 = verticale ; 2 = diagonale(haut gauche, bas droite)
      //3 = diagonale(haut droite, bas gauche)

      //On vérifie si le mot passe sur des cases déjà occupées
      //qui ne correspondent pas aux lettres du mot destinées à ces cases
      char point = cross(g, str, cX, cY, orientation);

      //Si oui on ajuste pour que la dernière lettre du mot commune à
      //celle d'une case occupée soit alignée avec celle-ci
      if (point != '0' && strchr(str, point) != NULL)
	{
	  i = strlen(str) - 1;

	  while (str[i] != point)
	    {
	      i--;
	    }

	  if (orientation == 0)
	    {
	      cX += i;
	    }
	  else if (orientation == 1)
	    {
	      cY += i;
	    }
	  else if (orientation == 2)
	    {
	      cX += i;
	      cY += i;
	    }
	  else
	    {
	      cX -= i;
	      cY += i;
	    }

	  //Si la correction permet de placer le mot on le place
	  //sinon on abandonne et on passe à un autre mot
	  point = cross(g, str, cX, cY, orientation);
	  if (point == '0')
	    {
	      //On vérifie que le mot ne dépasse pas selon son orientation
	      if (cX + strlen(str) < width && cX - (int)strlen(str) >= 0 && cY + strlen(str) < height && cY - (int)strlen(str) >= 0)
		{
		  if (orientation == 0)
		    {
		      add_word_horizontal(g, cX, cY, str, rnd);
		    }
		  else if (orientation == 1)
		    {
		      add_word_vertical(g, cX, cY, str, rnd);
		    }
		  else if (orientation == 2)
		    {
		      add_word_diagonal_tlbr(g, cX, cY, str, rnd);
		    }
		  else
		    {
		      add_word_diagonal_trbl(g, cX, cY, str, rnd);
		    }

		  cpt = 0;
		}
	    }
	}
      else  //Si le mot ne croise pas de case occupée on arrive ici
	{
	  //On vérifie que le mot ne dépasse pas sinon on décale d'une case jusqu'à ce qu'il rentre
	  if (orientation > 0)
	    {
	      while (cY + strlen(str) > height)
		{
		  cY--;
		}
	    }

	  if (orientation == 0 || orientation == 2)
	    {
	      while (strlen(str) + cX > width)
		{
		  cX--;
		}
	    }

	  if (orientation == 3)
	    {
	      while (cX - (int)strlen(str) < -1)
		{
		  cX++;
		}
	    }

	  //On vérifie si le mot passe sur des cases déjà occupées
	  //Si oui on essaie une dernière correction
	  char point = cross(g, str, cX, cY, orientation);
	  if (point != '0' && strchr(str, point) != NULL)
	    {
	      i = strlen(str) - 1;

	      while (str[i] != point)
		{
		  i--;
		}

	      if (orientation == 0)
		{
		  cX += i;
		}
	      else if (orientation == 1)
		{
		  cY += i;
		}
	      else if (orientation == 2)
		{
		  cX += i;
		  cY += i;
		}
	      else
		{
		  cX -= i;
		  cY += i;
		}

	      //Si la correction permet de placer le mot on le place
	      //sinon on abandonne et on passe à un autre mot
	      point = cross(g, str, cX, cY, orientation);
	      if (point == '0')  //On vérifie que le mot ne passe pas sur des cases déjà occupées
		{
		  //On revérifie que le mot ne dépasse pas selon son orientation
		  if (cX + strlen(str) < width && cX - (int)strlen(str) >= 0 && cY + strlen(str) < height && cY - (int)strlen(str) >= 0)
		    {
		      if (orientation == 0)
			{
			  add_word_horizontal(g, cX, cY, str, rnd);
			}
		      else if (orientation == 1)
			{
			  add_word_vertical(g, cX, cY, str, rnd);
			}
		      else if (orientation == 2)
			{
			  add_word_diagonal_tlbr(g, cX, cY, str, rnd);
			}
		      else
			{
			  add_word_diagonal_trbl(g, cX, cY, str, rnd);
			}

		      cpt = 0;
		    }
		}
	    }
	  else if(point == '0')  //Si le mot ne croise aucune case occupée
	    {
	      if (orientation == 0)
		{
		  add_word_horizontal(g, cX, cY, str, rnd);
		}
	      else if (orientation == 1)
		{
		  add_word_vertical(g, cX, cY, str, rnd);
		}
	      else if (orientation == 2)
		{
		  add_word_diagonal_tlbr(g, cX, cY, str, rnd);
		}
	      else
		{
		  add_word_diagonal_trbl(g, cX, cY, str, rnd);
		}

	      cpt = 0;
	    }
	}

      if (rnd == 0)
	{
	  free(str);
	}
    }

  unsigned int j;
  char* t = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  for (i = 0 ; i < width ; i++)
    {
      for (j = 0 ; j < height ; j++)
	{
	  if (g->tab[i][j] == '0')
	    {
	      add_char(g, i, j, t[rand() % strlen(t)]);
	    }
	}
    }

  /*for (i = 0; i < height; i++)
  {
    g->tab[i][width] ='\0';
    }*/


  char** buffer_list = calloc(nbWords, sizeof(char*));
    i = 0;

  while (i < g->inlist)
    {
      int sizeBuffer = strlen(g->list[i]);
      buffer_list[i] = malloc(strlen(g->list[i]) * sizeof(char)+1);
      memcpy( buffer_list[i], g->list[i], sizeBuffer );
      buffer_list[i][sizeBuffer]='\0';
      i++;
    }

  for (i = 0 ; i < nbWords ; i++)
    {
      free(g->list[i]);
    }

  free(g->list);
  g->list = buffer_list;
  destroy_dictionary(dico);

  return g;
}

void display_grid(Grid* g)
{
  unsigned int i, j;
  for (i = 0 ; i < g->height ; i++)
    {
      for (j = 0 ; j < g->width ; j++)
	{
	  printf("%c", g->tab[j][i]);
	}
      printf("\n");
    }
  printf("\n\n");
  for (i = 0 ; i < g->inlist ; i++)
    {
      printf("%s \n",g->list[i]);
    }

  printf("\n\n");
}

void display_grid_grid(Grid* g)
{
  unsigned int i, j;
  for (i = 0 ; i < g->height ; i++)
  {
    for (j = 0 ; j < g->width ; j++)
    {
      printf("%c", g->tab[j][i]);
    }
    printf("\n");
  }
  printf("\n");
}

void display_grid_words(Grid* g)
{
  unsigned int i;
  for (i = 0 ; i < g->inlist ; i++)
  {
    printf("%s\n",g->list[i]);
  }
  printf("\n");
}
