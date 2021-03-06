#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h> 
#include <time.h> /*Pour le rand()*/
#include <SDL/SDL.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "lotd.h"

/**
\file lotbgraphique.c
\author Julian Le Couster, Emmanuel-Paul Vincent, Xuehui Jia, Amina Zeghida
\brief 
*/
int autoDraw=0;
int B[3]={0,0,255};
int V[3]={0,255,0};
int R[3]={255,0,0};
int J[3]={255,255,0};
int M[3]={255,0,255};
int G[3]={130,130,130};
 SDL_Color couleurNoire = {0, 0, 0}, couleurBlanche = {255, 255, 255};
	char nbcoups_txt[50] = "";
	   	SDL_Surface *texte = NULL;
 	SDL_Rect position;
TTF_Font *police = NULL;

/*
  @reuires: ecran initialise,  (px,py):le cooedonnee debut de rectangle,  size: taille de rectangle, r,g,b: code RGB pour indiquer la couleur
  @assigns: ecran
  @ensures: dessiner un rectrangle de taille "size"dans la fenetre
*/
/**
   \fn void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b)
   \brief dessiner un rectrangle de taille "size"dans la fenetre
   \param ecran:ecran initialisé
   \param px:l'abscisse de la debut de rectangle  
   \param px:l'ordonnée de la debut de rectangle
   \param size: taille de rectangle
   \param r: valeur du Rouge dans la code RGB qui indique la couleur
   \param g: valeur du Vert dans la code RGB qui indique la couleur
   \param b: valeur du Bleu dans la code RGB qui indique la couleur
   \return none
*/

void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b) {
  SDL_Rect rect;
  rect.x=px;
  rect.y=py;
  rect.h=rect.w=size;
  SDL_FillRect(ecran, &rect, SDL_MapRGB(ecran->format, r, g, b));
  SDL_Flip(ecran);
}
/*
  @reuires: ecran initialise, ecran: le fenetre , r,g,b: code RGB pour indiquer la couleur
  @assigns: ecran
  @ensures: remplirer la fenetre avec une certaine couleur 
*/
/**
   \fn void fillScreen(SDL_Surface *ecran, int r, int g, int b)
   \brief remplirer la fenetre avec une certaine couleur 
   \param ecran:ecran initialisé
   \param r: valeur du Rouge dans la code RGB qui indique la couleur
   \param g: valeur du Vert dans la code RGB qui indique la couleur
   \param b: valeur du Bleu dans la code RGB qui indique la couleur
   \return none
*/
void fillScreen(SDL_Surface *ecran, int r, int g, int b) {
  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, r, g, b));
  SDL_Flip(ecran);              /*geng xin chuang kou*/
}
/*
  @reuires: rien
  @assigns: ecran
  @ensures: initialiser la fenetre
*/
/**
   \fn SDL_Surface *  initialiser()
   \brief initialiser la fenetre 
   \param none
   \return ecran : ecran initialisé 
*/
SDL_Surface *  initialiser()
{
  SDL_Surface *ecran = NULL;
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {   
    /* Failed, exit. */
    fprintf( stderr, "Video initialization failed: %s\n", SDL_GetError( ) );
    SDL_Quit( );
  }
      TTF_Init();
  const SDL_VideoInfo* info= NULL;
  info = SDL_GetVideoInfo( );
  if( !info ) {
    /* This should probably never happen. */
    fprintf( stderr, "Video query failed: %s\n", SDL_GetError( ) );
    SDL_Quit( );
  }
  ecran=SDL_SetVideoMode(1000, 1000, 32, SDL_HWSURFACE);   /*jian li yi ge 500*500*32wei de chuangkou*/
  SDL_WM_SetCaption("exemple SDL", NULL);                 /*she zhi biao ti*/
    
  fillScreen(ecran, 0,0,0);
  police = TTF_OpenFont("angelina.ttf", 55);

 	     sprintf(nbcoups_txt, "tapez d pour commancer, tapez q pour quitter"); /* On écrit dans la chaîne "temps" le nouveau temps */
      	      SDL_FreeSurface(texte); /* On supprime la surface précédente */
              texte = TTF_RenderText_Shaded(police, nbcoups_txt, couleurBlanche, couleurNoire); /* On écrit la chaîne temps dans la SDL_Surface */
              position.x = 0;
              position.y = 0;
        	  SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        	  SDL_Flip(ecran); 
        	  sleep(2);
  return ecran;
}

