#include <io.h>
#include <stdio.h>
#include <winsock2.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char buff[512];
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    struct sockaddr_in caddr;
    struct sockaddr_in saddr = {
        .sin_family      = AF_INET,
        .sin_addr.s_addr = htonl(INADDR_ANY),
        .sin_port        = htons(5000)
    };

    int server = socket(AF_INET, SOCK_STREAM, 0);
    int client, x;
    int csize  = sizeof caddr;

    bind(server, (struct sockaddr *) &saddr, sizeof saddr);
    listen(server, 5);

	printf("It worked!\n" );

    while(1){
        client = accept(server, (struct sockaddr *) &caddr, &csize);
        x = recv(client, buff, sizeof buff, 0);

        int valread = read(client, buff, 512);

        printf("%s\n", buff);

        send(client, buff, x, 0);

        fflush(stdout);

        closesocket(client);
    }

	return 0;
}