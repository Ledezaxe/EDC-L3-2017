/*
** main.c for  in /home/ledezaxe/etude_de_cas/Rouanet_Pouvreau_Foissac_EDC2016/source/algo
** 
** Made by ledezaxe
** Login   <quentin.rouanet@etudiant.univ-lr.fr>
** 
** Started on  Mon Oct 17 14:19:23 2016 Quentin Rouanet
** Last update Fri Dec  9 14:42:56 2016 Rouanet Quentin
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "force_brute.h"

char **map; // 11 car \0 à la fin  ||| map[x][y] -> x : ligne | y : colonne
char **words; // 13 car NULL à la fin de la liste pour eviter les segfaults nuls

int main()
{
  map = malloc(11 * sizeof(char *));

  map[0] = strdup("DYETKRIOAD");
  map[1] = strdup("HXTSCIERND");
  map[2] = strdup("SJIBGYWWUP");
  map[3] = strdup("KHGGMODISQ");
  map[4] = strdup("ATTENTIONG");
  map[5] = strdup("TDEMUFNSPO");
  map[6] = strdup("EITRAPBQZU");
  map[7] = strdup("RSETELUOFR");
  map[8] = strdup("MKAYAKXWJD");
  map[9] = strdup("DTJEFFIGIE");
  map[10] = NULL;
  
  // oui c'est sale comme initialisation mais c'est un main de test pour l'optimisation on verra plus tard

  /*  printf("%s\n", map[0]);
  printf("%s\n", map[1]);
  printf("%s\n", map[2]);
  printf("%s\n", map[3]);
  printf("%s\n", map[4]);
  printf("%s\n", map[5]);
  printf("%s\n", map[6]);
  printf("%s\n", map[7]);
  printf("%s\n", map[8]);
  printf("%s\n", map[9]);*/

  // toujours retirer 1 aux coordonnes : les tabs commencent à 0
  words = malloc(13 * sizeof(char *));

  words[0] = strdup("GOURDE");
  words[1] = strdup("ETE");
  words[2] = strdup("SKATER");
  words[3] = strdup("KIWI");
  words[4] = strdup("GITE");
  words[5] = strdup("SCIER");
  words[6] = strdup("FOULE");
  words[7] = strdup("FUME");
  words[8] = strdup("EFFIGIE");
  words[9] = strdup("KAYAK");
  words[10] = strdup("PARTIE");
  words[11] = strdup("ATTENTION");
  words[12] = NULL;

  Grid *truc;

  truc = filling(words, 10, 10, 12);

  display_grid(truc);
  char *res;

  res = strdup("DEBUT");
  while (res != NULL)
    {
      free(res);
      res = force_brute(truc->tab, truc->list, "QWARK", 10, 10);
      if (res != NULL)
	printf("%s\n", res);
    }
  return (1);
}
