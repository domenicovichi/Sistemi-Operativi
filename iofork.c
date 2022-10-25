#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t ret = fork();
    if (ret == 0)
    {
        printf("sono il figlio con pid: %d \n", getpid());
        usleep(2);
    }
    else if (ret > 0)
    {
        printf("sono il padre con pid: %d \n", getpid());
        usleep(10);
        printf("sono il padre2 con pid: %d \n", getpid());
    }
}