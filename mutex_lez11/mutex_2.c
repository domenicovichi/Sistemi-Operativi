/* Il thread maincrea una matrice di numeri interi di dimensione NxMassegnando a ciascun elemento della matrice un valore casuale compreso tra 0 e 255. Dopo aver creato la matrice, il thread maincrea N thread figli ciascuno dei quali ha il compito di eseguire la somma di una riga della matrice. Ciascun thread aggiunge la somma che ha calcolato ad una variabile di nome sommaMatche al termine dell'esecuzione del programma conterrà la somma di tutti gli elementi della matrice. Il valore della variabile sommaMatdeve essere stampato su video dal thread main. */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N 20
#define M 1024

pthread_mutex_t mut; /*mutex condiviso tra thread*/
int a[N][M];
int sommaMat = 0;

void *sommaRiga_th(void *arg){
    int i = (int)arg;
    int j;
    int sommaRiga=0;
    for(j=0;j<M;j++)
        sommaRiga+=a[i][j];
    pthread_mutex_lock(&mut); /*prologo sez critica*/
    sommaMat += sommaRiga;
    printf("thread %d: sommaRiga=%d, somma = %d\n",i,sommaRiga,sommaMat);
    sleep(1);
    pthread_mutex_unlock(&mut); /*epilogo sez critica*/
    pthread_exit(0);
}

int main(){
    int i,j;
    pthread_t th[N];
    pthread_mutex_init(&mut,NULL);
    srand(time(NULL));
    for(i=0; i<N; i++)
        for(j=0; j<M; j++)
            a[i][j] = rand()%256;
    for(i=0;i<N;i++)
        if(pthread_create(&th[i],NULL,sommaRiga_th,(int *)i)!=0){
            fprintf(stderr, "errore create thread i \n");
            exit(1);
        }
    for(i=0;i<N;i++)
        pthread_join(th[i],NULL);
    fprintf("Somma = %d \n",sommaMat);
}