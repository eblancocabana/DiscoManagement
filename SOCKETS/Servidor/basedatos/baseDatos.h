#ifndef _BASEDATOS_
#define _BASEDATOS_
#include "sqlite/sqlite3.h"
#include "../clases/entrada.h"
#include "../clases/reservalocal.h"

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
static int callback(void *NotUsed, int argc, char **argv, char **azColName);

int comprobarCodigoLocal(int cod);
int comprobarCodigoRRPP(int cod);
int comprobarUsuario(char* usuario);
int comprobarFecha(char* fecha, int evento);
int comprobarAdmin(char* user);
int comprobarExistencia(char* username, char* password);
int comprobarEntrada(char* codigo);

void mostrarlistadoeventos();
void mostrarFiestas();
void mostrarDJ();
void mostrarRRPP();
void mostrarLocales();

int insertarDiaFiesta(char* fecha, char* nomDiscoteca, char* eventoEsp);
int insertarRegistro(char* nombre, char* usuario, char* sexo, int edad, char* correo, char* contra);
int insertarEvento(char* fecha, char* nombreDisco, char* descripcionEvento);
int insertarEntrada(Entrada entradaInsertar);
int insertarReservaLocal(ReservaLocal reservarLocalInsertar);

int buscarUltimoCodigo(int evento);

#endif