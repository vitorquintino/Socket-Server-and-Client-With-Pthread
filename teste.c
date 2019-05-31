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

void* test(void* arguments);

struct arg_struct {
    int arg1;
    int arg2;
};


void* test(void* arguments){
	struct arg_struct* args = (struct arg_struct *)arguments;

	printf("%d DA THREAD\n", args->arg1);
	printf("%d DA THREAD\n", args->arg2);
}

int main(){
	struct arg_struct args;
	args.arg1 = 10;
	args.arg2 = 20;
	printf("%d\n", args.arg1);
	printf("%d\n", args.arg2);

	pthread_t thread;
    if(pthread_create(&thread, NULL, test, &args)){
    	printf("foi");
    }

  	//pthread_join(thread, NULL);
  	sleep(10);
    printf("salve");
	return 0;
}