#include <SDL/SDL.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>
#include "lotd.h"

/**
\file main.c
\author Julian Le Couster, Emmanuel-Paul Vincent, Xuehui Jia, Amina Zeghida
\brief 
*/

int main(){
  SDL_Surface *ecran ;
  presentation();
  int size,nbcoup,choix;
  char typeinitialisation,typejeu,solveur;
  lectureinit(&size,&nbcoup,&typeinitialisation,&typejeu,&solveur);
  matrice  m=allocation(size);  
  choixinitialisation(typeinitialisation,m);
  if(solveur == 'y'){
    choix=choixsolveur();    
  }
  else{
    choix = 0;
  }
  if(typejeu == 'y'){
    ecran=initialiser();
    events(ecran,m,nbcoup,choix);
  }
  else{
    jeu(m,nbcoup,choix);
  }
  return 0;
}
