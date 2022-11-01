/*Semplice struttura di un’applicazione multithread. Il thread main crea un insieme di thread (nell’esempio 2) e attende la loro terminazione. Ciascun thread inizia la sua esecuzione dalla funzione indicata nel terzo parametro della system call pthread_create().*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int a = 0;
char buffer[1024]; /*variabili globali condivise tra i thread*/

void *codice_th1(void *arg)
{
    printf("ciao, sono il thread 1\n");
    pthread_exit(0);
}

void *codice_th2(void *arg)
{
    printf("ciao, sono il thread 2 \n");
    pthread_exit(0);
}

int main()
{
    pthread_t th1, th2;
    int ret;
    // creazione e attivazione del primo thread
    if (pthread_create(&th1, NULL, codice_th1, "") != 0)
    {
        fprintf(stderr, "Errore di creazione thread 1 \n");
        exit(1);
    }
    // creazione e attivazione del secondo thread
    if (pthread_create(&th2, NULL, codice_th2, "") != 0)
    {
        fprintf(stderr, "Errore di creazione thread 2 \n");
        exit(1);
    }
    // attesa della terminazione del primo thread
    ret = pthread_join(th1, NULL);
    if (ret != 0)
        fprintf(stderr, "join fallito %d \n", ret);
    else
        printf("ret: %d \n", ret);
    printf("terminato il thread 1 \n");

    // attesa della terminazione del secondo thread
    ret = pthread_join(th2, NULL);
    printf("ret: %d \n", ret);
    if (ret != 0)
        fprintf(stderr, "join fallito %d \n", ret);
    else
        printf("terminato il thread 2 \n");
}
