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
    char client_queue_name[16];
    mqd_t qd_server, qd_client; /*descrittore code*/
    /*crea coda client per ricevere i messaggi dal server*/
    sprintf(client_queue_name, "/mq_%d",getpid());
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = sizeof(msg_send);
    attr.mq_curmsgs = 0;
    qd_client = mq_open(client_queue_name, O_CREAT|O_RDONLY, QUEUE_PERMISSION, &attr);
    /*apre la coda del server per inviare il proprio identificatore*/
    qd_server = mq_open (SERVER_QUEUE_NAME, O_WRONLY);
    printf("Richiedi un numero (premi <INVIO>):");
    char in_buf[10];
    msg_send.pid = getpid();
    if(argc > 1)
        strcpy(msg_send.text,argv[1]); //nickname
    else {
        strcpy(msg_send.text,"Pietro"); //default nickname
    }
    while(fgets (in_buf,2,stdin)){
        //invia msg al server
        mq_send (qd_server, (const char *)&msg_send, sizeof(msg_send),0);
        //riceve risposta dal server
        mq_receive(qd_client, (char *)&msg_rcv, sizeof(msg_rcv),NULL);
        //visualizza messaggio ricevuto dal server
        printf("client: messaggio dal server: %s\n\n",msg_rcv.text);
        printf("richiedi un numero (premi<INVIO>):");
    }
    mq_close(qd_client);
    mq_unlink(client_queue_name);
    printf("client: ciao \n");
}