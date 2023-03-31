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

int argmax(float * values, int length) {
    float maxFreq = -1.0;
    int max_i = -1;
    for (int i = 0;i < length;i++) {
        if (values[i] > maxFreq) {
            maxFreq = values[i];
            max_i = i;
        }
    }
    return max_i;
}

float * periodigramme(float * signal, int length, int sample_size) {
    float * signal_copy = malloc(sizeof(*signal_copy) * sample_size);
    float * somme = malloc(sizeof(float) * sample_size);
    float * im = malloc(sizeof(float) * sample_size);
    float * mod = malloc(sizeof(float) * sample_size);

    for (int i = 0;i < sample_size;i++) {
        somme[i] = 0.0;
        im[i] = 0.0;
        mod[i] = 0.0;
    }


    int num_iter = 0;
    for (int i_sample = 0;i_sample * sample_size / 2 < length;i_sample++) {
        num_iter += 1;
        int offset = i_sample * sample_size / 2;

        // on copie la fenêtre
        for (int i = 0;i < sample_size;i++) {
            signal_copy[i] = signal[i + offset];
            im[i] = 0.0;
            mod[i] = 0.0;
        }
        
        FFT1D(signal_copy, im, sample_size);

        ModVct(mod, signal_copy, im, sample_size);

        for (int i = 0;i < sample_size;i++) {
            somme[i] += mod[i];
        }

        // IFFT1D(signal_copy, im, sample_size);
    }

    // on divise par n
    for (int i = 0;i < sample_size;i++) {
        somme[i] /= num_iter;
    }    
    return somme;
}

float * periodigramme_pondere(float * signal, int length, int sample_size) {
    float * signal_copy = malloc(sizeof(*signal_copy) * sample_size);
    float * somme = malloc(sizeof(float) * sample_size);
    float * im = malloc(sizeof(float) * sample_size);
    float * mod = malloc(sizeof(float) * sample_size);

    for (int i = 0;i < sample_size;i++) {
        somme[i] = 0.0;
        im[i] = 0.0;
        mod[i] = 0.0;
    }


    int num_iter = 0;
    for (int i_sample = 0;i_sample * sample_size / 2 < length;i_sample++) {
        num_iter += 1;
        int offset = i_sample * sample_size / 2;

        // on copie la fenêtre
        for (int i = 0;i < sample_size;i++) {
            signal_copy[i] = signal[i + offset];
            im[i] = 0.0;
            mod[i] = 0.0;
        }
        
        FFT1D(signal_copy, im, sample_size);

        ModVct(mod, signal_copy, im, sample_size);

        for (int i = 0;i < sample_size;i++) {

            // h(t) = 0.54 − 0.46 cos(2π t/T)
            //
            // T = 511
            float ponderation = 0.54 - 0.46 * cos(2 * PI * i / sample_size - 1);
            somme[i] += mod[i] * ponderation;
        }

        // IFFT1D(signal_copy, im, sample_size);
    }

    // on divise par n
    for (int i = 0;i < sample_size;i++) {
        somme[i] /= num_iter;
    }    
    return somme;
}


/*------------------------------------------------*/
/* PROGRAMME PRINCIPAL   -------------------------*/                     
/*------------------------------------------------*/
int main(int argc,char **argv)
{
    int i,j,k;
    int length;
    char BufSystVisuSig[100];


    float * signal = LoadSignalDat("moteur2",&length);
    
    //===============================
    //Question 3.2
    //===============================
    float * moy = periodigramme(signal, length, 512);
    SaveSignalDat("moteur2_periodigramme", moy, 512);
    
    //===============================
    //Question 3.3
    //===============================    
    float * moy_fen = periodigramme_pondere(signal, length, 512);
    SaveSignalDat("moteur2_periodigramme_fenetre", moy_fen, 512);


    float * signal2 = LoadSignalDat("Spectre",&length);
    
    //===============================
    //Question 3.4
    //===============================
    float * moy2 = periodigramme(signal2, length, 512);
    SaveSignalDat("spectre_periodigramme", moy2, 512);
    
    float * moy_fen2 = periodigramme_pondere(signal2, length, 512);
    SaveSignalDat("spectre_periodigramme_fenetre", moy_fen2, 512);

    return 0;
}


