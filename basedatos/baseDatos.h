#ifndef _BASEDATOS_
#define _BASEDATOS_
#include "sqlite/sqlite3.h"

int dbExiste(char* fichero);
int abrirConexion();
void cerrarConexion(sqlite3* baseDatos);

int gestionarError(sqlite3* baseDatos);
int eliminarTablas();

int inicializacion();

#endif