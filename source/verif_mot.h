/*
** verif_mot.h for  in /home/ledezaxe/etude_de_cas/Rouanet_Pouvreau_Foissac_EDC2016/source/algo
** 
** Made by ledezaxe
** Login   <quentin.rouanet@etudiant.univ-lr.fr>
** 
** Started on  Tue Oct 18 10:14:57 2016 Quentin Rouanet
** Last update Tue Oct 18 10:58:18 2016 Quentin Rouanet
*/

#ifndef VERIF_MOT_H__
# define VERIF_MOT_H__

#include <stdio.h>

/**
 * verif mot is a function who verify the word that the player think founded.
 * the function use all other functions in verif_mot.c
 * And it's represents which possibilities of direction of the spelling of the word
 * directions X to number
 * 1   2   3
 * 4   X   5
 * 6   7   8
 */
int verif_mot(char *word,char ** grid , int x1, int y1, int x2, int y2);

int haut_droite(char *word,char ** grid , int x1, int y1, int x2, int y2);
int haut_gauche(char *word,char ** grid , int x1, int y1, int x2, int y2);
int haut(char *word,char ** grid , int x1, int y1, int x2, int y2);

int bas_droite(char *word,char ** grid , int x1, int y1, int x2, int y2);
int bas_gauche(char *word,char ** grid , int x1, int y1, int x2, int y2);
int bas(char *word, char ** grid ,int x1, int y1, int x2, int y2);

int ligne_droite(char *word,char ** grid , int x1, int y1, int x2, int y2);
int ligne_gauche(char *word,char ** grid , int x1, int y1, int x2, int y2);
int ligne(char *word,char ** grid, int x1,  int y1, int x2, int y2);

#endif /* !VERIF_MOT_H__ */
