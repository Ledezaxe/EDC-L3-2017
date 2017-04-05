/*
** main.c for  in /home/ledezaxe/etude_de_cas/Rouanet_Pouvreau_Foissac_EDC2016/source/algo
** 
** Made by ledezaxe
** Login   <quentin.rouanet@etudiant.univ-lr.fr>
** 
** Started on  Mon Oct 17 14:19:23 2016 Quentin Rouanet
** Last update Tue Oct 18 10:59:28 2016 Quentin Rouanet
*/

#include <string.h>
#include <stdio.h>

#include "verif_mot.h"

char map[11][11]; // 11 car \0 à la fin  ||| map[x][y] -> x : ligne | y : colonne

int main()
{
  strcpy(map[0], "DYETKRIOAD");
  strcpy(map[1], "HXTSCIERND");
  strcpy(map[2], "SJIBGYWWUP");
  strcpy(map[3], "KHGGMODISQ");
  strcpy(map[4], "ATTENTIONG");
  strcpy(map[5], "TDEMUFNSPO");
  strcpy(map[6], "EITRAPBQZU");
  strcpy(map[7], "RSETELUOFR");
  strcpy(map[8], "MKAYAKXWJD");
  strcpy(map[9], "DTJEFFIGIE");

  // oui c'est sale comme initialisation mais c'est un main de test pour l'optimisation on verra plus tard

  printf("%s\n", map[0]);
  printf("%s\n", map[1]);
  printf("%s\n", map[2]);
  printf("%s\n", map[3]);
  printf("%s\n", map[4]);
  printf("%s\n", map[5]);
  printf("%s\n", map[6]);
  printf("%s\n", map[7]);
  printf("%s\n", map[8]);
  printf("%s\n", map[9]);

  // toujours retirer 1 aux coordonnes : les tabs commencent à 0

  char *test;

  test = strdup("TEST");
  printf("\n Test (0 attendu) : %d\n", verif_mot(test, 0, 5, 6, 4)); // c'est faux normalement
  test = strdup("ATTENTION");
  printf("\n Attention (1 attendu) : %d\n", verif_mot(test, 4, 0, 4, 8)); // c'est vrai normalement

  return (1);
}
