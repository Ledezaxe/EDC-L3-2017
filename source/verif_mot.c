/*
** verif_mot.c for  in /home/ledezaxe/etude_de_cas/Rouanet_Pouvreau_Foissac_EDC2016/source/algo
** 
** Made by ledezaxe
** Login   <quentin.rouanet@etudiant.univ-lr.fr>
** 
** Started on  Tue Oct 18 09:56:45 2016 Quentin Rouanet
** Last update Tue Oct 18 11:03:40 2016 Quentin Rouanet
*/

#include "verif_mot.h"

// grid est une globale contenant la grille
// definir si je verifie les coords ou si c'est fait avant


int verif_mot(char *word, char ** grid, int x1, int y1, int x2, int y2) // x1/y1 c'est la pos du debut du mot et x2/y2 celle de fin // renvoie 1 si vrai 0 si faux
{
  // 8 directions possibles
  if (x1 > x2) // vers le haut
    {
      if (y1 > y2) // et vers droite
	return (haut_droite(word,grid, x1, y1, x2, y2));
      else if (y1 < y2) // et vers la gauche
	return (haut_gauche(word,grid, x1, y1, x2, y2));
      else
	return (haut(word,grid, x1, y1, x2, y2));
    }
  else if (x1 < x2) // vers le bas
    {
      if (y1 > y2) // et vers droite
	return (bas_droite(word,grid ,x1, y1, x2, y2));
      else if (y1 < y2) // et vers la gauche
	return (bas_gauche(word, grid ,x1, y1, x2, y2));
      else
	return (bas(word,grid , x1, y1, x2, y2));
    }
  else // en ligne
    {
      if (y1 > y2) // et vers droite
        return (ligne_droite(word, grid ,x1, y1, x2, y2));
      else if (y1 < y2) // et vers la gauche
        return (ligne_gauche(word,grid , x1, y1, x2, y2));
      else // un mot de 1 letre ... à reflechir
        return (ligne(word, grid ,x1, y1, x2, y2));
    }

  return 0;
}


int haut_droite(char *word,char ** grid ,int x1, int y1, int x2, int y2)
{
  int index = 0;

  while (word[index] != '\0' || (x1 > x2 && y1 > y2))
    {
      if (word[index] != grid[x1][y1])
	return 0;
      index++;
      x1--;
      y1--;
    }
  if (word[index] == '\0' && ++x1 == x2 && ++y1 == y2) // en gros si j'ai bien la fin du mot sur la grid ET coté coords aussi
    return 1;
  return 0;
}

int haut_gauche(char *word,char ** grid, int x1, int y1, int x2, int y2)
{
  int index = 0;

  while (word[index] != '\0' || (x1 > x2 && y1 < y2))
    {
      if (word[index] != grid[x1][y1])
	return 0;
      index++;
      x1--;
      y1++;
    }
  if (word[index] == '\0' && ++x1 == x2 && --y1 == y2) // en gros si j'ai bien la fin du mot sur la grid ET coté coords aussi
    return 1;
  return 0;
}

int haut(char *word,char ** grid, int x1, int y1, int x2, int y2)
{
  int index = 0;

  while (word[index] != '\0' || (x1 > x2))
    {
      if (word[index] != grid[x1][y1])
	return 0;
      index++;
      x1--;
    }
  if (word[index] == '\0' && ++x1 == x2 && y1 == y2) // en gros si j'ai bien la fin du mot sur la grid ET coté coords aussi
    return 1;
  return 0;
}

int bas_droite(char *word, char ** grid ,int x1, int y1, int x2, int y2)
{
  int index = 0;

  while (word[index] != '\0' || (x1 < x2 && y1 > y2))
    {
      if (word[index] != grid[x1][y1])
	return 0;
      index++;
      x1++;
      y1--;
    }
  if (word[index] == '\0' && --x1 == x2 && ++y1 == y2) // en gros si j'ai bien la fin du mot sur la grid ET coté coords aussi
    return 1;
  return 0;
}

int bas_gauche(char *word, char ** grid ,int x1, int y1, int x2, int y2)
{
  int index = 0;

  while (word[index] != '\0' || (x1 < x2 && y1 < y2))
    {
      if (word[index] != grid[x1][y1])
	return 0;
      index++;
      x1++;
      y1++;
    }
  if (word[index] == '\0' && --x1 == x2 && --y1 == y2) // en gros si j'ai bien la fin du mot sur la grid ET coté coords aussi
    return 1;
  return 0;
}

int bas(char *word,char ** grid, int x1, int y1, int x2, int y2)
{
  int index = 0;

  while (word[index] != '\0' || (x1 < x2))
    {
      if (word[index] != grid[x1][y1])
	return 0;
      index++;
      x1++;
    }
  if (word[index] == '\0' && --x1 == x2 && y1 == y2) // en gros si j'ai bien la fin du mot sur la grid ET coté coords aussi
    return 1;
  return 0;
}

int ligne_droite(char *word, char ** grid,int x1, int y1, int x2, int y2)
{
  int index = 0;

  while (word[index] != '\0' || (y1 > y2))
    {
      if (word[index] != grid[x1][y1])
	return 0;
      index++;
      y1--;
    }
  if (word[index] == '\0' && x1 == x2 && ++y1 == y2) // en gros si j'ai bien la fin du mot sur la grid ET coté coords aussi
    return 1;
  return 0;
}

int ligne_gauche(char *word,char ** grid, int x1, int y1, int x2, int y2)
{
  int index = 0;

  while (word[index] != '\0' || (y1 < y2))
    {
      if (word[index] != grid[x1][y1])
	return 0;
      index++;
      y1++;
    }
  if (word[index] == '\0' && x1 == x2 && --y1 == y2) // en gros si j'ai bien la fin du mot sur la grid ET coté coords aussi
    return 1;
  return 0;
}

int ligne(char *word, char ** grid ,int x1, int y1, int x2, int y2)
{
  if (word[0] == grid[x1][y1] && x1 == x2 && y1 == y2) // en gros si j'ai bien la fin du mot sur la grid ET coté coords aussi
    return 1;
  return 0;
}

// tu l'as senti le gros copy-paste(abox) du turfu ?
