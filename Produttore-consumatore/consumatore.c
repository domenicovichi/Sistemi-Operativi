#include<stdio.h>
#include<stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(){
    const int SIZE = 4096; //dimensione del segmento condiviso
    const char *nome = "MEMCOND"; //nome del segmento condiviso 
    int shm_fd; //descrittore del segmento condiviso

    void *shm_ptr; //puntatore al segmento condiviso
    shm_fd = shm_open (nome, O_RDONLY, 0666);
    shm_ptr = mmap(0,SIZE,PROT_READ,MAP_SHARED,shm_fd,0);
    printf("%s",(char *) shm_ptr);
    shm_unlink(nome);
    return 0;
}