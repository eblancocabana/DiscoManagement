#ifndef _BASEDATOS_
#define _BASEDATOS_
#include "sqlite/sqlite3.h"

int dbExiste(char* fichero);
int gestionarError(sqlite3* baseDatos);
void cerrarConexion(sqlite3* baseDatos);
int abrirConexion();
int inicializacion();

#endif