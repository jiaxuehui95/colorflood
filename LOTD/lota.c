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
#include "lota.h"

/**
\file lota.c
\author Julian Le Couster, Emmanuel-Paul Vincent, Xuehui Jia, Amina Zeghida
\brief 
*/

//Dans notre index.html généré par la commande : doxygen Doxyfile 
//  les commentaires Doxygen (/** */ et /*! */ ) disparaissent

/*@requires : rien
  @assigns  : nettoie le terminal
  @ensures  : un écran noir sur terminal*/
/**
   \fn void clean()
   \brief efface l'écran
   \param none
   \return none
*/
void clean(){
  system("clear");
}

/*@requires : rien
  @assigns  : la variable buffer
  @ensures  : retourne le caractère entré par le joueur*/
/**
   \fn char get_carac()
   \brief récupère les valeurs rentrées par l'utilisateur, même s'il rentre plusieurs caractères seul le premier aura une influence sur le jeu
   \param none
   \return la première valeur que l'utilisateur a rentré
*/
char get_carac(){
  char input;
  char buffer[2];
  scanf("%1s",buffer);
  input = buffer[0];
  return input;
}

/*@requires : rien
  @assigns  : rien
  @ensures  : efface tout ce qui est stocké sur le buffer*/
/**
   \fn void vide_buffer()
   \brief vide le buffer utilisé lors de la question get_carac
   \param none
   \return none
*/
void vide_buffer(){
  int c=0;
  while((c!='\n') && (c!=EOF)){
    /*la boucle s'arrête dès qu'un '\n' est aperçu ou s'il arrive à la fin du mot (si l'utilisateur a entré un nom de plus de 9 caractères) */
    c=getchar();
  }
}
/*@requires  : rien
  @assigns   : rien
  @ensures   : vide l'écran et présente jeu*/
/**
   \fn void presentation()
   \brief efface l'écran et affiche le nom du jeu
   \param none
   \return none
*/
void presentation(){
  clean();
  printf("################################################################################\n");
  printf("################################################################################\n");
  printf("################################# Color Flood ##################################\n");
  printf("################################################################################\n");
  printf("################################################################################\n");
}




/*@requires : m valide
  @assigns  : m
  @ensures  : initialise les cases du tableau de m avec des nombres aléatoires entre 1 et 6
*/
/**
   \fn void initialisation(matrice m)
   \brief permet d'initialiser les valeurs de la matrice avec des valeurs aléatoires
   \param m : matrice valide 
   \return none (la matrice est modifier)
*/
void initialisation(matrice m){
  int n=m.size;
  int i,j;
  srand((int)time(0));
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      m.tab[i][j]=rand()%6+1;/*mettre un random*/
    }
  }
}

/*@requires : la taille souhaitée
  @assigns  : demande la place pour créer le plateau
  @ensures  : la matrice mat, avec la mémoire allouée
*/
/**
   \fn matrice allocation(int size)
   \brief permet d'allouer la mémoire du tableau de la matrice en fonction de la taille souhaitée
   \param size : entier représentant la taille souhaitée
   \return la matrice avec la mémoire de son tableau allouée
*/
matrice allocation(int size){
  matrice mat;
  int i,j;
  mat.size=size;
  mat.tab=(int**)malloc(size*sizeof(int*));
  for(i=0;i<size;i=i+1){
    mat.tab[i]=(int*)malloc(size*sizeof(int));
    for(j=0;j<size;j=j+1){
      mat.tab[i][j]=0;}}
  return mat;
}


/**
   \fn void free1(int **tab,int size)
   \brief permet de libérer la mémoire libérer pour une grille
   \param tab : tableau d'entiers valide
   \param size : entier correspondant à la taille du tableau
   \return none
*/
void free1(int **tab,int size){
  int i;
  for(i=0;i<size;i++){
      free(tab[i]);
  }
  free(tab);
}

/*@requires : m valide
  @assigns  : le tableau de m
  @ensures  : initialise le tableau à partir d'un fichier*/
