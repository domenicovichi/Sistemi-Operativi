#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int ns = 1; //periodo iniziale di allarme
int nmax = 10; //valore massimo dell'intervallo di allarme

void azione(){
    /*questa funzione viene eseguita ogni volta che il processo riceve il segnale SIGALARM*/
    printf("segnale di allarme ricevuto.. eseguo date \n");
    system("date"); //eseguo comando date

    /*riassegnamento del periodo di allarme che cancella il precedente periodo assegnato*/

    alarm(ns);//ns viene incrementato
}

int main(){
    int i;
    signal(SIGALRM,azione);
    alarm(ns);
    while(ns <= nmax){
        printf("processo in pausa\n");
        pause();
        printf("fine pausa \n");
        ns++; //incremento periodo di allarme
    }
    exit(0);
}