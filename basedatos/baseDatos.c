#include <stdio.h>
#include <string.h>
#include "sqlite/sqlite3.h"


int db_existe(char * nombrearch) {
  FILE * arch = fopen(nombrearch, "r");
  if (arch) {
    fclose(arch);
    return 1;
  }
  return 0;
}

int main(int argc, char * argv[]) {
  sqlite3 * db;
  int db_exists = db_existe("basedatos.db");
  char * err_msg = 0;
  int rc = sqlite3_open("basedatos.db", & db);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "No se puede abrir la base de datos: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return 1;
  }

  printf("La base de datos se ha creado o abierto con éxito.\n");
  if (!db_exists) {
    // Implementacion de importacion de datos CSV
    char * sql = "CREATE TABLE dias_de_fiesta(Codigo TEXT PRIMARY KEY NOT NULL,Fecha TEXT NOT NULL,Nombre TEXT NOT NULL,Entradas INT NOT NULL,Especial TEXT NOT NULL);";
    rc = sqlite3_exec(db, sql, 0, 0, & err_msg);
    if (rc != SQLITE_OK) {
      fprintf(stderr, "SQL error: %s\n", err_msg);
      sqlite3_free(err_msg);
      sqlite3_close(db);
      return 1;
    }

    FILE * fp = fopen("dias_de_fiesta.csv", "r");
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

      rc = sqlite3_exec(db, sql_insert, 0, 0, & err_msg);

      if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        break;

      }
    }

    fclose(fp);

    char * sql2 = "CREATE TABLE dj(identificador INT PRIMARY KEY NOT NULL,nombre_comercial TEXT NOT NULL,genero_musical TEXT NOT NULL,fecha_nacimiento TEXT NOT NULL,numero_contacto TEXT NOT NULL);";
    rc = sqlite3_exec(db, sql2, 0, 0, & err_msg);
    if (rc != SQLITE_OK) {
      fprintf(stderr, "SQL error: %s\n", err_msg);
      sqlite3_free(err_msg);
      sqlite3_close(db);
      return 1;
    }

    FILE * fp2 = fopen("dj.csv", "r");
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

      rc = sqlite3_exec(db, sql_insert, 0, 0, & err_msg);

      if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        break;

      }
    }

    fclose(fp2);

    char * sql3 = "CREATE TABLE listaeventos(Dia TEXT NOT NULL,Descripcion TEXT NOT NULL,nombre_discoteca TEXT NOT NULL,Aforo INT NOT NULL);";
    rc = sqlite3_exec(db, sql3, 0, 0, & err_msg);
    if (rc != SQLITE_OK) {
      fprintf(stderr, "SQL error: %s\n", err_msg);
      sqlite3_free(err_msg);
      sqlite3_close(db);
      return 1;
    }

    FILE * fp3 = fopen("listaeventos.csv", "r");
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

      rc = sqlite3_exec(db, sql_insert, 0, 0, & err_msg);

      if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        break;

      }
    }

    fclose(fp3);

    char * sql4 = "CREATE TABLE rrpp(Codigo INT PRIMARY KEY NOT NULL,nombre TEXT NOT NULL,zona_recogida TEXT NOT NULL,hora_recogida TEXT NOT NULL,numero_contacto TEXT NOT NULL);";
    rc = sqlite3_exec(db, sql4, 0, 0, & err_msg);
    if (rc != SQLITE_OK) {
      fprintf(stderr, "SQL error: %s\n", err_msg);
      sqlite3_free(err_msg);
      sqlite3_close(db);
      return 1;
    }

    FILE * fp4 = fopen("rrpp.csv", "r");
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

      rc = sqlite3_exec(db, sql_insert, 0, 0, & err_msg);

      if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        break;

      }
    }

    fclose(fp4);

    char * sql5 = "CREATE TABLE usuarios(Nombre TEXT NOT NULL,nombre_usuario TEXT NOT NULL,Sexo TEXT NOT NULL,Edad INT NOT NULL,email TEXT NOT NULL,password TEXT NOT NULL);";
    rc = sqlite3_exec(db, sql5, 0, 0, & err_msg);
    if (rc != SQLITE_OK) {
      fprintf(stderr, "SQL error: %s\n", err_msg);
      sqlite3_free(err_msg);
      sqlite3_close(db);
      return 1;
    }

    FILE * fp5 = fopen("usuarios.csv", "r");
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

      rc = sqlite3_exec(db, sql_insert, 0, 0, & err_msg);

      if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        break;

      }
    }

    fclose(fp5);

  }
  sqlite3_close(db);
  return 0;
}