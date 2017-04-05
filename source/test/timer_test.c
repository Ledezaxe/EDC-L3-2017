/*
** main.c for  in /home/ledezaxe/etude_de_cas/Rouanet_Pouvreau_Foissac_EDC2016/source/timer
** 
** Made by ledezaxe
** Login   <quentin.rouanet@etudiant.univ-lr.fr>
** 
** Started on  Thu Oct 20 09:01:22 2016 Quentin Rouanet
** Last update Thu Oct 20 09:41:45 2016 Quentin Rouanet
*/

#include "timer.h"
#include <pthread.h>
#include <stdio.h>


int main()
{
  pthread_t timer_th;

  int res = 56;

  if (pthread_create(&timer_th, NULL, launch_timer, NULL) == -1)
    printf("thread : erreur création\n");

  while (res > 50)
    {
      sleep(10);
      res = pts_timer(0, 0);
      printf("%d\n", res);
    }

  res = reset_timer();
  printf("avant reset : %d\n", res);
  res = reset_timer();
  printf("après reset : %d\n", res);

  return (1);
}
