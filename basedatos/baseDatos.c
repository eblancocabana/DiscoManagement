#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite/sqlite3.h"
#include "baseDatos.h"

sqlite3* database;
int apertura;
int existeBD;
char* mensajeError = 0;

int dbExiste(char* fichero) {
  FILE* arch = fopen(fichero, "r");

  if (arch) {
    fclose(arch);
    return 1;
  }
  return 0;
}

int gestionarError(sqlite3* baseDatos) {
  fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(baseDatos));
  return sqlite3_errcode(baseDatos);
}

void cerrarConexion(sqlite3* baseDatos) {
  sqlite3_close(baseDatos);
  fprintf(stdout, "La Base de datos se cerro exitosamente\n");
}

int abrirConexion() {
  existeBD = dbExiste("basedatosSSR.db");
  apertura = sqlite3_open("basedatosSSR.db", &database);
  
  if (apertura != SQLITE_OK) {
    fprintf(stderr, "No se puede abrir la Base De Datos: %s\n", gestionarError(database));
    cerrarConexion(database);
    return 1;

  } else {
    fprintf(stdout, "La Base De Datos se abrio exitosamente\n");
    return 0;
  }
}

int inicializacion() {
  
  abrirConexion();

  if (!existeBD) {
    // Implementacion de importacion de datos CSV
    char * sql = "CREATE TABLE dias_de_fiesta(Codigo TEXT PRIMARY KEY NOT NULL,Fecha TEXT NOT NULL,Nombre TEXT NOT NULL,Entradas INT NOT NULL,Especial TEXT NOT NULL)";
    apertura = sqlite3_exec(database, sql, 0, 0, & mensajeError);
    if (apertura != SQLITE_OK) {
      gestionarError(database);
      sqlite3_free(mensajeError);
      cerrarConexion(database);
      return 1;
    }

    FILE* fp = fopen("ficheros/dias_de_fiesta.csv", "r");
    if (!fp) {
      printf("No se puede abrir el archivo\n");
      return 1;
    }

    char line[1024];

    fgets(line, sizeof(line), fp); // Saltar la primera línea (encabezados)

    while (fgets(line, sizeof(line), fp)) {

      char codigo[50], fecha[50], nombre[50], entradas[50], especial[50];

      sscanf(line, "%[^','],%[^','],%[^','],%[^','],%s", codigo,
        fecha, nombre,
        entradas,
        especial);

      char sql_insert[1024];

      sprintf(sql_insert, "INSERT INTO dias_de_fiesta VALUES('%s','%s','%s',%s,'%s');",
        codigo,
        fecha,
        nombre,
        entradas,
        especial);

      apertura = sqlite3_exec(database, sql_insert, 0, 0, & mensajeError);

      if (apertura != SQLITE_OK) {
        gestionarError(database);
        sqlite3_free(mensajeError);
        break;
      }
    }

    fclose(fp);

    char * sql2 = "CREATE TABLE dj(identificador INT PRIMARY KEY NOT NULL,nombre_comercial TEXT NOT NULL,genero_musical TEXT NOT NULL,fecha_nacimiento TEXT NOT NULL,numero_contacto TEXT NOT NULL);";
    apertura = sqlite3_exec(database, sql2, 0, 0, & mensajeError);
    if (apertura != SQLITE_OK) {
      gestionarError(database);
      sqlite3_free(mensajeError);
      cerrarConexion(database);
      return 1;
    }

    FILE * fp2 = fopen("ficheros/dj.csv", "r");
    if (!fp2) {
      printf("No se puede abrir el archivo\n");
      return 1;
    }

    char line2[1024];

    fgets(line2, sizeof(line2), fp2); // Saltar la primera línea (encabezados)

    while (fgets(line2, sizeof(line2), fp2)) {

      char identificador[50], nombre_comercial[50], genero_musical[50], fecha_nacimiento[50], numero_contacto[50];

      sscanf(line2, "%[^','],%[^','],%[^','],%[^','],%s", identificador,
        nombre_comercial,
        genero_musical,
        fecha_nacimiento,
        numero_contacto);

      char sql_insert[1024];

      sprintf(sql_insert, "INSERT INTO dj VALUES(%s,'%s','%s','%s','%s');",
        identificador,
        nombre_comercial,
        genero_musical,
        fecha_nacimiento,
        numero_contacto);

      apertura = sqlite3_exec(database, sql_insert, 0, 0, & mensajeError);

      if (apertura != SQLITE_OK) {
        gestionarError(database);
        sqlite3_free(mensajeError);
        break;

      }
    }

    fclose(fp2);

    char * sql3 = "CREATE TABLE listaeventos(Dia TEXT NOT NULL,Descripcion TEXT NOT NULL,nombre_discoteca TEXT NOT NULL,Aforo INT NOT NULL);";
    apertura = sqlite3_exec(database, sql3, 0, 0, & mensajeError);
    if (apertura != SQLITE_OK) {
      gestionarError(database);
      sqlite3_free(mensajeError);
      cerrarConexion(database);
      return 1;
    }

    FILE * fp3 = fopen("ficheros/listaeventos.csv", "r");
    if (!fp3) {
      printf("No se puede abrir el archivo\n");
      return 1;
    }

    char line3[1024];

    fgets(line3, sizeof(line3), fp3); // Saltar la primera línea (encabezados)

    while (fgets(line3, sizeof(line3), fp3)) {

      char Dia[50], Descripcion[50], nombre_discoteca[50], Aforo[50];

      sscanf(line3, "%[^','],%[^','],%[^','],%s", Dia,
        Descripcion,
        nombre_discoteca,
        Aforo);

      char sql_insert[1024];

      sprintf(sql_insert, "INSERT INTO listaeventos VALUES('%s','%s','%s',%s);",
        Dia,
        Descripcion,
        nombre_discoteca,
        Aforo);

      apertura = sqlite3_exec(database, sql_insert, 0, 0, & mensajeError);

      if (apertura != SQLITE_OK) {
        gestionarError(database);
        sqlite3_free(mensajeError);
        break;

      }
    }

    fclose(fp3);

    char * sql4 = "CREATE TABLE rrpp(Codigo INT PRIMARY KEY NOT NULL,nombre TEXT NOT NULL,zona_recogida TEXT NOT NULL,hora_recogida TEXT NOT NULL,numero_contacto TEXT NOT NULL);";
    apertura = sqlite3_exec(database, sql4, 0, 0, & mensajeError);
    if (apertura != SQLITE_OK) {
      gestionarError(database);
      sqlite3_free(mensajeError);
      cerrarConexion(database);
      return 1;
    }

    FILE * fp4 = fopen("ficheros/rrpp.csv", "r");
    if (!fp4) {
      printf("No se puede abrir el archivo\n");
      return 1;
    }

    char line4[1024];

    fgets(line4, sizeof(line4), fp4); // Saltar la primera línea (encabezados)

    while (fgets(line4, sizeof(line4), fp4)) {

      char Codigo[50], nombre[50], zona_recogida[50], hora_recogida[50], numero_contacto[50];

      sscanf(line4, "%[^','],%[^','],%[^','],%[^','],%s", Codigo,
        nombre,
        zona_recogida,
        hora_recogida,
        numero_contacto);

      char sql_insert[1024];

      sprintf(sql_insert, "INSERT INTO rrpp VALUES(%s,'%s','%s','%s','%s');",
        Codigo,
        nombre,
        zona_recogida,
        hora_recogida,
        numero_contacto);

      apertura = sqlite3_exec(database, sql_insert, 0, 0, & mensajeError);

      if (apertura != SQLITE_OK) {
        gestionarError(database);
        sqlite3_free(mensajeError);
        break;

      }
    }

    fclose(fp4);

    char * sql5 = "CREATE TABLE usuarios(Nombre TEXT NOT NULL,nombre_usuario TEXT NOT NULL,Sexo TEXT NOT NULL,Edad INT NOT NULL,email TEXT NOT NULL,password TEXT NOT NULL);";
    apertura = sqlite3_exec(database, sql5, 0, 0, & mensajeError);
    if (apertura != SQLITE_OK) {
      gestionarError(database);
      sqlite3_free(mensajeError);
      cerrarConexion(database);
      return 1;
    }

    FILE * fp5 = fopen("ficheros/usuarios.csv", "r");
    if (!fp5) {
      printf("No se puede abrir el archivo\n");
      return 1;
    }

    char line5[1024];

    fgets(line5, sizeof(line5), fp5); // Saltar la primera línea (encabezados)

    while (fgets(line5, sizeof(line5), fp5)) {

      char Nombre[50], nombre_usuario[50], Sexo[50], Edad[50], email[50], password[50];

      sscanf(line5, "%[^','],%[^','],%[^','],%[^','],%[^','],%s", Nombre,
        nombre_usuario,
        Sexo,
        Edad,
        email,
        password);

      char sql_insert[1024];

      sprintf(sql_insert, "INSERT INTO usuarios VALUES('%s','%s','%s',%s,'%s','%s');",
        Nombre,
        nombre_usuario,
        Sexo,
        Edad,
        email,
        password);

      apertura = sqlite3_exec(database, sql_insert, 0, 0, & mensajeError);

      if (apertura != SQLITE_OK) {
        gestionarError(database);
        sqlite3_free(mensajeError);
        break;

      }
    }
    fclose(fp5);
  }
  
  cerrarConexion(database);
  printf("\nSe mantendra cerrada hasta cualquier cambio\n");

  return 0;
}