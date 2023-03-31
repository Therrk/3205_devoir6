/*------------------------------------------------------*/
/* Prog    : Tp6_IFT3205.c                              */
/* Auteur  : Justin Veilleux, Élie Leblanc              */
/* Date    : --/--/2010                                 */
/* version :                                            */ 
/* langage : C                                          */
/* labo    : DIRO                                       */
/*------------------------------------------------------*/

/*------------------------------------------------*/
/* FICHIERS INCLUS -------------------------------*/
/*------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "FonctionDemo6.h"

/*------------------------------------------------*/
/* DEFINITIONS -----------------------------------*/   
/*------------------------------------------------*/
#define NAME_VISUALISER "./ViewSig.sh "

/*------------------------------------------------*/
/* PROTOTYPE DE FONCTIONS  -----------------------*/   
/*------------------------------------------------*/

/*------------------------------------------------*/
/* PROGRAMME PRINCIPAL   -------------------------*/                     
/*------------------------------------------------*/
int main(int argc,char **argv)
 {
  int i,j,k;
  int length;
  char BufSystVisuSig[100];

  //===============================
  //Question 2.1.(a)
  //===============================
  float*  Sign1=LoadSignalDat("moteur1",&length);
  float*  Sign1I=fmatrix_allocate_1d(length);
  float*  Sign1M=fmatrix_allocate_1d(length); 
  FFT1D(Sign1,Sign1I,length);
  ModVct(Sign1M,Sign1,Sign1I,length);
  CenterVct(Sign1M,length);
  SaveSignalDat("FFT_Moteur1",Sign1M,length);  

  float maxFreq = -1.0;
  int max_i = -1;
  for (int i = 0;i < length;i++) {
      if (Sign1M[i] > maxFreq) {
          maxFreq = Sign1M[i];
          max_i = i;
      }
  }

  float samplerate = 11025; //en sample/seconde

  float enr_length = ((float)length)/samplerate; // en secondes
  
  int distance_from_center = abs(max_i - (length/2));
  
  float freq = (float)distance_from_center / enr_length;
  
  printf("max = %f at %d\n", maxFreq, max_i);
  printf("fréquence la plus forte = %f\n", freq);
  printf("en tours par minute: %f\n", freq / 2 * 60);
  
   
  return 0; 	 
}


