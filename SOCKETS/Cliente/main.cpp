#include <iostream>
#include <locale.h>
#include "inicio.h"
#include "basedatos/baseDatos.h"
#include "enviar_datos.h"
#include "recibir_datos.h"

// IMPORTANT: Winsock Library ("ws2_32") should be linked

#include <winsock2.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

SOCKET s;

template <typename T>
T recibir_datos() {
    char recvBuff[512];
    int bytesReceived = recv(s, recvBuff, sizeof(recvBuff), 0);
    if (bytesReceived > 0) {
        T data;
        memcpy(&data, recvBuff, sizeof(T));
        return data;
    } else {
        // Handle error when receiving data
    }
}


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

    std::cout << "\n\n\n\n";
    std::cout << "\e[34m\e[1m";
    std::cout << "********************************\n";
    std::cout << "* *\n";
    std::cout << "* SOUND STRATEGY PARTNERS *\n";
    std::cout << "* *\n";
    std::cout << "********************************\n";
    std::cout << "\e[0m";
    std::cout << "\n";

    WSADATA wsaData;

    struct sockaddr_in server;
    char sendBuff[512], recvBuff[512];

    std::cout << "\nInitialising Winsock...\n";
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "Failed. Error Code : " << WSAGetLastError();
        return -1;
    }

    std::cout << "Initialised.\n";

    //SOCKET creation
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cout << "Could not create socket : " << WSAGetLastError();
        WSACleanup();
        return -1;
    }

    std::cout << "Socket created.\n";

    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);

    //CONNECT to remote server
    if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
        std::cout << "Connection error: " << WSAGetLastError();
        closesocket(s);
        WSACleanup();
        return -1;
    }

     std::cout << "Connection stablished with: " << inet_ntoa(server.sin_addr) <<
            "(" << ntohs(server.sin_port) << ")" << "\n";

    
     inicializacion();
     login();

     // CLOSING the socket and cleaning Winsock...
     closesocket(s);
     WSACleanup();

     return 0;
}