/*
  @reuires: ecran initialise, matrice m, nbcoup
  @assigns: ecran,m,ncoup
  @ensures: le joueur joue jusqu'à ce qu'il quitte, gagne la partie ou épuise son nombre de coups. imprimer le grille dans la fenetre,On libère la mémoire allouée aux matrices. Le jeu et le nombre de coups sont affichés à chaque tour. 

*/
/**
   \fn void events(SDL_Surface *ecran,matrice m,int nbcoup,int choix)
   \brief le joueur joue jusqu'à ce qu'il quitte, gagne la partie ou épuise son nombre de coups. imprimer le grille dans la fenetre,On libère la mémoire allouée aux matrices. Le jeu et le nombre de coups sont affichés à chaque tour.  
   \param ecran : ecran initialisé 
   \param m : tableau représentant le tableau d'une matrice (le jeu) 
   \param nbcoup : entier correspondant au nombre de coups souhaitée par le joueur et qui est décrémenté lors du jeu       
   \param choix : entier correspondant au choix du solveur  
   \return ecran  : none
*/
void events(SDL_Surface *ecran,matrice m,int nbcoup,int choix)
{
  SDL_Event event;
  int continuer = 1;
  int i,j;
  int c;
  int quitte=0;
  int x,y;
   police = TTF_OpenFont("angelina.ttf", 65);
fillScreen(ecran, 0,0,0);

  fprintf(stderr,"tapez d pour commancer,tapez q pour quitter\n");
	pile p=NULL;
  matrice id = allocation(m.size);
  for(i=0;i<m.size;i++)
    {
      for(j=0;j<m.size;j++)
	{
	  id.tab[i][j]=-1;
	}

    }
	
  identification(m.tab,id.tab,0,0,m.size);
  if(choix == 1){
    nbcoup=solveuraleatoire(m,id,p)+2;
  }
  if(choix == 2){
    nbcoup=solveur(m,id,p,0)+2;
  }
  while(!presence(id) && nbcoup!=0 && quitte != 1)
    {	
      fprintf(stderr,"Nombre de coups restants %i\n",nbcoup);
      while (continuer) 
	{
	  SDL_WaitEvent(&event);
	  switch(event.type) 
	    {
	    case SDL_QUIT:                          /*esc*/
	      continuer = 0;
	      break;
	    case SDL_KEYDOWN: // gestion des évènements clavier
	      switch (event.key.keysym.sym) 
		{
		case SDLK_d: 
			                        /*hua tu*/
		  for(i=0;i<m.size;i++) 
		    {
		      for(j=0;j<m.size;j++)
			{
			  if(m.tab[i][j]==1)
			    { drawRectangle(ecran, 3+(33*j), 3+(33*i), 30, B[0], B[1], B[2]);}
			  if(m.tab[i][j]==2)
			    {drawRectangle(ecran, 3+(33*j), 3+(33*i), 30, V[0], V[1], V[2]);}
			  if(m.tab[i][j]==3)
			    {drawRectangle(ecran, 3+(33*j), 3+(33*i), 30, R[0], R[1], R[2]);}				
			  if(m.tab[i][j]==4)
			    {drawRectangle(ecran, 3+(33*j), 3+(33*i), 30, J[0], J[1], J[2]);}				
			  if(m.tab[i][j]==5)
			    {drawRectangle(ecran, 3+(33*j), 3+(33*i), 30, M[0], M[1], M[2]);}				
			  if(m.tab[i][j]==6)
			    {drawRectangle(ecran, 3+(33*j), 3+(33*i), 30, G[0], G[1], G[2]);}				
			}
		    }
		   sprintf(nbcoups_txt, "coups restants: %d ", nbcoup);
		    texte = TTF_RenderText_Shaded(police, nbcoups_txt, couleurBlanche, couleurNoire);
			 position.x = 300;
              position.y = 875;
        	  SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        	  SDL_Flip(ecran);            


		  drawRectangle(ecran, 3, 900, 30, B[0], B[1], B[2]);
		  drawRectangle(ecran, 36, 900, 30, V[0], V[1], V[2]);
		  drawRectangle(ecran, 69, 900, 30, R[0], R[1], R[2]);
		  drawRectangle(ecran, 102, 900, 30, J[0], J[1], J[2]);
		  drawRectangle(ecran, 135, 900, 30, M[0], M[1], M[2]);
		  drawRectangle(ecran, 168, 900, 30, G[0], G[1], G[2]);
		  break;
		case SDLK_e:
		  fillScreen(ecran, 255,0,255);
		  break;
		case SDLK_r:
		  fillScreen(ecran, 0,0,0);
		  break;
		case SDLK_ESCAPE:
		  continuer=0; 
		  break;
		case SDLK_q:
		  quitte=1;
		  continuer=0;
		  SDL_Quit();
		  break;
		 default:
		  	break;
		} 
	      break;
	    case SDL_MOUSEBUTTONDOWN:
	      if (event.button.button == SDL_BUTTON_LEFT)
		{
		  x = event.button.x ;
		  y = event.button.y ;
		  int bpp = ecran->format->BytesPerPixel;
		  /* Here p is the address to the pixel we want to retrieve */
		  Uint8 *p = (Uint8 *)ecran->pixels + y*ecran->pitch + x*bpp;
		  // should be p[0], p[1], p[2] ...
		  // fprintf(stderr,"%d %d -> %d %d %d\n",y, x, p[2], p[1], p[0]);
		  if(y<930&&y>900)
		    {
		      if(3<x&&x<33) {c=1;}
		      else if(36<x&&x<66) {c=2;}
		      else if(69<x&&x<99) {c=3;}
		      else if(102<x&&x<132) {c=4;}
		      else if(135<x&&x<165) {c=5;}
		      else if(168<x&&x<198) {c=6;}
		      else c=0;
		    }
		  else
		    c=0;
		  if(c!=0 &&(c!=m.tab[0][0]))
		    {
		      nbcoup--;
		      sprintf(nbcoups_txt, "coups restants: %d ", nbcoup); /* On écrit dans la chaîne "temps" le nouveau temps */
      	      SDL_FreeSurface(texte); /* On supprime la surface précédente */
              texte = TTF_RenderText_Shaded(police, nbcoups_txt, couleurBlanche, couleurNoire); /* On écrit la chaîne temps dans la SDL_Surface */
              position.x = 300;
              position.y = 875;
        	  SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        	  SDL_Flip(ecran);
		      for(i=0;i<m.size;i++)
			{
			  for(j=0;j<m.size;j++)
			    {
			      if(id.tab[i][j]==1)
				{ drawRectangle(ecran, 3+(33*j), 3+(33*i), 30, p[2], p[1], p[0]);}
			    }
			}
		    }
		  continuer=0;
		}
	      break;
	      default:
		  	break;
	    }
	  if(continuer==0)
	    break;
	}
      continuer = 1;
      for(i=0;i<m.size;i++)
	{
	  for(j=0;j<m.size;j++)
	    {	
	      if(id.tab[i][j]==1)
		{
		  id.tab[i][j]=-1;
		  m.tab[i][j]=c;
		}
	      if(id.tab[i][j]==0)
		{
		id.tab[i][j]=-1;
		}
	    }
	}
      identification(m.tab,id.tab,0,0,m.size);
    }
  
  if(presence(id)){
    fprintf(stderr,"Bravo!!vous avez gagne\n");
 	     sprintf(nbcoups_txt, "Bravo!!vous avez gagne"); /* On écrit dans la chaîne "temps" le nouveau temps */
      	      SDL_FreeSurface(texte); /* On supprime la surface précédente */
              texte = TTF_RenderText_Shaded(police, nbcoups_txt, couleurBlanche, couleurNoire); /* On écrit la chaîne temps dans la SDL_Surface */
              position.x = 200;
              position.y = 450;
        	  SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        	  SDL_Flip(ecran); 
        	  sleep(2);
 
  }
  else{
    if(nbcoup<=0)
    {
      fprintf(stderr,"Il ne reste plus de coups,vous avez perdu\n");
      sprintf(nbcoups_txt, "Il ne reste plus de coups,vous avez perdu "); /* On écrit dans la chaîne "temps" le nouveau temps */
      	      SDL_FreeSurface(texte); /* On supprime la surface précédente */
              texte = TTF_RenderText_Shaded(police, nbcoups_txt, couleurBlanche, couleurNoire); /* On écrit la chaîne temps dans la SDL_Surface */
              position.x = 100;
              position.y = 450;
        	  SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
        	  SDL_Flip(ecran); 
        	    sleep(2);
 
    }
    else{
      fprintf(stderr,"Vous avez quitté\n");
  }
  }
    free1(m.tab,m.size);
    free1(id.tab,id.size);

     TTF_CloseFont(police);
    TTF_Quit();

    SDL_FreeSurface(texte);
    SDL_Quit();
   
 
}


 
