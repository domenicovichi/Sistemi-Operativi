#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t ret, pid;
    int stato;
    ret = fork();

    if (ret == 0)
    {
        // codice del figlio
        printf("Sono il figlio pid: %d \n", getpid());
        sleep(2); // funzione che sospende per 10 sec il processo
        exit(1);  // l'intero indica lo stato in caso di interruzione volontaria
        //in caso di interruzione forzata, dipende dal segnale ricevuto
        /*
        byte1 byte2 = 00000010000000000 -> con shift (>>) 0000000000000100
        byte 1:00000100
        byte 2:00000000
        */
    }
    else if (ret > 0)
    {
        // codice del padre
        pid = wait(&stato); //sincronizzazione padre figlio
        printf("processo figlio pid: %d terminato \n", pid);
        printf("stato : %d \n", stato);
        if (stato < 256) 
            printf("terminazione forzata: segnale = %d \n", stato);
        else
            printf("terminazione volontaria: segnale = %d \n", stato >> 8);
    }
    else
        printf("fork fallita");
}

