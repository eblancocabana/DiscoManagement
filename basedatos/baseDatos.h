#ifndef _BASEDATOS_
#define _BASEDATOS_
#include "sqlite/sqlite3.h"

int dbExiste(char* fichero);
int abrirConexion();
void cerrarConexion(sqlite3* baseDatos);
void clearIfNeeded(char *str, int max_line);
char* limpiarInput(char* input);
int reiniciarBD();

int gestionarError(sqlite3* baseDatos);
void gestionarFree(char* str);
void seleccionarRRPP();
static int callback(void *NotUsed, int argc, char **argv, char **azColName);
void mostrarlistadoeventos();
void mostrarFiestas();

void cargarLocales();
int comprobarCodigoLocal(int cod);
int comprobarCodigoRRPP(int cod);
int comprobarUsuario(char* usuario);
int comprobarFecha(char* fecha);
int comprobarAdmin(char* user);
int comprobarExistencia(char* username, char* password);

int inicializacion();
int inicializarUsuarios();
int inicializarDiasDeFiesta();
int inicializarDJ();
int inicializarRRPP();
int inicializarListaEventos();

int insertarDiaFiesta(char* fecha, char* nomDiscoteca, char* eventoEsp);
int insertarRegistro(char* nombre, char* usuario, char* sexo, int edad, char* correo, char* contra);
int insertarEvento(char* fecha, char* nombreDisco, char* descripcionEvento);

#endif