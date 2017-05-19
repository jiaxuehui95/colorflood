typedef struct matrice{
  int size;
  int** tab;} matrice;

void clean();

char get_carac();

void vide_buffer();

void presentation();
 
void initialisation(matrice m);
 
matrice allocation(int size);

void free1(int **tab,int size);
 
matrice initialisationfichier1(matrice m);
 
void create_fichier1(matrice m);

matrice remplace(matrice m, int x, int y, int c);

char itoc(int i);
 
int ctoi(char c);

void identification (int ** matrix,int** flag,int x,int y,int size);

matrice changement(matrice m, matrice id, int c);

int presence(matrice id);
