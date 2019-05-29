#include <io.h>
#include <stdio.h>
#include <winsock2.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* threadFunction(void* arg);
void* respondRequisitions(void* arg);

char queue[50][512];
int lastOnTheQueue;

int main(){
    //Inicializa o buffer de requisição.
    char request[512];

    //Inicializa os sockets do c para o windows.
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    struct sockaddr_in caddr;

    //Coloca o IP e a porta do servidor, baseado em variáveis padrões dos sockets.
    struct sockaddr_in saddr = {
        .sin_family      = AF_INET,
        .sin_addr.s_addr = htonl(INADDR_ANY),
        .sin_port        = htons(5000)
    };

    //Cria o socket de servidor, com os endereços padrões.
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if(server == -1){
        printf("Socket creation failed!");
        return -1;    
    }
    else{
        printf("Socket created. Server started.\n");
    } 
    int client, x;
    int csize  = sizeof caddr;

    //Aloca o socket recém criado ao IP e porta designados acima.
    bind(server, (struct sockaddr *) &saddr, sizeof saddr);

    //Deixa o servidor "ouvindo" as requisições.
    listen(server, 5);

    pthread_t thread;
    pthread_create(&thread, NULL, respondRequisitions, NULL);

    //Loop infinito para aceitar requisições.
    while(1){
        printf("Started accepting requests.\n");
        //Zera o buffer para que em cada requisição se tenha um buffer novo.
        memset(request, 0, 512);

        //Aceita uma conexão de um cliente.
        client = accept(server, (struct sockaddr *) &caddr, &csize);
        if(client < 0){
            printf("Error while accepting request.");
            return -1;
        }
        else{
            printf("Request accepted!\n");
        }
        while(1){
            //Recebe e printa na tela os bytes da requisição do cliente.
            x = recv(client, request, sizeof request, 0);
            printf("Request message: %s", request, x);
            if(x<1) break;
        }
        pthread_t thread[10];
        int num[10];
        int threadCreated;

        /*int j = 0;
        for(j = 0; j < 10; j++){
            num[j] = j;
            threadCreated = pthread_create(&thread[j], NULL, threadFunction, &num[j]);
        }
        for(j = 0; j < 10; j++){
            pthread_join(thread[j], NULL);
            printf("thread %d ended\n", j);
        }*/

        closesocket(client);

        printf("Request ended.\n");
    }

	return 0;
}



void* threadFunction(void* arg){
    int *k = (int*) arg;
    int j = *k;
    sleep(10*j);
    printf("THREAD TERMINADA");
}


void* respondRequisitions(void* arg){
    pthread_t threads[10];
    int usedThreads[10];

    pthread_t thread;
    int x = 1;
    pthread_create(&thread, NULL, threadFunction, &x);
    while(1){

    }
}