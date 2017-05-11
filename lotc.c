#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "lotc.h"

/**
\file lotc.c
\author Julian Le Couster, Emmanuel-Paul Vincent, Xuehui Jia, Amina Zeghida
\brief 
*/

/**
   \fn int estVide(pile l)
   \brief permet de tester si une pile est vide
   \param l : pile valide
   \return 1 si la pile est vide, 0 sinon
*/
int estVide(pile l){
  return NULL == l;
}

/**
   \fn int estDans(pile l, int i)
   \brief permet de tester si un entier est dans une pile
   \param l : pile valide
   \param i : un entier
   \return 1 si l'entier est dans la pile, 0 sinon
*/
int estDans(pile l,int i){
  int a=0;
  while(!estVide(l) && a!=5){
    if(l->val == i){
      return 1;
    }
    l=l->next;
    a++;
  }
  return 0;
}

/**
   \fn int egale(matrice a, matrice b)
   \brief permet de tester si deux matrices sont égales
   \param a : une matrice valide
   \param b : une matrice valide
   \return 1 si les matrices sont égales, 0 sinon
*/

int egale(matrice a, matrice b){
  int i,j;
  for(j=0;j<a.size;j++){
    for(i=0;i<a.size;i++){
      if(a.tab[j][i] != b.tab[j][i]){
	return 0;
      }
    }
  }
  return 1;
}

/**
   \fn pile empiler(pile l, int i)
   \brief permet d'empiler un entier au sommet de la pile
   \param l : pile valide
   \param i : un entier
   \return retourne la pile avec l'entier i au sommet
*/
pile empiler(pile l, int i){
  pile p = (pile) malloc(sizeof(struct maillon));
  p->val=i;
  p->next = l;
  return p;
}

/**
   \fn void depiler(pile *l)
   \brief permet de depiler l'élément au sommet de la pile
   \param *l : un pointeur vers une pile, valide
   \return none 
*/
void depiler(pile *l){
  (*l)=(*l)->next;
}


/**
   \fn int longueur(pile p)
   \brief permet d'avoir la longueur de la pile
   \param p : pile valide
   \return retourne la longueur de la pile
*/
int longueur(pile p){
  int i=0;
  while(!estVide(p)){
    p=p->next;
    i++;
  }
  return i;
}

/**
   \fn void uneSolutionTrouvee(pile solution)
   \brief permet d'affiche la pile lorsqu'elle correspond à une solution
   \param solution : pile valide
   \return none
*/
void uneSolutionTrouvee(pile solution){
  printf("Une solution : ");
  char a;
  while(!estVide(solution)){
    a = solution->val;
    printf("%c ",itoc(a));
    depiler(&solution);
  }
  printf("\n");
}

int profondeurmax = INT_MAX;

/**
   \fn void solveur(matrice m, matrice id, pile solution, int profondeur)
   \brief permet d'afficher toutes les solutions du jeu à condition qu'elles soient meilleures que les précédentes solutions trouvées
   \param m : matrice valide
   \param id : matrice valide
   \param solution : pile valide
   \param profondeur : entier
   \return none
*/
void solveur(matrice m, matrice id, pile solution, int profondeur){
  if(profondeur+1 < profondeurmax){
  int i,j,k;
  matrice m2= allocation(m.size);
  matrice id2= allocation(id.size);
  for(i=1;i<7;i++){
    /*if(!estDans(solution,i)){*/
         
   
      solution = empiler(solution,i);
   
      for(k=0;k<m.size;k++){
	for(j=0;j<m.size;j++){
	  id2.tab[k][j]=id.tab[k][j];
	  m2.tab[k][j]=m.tab[k][j];
	}
      }

      changement(m2,id2,i);
          
      identification(m2.tab,id2.tab,0,0,m.size);
      if(!egale(id,id2)){ //on vérifie que le coup a modifié quelque chose, sinon il ne sert à rien
	if(presence(id2)){
	  profondeurmax=longueur(solution); //profondeur a la place d'utiliser la fonction longueur
	  uneSolutionTrouvee(solution);
	  
	}
	else{
	  /*i++;
	    if(i==7){
	    i=1;}*/
	  
	    solveur(m2,id2,solution,profondeur+1);
	  
	}
      }
      depiler(&solution);
      /*}*/
  }
  free1(m2.tab,m2.size);
  free1(id2.tab,id2.size);
  }
}




