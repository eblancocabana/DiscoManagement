#include "recibir_datos.h"
#include <winsock2.h>
SOCKET s;
template <typename T>
T recibir_datos(); 
/*{
    char buffer[sizeof(T)];
    int bytes_recibidos = recv(s, buffer, sizeof(buffer), 0);
    if (bytes_recibidos == sizeof(T)) {
        T resultado;
        memcpy(&resultado, buffer, sizeof(T));
        return resultado;
    } else {
        std::cerr << "Error al recibir datos del servidor jiefjijerfih" << std::endl;
        return T();
    }
}*/