/**
   \fn matrice initialisationfichier1(matrice m)
   \brief permet d'initialiser les valeurs de la matrice à partir d'un fichier, en récupérant son nom 
   \param m : matrice valide
   \return la matrice initialisée à partir des valeurs du fichier dont le nom a été rentré par l'utilisateur
*/
matrice initialisationfichier1(matrice m){
  int i,j,r;
  char* argv = (char*) malloc(10*sizeof(char));
  char* buf=(char*) malloc(sizeof(char));
  printf("Quel fichier souhaitez-vous ouvrir (Le nom ne doit pas faire plus de 10 lettres)?\n");
  scanf("%s",argv);
  int fdin=open(argv,O_RDONLY);
  if(fdin==-1){
    fprintf(stderr,"initialisation fichier : fail open %s\n",strerror(errno));
    exit(1);
  }
  for(i=0;i<m.size;i++){
    for(j=0;j<m.size;j++){
      r=read(fdin,buf,1);
      if(r!=1){
	printf("Il y a eu un problème lors de la lecture !\n Le fichier n'est peut être pas assez long\n");
	free(argv);
	free(buf);
	free1(m.tab,m.size);
	close(fdin);
	exit(1);
      }
      m.tab[i][j]=atoi(buf);
    }
  }
  free(argv);
  free(buf);
  close(fdin);
  return m;
}

/*@requires : m valide
  @assigns  : le fichier
  @ensures  : créer le fichier ou le remplace, et on y stocke les valeurs du tableau de la matrice */
/**
   \fn void create_fichier1(matrice m)
   \brief permet de créer un fichier et de stocker les valeurs du tableau de la matrice dans ce fichier, on demande le nom de ce fichier à l'utilisateur et si un fichier porte déjà ce nom alors il est remplacé
   \param m : matrice valide
   \return none (le fichier a été crée)
*/
void create_fichier1(matrice m){
  char *argv = (char*) malloc(10*sizeof(char));
  int i,j,r;
  char* buf = (char*) malloc(255*sizeof(char));
  printf("\nComment voulez-vous nommer le fichier ?\n");
  printf("(le nom ne doit pas faire plus de 10 lettres)\n");
  printf("Attention ! S'il existe déjà un fichier de ce nom, il sera supprimé!\n");
  scanf("%s",argv);
  int fdout = open(argv,O_WRONLY|O_TRUNC|O_CREAT, 0666);
  if(fdout==-1){
    fprintf(stderr,"create_fichier : fail open %s\n",strerror(errno));
    exit(1);
  }
  for(i=0;i<m.size;i++){
    for(j=0;j<m.size;j++){
      sprintf(buf,"%d",m.tab[i][j]);
      r=write(fdout,buf,1);
      if(r!=1){
	printf("Il y a eu un problème lors de l'écriture !\n");
	free(argv);
	free(buf);
	free1(m.tab,m.size);
	close(fdout);
	exit(1);
      }
    }
  }
  close(fdout);
  free(argv);
  free(buf);

}



/*
@requires : m valide, c appartient à [1,6]
@assigns  : le tableau de m à la coordonnée x,y
@ensures  : la matrice m avec sa coordonnée x,y modifiée
*/
/**
   \fn matrice remplace(matrice m, int x, int y, int c)
   \brief remplace la valeur de coordonnées (x,y) dans le tableau de la matrice m par la valeur c
   \param m : matrice valide
   \param x : entier représentant la ligne du tableau de la matrice
   \param y : entier représentant la colonne du tableau de la matrice
   \param c : entier représentant la couleur qui va apparaitre dans la matrice (entre 1 et 6)
   \return la matrice modifiée
*/
matrice remplace(matrice m, int x, int y, int c){
  m.tab[x][y]=c;
  return m;
}

/*
@requires : rien
@assigns  : rien
@ensures  : retourne la couleur correspondant à l'entier passé en paramètre et 'F' sinon il ne correspond à rien
*/
/**
   \fn char itoc(int i)
   \brief convertit un entier en caractère en fonction des caractères souhaités et F si l'entier ne correspond à rien
   \param i : entier représentant une couleur
   \return le caractère correspondant à la couleur représentée par l'entier 
*/
char itoc(int i){
  switch(i){
  case 1 : return 'B';;
  case 2 : return 'V';;
  case 3 : return 'R';;
  case 4 : return 'J';;
  case 5 : return 'M';;
  case 6 : return 'G';;
  }
  return 'F';
}


