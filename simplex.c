#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#include"readlinear.h"
#define MAX_INT 2147483647
#define M  nbLignes()
#define N  nbLignes() + nbVar()

/*todo :  1 finish 1st phase
          2 make a GUI
          3 make it so it can read canonical form
*/

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
    int num = matri[i][N-1];
    int den = matri[i][ve];
    if(den != 0){
      if(res > num/den && num/den > 0){
        res = num/den;
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
  function that runs the second phase
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

/*
  function that read the solution matrix to find the values of the non basic variables to get the result
*/

float* findRes(float** matri){
  float* res = NULL;
  res = (float*)malloc(sizeof(float)*(nbVar()-1));
  for(int k = 0; k < nbVar()-1; k++)
    res[k] = 0;
  for(int i = 1; i < M; i++){
    for(int j = 1; j < nbVar(); j++){
      if(matri[i][j] == 1){
        res[j-1] = matri[i][N-1];
      }
      else if(matri[i][j] != 0 && matri[i][N-1] != 0 && matri[0][j] == 0){
        res[j-1] = matri[i][N-1]/matri[i][j];
      }
    }
  }
  return res;
}

/*
  function that returns the absolute value of a float
*/

float absol(float val){
  if(val < 0)
    return (val * -1.0f);
  else
    return val;
}

/*
  function that returns an array in which each cell correspond to a constraint and if it is
  equals to 1, it means that the constraint is negative
*/

int* checkFirstPhase(float** matri){
  int* i = NULL;
  i = malloc(sizeof(int)*(M))
  for (int j = 1; j < count; j++) {
    if(matri[j][N-1] < 0)
      i[j] = 1;
    else
      i[j] = 0;
  }
  return (i);
}

/*
  function that find the values of the eventual artificial variables
*/

float** firstphase(float** matri){
  int* ligneNeg = NULL;
  ligneNeg = checkFirstPhase(matri);
  int checkCursor = 1;

  while (checkCursor < M && ligneNeg[checkCursor] == 0){
    checkCursor++;
  }

  if(checkCursor == M){
    return matri;
  }

  else{
    float* tempObj = NULL;
    tempObj = matri[0];
    matri[0][0] = 1

    for(int i = 1; i < N; i++){
      matri[0][i] = 0;
    }

    for(int i = 1; i < M; i++){
      matri[ligneNeg[i]][0] = -1.0f;
    }
    return matri;
  }
}

int main()
{
  float** matri = NULL;
  matri = lect_donnees();
  afficher_matrice(matri);
  matri = simplex(matri);
  printf("\n the result is %f", absol(matri[0][N-1]));
  float* res = NULL;
  res = findRes(matri);
  for (int i = 0; i < nbVar()-1; i++) {
    printf("\t x%d = %f", i+1, res[i]);
  }
}
