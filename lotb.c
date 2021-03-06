#include <stdio.h>
#include <stdlib.h>
/*#include "lotb.h"*/
#include "lotd.h"


/**
\file lotb.c
\author Julian Le Couster, Emmanuel-Paul Vincent, Xuehui Jia, Amina Zeghida
\brief 
*/
/*@requires m,nbcoup et typeinitialisation valide
  @assigns  la valeur de la variable m, la variable nbcoup et la variable typeinitialisation
  @ensures  la taille de damier souhaitée par l'utilisateur, le nombre de coups souhaité et le type d'initialisation (à partir d'un fichier ou non)
*/
/**
   \fn void lectureinit(int* m, int* nbcoup, char* typeinitialisation,char *typejeu, char *solveur)
   \brief récupère la taille souhaitée par l'utilisateur, le nombre de coup et le type d'initialisation qu'il souhaite
   \param *m : pointeur représentant la taille du jeu souhaitée
   \param *nbcoup : pointeur représentant le nombre de coup souhaité
   \param *typeinitialisation : pointeur représentant le type d'initialisation (à partir d'un fichier ou non) souhaitée
   \param *solveur : pointeur représentant le choix du solveur
   \return les valeurs souhaitées à travers les pointeurs
*/
void lectureinit(int* m, int* nbcoup, char* typeinitialisation,char *typejeu,char *solveur){
  printf("Quelle est la taille du plateau avec lequel vous voulez jouer ? \n");
  printf("6: (6*6) , 12 : (12*12) , 18 : (18*18) et 24 : (24*24)\n");
  scanf("%i",&(*m));
  if(*m != 6 && *m != 12 && *m != 18 && *m != 24){
    printf("\n");
    printf("Taille incorrecte !\n");
    printf("Ce n'est pas très gentil d'essayer de faire planter mon programme !\n");
    printf("Puisque c'est ça, vous jouerez avec la taille standard 18*18 !\n\n");
    *m=18;
  }
  
  printf("Quelle est le nombre de coups que vous souhaitez ? (Minimum %i)\n",2*(*m));
  scanf("%i",&(*nbcoup));
  if(*nbcoup < 2*(*m)){
    printf("\n");
    printf("Taille incorrecte !\n");
   
    printf("Puisque c'est ça, vous jouerez avec le nombre de coups minimum : %i !\n\n",2*(*m));
    *nbcoup=2*(*m);
  }

  printf("Souhaitez-vous chargez la partie à l'aide d'un fichier ? (y/n)\n");
  *typeinitialisation = get_carac();
  vide_buffer();
  if(*typeinitialisation != 'y' && *typeinitialisation != 'n'){
    printf("\n");
    printf("Valeur incorrecte !\n");
   
    printf("Puisque c'est ça, la partie sera initialisée aléatoirement !\n\n");
    *typeinitialisation='n';
  }
  printf("Souhaitez-vous jouer en mode graphique ? (y/n)\n");
  *typejeu = get_carac();
  vide_buffer();
  if(*typejeu!= 'y' && *typejeu != 'n'){
    printf("\n");
    printf("Valeur incorrecte !\n");
   
    printf("Puisque c'est ça, la partie sera en mode terminal !\n\n");
    *typejeu='n';
  }
  printf("Souhaitez-vous jouer avec un solveur ? (y/n)\n");
  printf("Attention le nombre de coups sera initialisé à partir de la solution trouvée\n");
  *solveur = get_carac();
  vide_buffer();
  if(*solveur!= 'y' && *solveur != 'n'){
    printf("\n");
    printf("Valeur incorrecte !\n");
   
    printf("Puisque c'est ça, vous jouerez sans solveur !\n\n");
    *solveur='n';
  }
}

/*
@requires : m valide
  @assigns  : m et le fichier créé si on choisit de stocker les valeurs
  @ensures  : initialise la matrice en fonction de la méthode choisie (si i=y, on initialise à partir d'un fichier, sinon on initialise aléatoirement) et on stocke cette matrice dans un fichier si on le souhaite
*/
/**
   \fn void choixinitialisation(char i,matrice m)
   \brief permet d'initialiser la matrice en fonction du choix de l'utilisateur, soit à partir d'un fichier soit aléatoirement. On peut également choisir de stocker les valeurs en créant ou remplaçant un fichier.
   \param m : matrice valide
   \param i : caractère précisant si l'utilisateur souhaite initialiser ou non à partir d'un fichier
   \return none (la matrice est initialisée)
*/
void choixinitialisation(char i,matrice m){
  char choix;
  if(i=='y'){
    m= initialisationfichier1(m);
  }
  else{
    choix = 'a';
    while(choix!='y' && choix!='n'){
    printf("Souhaitez-vous enregistrer votre partie dans un fichier ? (y/n)\n");
    choix = get_carac();
    vide_buffer();
    }
    initialisation(m);
    if(choix=='y'){
      create_fichier1(m);
    }    
  }
}

