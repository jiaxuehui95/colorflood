#include "lotb.h"

typedef struct maillon* pile;

struct maillon{
  int val;
  pile next;
};

int estVide(pile l);

pile empiler(pile l, int i);

void depiler(pile *l);

void uneSolutionTrouvee(pile solution);

void solveur(matrice m, matrice id, pile solution, int profondeur);




