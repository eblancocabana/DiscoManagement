#ifndef _BASEDATOS_
#define _BASEDATOS_
#include "sqlite/sqlite3.h"
#include "../estructuras/reservarlocal_est.h"
#include "../estructuras/entrada_est.h"
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

SOCKET socket_fd;

int dbExiste(const char* fichero);
int reiniciarBD();
int verificarFecha(char* fecha);

int abrirConexion();
void cerrarConexion(sqlite3* baseDatos);

void gestionarFree(char* str);
int gestionarError(sqlite3* baseDatos);

int inicializacion();
int inicializarUsuarios();
int inicializarDiasDeFiesta();
int inicializarDJ();
int inicializarRRPP();
int inicializarListaEventos();
int inicializarEntradas();
int inicializarReservaLocal();

char* limpiarInput(char* input);
void clearIfNeeded(char *str, int max_line);
static int callbackClient(void *socket_fd, int argc, char **argv, char **azColName);
static int callback(void *NotUsed, int argc, char **argv, char azColName);

int comprobarCodigoLocal(int cod);
int comprobarCodigoRRPP(int cod);
int comprobarUsuario(char* usuario);
int comprobarFecha(char* fecha, int evento);
int comprobarAdmin(char* user);
int comprobarExistencia(char* username, char* password);
int comprobarEntrada(char* codigo);

void mostrarlistadoeventos(SOCKET socket_fd);
void mostrarFiestas(SOCKET socket_fd);
void mostrarDJ(SOCKET socket_fd);
void mostrarRRPP(SOCKET socket_fd);
void mostrarLocales(SOCKET socket_fd);

void mostrarlistadoeventosAdmin();
void mostrarFiestasAdmin();
void mostrarDJAdmin();
void mostrarRRPPAdmin();
void mostrarLocalesAdmin();


int insertarDiaFiesta(char* fecha, char* nomDiscoteca, char* eventoEsp);
int insertarRegistro(char* nombre, char* usuario, char* sexo, int edad, char* correo, char* contra);
int insertarEvento(char* fecha, char* nombreDisco, char* descripcionEvento);
int insertarEntrada(EntradaEst entradaInsertar);
int insertarReservaLocal(ReservaLocalEst reservarLocalInsertar);

int buscarUltimoCodigo();
char* buscarFechaConCodigoFecha(int codigoFecha);
char* buscarDiscotecaConCodigoFecha(int codigoFecha);

#endif