/*
@requires : m valide
@assigns  : rien
@ensures  : affiche les éléments du tableau de m (on affiche chaque ligne du tableau à la ligne)
*/
/**
   \fn void affichage(matrice m)
   \brief affiche la matrice passée en paramètre
   \param m : matrice valide
   \return none (le fichier a été affichée)
*/
void affichage(matrice m){
  int n = m.size;
  int i,j;
  printf("\n");
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      printf("%c ",itoc(m.tab[i][j]));
    }
    printf("\n");
  }
}

/*
@requires : rien
@assigns  : rien
@ensures  : affiche le message proposant au joueur de rentrer une valeur pour jouer
*/
/**
   \fn void message()
   \brief affiche le message permettant à l'utilisateur de savoir quelles valeurs il peut rentrer
   \param none
   \return none (le fichier a été crée)
*/
void message(){
    printf("Quelle couleur souhaitez-vous jouer ? (q pour quitter)\n");
    printf("Le choix est : B, V, R, J, M et G\n");
}

/*
@requires : c et nbcoup valide
@assigns  : c et nbcoup
@ensures  : on demande au joueur de jouer jusqu'à ce qu'il rentre un caractère valide (B, V, R, J, M, G ou q). Si il rentre q, on quitte la partie. Sinon on renvoie dans c l'entier correspond à la valeur jouée par le joueur et décrémente le nombre de coup.
*/
/**
   \fn int selection(int *c, int* nbcoup, int tache)
   \brief permet de demander et de récupérer la valeur que l'utilisateur souhaite joueur. Si il souhaite quitter la partie il peut rentrer q. On diminue également le nombre de coups restants si il rentre une valeur valide.
   \param *c : un pointeur correspondant au choix de jeu de l'utilisateur
   \param *nbcoup : pointeur correspondant au nombre de coups restants de l'utilisateur
   \return 1 si le joueur a joué, 0 si il quitte (le nombre de coup et la couleur ont été modifiées)
*/
int selection(int *c, int* nbcoup, int tache){
  int ok=0;
  char couleur;
  while(!ok){
    message();
    couleur = get_carac();
    if(((*c)=ctoi(couleur)) !=0 && (*c) != tache){ /*Si *c est bien une couleur souhaitée */
      (*nbcoup)--;
      ok=1;
      return 1;
    }
    if((*c) == tache){
      printf("Inutile de jouer la même couleur que la tâche !\n");
    }
    
    if(couleur=='q'){
      printf("Vous quittez !\n");
      return 0;
    }
  }
  return 0;
}


/*
@requires : m valide
@assigns  : m
@ensures  : le joueur joue jusqu'à ce qu'il quitte, gagne la partie ou épuise son nombre de coups. On libère la mémoire allouée aux matrices. Le jeu et le nombre de coups sont affichés à chaque tour. 
*/
/**
   \fn void jeu(matrice m, int nbcoup, int choix)
   \brief permet au joueur de jouer. On alloue la mémoire de la matrice, on initialise la matrice d'identification, puis on joue tant que l'on n'a pas gagné ou épuisé le nombre de coups
   \param m : matrice valide
   \param nbcoup : entier correspondant au nombre de coups souhaitée par le joueur et qui est décrémenté lors du jeu
   \param choix : entier qui détermine le choix pour le solveur
   \return none (se termine lorsque la partie est terminée ou que le joueur souhaite quitter la partie)
*/
void jeu(matrice m, int nbcoup, int choix){
  int c,i,j;
  matrice id = allocation(m.size);
  pile p=NULL;
  for(i=0;i<m.size;i++){
    for(j=0;j<m.size;j++){
      id.tab[i][j]=-1;
    }
  }
  identification(m.tab,id.tab,0,0,m.size);
  if(choix == 2){
    nbcoup=solveur(m,id,p,0)+2; //+2 car on lui laisse un peu plus de chance
  }
  if(choix == 1){
    nbcoup = solveuraleatoire(m,id,p)+2;
  }
  while(!presence(id) && nbcoup!=0){
    affichage(m);
    printf("\nIl vous reste : %i coups\n",nbcoup);
    if(selection(&c,&nbcoup,m.tab[0][0])==0){ //rajouter la couleur de la tache
      free1(m.tab,m.size);
      free1(id.tab,m.size);
      exit(0);
    }
    changement(m,id,c);
    identification(m.tab,id.tab,0,0,m.size);
  }
  if(presence(id)){
    affichage(m);
    printf("\nBravo vous avez gagné!\n"); 
  }
  else{
    if(nbcoup == 0){  
    printf("Vous avez épuisé votre nombre de coups et vous avez perdu!\n");
    }
  }
  free1(m.tab,m.size);
  free1(id.tab,id.size);
}
