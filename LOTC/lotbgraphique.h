#include "lotb.h"
#include <SDL/SDL.h>
#include <SDL/SDL.h>

void drawRectangle(SDL_Surface *ecran, int px, int py, int size, int r, int g, int b);

void fillScreen(SDL_Surface *ecran, int r, int g, int b);

SDL_Surface *  initialiser();

void events(SDL_Surface *ecran,matrice m,int nbcoup,int choix);
