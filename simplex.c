
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FICHIER "donneesSimplex.txt"
#define MAX_INT 2147483647

/*
  initialise the matrix at 0
*/

float** setupMatrice(float** mat, int m, int n){
  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j ++){
      mat[i][j] = 0.0f;
    }
  }
  return mat;
}

/*
  Read the number of constraints
*/

int nbLignes(){
  int lines = 0;
  int ch = 0;
  FILE * F = NULL;
  F = fopen(FICHIER, "r");
  if(F != NULL)
  {
    while(!feof(F))
    {
      ch = fgetc(F);
      if(ch == '\n')
      {
        lines++;
      }
    }
    fclose(F);
  }
  return lines;
}

/*
  read the number of nonbasic variables
*/

int nbVar(){
  int vals = 0;
  float ch = 0;
  FILE * F = NULL;
  F = fopen(FICHIER, "r");
  if(F != NULL)
  {
    while(fscanf(F, "%f", &ch) == 1)
    {
      vals++;
    }
    fclose(F);
  }
  return vals/nbLignes();
}

/*
  Read the data in the text file and create the corresponding standart matrix
*/

float** lect_donnees(){
  int i = 0;  //used to describe the actual line
  int j = 0;  //used to describe the actual column
  float** A;  //matrix
  int m = nbLignes() - 1; //number of lines of the matrix
  int n = nbVar();  //number of columuns of the matrix
  FILE * F = NULL;  //file reader
	F = fopen(FICHIER, "r");
  if(F != NULL)
  {
    A = (float**)malloc(sizeof(float*) * (m+1));  //allocating space for the matrix
    for(int k = 0; k <= m; k++ ){
      A[k] = (float*)malloc(sizeof(float)* (n+m+2));
    }
    /*
    the reason the number of columns is (n+m+2) is because :
      - m columns for the identity matrix and result column,
      - n columns for nonbasic vars,
      - 1 column for the artificial variable
      - 1 column where the matrix dimensions are stored (to find the dimensions easily)
    */
    A = setupMatrice(A, m+1, (n+m+2)); //initialise the matrix

		while(fscanf(F, "%f", &A[i][j+1]) == 1)
		{
      j++;
      if(j > n-1){
        /*
        result column, since each variable is attributed as soon at the fscanf reads it,
        i must move it afterwards
        */
        A[i][j+m] = A[i][j];
        A[i][j] = 0.0f;
        j = 0;
        i++;
      }
		}

    //identity matrix
    for(int i = 0; i < m; i++){
      for(int j = 0; j < m; j++){
        if(i == j)
          A[i+1][j+n]= 1;
        else
          A[i+1][j+n] = 0.0f;
      }
    }
    //attribution of the matrix dimensions
    A[0][n+m+1] = m+1;
    A[1][n+m+1] = (n+m+1);
	}
  return A;
}

/*
  function to display the matrix in the terminal
*/

void afficher_matrice(float** mat, int m, int n){
  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      if(mat[i][j]-(int)mat[i][j] <= 0.01 && mat[i][j]-(int)mat[i][j] >= -0.01)
        printf("[%d]\t", (int)mat[i][j]);
      else
        printf("[%0.2f]\t",mat[i][j]);
    }
    printf("\n");
  }
}

/*
  function to find the entering variable during each step
*/

int trouverVE(float** matri){
  for (int i = 0; i < (int)matri[1][nbVar()+nbLignes()]; i++){
    if(matri[0][i] != 0 && matri[0][i] > 0){
      return i;
    }
  }
  return -1;
}

/*
  function to find the active constraint during each step
*/

int trouverCA(float** matri, int ve, int n){
  int pos;
  int res = MAX_INT;
  for(int i = 1; i < nbLignes(); i++){
    if(matri[i][ve] != 0){
      if(res > matri[i][n]/matri[i][ve] && matri[i][n]/matri[i][ve] > 0){
        res = matri[i][n]/matri[i][ve];
        pos = i;
      }
    }
  }
  return pos;
}

/*
  Methode qui va effectuer le pivot de gauss
*/

void pivot_gauss(float** matri, int ve, int ca)
{
  int m = (int)matri[0][nbVar()+nbLignes()];
  int n = (int)matri[1][nbVar()+nbLignes()];
	int i;
	int j;
	float pivot = matri[ca][ve];
	float coeff;

  for(i = 0; i < m; i++){

    if(i != ca){
      coeff = (matri[i][ve]/pivot);

      for(j = 0; j < n; j++){
        matri[i][j] -= (matri[ca][j] * coeff);
      }
    }
  }
  }

/*
  function that runs until the simplex algorithm is finished
*/

float** simplex(float** matri, int n){
  while(trouverVE(matri) != -1){
    int ve = trouverVE(matri);
    int ca = trouverCA(matri, ve, n);
    printf("entering variable : %d, active constraint : %d \n", ve, ca);
    pivot_gauss(matri,ve,ca);
    afficher_matrice(matri, (int)matri[0][nbVar()+nbLignes()], (int)matri[1][nbVar()+nbLignes()]);
  }
  return matri;
}

int main()
{
  float** matri = NULL;
  matri = lect_donnees();
  int m = (int)matri[0][nbVar()+nbLignes()];
  int n = (int)matri[1][nbVar()+nbLignes()];
  afficher_matrice(matri, m, n);
  simplex(matri, n-1);
}
