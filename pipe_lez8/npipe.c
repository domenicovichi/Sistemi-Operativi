#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

struct message_t
{
    int numero;
    char text[64];
} msg;

int main(int argc, char *argv[])
{
    int fd, i = 0, n = 10;
    int size = sizeof(msg);
    srand(time(NULL));                    // ottengo diverse sequenze per ogni esecuzione
    mknod("mia_pipe", S_IFIFO | 0666, 0); // crea file FIFO
    if (argc == 2)
        fd = open("mia_pipe", O_WRONLY); // produttore
    else
        fd = open("mia_pipe", O_RDONLY); // consumatore
            strcpy(msg.text, "Auguri");
    for (i = 0; i < n; i++)
        if (argc == 2)
        {
            msg.numero = rand() % 100 + 1; // numero casuale
            printf("produttore: %s %d \n", msg.text, msg.numero);
            write(fd, &msg, size); // scrivo il messaggio in pipe
            sleep(1);              // sospensione per 1 sec
        }
        else
        {                         // consumatore
            read(fd, &msg, size); // legge il messaggio dalla pipe
            printf("consumatore: %s %d \n", msg.text, msg.numero);
            sleep(1);
        }
}
