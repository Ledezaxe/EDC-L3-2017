/*
** timer.c for  in /home/ledezaxe/etude_de_cas/Rouanet_Pouvreau_Foissac_EDC2016/source/timer
** 
** Made by ledezaxe
** Login   <quentin.rouanet@etudiant.univ-lr.fr>
** 
** Started on  Thu Oct 20 08:39:10 2016 Quentin Rouanet
** Last update Thu Oct 20 09:10:42 2016 Quentin Rouanet
*/

#include "timer.h"

void *launch_timer() // cette fonction à clairement pour but de tourner en rond en gros on lance le bouzin dans un thread et zou ça tourne
{
  pts_timer(1, 100);

  while(JCVD)
  {
    sleep(1);
    pts_timer(1, pts_timer(0, 0) - 1); // ici on decremente la valeur de pts timer ... et puis comme ça si il y a besoin d'un mutex c'est moult plus simple
  }
  return NULL;
}
int reset_timer() // ici on remet le timer à 100 pts et on renvoie le score donc timer + 1
{
  return (pts_timer(1, 100));
}

int pts_timer(int mode, int val)
{
  static int score; // pourquoi faire une fausse globale plutot qu'une énième globale ? déja je trouve ça naze les globales puis le challenge d'en faire une et puis en cas de soucis avec les threads y mettre un mutex dessus sera plus simple, on en met un DANS cette fonction et basta
  int ret;

  if (mode == 0) // consultation
    return (score);
  else
    {
      ret = score;
      score = val;
      return (ret);
    }
}
