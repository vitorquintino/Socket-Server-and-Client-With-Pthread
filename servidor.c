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

void* requisitionResponder(void* arg);
void* respondRequisitions(void* arg);
int threadAvailable();
int getAvailableThread();

char queue[50][512];
int lastOnTheQueue;
int usedThreads[10];
int queueResourceAvailable;

int main(){

    int init;
    for(init=0; init<10; init++){
        usedThreads[init] = 0;
    }

    lastOnTheQueue = 0;
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

        queueResourceAvailable = 1;
        while(1){
            //Recebe e printa na tela os bytes da requisição do cliente.
            x = recv(client, request, sizeof request, 0);
            //printf("Request message: %s", request, x);
            if(x<1) break;
            strncpy(queue[lastOnTheQueue++], request, strlen(request) - 1);
        }
        queueResourceAvailable = 0;

        printf("%d\n", lastOnTheQueue);
        /*int j;
        for(j = 0; j < lastOnTheQueue; j++){
                printf("%s\n", queue[j]);
        }*/

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



void* requisitionResponder(void* arg){
    printf("Entered thread");
    //int *k = (int*) arg;
    //int j = *k;
    //sleep(1);
    //usedThreads[j] = 0;
    //printf("Thread %d terminated", j);
}


void* respondRequisitions(void* arg){
    pthread_t threads[10];
    char localQueue[50][512];
    char localLastOnTheQueue = 0;
    pthread_t th;
    pthread_create(&th, NULL, requisitionResponder, NULL);

    while(1){
        if(lastOnTheQueue > 0 && queueResourceAvailable == 0){
            while(lastOnTheQueue > 0){
                lastOnTheQueue--;
                strcpy(localQueue[localLastOnTheQueue], queue[lastOnTheQueue]);
                localLastOnTheQueue++;
            }
        }

        while(threadAvailable() == 1){
            if(localLastOnTheQueue > 0){
                int threadNumber = getAvailableThread();
                if(threadNumber > -1){
                    int* threadAllocated = malloc(sizeof(*threadAllocated));
                    *threadAllocated = threadNumber;
                    printf("%d", threadNumber);
                    pthread_t auxThread = threads[threadNumber];
                    pthread_create(&auxThread, NULL, requisitionResponder, NULL);
                    usedThreads[threadNumber] = 1;
                }
                //else feito apenas para teste
                else{
                    printf("All threads are being used");
                }
            }
            else{
                break;
            }
        }
    }
}

int threadAvailable(){
    int i = 0;
    for(int i = 0; i < 10; i++){
        if(usedThreads[i] == 0) return 1;
    }
    return 0;
}

int getAvailableThread(){
    int i = 0;
    for(int i = 0; i < 10; i++){
        if(usedThreads[i] == 0) return i;
    }
    return -1;
}