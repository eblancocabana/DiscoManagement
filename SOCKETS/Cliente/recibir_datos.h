#ifndef RECIBIR_DATOS_H
#define RECIBIR_DATOS_H

#include <cstring>
#include <type_traits>

template <typename T>
T
recibir_datos();

#endif

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