#include <stdio.h>
#include <pthread.h>
#include <string.h>

const char* requests[5];
int i = 0; 

void* threadFunction(const char* requestString);

int main(){
	requests[0] = "Requisicoes";
	requests[1] = "Que";
	requests[2] = "Serao";
	requests[3] = "Invertidas";
	requests[4] = "No pthread";

	for(i = 0; i < 5; i++){
		pthread_t thread;
		int threadCreated;

		threadCreated = pthread_create(&thread, NULL, threadFunction(requests[i]), NULL);
		/*if(threadCreated == 0){
	        printf("PThread %d created successfully.\n", i);
	    }
	    else{
	        printf("PThread %d not created.\n", i);
	    }*/
	}

	return 0;
}


void* threadFunction(const char* requestString){
	printf("PThread %d created successfully.\n", i);
    
    printf("Requisicao antes de inverter: %s\n", requestString);
	int tamanhoString = strlen(requestString), iterador;

	for(iterador = tamanhoString - 1; iterador >= 0; iterador--){
		printf("%c", requestString[iterador]);
	}

    printf("\nPThread %d ended successfully.\n", i);
}