#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"readlinear.h"
#define MAX_INT 2147483647
#define M  nbLignes()
#define N  nbLignes() + nbVar()

/*
  function to display the matrix in the terminal
*/

void afficher_matrice(float** mat){
  for(int i = 0; i < M; i++){
    for(int j = 0; j < N; j++){
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
  for (int i = 0; i < N; i++){
    if(matri[0][i] != 0 && matri[0][i] > 0){
      return i;
    }
  }
  return -1;
}

/*
  function to find the active constraint during each step
*/

int trouverCA(float** matri, int ve){
  int pos;
  int res = MAX_INT;
  for(int i = 1; i < nbLignes(); i++){
    if(matri[i][ve] != 0){
      if(res > matri[i][N-1]/matri[i][ve] && matri[i][N-1]/matri[i][ve] > 0){
        res = matri[i][N-1]/matri[i][ve];
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
	int i;
	int j;
	float pivot = matri[ca][ve];
	float coeff;

  for(i = 0; i < M; i++){

    if(i != ca){
      coeff = (matri[i][ve]/pivot);

      for(j = 0; j < N; j++){
        matri[i][j] -= (matri[ca][j] * coeff);
      }
    }
  }
  }

/*
  function that runs until the simplex algorithm is finished
*/

float** simplex(float** matri){
  while(trouverVE(matri) != -1){
    int ve = trouverVE(matri);
    int ca = trouverCA(matri, ve);
    printf("entering variable : %d, active constraint : %d \n", ve, ca);
    pivot_gauss(matri,ve,ca);
    afficher_matrice(matri);
  }
  return matri;
}

int main()
{
  float** matri = NULL;
  matri = lect_donnees();
  afficher_matrice(matri);
  matri = simplex(matri);
  printf("\n the result is %f", matri[0][N-1]);
}
