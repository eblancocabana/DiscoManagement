#ifndef _BASEDATOS_
#define _BASEDATOS_
#include "sqlite/sqlite3.h"

int dbExiste(char* fichero);
int abrirConexion();
void cerrarConexion(sqlite3* baseDatos);
void clearIfNeeded(char *str, int max_line);
int eliminarBD();

int gestionarError(sqlite3* baseDatos);
void gestionarFree(char* str);
void seleccionarRRPP();
int comprobarExistencia();
static int callback(void *NotUsed, int argc, char **argv, char **azColName);
void mostrarlistadoeventos();
void mostrarFiestas();

void cargarLocales();
int comprobarCodigoLocal(int cod);
int comprobarCodigoRRPP(int cod);

int inicializacion();
int inicializarUsuarios();
int inicializarDiasDeFiesta();
int inicializarDJ();
int inicializarRRPP();
int inicializarListaEventos();

int insertarDiaFiesta(char* fecha, char* nomDiscoteca, char* eventoEsp);

#endif