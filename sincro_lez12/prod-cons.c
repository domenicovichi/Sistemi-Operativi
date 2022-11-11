#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define FINE (-1)
#define DIM 10
#define MAX 20

typedef struct
{
    int messaggio[DIM]; // i messaggi sono valori interi quindi li salviamo in un vettore
    pthread_mutex_t M;
    int leggi, scrivi;
    int cont;
    pthread_cond_t PIENO;
    pthread_cond_t VUOTO;
} buffer_t;

// buffer globale
buffer_t buf;

void init(buffer_t *buf);
void produci(buffer_t *buf, int mes);
int consuma(buffer_t *buf);

// inizializzo il buffer con i valori di default
void init(buffer_t *buf)
{
    pthread_mutex_init(&buf->M, NULL);
    pthread_cond_init(&buf->PIENO, NULL);
    pthread_cond_init(&buf->VUOTO, NULL);
    buf->cont = 0;
    buf->leggi = 0;
    buf->scrivi = 0;
}

void produci(buffer_t *buf, int mes)
{
    // blocca il buffer
    pthread_mutex_lock(&buf->M);
    // Il buffer è pieno? se si, aspetta
    if (buf->cont == DIM)
    {
        // il thread che chiama la wait viene sospeso fintanto che &buf->PIENO(vedi lez 11, &buf->PIENO è una condizione)
        pthread_cond_wait(&buf->PIENO, &buf->M);
    }
    // scrivi il messaggio nell'indice 'scrivi' del vettore
    buf->messaggio[buf->scrivi] = mes;
    // incrementa l'attuale dimensione del buffer in utilizzo
    buf->cont++;
    // incrementa l'indice per poter scrivere il prossimo valore
    buf->scrivi++;
    // la gestione del buffer è circolare
    if (buf->scrivi == DIM)
    {
        buf->scrivi = 0;
    }
    // risveglia un evenutale thread consumatore sospeso
    pthread_cond_signal(&buf->VUOTO);
    pthread_mutex_unlock(&buf->M);
}

int consuma(buffer_t *buf)
{
    int mes;
    // blocca il buffer
    pthread_mutex_lock(&buf->M);
    // il buffer è vuoto?
    if (buf->cont == 0)
    {
        // vedi sopra
        pthread_cond_wait(&buf->VUOTO, &buf->M);
    }
    // leggi il messaggio e aggiorna lo stato del buffer
    mes = buf->messaggio[buf->leggi];
    // il messaggio è stato letto
    buf->cont--;
    // il prossimo messaggio da leggere si trova nell'indice successivo
    buf->leggi++;
    // la gestione è circolare
    if (buf->leggi >= DIM)
    {
        buf->leggi = 0;
    }
    // risveglia un eventuale thread produttore
    pthread_cond_signal(&buf->PIENO);
    pthread_mutex_unlock(&buf->M);
    return mes;
}

void *produttore(void *arg)
{
    int n;
    for (n = 0; n < MAX; n++)
    {
        printf("Produttore %d -> %d\n", (int)arg, n);
        produci(&buf, n);
        sleep(1);
    }
    // aggiungi -1 quando finisci di scrivere sul buffer
    produci(&buf, FINE);
}

void *consumatore(void *arg)
{
    int d;
    while (1)
    {
        d = consuma(&buf);
        // quando legge -1 vuol dire che il vettore è svuotato
        if (d == FINE)
            break;
        printf("%d <- consumatore %d\n", d, (int)arg);
        sleep(2);
    }
}

int main()
{
    int i;
    int nprod = 1, ncons = 1;
    pthread_t prod[nprod], cons[ncons];
    init(&buf);

    // creazione thread
    for (i = 0; i < nprod; i++)
    {
        pthread_create(&prod[i], NULL, produttore, (void *)i);
    }
    for (i = 0; i < ncons; i++)
    {
        pthread_create(&cons[i], NULL, consumatore, (void *)i);
    }

    // attesa terminazione thread creati
    for (i = 0; i < nprod; i++)
    {
        pthread_join(prod[i], NULL);
    }
    for (i = 0; i < ncons; i++)
    {
        pthread_join(cons[i], NULL);
    }
    return 0;
}