/*#include <SDL/SDL.h>
#include <SDL/SDL.h>
*/
#include <stdlib.h>
#include <stdio.h>
#include "lotc.h"

/**
\file main.c
\author Julian Le Couster, Emmanuel-Paul Vincent, Xuehui Jia, Amina Zeghida
\brief 
*/

int main(){
  /*  SDL_Surface *ecran ;*/
    /*  SDL_Surface *ima=NULL;
     */ 
  presentation();
  int size,nbcoup;
  char typeinitialisation,typejeu;
  lectureinit(&size,&nbcoup,&typeinitialisation,&typejeu);
  matrice  m=allocation(size);
  
  choixinitialisation(typeinitialisation,m);
  /*if(typejeu == 'y'){
   ecran=initialiser();
    events(ecran,m,nbcoup);
  }
  else{*/
  jeu(m,nbcoup);
    /*}*/
  return 0;
}
