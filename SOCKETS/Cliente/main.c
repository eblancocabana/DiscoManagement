#include <stdio.h>
#include <locale.h>
#include "inicio.h"
#include "basedatos/baseDatos.h"
 
// IMPORTANT: Winsock Library ("ws2_32") should be linked

#include <stdio.h>
#include <winsock2.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

SOCKET s;

void enviar_datos(char *nombre_funcion, int num_args, ...) {
    char sendBuff[512];
    sprintf(sendBuff, "%s:", nombre_funcion);

    va_list args;
    va_start(args, num_args);

    for (int i = 0; i < num_args; i++) {
        void *arg = va_arg(args, void*);
        size_t arg_size = va_arg(args, size_t);
        memcpy(sendBuff + strlen(sendBuff), arg, arg_size);
    }

    va_end(args);

    send(s, sendBuff, sizeof(sendBuff), 0);
}


int main(int argc, char *argv[]) {

    printf("\n\n\n\n");
    printf("\e[34m\e[1m");
    printf("********************************\n");
    printf("*                              *\n");
    printf("*   SOUND STRATEGY PARTNERS    *\n");
    printf("*                              *\n");
    printf("********************************\n");
    printf("\e[0m");
    printf("\n"); 

	WSADATA wsaData;

	struct sockaddr_in server;
	char sendBuff[512], recvBuff[512];

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		printf("Connection error: %d", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	printf("Connection stablished with: %s (%d)\n", inet_ntoa(server.sin_addr),
			ntohs(server.sin_port));


    
    inicializacion();
    login();

	// CLOSING the socket and cleaning Winsock...
	closesocket(s);
	WSACleanup();

	return 0;
}
