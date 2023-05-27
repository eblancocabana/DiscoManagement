// IMPORTANT: Winsock Library ("ws2_32") should be linked

#include <iostream>
#include <winsock2.h>
#include <string>
#include <sstream>
#include <limits>

extern "C" {
  #include "basedatos/sqlite/sqlite3.h"

  #include "basedatos/baseDatos.h"

  #include "estructuras/entrada_est.h"

  #include "estructuras/reservarlocal_est.h"

}

#include "clases/reservalocal.h"
#include "administrador/inicio_servidor.h"

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

#define MAX_SELECCION 5
#define MAX_REGISTRO 20
#define MAX_LOGIN 15

#define MAX_NOMBRE 20
#define MAX_NOMBRE_USU 20
#define MAX_SEXO 20
#define MAX_EDAD 20
#define MAX_CORREO 20
#define MAX_CONTRASENYA 20

using namespace std;

//Para ejecutar el "servidor.exe"

//gcc -c basedatos/baseDatos.c -o bd.o         CREAR .O DE LOS C
//gcc -c basedatos/sqlite/sqlite3.c -o sqlite.o         CREAR .O DE LOS C
//g++ -c administrador/inicio_servidor.cpp -o inicio.o         CREAR .O DE LOS C++
//g++ -c main.cpp -o main.o         CREAR .O DE LOS C++

//g++ main.o inicio.o sqlite.o bd.o -o servidor.exe -lWs2_32        EJECUTAR EL ARCHIVO

void iniciarSesion() {
  int existe = 1;
  char input[MAX_REGISTRO];

  std::cout << "Usuario: ";
  cin.getline(input, MAX_NOMBRE_USU);
  char * us = limpiarInput(input);

  std::cout << "Contrasenya: ";
  cin.getline(input, MAX_CONTRASENYA);
  char * pa = limpiarInput(input);

  existe = comprobarExistencia(us, pa);
  int admin = comprobarAdmin(us);

  if ((existe == 0) && (admin == 0)) {
    std::cout << "\nADMIN ENCONTRADO, accediendo al menu\n";
    inicioServidor();

  } else if ((existe == 0)) {
    std::cout << "\nUSUARIO NO ADMIN. Acceso denegado\n";
    std::cout << "Ejecucion finalizada\n";

    return;
  } else {
    // Hacer algo si no se encuentra el usuario o la contraseña es incorrecta
  }
}

