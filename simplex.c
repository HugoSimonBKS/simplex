
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FICHIER "donneesSimplex.txt"

/*
  lit les variables du probleme en forme canonique
*/

float** setupMatrice(float** mat, int m, int n){
  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j ++){
      mat[i][j] = 0;
    }
  }
  return mat;
}

/*
  lit le nombre de contraintes + la ligne du probleme
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
  Compte le nb de var par ligne
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

/*printf("val + %d", nbval);
  lit les donnees du simplex et les mets dans une matrice
*/

float** lect_donnees(){
  int nbval = 0;
  int i = 0;
  int j = 0;
  float* c;
  float* b;
  float** A;
  int m = nbLignes() - 1;
  int n = nbVar();
  float charactu;
  FILE * F = NULL;
	F = fopen(FICHIER, "r");
  if(F != NULL)
    {
    A = (float**)malloc(sizeof(float*) * (m+1));
    for(int k = 0; k <= m; k++ ){
      A[k] = (float*)malloc(sizeof(float)* (1+n+m+1));
    }
    //(1+n+m+1)
    A = setupMatrice(A, m+1, (1+n+m+1)+1);
		while(fscanf(F, "%f", &A[i][j+1]) == 1)
		{
      nbval++;
      j++;
      if(j > n-1){
        //contraintes
        A[i][j+m] = A[i][j];
        A[i][j] = 0;
        j = 0;
        i++;
      }
		}
    //matrice identite
    for(int i = 0; i < m; i++){
      for(int j = 0; j < m; j++){
        if(i == j)
          A[i+1][j+n]= 1;
        else
          A[i+1][j+n] = 0;
      }
    }
    //on met les dimensions de la matrice dans la derniere col
    A[0][n+m+2] = m+1;
    A[1][n+m+2] = 1+n+m+1;
	}
  return A;
}

void afficher_matrice(float** mat, int m, int n){
  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      if(mat[i][j] != 0)
        printf("[%f]",mat[i][j]);
      else
        printf("[0]");
    }
    printf("\n");
  }
}

int trouverVE(float** matri){
  for (int i = 0; i < (int)matri[1][nbVar()+nbLignes()+1]; i++){
    if(matri[0][i] != 0 && matri[0][i] > 0){
      return i;
    }
  }
  return -1;
}
int trouverCA(float** matri, int VE){
  res = 0
  for(int i = 0; i < nbLignes() -1; i++){

    res = matri matri[i][VE]
  }
}

float** simplex(float** matri){
  while(trouverVE(matri) != -1){
    int ve = trouverVE(matri);
    int ca = trouverCA(matri, ve);
  }
  return matri;
}

int main()
{


  float** matri = NULL;
  matri = lect_donnees();
  int m = (int)matri[0][nbVar()+nbLignes()+1];
  int n = (int)matri[1][nbVar()+nbLignes()+1];
  afficher_matrice(matri, m,n);
}
