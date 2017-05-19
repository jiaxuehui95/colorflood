#include "lotbgraphique.h"

typedef struct maillon* pile;

struct maillon{
  int val;
  pile next;
};

int estVide(pile l);

pile empiler(pile l, int i);

void depiler(pile *l);

int longueur(pile p);

void uneSolutionTrouvee(pile solution);

int solveur(matrice m, matrice id, pile solution, int profondeur);




