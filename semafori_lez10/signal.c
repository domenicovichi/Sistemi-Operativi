#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


void gestore(int signum){
    static int cont = 0;
    printf("processo con pid %d; ricevuti n. %d segnali %d\n", getpid(), ++cont, signum);
}

int main(){
    pid_t pid; 
    signal(SIGUSR1, gestore); 
    pid = fork();
    if(pid == 0)
        for(; ;) pause(); //ciclo for infinito è come while(1)
    else
        for(; ;) {
            kill(pid,SIGUSR1); //invia al processo figlio il segnale SIGSR1
            sleep(1);
        }
}