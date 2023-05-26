// inicio.h
#ifndef RECIBIR_DATOS_H
#define RECIBIR_DATOS_H

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <type_traits>
#include <winsock2.h>

extern SOCKET s;

template <typename T>
T recibir_datos() {
    printf("1\n");
    char buffer[sizeof(T)];
    printf("2\n");
    int bytes_recibidos = recv(s, buffer, sizeof(buffer), 0);
    printf("bytes %i, size %i\n",bytes_recibidos, sizeof(T));
    if (bytes_recibidos == sizeof(T)) {
        T resultado;
        memcpy(&resultado, buffer, sizeof(T));
        return resultado;
    } else {
        std::cerr << "Error al recibir datos del servidor" << std::endl;
        return T();
    }
}

#endif