void deserializar_y_llamar_funcion(SOCKET comm_socket, char * recvBuff) {
  // Dividir el buffer recibido en el nombre de la función y los argumentos
  char * nombre_funcion = strtok(recvBuff, ":");
  char * args = strtok(NULL, ":");

  // Buffer para enviar el valor devuelto por la función llamada
  char sendBuff[8193];
  printf("BUFF: %s\n", sendBuff);

  int pos = 0;
  printf("RECIBIDO: %s - ARGUMENTO: %s", nombre_funcion, args);

  // Llamar a la función correspondiente con sus argumentos y enviar el valor devuelto
  if (strcmp(nombre_funcion, "inicializarUsuarios") == 0) {
    int ret = inicializarUsuarios();
    const char * rret = (std::to_string(ret)).c_str();
    size_t size = sizeof(rret) + 1;

    memcpy(sendBuff + pos, rret, size);
    pos += size;

  } else if(strcmp(nombre_funcion,"mostrarentradas")==0){
    char* ret = mostrarMisEntradas(args);

    size_t size = strlen(ret) + 1;
    memcpy(sendBuff + pos, ret, size);
    
    pos += size;
  } else if (strcmp(nombre_funcion, "inicializarDiasDeFiesta") == 0) {
    int ret = inicializarDiasDeFiesta();
    const char * rret = (std::to_string(ret)).c_str();

    size_t size = sizeof(rret) + 1;
    memcpy(sendBuff + pos, rret, size);
    pos += size;

  } else if (strcmp(nombre_funcion, "inicializarDJ") == 0) {
    int ret = inicializarDJ();
    const char * rret = (std::to_string(ret)).c_str();

    size_t size = sizeof(rret) + 1;
    memcpy(sendBuff + pos, rret, size);
    pos += size;

  } else if (strcmp(nombre_funcion, "inicializarRRPP") == 0) {
    int ret = inicializarRRPP();
    const char * rret = (std::to_string(ret)).c_str();

    size_t size = sizeof(rret) + 1;
    memcpy(sendBuff + pos, rret, size);
    pos += size;

  } else if (strcmp(nombre_funcion, "inicializarListaEventos") == 0) {
    int ret = inicializarListaEventos();
    const char * rret = (std::to_string(ret)).c_str();

    size_t size = sizeof(rret) + 1;
    memcpy(sendBuff + pos, rret, size);
    pos += size;

  } else if (strcmp(nombre_funcion, "inicializacion") == 0) {
    printf("Llamando a inicializacion:\n");
    int ret = inicializacion();
    printf("Retorno de inicializacion: %d\n", ret);

    const char * rret = (std::to_string(ret)).c_str();
    size_t size = sizeof(rret) + 1;
    memcpy(sendBuff + pos, rret, size);
    pos += size;

  } else if (strcmp(nombre_funcion, "limpiarInput") == 0) {
    char * ret = limpiarInput(args);
    size_t size = strlen(ret) + 1;
    memcpy(sendBuff + pos, ret, size);
    pos += size;

    printf("Sending: %s through socket:\n", ret);
  } else if (strcmp(nombre_funcion, "clearIfNeeded") == 0) {
    // Dividir los argumentos en str y max_line

    char * ret = strtok(args, ",");
    int max_line = atoi(strtok(NULL, ","));
    clearIfNeeded(ret, max_line);

    size_t size = strlen(ret) + 1;
    memcpy(sendBuff + pos, ret, size);
    pos += size;

  } else if (strcmp(nombre_funcion, "comprobarCodigoLocal") == 0) {
    char* cod = strtok(args, ",");
    printf("%s\n", cod);

    int ret = comprobarCodigoLocal(cod);
    printf("%i\n", ret);

    const char* rret = (std::to_string(ret)).c_str();
    size_t size = sizeof(rret) + 1;
    memcpy(sendBuff + pos, rret, size);
    pos += size;

  } else if (strcmp(nombre_funcion, "comprobarCodigoRRPP") == 0) {
    char* cod = strtok(args, ",");
    int ret = comprobarCodigoRRPP(cod);

    const char * rret = (std::to_string(ret)).c_str();
    size_t size = sizeof(rret) + 1;
    memcpy(sendBuff + pos, rret, size);
    pos += size;

  } else if (strcmp(nombre_funcion, "comprobarUsuario") == 0) {
    char * rett = strtok(args, ",");
    int ret = comprobarUsuario(rett);

    const char * rret = (std::to_string(ret)).c_str();
    size_t size = sizeof(rret) + 1;
    memcpy(sendBuff + pos, rret, size);
    pos += size;

  } else if (strcmp(nombre_funcion, "comprobarFecha") == 0) {
    //Dividir los argumentos en fecha y evento

    char * fecha = strtok(args, ",");
    int evento = atoi(strtok(NULL, ","));

    int ret = comprobarFecha(fecha, evento);
    memcpy(sendBuff + pos, & ret, sizeof(ret));
    pos += sizeof(ret);

  } else if (strcmp(nombre_funcion, "comprobarAdmin") == 0) {
    int ret = comprobarAdmin(args);
    const char * rret = (std::to_string(ret)).c_str();

    size_t size = sizeof(rret) + 1;
    memcpy(sendBuff + pos, rret, size);
    pos += size;

  } else if (strcmp(nombre_funcion, "comprobarExistencia") == 0) {
    //Dividir los argumentos en username y password
    
    char * username = strtok(args, ",");
    char * password = strtok(NULL, ",");

    int ret = comprobarExistencia(username, password);
    const char * rret = (std::to_string(ret)).c_str();
    size_t size = sizeof(rret) + 1;
    memcpy(sendBuff + pos, rret, size);
    pos += size;

  } else if (strcmp(nombre_funcion, "comprobarCodigoEntrada") == 0) {
    char * entrada = strtok(args, ",");
    int ret = comprobarEntrada(entrada);
    const char * rret = (std::to_string(ret)).c_str();

    size_t size = sizeof(rret) + 1;
    memcpy(sendBuff + pos, rret, size);
    pos += size;

  } else if (strcmp(nombre_funcion, "insertarDiaFiesta") == 0) {
    //Dividir los argumentos en fecha,nomDiscoteca y eventoEsp

    char * fecha = strtok(args, ",");
    char * nomDiscoteca = strtok(NULL, ",");
    char * eventoEsp = strtok(NULL, ",");
    int ret = insertarDiaFiesta(fecha, nomDiscoteca, eventoEsp);

    const char * rret = (std::to_string(ret)).c_str();
    size_t size = sizeof(rret) + 1;
    memcpy(sendBuff + pos, rret, size);
    pos += size;

  } else if (strcmp(nombre_funcion, "insertarRegistro") == 0) {
    //Dividir los argumentos en nombre usuario sexo edad correo contra

    char* nombre = strtok(args, ",");
    char* usuario = strtok(NULL, ",");
    char* sexo = strtok(NULL, ",");
    int edad = atoi(strtok(NULL, ","));
    char* correo = strtok(NULL, ",");
    char* contra = strtok(NULL, ",");

    printf(nombre);
    printf(usuario);
    printf(sexo);
    printf("%d", edad);
    printf(correo);
    printf(contra);

    int ret = insertarRegistro(nombre, usuario, sexo, edad, correo, contra);
    const char * rret = (std::to_string(ret)).c_str();

    size_t size = sizeof(rret) + 1;
    memcpy(sendBuff + pos, rret, size);
    pos += size;

  } else if (strcmp(nombre_funcion, "insertarEvento") == 0) {
    //Dividir los argumentos en fecha,nombreDisco y descripcionEvento

    char* fecha = strtok(args, ",");
    char* nombreDisco = strtok(NULL, ",");
    char* descripcionEvento = strtok(NULL, ",");
    int ret = insertarEvento(fecha, nombreDisco, descripcionEvento);
    const char* rret = (std::to_string(ret)).c_str();

    size_t size = sizeof(rret) + 1;
    memcpy(sendBuff + pos, rret, size);
    pos += size;

  } else if (strcmp(nombre_funcion, "insertarReservaLocal") == 0) {
    //Dividir los argumentos en codigo_aux, fecha_loc, aforo, numeroTarjeta, cvvTarjeta, caducidadTarjeta

    char* codigo_aux = strtok(args, ",");
    char* fecha_loc = strtok(NULL, ",");
    char* nombreDiscoteca = strtok(NULL, ",");
    char* aforo = strtok(NULL, ",");
    char* numeroTarjeta = strtok(NULL, ",");
    char* cvvTarjeta = strtok(NULL, ",");
    char* caducidadTarjeta = strtok(NULL, ",");

    int ret = insertarReservaLocal(codigo_aux, fecha_loc, nombreDiscoteca, aforo, numeroTarjeta, cvvTarjeta, caducidadTarjeta);
    const char* rret = (std::to_string(ret)).c_str();

    size_t size = sizeof(rret) + 1;
    memcpy(sendBuff + pos, rret, size);
    pos += size;

  } else if (strcmp(nombre_funcion, "insertarEntrada") == 0) {
    //Dividir los argumentos en codFechaAux, fecha_ent, nomDiscoteca, numEntradasAux, gmail, numTarjeta, cvvTar, caducidadTar, entradaCatFin, preciosAux, nombreCompleto
    
    char* codFechaAux = strtok(args, ",");
    char* fecha_ent = strtok(NULL, ",");
    char* nomDiscoteca = strtok(NULL, ",");
    char* numEntradasAux = strtok(NULL, ",");
    char* gmail = strtok(NULL, ",");
    char* numTarjeta = strtok(NULL, ",");
    char* cvvTar = strtok(NULL, ",");
    char* caducidadTar = strtok(NULL, ",");
    char* entradaCatFin = strtok(NULL, ",");
    char* preciosAux = strtok(NULL, ",");
    char* nombreCompleto = strtok(NULL, ",");

    printf("%s\n", codFechaAux);
    printf("%s\n", fecha_ent);
    printf("%s\n", nomDiscoteca);
    printf("%s\n", numEntradasAux);
    printf("%s\n", gmail);
    printf("%s\n", numTarjeta);
    printf("%s\n", cvvTar);
    printf("%s\n", caducidadTar);
    printf("%s\n", entradaCatFin);
    printf("%s\n", preciosAux);
    printf("%s\n", nombreCompleto);

    int ret = insertarEntrada(codFechaAux, fecha_ent, nomDiscoteca, numEntradasAux, gmail, numTarjeta, cvvTar, caducidadTar, entradaCatFin, preciosAux, nombreCompleto);
    const char* rret = (std::to_string(ret)).c_str();

    size_t size = sizeof(rret) + 1;
    memcpy(sendBuff + pos, rret, size);
    pos += size;

  } else if (strcmp(nombre_funcion, "mostrarlistadoeventos") == 0) {
    char* ret= mostrarlistadoeventos();
    size_t size = strlen(ret) + 1;
    memcpy(sendBuff + pos, ret, size);
    pos += size;

  } else if (strcmp(nombre_funcion, "mostrarFiestas") == 0) {
    char* ret= mostrarFiestas();
    size_t size = strlen(ret) + 1;
    memcpy(sendBuff + pos, ret, size);
    pos += size;

  } else if (strcmp(nombre_funcion, "inicicializacionSOCKET") == 0) {
    int ret = 1;
    const char * rret = (std::to_string(ret)).c_str();

    size_t size = sizeof(rret) + 1;
    memcpy(sendBuff + pos, rret, size);
    pos += size;

  } else if (strcmp(nombre_funcion, "mostrarRRPP") == 0) {
    char* ret= mostrarRRPP();
    size_t size = strlen(ret) + 1;
    memcpy(sendBuff + pos, ret, size);
    pos += size;

  } else if (strcmp(nombre_funcion, "mostrarLocales") == 0) {
    char* ret= mostrarLocales();
    size_t size = strlen(ret) + 1;
    memcpy(sendBuff + pos, ret, size);
    pos += size;

  } else if (strcmp(nombre_funcion, "buscarFechaConCodidoFecha") == 0) {
    char* ret = buscarFechaConCodigoFecha(args);
    printf("Sending: %s through socket\n", ret);

    size_t size = sizeof(ret) + 1;
    memcpy(sendBuff + pos, ret, size);
    pos += size;

  } else if (strcmp(nombre_funcion, "buscarDiscotecaConCodigoFecha") == 0) {
    char* ret = buscarDiscotecaConCodigoFecha(args);
    printf("Sending: %s through socket\n", ret);

    size_t size = sizeof(ret) + 1;
    memcpy(sendBuff + pos, ret, size);
    pos += size;

  } 
  printf("BUFFER: %s", sendBuff);

  // Enviar el valor devuelto por la función llamada a través del socket
  int bytes_sent = send(comm_socket, sendBuff, pos, 0);

  if (bytes_sent == -1) {
    int error_code = WSAGetLastError();
    printf("Error al enviar datos: %d\n", error_code);
  }
  return;
}

