#include <io.h>
#include <stdio.h>
#include <winsock2.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define PORT 5000

int main() 
{
    char request[512];
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    int sockfd, connfd, n; 
    struct sockaddr_in servaddr, cli; 
  
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(PORT); 

    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    printf("Enter the request string: ");

    n = 0; 
    while ((request[n++] = getchar()) != '\n') ;

    printf("%s", request);
    send(sockfd, request, (int)strlen(request), 0);
}