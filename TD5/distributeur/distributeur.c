#include <pthread.h>
#include "distributeur.h"

static int indice = 0;
pthread_mutex_t m;
int distributeur_suivant()
{
    pthread_mutex_lock(&m);
    indice ++;
    pthread_mutex_unlock(&m);
    return indice;
}


int distributeur_valeur()
{
    return indice;
}


void raz()
{
    indice = 0;
}