int main(int argc, char * argv[]) {
  std::cout << "\n\n\n\n";
  std::cout << "\e[34m\e[1m";
  std::cout << "********************************\n";
  std::cout << "*                              *\n";
  std::cout << "*   SOUND STRATEGY PARTNERS    *\n";
  std::cout << "*                              *\n";
  std::cout << "********************************\n";
  std::cout << "\e[0m";
  std::cout << "\n";

  WSADATA wsaData;
  SOCKET conn_socket;
  SOCKET comm_socket;
  struct sockaddr_in server;
  struct sockaddr_in client;
  char sendBuff[512], recvBuff[512];

  int opcion = 0;
  std::string entrada;

  while (opcion != 1 && opcion != 2) {
    std::cout << "Ingrese una opcion\n";
    std::cout << "\t1. Acceder como admin modo local\n";
    std::cout << "\t2. Ejecutar el servidor\n";

    getline(cin, entrada);

    try {
      opcion = std::stoi(entrada);

      if (opcion == 1) {
        std::cout << "Accediendo como admin modo local...\n";
        inicializacion();
        iniciarSesion();

        return 0;
      } else if (opcion == 2) {
        std::cout << "Ejecutando el servidor para ponerse en escucha...\n";
      } else {
        std::cout << "Opcion no valida. Por favor, intente nuevamente.\n";
      }
    } catch (std::exception
      const & e) {
      std::cout << "Entrada no valida. Por favor, ingrese un numero entero.\n";
    }
  }

  std::cout << "\nInitialising Winsock...\n";
  if (WSAStartup(MAKEWORD(2, 2), & wsaData) != 0) {
    std::cout << "Failed. Error Code : " << WSAGetLastError();

    return -1;
  }

  std::cout << "Initialised.\n";

  //SOCKET creation
  if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
    std::cout << "Could not create socket : " << WSAGetLastError();
    WSACleanup();

    return -1;
  }

  std::cout << "Socket created.\n";

  server.sin_addr.s_addr = inet_addr(SERVER_IP);
  server.sin_family = AF_INET;
  server.sin_port = htons(SERVER_PORT);

  //BIND (the IP/port with socket)
  if (bind(conn_socket, (struct sockaddr * ) & server,
      sizeof(server)) == SOCKET_ERROR) {
    std::cout << "Bind failed with error code: " << WSAGetLastError();
    closesocket(conn_socket);
    WSACleanup();

    return -1;
  }

  std::cout << "Bind done.\n";

  //LISTEN to incoming connections (socket server moves to listening mode)
  if (listen(conn_socket, 1) == SOCKET_ERROR) {
    std::cout << "Listen failed with error code: " << WSAGetLastError();
    closesocket(conn_socket);
    WSACleanup();

    return -1;
  }

  //ACCEPT incoming connections (server keeps waiting for them)
  std::cout << "Waiting for incoming connections...\n";
  int stsize = sizeof(struct sockaddr);
  comm_socket = accept(conn_socket, (struct sockaddr * ) & client, & stsize);
  // Using comm_socket is able to send/receive data to/from connected client
  if (comm_socket == INVALID_SOCKET) {
    std::cout << "accept failed with error code : " << WSAGetLastError();
    closesocket(conn_socket);
    WSACleanup();

    return -1;
  }
  std::cout << "Incomming connection from: " << inet_ntoa(client.sin_addr) <<
    "(" << ntohs(client.sin_port) << ")" << std::endl;

  // Closing the listening sockets (is not going to be used anymore)
  closesocket(conn_socket);

  //SEND and RECEIVE data
  std::cout << "Waiting for incoming messages from client... \n";
  do {
    int bytes = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
    if (bytes > 0) {
      std::cout << "Receiving message... \n";
      std::cout << "Data received: " << recvBuff << std::endl;

      // Deserializar los datos recibidos y llamar a la función correspondiente con sus argumentos
      deserializar_y_llamar_funcion(comm_socket, recvBuff);

      if (strcmp(recvBuff, "Bye") == 0)
        break;
    } else{
    }

  } while (1);

  // CLOSING the sockets and cleaning Winsock...
  closesocket(comm_socket);
  WSACleanup();

  return 0;
}