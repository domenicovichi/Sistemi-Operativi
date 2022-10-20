#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t ret;
    int stato;
    ret = fork();
    printf("pid = %d \n", getpid());
    if(ret == 0){
        //figlio
        execl("./nuovo", "Saluti", "dal processo", "padre",(char *)0);
        printf("exec fallita");
        exit(1);
    } else if (ret > 0) {
        printf(" sono il padre con pid = %d", getpid());
        ret = wait(&stato);
    } else{
        printf("errore fork");  
    }
}