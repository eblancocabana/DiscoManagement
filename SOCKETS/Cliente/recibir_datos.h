// inicio.h
#ifndef RECIBIR_DATOS_H
#define RECIBIR_DATOS_H

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <type_traits>
#include <winsock2.h>

extern SOCKET s;
inline char * recibir_datos_char() {
  char buffer[512];
  int bytes_recibidos = recv(s, buffer, sizeof(buffer), 0);
  if (bytes_recibidos > 0) {
    printf("SIIIII");
    printf("Bytes recibidos: %d\n", bytes_recibidos);
    char * resultado = new char[bytes_recibidos + 1];
    memcpy(resultado, buffer, bytes_recibidos);
    resultado[bytes_recibidos] = '\0';
    return resultado;
  } else {
    printf("NIOOOIOI");
    std::cerr << "Error al recibir datos del servidor" << std::endl;
    return nullptr;
  }
}

inline int recibir_datos_int() {
  char buffer[512];
  int bytes_recibidos = recv(s, buffer, sizeof(buffer), 0);
  if (bytes_recibidos > 0) {
    return atoi(buffer);
  } else {
    std::cerr << "Error al recibir datos del servidor" << std::endl;
    return 0;
  }
}

#endif