/*
@requires : rien
@assigns  : rien
@ensures  : retourne l'entier correspond à la couleur passé en paramètre et 0 si elle ne correspond à rien
*/
/**
   \fn int ctoi(char c)
   \brief convertit un caractère en entier en fonction des caractères souhaités et 0 si le caractère ne correspond à rien
   \param i : caractère représentant une couleur
   \return l'entier correspondant à la couleur représentée par le caractère
*/
int ctoi(char c){
  switch(c){
  case 'B' : return 1;;
  case 'V' : return 2;;
  case 'R' : return 3;;
  case 'J' : return 4;;
  case 'M' : return 5;;
  case 'G' : return 6;;
  }
  return 0;
}


/*
@requires : m et flag valide
@assigns  :  matrix: le matrix original
       flag:le matrix pour indiquer le status,1->même couleur que matrix[0][0],0->pas de même couleur ,-1->pas encore passer cette case.
        x,y:coordonne de case , et à partir cette case , on recherche ses voisins par récusif function identification
@ensures  : rien
*/

/**
   \fn void identification (int ** matrix,int** flag,int x,int y,int size)
   \brief Trouve la tâche de la couleur de la case du coin supérieur gauche, et change le flag : 1 si la case appartient à la tâche, 0 sinon et -1 si elle n'a pas été testée. 
   \param **matrix : tableau représentant le tableau d'une matrice (le jeu)
   \param **flag : tableau représentant le tableau de la matrice d'identification
   \param x : entier correspondant à  la ligne à tester
   \param y : entier correspondant à  la colonne à tester
   \param size : entier correspondant à la taille du tableau de la matrice   
   \return none (le tableau flag est modifiée pour toutes les valeurs de x et y)
*/
void identification (int ** matrix,int** flag,int x,int y,int size){
  if(x==0&&y==0){
      flag[0][0]=1;
       identification(matrix,flag,x+1,y,size  );
       identification(matrix,flag,x  ,y+1,size);}
 if(x>=0&&x<size&&y>=0&&y<size)
   {
	  if(flag[x][y]==-1)
	    {
	      if(matrix[x][y]==matrix[0][0]){
		  flag[x][y]=1;
		  if(x<size-1)
		    {identification(matrix,flag,x+1,y  ,size);}/*droit*/
		  if(x>0)
		    {identification(matrix,flag,x-1,y  ,size);}/*gauche*/
		  if(y>0)
		    {identification(matrix,flag,x  ,y-1,size);}/*haut*/
		  if(y<size-1)
		    {identification(matrix,flag,x  ,y+1,size);}/*dessous*/
	      }
	      else {
		  flag[x][y]=0;
		  return ;
	      }}
	  else return ;
            }
}





/*
@requires : m et id valide, c appartient à [1,6]
@assigns  : m
@ensures  : retourne la matrice m dont les cases du tableau correspondent à la couleur passée en paramètre si il y a un 1 dans la case correspondante de la matrice id (la case de m est inchangée sinon)
*/
/**
   \fn matrice changement(matrice m, matrice id, int c)
   \brief modifie les valeurs du tableau de la matrice par c si il y a un 1 dans la case associée du tableau de la matrice id (c'est à dire si la case appartient à la tâche de couleur) 
   \param m : matrice valide
   \param id : matrice valide
   \param c : entier représentant une couleur, appartient à [1,6]
   \return la matrice modifiée avec une tâche de couleur c
*/
matrice changement(matrice m, matrice id, int c){
  int i, j;
  int n = m.size;
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      if(id.tab[i][j]==1){
	id.tab[i][j]=-1;
	remplace(m,i,j,c);
      }
      if(id.tab[i][j]==0){
	id.tab[i][j]=-1;
      }
    }
  }
  return m;
}

/*
@requires : id valide
@assigns  : rien
@ensures  : renvoie 1 si toutes les cases du tableau de id sont égales à 1 (c'est à dire si le joueur a gagné), 0 sinon
*/
/**
   \fn int presence(matrice id)
   \brief renvoie 1 si le jeu est terminé c'est à dire s'il y a des 1 partout dans la matrice d'identification
   \param id : matrice valide
   \return 1 si l'utilisateur a gagné,0 sinon
*/
int presence(matrice id){
  int i, j;
  int n = id.size;
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      if(id.tab[i][j]!=1){
	return 0;
      }
    }
  }
  return 1;
}



