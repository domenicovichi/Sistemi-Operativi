#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <mqueue.h>

#define SERVER_QUEUE_NAME "/mq_server"
#define QUEUE_PERMISSION 0660
#define MAX_MESSAGES 10

struct message{
    int pid;
    char text[64];
} msg_send, msg_rcv;


int main(int argc, char *argv[]){
    mqd_t qd_server, qd_client; //descrittori code
    long serial_number = 1; /*numero seriale da inviare al client*/
    char client_queue_name[16]; //nome coda del client
    struct mq_attr attr; //attributi della coda
    attr.mq_flags = 0; //bloccante quindi sincrono
    attr.mq_maxmsg = MAX_MESSAGES; /*numero massimo di messaggi nella coda*/
    attr.mq_msgsize = sizeof(msg_rcv);
    attr.mq_curmsgs = 0;

    printf("Server: benvenuto! \n");
    qd_server = mq_open(SERVER_QUEUE_NAME, O_RDONLY|O_CREAT, QUEUE_PERMISSION, &attr); //creo un buffer per leggere msg dal client

    while(1){
        /*preleva dalla coda il messaggio con priorità più alta*/
        mq_receive (qd_server, (char*)& msg_rcv,sizeof(msg_rcv),NULL);
        printf("Server: messaggio ricevuto dal client %d, %s. \n",msg_rcv.pid,msg_rcv.text);
        sprintf(client_queue_name,"/mq_%d", msg_rcv.pid);  //salva dentro client_queue name, msg_rcv.pid
        
        /*invia il messaggio di risposta al client*/
        qd_client = mq_open(client_queue_name, O_WRONLY);
        sprintf(msg_send.text, "benvenuto client %d, il tuo numero è %ld", msg_rcv.pid, serial_number);
        mq_send (qd_client, (const char *)&msg_send,sizeof(msg_send), 0);
        printf("server: risposta inviata al client. \n");
        serial_number ++;
    }
}