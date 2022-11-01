/*Il thread main crea due thread th1 e th2 e attende la loro terminazione. I due thread eseguono concorrentemente la stessa funzione codice_T.*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// variabili condivise
char MSG[] = "Ciao!";
void *codice_T(void *arg)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        printf("Thread %s: %s\n", (char *)arg, MSG);
        sleep(1); /*sospensione 1 sec*/
    }
    pthread_exit(0);
}

int main()
{
    pthread_t th1, th2;
    int ret;
    /*creazione del primo thread*/
    if (pthread_create(&th1, NULL, codice_T, "1") < 0)
    {
        fprintf(stderr, "errore di creazione thread 1 \n");
        exit(1);
    }
    /*creazione secondo thread*/
    if (pthread_create(&th2, NULL, codice_T, "2") < 0)
    {
        fprintf(stderr, "errore di creazione thread 2 \n");
        exit(1);
    }
    ret = pthread_join(th1, NULL);
    if (ret != 0)
        fprintf(stderr, "join fallito %d \n", ret);
    else
        printf("terminato il thread 1 \n");
    ret = pthread_join(th2, NULL);
    if (ret != 0)
        fprintf(stderr, "join fallito %d \n", ret);
    else
        printf("terminato il thread 2 \n");
    return 0;
}