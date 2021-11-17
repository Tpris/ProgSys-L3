#include <pthread.h>
#include "distributeur.h"

static int indice = 0;

int distributeur_suivant()
{
    int i;
    pthread_mutex_lock(&m);
    i = indice ++;
    pthread_mutex_unlock(&m);
    return i;
}


int distributeur_valeur()
{
    return indice;
}


void raz()
{
    pthread_mutex_lock(&m);
    indice = 0;
    pthread_mutex_lock(&m);
}

/**
 * pb avec 
 * lock
 * ind ++
 * unlock
 * lock
 * ind++
 * unlock
 * return ind
 * return ind 
 * 
 * PB raz non protégé
 * 
 * ld 11
 * inc 12
 * sto 0
 * sto 12
 * 
 * 
 * Si étude f(x)=y
 * lock 
 * x++
 * y++
 * unlock
 * 
 * puis pour consultation :
 * lock
 *  monX = x
 *  monY = y
 * unlock
 * sinon risque de x != y
 * 
 * Bareme sur 23 :
 * 2.5 2.5 5 4 4
 **/
