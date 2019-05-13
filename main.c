#include <stdio.h>
#include <pthread.h>

void* threadFunction(void* args);

int main(){
	printf("Hello, World!\n");
	pthread_t id;
	int ret;

	ret = pthread_create(&id, NULL, &threadFunction, NULL);
	if(ret==0){
        printf("Thread created successfully.\n");
    }
    else{
        printf("Thread not created.\n");
        return 0;
    }

	return 0;
}


void* threadFunction(void* args){
    printf("I am threadFunction.\n");
}