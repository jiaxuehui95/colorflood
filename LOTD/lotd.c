#include <stdio.h>
#include <stdlib.h>
#include "lotd.h"

/**
\file lotd.c
\author Julian Le Couster, Emmanuel-Paul Vincent, Xuehui Jia, Amina Zeghida
\brief 
*/

/**
   \fn void couleur(matrice m, matrice id, int *tab)
   \brief permet de déterminer le nombre d'apparitions de chaque couleur autour de la tache
   \param m : matrice valide
   \param id : matrice valide
   \param tab : tableau d'entiers,valide
   \return none
*/
void couleur(matrice m, matrice id, int *tab){
  int i,j;
  for(i=0;i<m.size;i++){
    for(j=0;j<m.size;j++){
      if(id.tab[i][j] == 0){
	tab[m.tab[i][j]-1]++; //pour compter le nombre d'apparitions de chaque couleur autour de la tache
      }
    }
  }
}

/**
   \fn int maxcouleur(int *tab)
   \brief permet de retourner l'emplacement dans le tableau de la couleur qui apparait le plus autour de la tache
   \param tab : tableau d'entiers, valide
   \return un entier correspondant à l'indice de l'élément maximum du tableau
*/
int maxcouleur(int *tab){
  int i,imax=0;
  for(i=1;i<6;i++){
    if(tab[imax]<tab[i]){
      imax=i;
    }
  }
  return imax;
}

/**
   \fn void remiseazero(int *tab)
   \brief permet de réinitialiser à 0 toutes les cases du tableau
   \param tab : tableau d'entiers, valide
   \return none 
*/
void remiseazero(int *tab){
  int i;
  for(i=0;i<6;i++){
    tab[i]=0;
  }
}

/**
   \fn void solveuraleatoire(matrice m2, matrice id2, pile solution)
   \brief permet de trouver une solution en fonction du nombre d'apparition de chaque couleur autour de la tâche du jeu
   \param m2 : matrice valide
   \param id2 : matrice valide
   \param solution : pile valide
   \return un entier : la longueur de la solution
*/
int solveuraleatoire(matrice m2, matrice id2, pile solution){
  int *tab = (int*) calloc(6,sizeof(int));
  matrice m = allocation(m2.size);
  matrice id = allocation(id2.size);
  int i,k;
  for(k=0;k<m.size;k++){
	for(i=0;i<m.size;i++){
	  id.tab[k][i]=id2.tab[k][i];
	  m.tab[k][i]=m2.tab[k][i];
	}
      }

  while(!presence(id)){
    couleur(m,id,tab);
    i=maxcouleur(tab);
    solution =empiler(solution,i+1);
    changement(m,id,i+1);
    identification(m.tab,id.tab,0,0,m.size);
    remiseazero(tab);
  }
  uneSolutionTrouvee(solution);
  int prof = longueur(solution);
  while(!estVide(solution)){
    depiler(&solution);
  }//pour libérer la mémoire de la pile
  free(tab);
  free1(m.tab,m.size);
  free1(id.tab,id.size);
  return prof;
}


/**
   \fn int choixsolveur()
   \brief permet de demander à l'utilisateur le type de solveur qu'il souhaite utiliser
   \param : none
   \return un entier correspondant au type de solveur (1 pour aléatoire et 2 pour la meilleure solution)
*/

int choixsolveur(){
  int i;
  printf("Quel solveur souhaitez- vous utilisé (1: aléatoire 2 : optimal) ? \n");
  printf("Attention le solveur donnant la solution optimal peut être très long\n");
  scanf("%i",&i);
  if(i !=1 && i != 2){
    printf("\n");
    printf("Valeur incorrecte !\n");
    printf("Puisque c'est ça, le solveur sera aléatoire !\n\n");
    i=1;
  }
  return i;
}
