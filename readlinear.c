#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"readlinear.h"

#define FICHIER "donneesSimplex.txt"
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
  float** matri;  //matrix
  int m = nbLignes() - 1; //number of lines of the matrix
  int n = nbVar();  //number of columuns of the matrix
  FILE * F = NULL;  //file reader
	F = fopen(FICHIER, "r");
  if(F != NULL)
  {
    matri = (float**)malloc(sizeof(float*) * (m+1));  //allocating space for the matrix
    for(int k = 0; k <= m; k++ ){
      matri[k] = (float*)malloc(sizeof(float)* (n+m+1));
    }
    /*
    the reason the number of columns is (n+m+2) is because :
      - m columns for the identity matrix and result column,
      - n columns for nonbasic vars,
      - 1 column for the artificial variable
      - 1 column where the matrix dimensions are stored (to find the dimensions easily)
    */
    matri = setupMatrice(matri, m+1, (n+m+1)); //initialise the matrix

		while(fscanf(F, "%f", &matri[i][j+1]) == 1)
		{
      j++;
      if(j > n-1){
        /*
        result column, since each variable is attributed as soon at the fscanf reads it,
        i must move it afterwards
        */
        matri[i][j+m] = matri[i][j];
        matri[i][j] = 0.0f;
        j = 0;
        i++;
      }
		}

    //identity matrix
    for(int i = 0; i < m; i++){
      for(int j = 0; j < m; j++){
        if(i == j)
          matri[i+1][j+n]= 1;
        else
          matri[i+1][j+n] = 0.0f;
      }
    }
	}
  return matri;
}
