/*
** timer.h for  in /home/ledezaxe/etude_de_cas/Rouanet_Pouvreau_Foissac_EDC2016/source/timer
** 
** Made by ledezaxe
** Login   <quentin.rouanet@etudiant.univ-lr.fr>
** 
** Started on  Thu Oct 20 08:39:57 2016 Quentin Rouanet
** Last update Thu Oct 20 09:08:36 2016 Quentin Rouanet
*/

#ifndef TIMER_H__
# define TIMER_H__

// ici c'est le timer du score pour le solo le timer debut à 100 pts (a definir encore) et toute les seconde on perd 1 pt jusqu'a 0 et quand on valide un mot non fait encore on repart a 100 et on gagne valeur du timer +1 pour différentier le fait qu'un mot soit bon mais déja validé d'un nouveau mot trouvé

#include <unistd.h>

# define JCVD 1 // car si tu parles à ton eau de javel pendant que tu fait la lessive, elle est moins concentrée ... de rien // en vrai c'est juste en attente de la fonction qui dit "hey la partie est finie" comme ça on quitte proprement

/**
 * launch_timer initialze the timer whit a score of 100 and wait for each time to decrease the counter
 * @return void*
 */
void *launch_timer();

/**
 * reset_timer resets the timer.
 * @return int
 */
int reset_timer();

/**
 * pts_timer use a fake global variable to keep the score update and return the score which mode is used on call
 * @param mode
 * @param val
 * @return int
 */
int pts_timer(int mode, int val); // 0 : consultation || 1 : modification

#endif /* !TIMER_H__ */
