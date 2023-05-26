#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite/sqlite3.h"
#include "baseDatos.h"
#include "../estructuras/reservarlocal_est.h"
#include "../estructuras/entrada_est.h"
#include <winsock2.h>

extern SOCKET comm_socket;

#define MAX_REGISTRO 20
#define MAX_LOGIN 15
#define MAX_NOMBRE_USU 20
#define MAX_CONTRASENYA 20
#define MAX_INPUT 30

sqlite3* database;
int apertura;
int aperturaInsert;
int existeBD;
char* mensajeError = NULL;
char* errorMessage = NULL;
int admin = 1;

    // ACCIONES BASICAS CON LA BASE DE DATOS

int dbExiste(const char* fichero) {
  FILE* arch = fopen(fichero, "r");

  if (arch) {
    fclose(arch);
    return 1;
  }
  return 0;
}

int reiniciarBD() {
  abrirConexion();

  inicializarUsuarios();
  inicializarDiasDeFiesta();
  inicializarDJ();
  inicializarRRPP();
  inicializarListaEventos();
  inicializarEntradas();
  inicializarReservaLocal();

  cerrarConexion(database);
}

int verificarFecha(char* fecha) {
    int dia, mes, anio;
    
    // Convierte los primeros dos caracteres en el día
    dia = atoi(fecha);
    
    // Convierte los caracteres 3 y 4 en el mes
    mes = atoi(fecha + 3);
    
    // Convierte los últimos dos caracteres en el año
    anio = atoi(fecha + 6);
    
    // Verifica si los valores son válidos para día, mes y año
    if (dia < 1 || dia > 31) {
        return 0;
    }
    
    if (mes < 1 || mes > 12) {
        return 0;
    }
    
    if (anio < 23 || anio > 99) {
        return 0;
    }
    
    return 1;
}

    // CONEXION A LA BASE DE DATOS

void cerrarConexion(sqlite3* baseDatos) {
  sqlite3_close(baseDatos);
  //fprintf(stdout, "\nLa Base De Datos se cerro exitosamente\n");
}

int abrirConexion() {
  existeBD = dbExiste("basedatosSSR.db");
  apertura = sqlite3_open("basedatosSSR.db", &database);
  
  if (apertura != SQLITE_OK) {
    fprintf(stderr, "No se puede abrir la Base De Datos: %s\n", gestionarError(database));
    cerrarConexion(database);
    return 0;

  } else {
    //fprintf(stdout, "\nLa Base De Datos se abrio exitosamente\n");
    return 1;
  }
}

    // GESTION DE SUCESOS EN LA BASE DE DATOS

int gestionarError(sqlite3* baseDatos) {
  int resultado = strcmp(sqlite3_errmsg(baseDatos), "not an error");
    
  if (resultado == 0) {
      return 0;
  } else {

    fprintf(stderr, "\nSQL Error: %s\n", sqlite3_errmsg(baseDatos));
    return sqlite3_errcode(baseDatos);
  }
}

void gestionarFree(char* str) {
  sqlite3_free(str);
}

    // INICIALIZACION DE LOS VALORES DE LA BASE DE DATOS (VALORES POR DEFECTO)

int inicializarReservaLocal() {
    abrirConexion();

    //Eliminar tabla si existe
    const char* sentenciaRL = "DROP TABLE IF EXISTS reservalocal;";
    int resultadoRL = sqlite3_exec(database, sentenciaRL, NULL, NULL, &mensajeError);

    if (resultadoRL != SQLITE_OK) {
        // Manejar el error si ocurre
        gestionarError(database);
        gestionarFree(mensajeError);
        cerrarConexion(database);
        return 1;
    }

    // Crear tabla
    const char* sqlRL = "CREATE TABLE reservalocal(codigo TEXT PRIMARY KEY NOT NULL, fecha TEXT NOT NULL, nombrediscoteca TEXT NOT NULL, aforo INT NOT NULL, numerotarjeta TEXT NOT NULL, cvvtarjeta TEXT NOT NULL, caducidadtarjeta TEXT NOT NULL)";
    apertura = sqlite3_exec(database, sqlRL, 0, 0, &mensajeError);
    if (apertura != SQLITE_OK) {
        gestionarError(database);
        gestionarFree(mensajeError);
        cerrarConexion(database);
        return 1;
    }
    
    cerrarConexion(database);
}

int inicializarEntradas() {
    abrirConexion();

    //Eliminar tabla si existe
    const char* sentenciaEntra = "DROP TABLE IF EXISTS entradas;";
    int resultadoEntra = sqlite3_exec(database, sentenciaEntra, NULL, NULL, &mensajeError);

    if (resultadoEntra != SQLITE_OK) {
        // Manejar el error si ocurre
        gestionarError(database);
        gestionarFree(mensajeError);
        cerrarConexion(database);
        return 1;
    }

    // Crear tabla
    const char* sqlEntra = "CREATE TABLE entradas(codigoFecha INT PRIMARY KEY NOT NULL, fechaEntrada TEXT NOT NULL, nombreDiscoteca TEXT NOT NULL, numeroEntradas INT NOT NULL, cuentaGmail TEXT NOT NULL, numeroTarjetaCredito TEXT NOT NULL, cvvTarjeta TEXT NOT NULL, caducidadTarjeta TEXT NOT NULL, tipoEntrada TEXT NOT NULL, precio REAL NOT NULL, nombreUsuario TEXT NOT NULL)";
    apertura = sqlite3_exec(database, sqlEntra, 0, 0, &mensajeError);
    if (apertura != SQLITE_OK) {
        gestionarError(database);
        gestionarFree(mensajeError);
        cerrarConexion(database);
        return 1;
    }

    cerrarConexion(database);
}


int inicializarDiasDeFiesta() {

  abrirConexion();
  //Eliminar tabla si existe
  const char* sentenciaDDF = "DROP TABLE IF EXISTS dias_de_fiesta;";
  int resultadoDDF = sqlite3_exec(database, sentenciaDDF, NULL, NULL, &mensajeError);

  if (resultadoDDF != SQLITE_OK) {
      // Manejar el error si ocurre
      gestionarError(database);
      gestionarFree(mensajeError);

      cerrarConexion(database);
      return 1;
  }

  // Implementacion de importacion de datos CSV
  const char* sqlDDF = "CREATE TABLE dias_de_fiesta(codigo TEXT PRIMARY KEY NOT NULL, fecha TEXT NOT NULL, nombre TEXT NOT NULL, entradas INT NOT NULL, especial TEXT NOT NULL)";
  apertura = sqlite3_exec(database, sqlDDF, 0, 0, &mensajeError);

  if (apertura != SQLITE_OK) {
    gestionarError(database);
    gestionarFree(mensajeError);

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

    sscanf(line, "%[^','],%[^','],%[^','],%[^','],%s",
      codigo,
      fecha, 
      nombre,
      entradas,
      especial);

    char sql_insert[1024];

    sprintf(sql_insert, "INSERT INTO dias_de_fiesta VALUES('%s','%s','%s',%s,'%s');",
      codigo,
      fecha,
      nombre,
      entradas,
      especial);

    aperturaInsert = sqlite3_exec(database, sql_insert, 0, 0, &mensajeError);

    if (apertura != SQLITE_OK) {
      gestionarFree(mensajeError);
      //gestionarError(database);
      gestionarFree(errorMessage);

      cerrarConexion(database);
      return 1;
    }
  }
  
  fclose(fp);
  cerrarConexion(database);
}

int inicializarDJ() {

  abrirConexion();
  //Eliminar tabla si existe
  const char* sentenciaDJ = "DROP TABLE IF EXISTS dj;";
  int resultadoDJ = sqlite3_exec(database, sentenciaDJ, NULL, NULL, &mensajeError);

  if (resultadoDJ != SQLITE_OK) {
      // Manejar el error si ocurre
      gestionarError(database);
      gestionarFree(mensajeError);

      cerrarConexion(database);
      return 1;
  }

  // Implementacion de importacion de datos CSV
  const char* sqlDJ = "CREATE TABLE dj(identificador INT PRIMARY KEY NOT NULL, nombre_comercial TEXT NOT NULL, genero_musical TEXT NOT NULL, fecha_nacimiento TEXT NOT NULL, numero_contacto TEXT NOT NULL);";
  apertura = sqlite3_exec(database, sqlDJ, 0, 0, &mensajeError);

  if (apertura != SQLITE_OK) {
    gestionarError(database);
    gestionarFree(mensajeError);

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

    aperturaInsert = sqlite3_exec(database, sql_insert, 0, 0, &mensajeError);
    
    if (apertura != SQLITE_OK) {
      gestionarFree(mensajeError);
      gestionarError(database);
      gestionarFree(errorMessage);

      cerrarConexion(database);
      return 1;
    }
  }
  
  fclose(fp2);
  cerrarConexion(database);
}

int inicializarListaEventos() {

  abrirConexion();
  //Eliminar tabla si existe
  const char* sentenciaLE = "DROP TABLE IF EXISTS eventos;";
  int resultadoLE = sqlite3_exec(database, sentenciaLE, NULL, NULL, &mensajeError);

  if (resultadoLE != SQLITE_OK) {
      // Manejar el error si ocurre
      gestionarError(database);
      gestionarFree(mensajeError);

      cerrarConexion(database);
      return 1;
  }

  // Implementacion de importacion de datos CSV
  const char* sqlEvent = "CREATE TABLE eventos(dia TEXT NOT NULL, descripcion TEXT NOT NULL, nombre_discoteca TEXT NOT NULL, aforo TEXT NOT NULL);";
  apertura = sqlite3_exec(database, sqlEvent, 0, 0, &mensajeError);

  if (apertura != SQLITE_OK) {
    gestionarError(database);
    gestionarFree(mensajeError);

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

    char dia[50], descripcion[80], nombre_discoteca[50], aforo[50];

    sscanf(line3, "%[^','],%[^','],%[^','],%s", dia,
      descripcion,
      nombre_discoteca,
      aforo);

    char sql_insert[1024];

    sprintf(sql_insert, "INSERT INTO eventos VALUES('%s','%s','%s',%s);",
      dia,
      descripcion,
      nombre_discoteca,
      aforo);

    aperturaInsert = sqlite3_exec(database, sql_insert, 0, 0, &mensajeError);
    
    if (apertura != SQLITE_OK) {
      gestionarFree(mensajeError);
      gestionarError(database);
      gestionarFree(errorMessage);

      cerrarConexion(database);
      return 1;
    }
  }

  fclose(fp3);
  cerrarConexion(database);
}

int inicializarRRPP() {

  abrirConexion();
  //Eliminar tabla si existe
  const char* sentenciaRRPP = "DROP TABLE IF EXISTS rrpp;";
  int resultadoRRPP = sqlite3_exec(database, sentenciaRRPP, NULL, NULL, &mensajeError);

  if (resultadoRRPP != SQLITE_OK) {
      // Manejar el error si ocurre
      gestionarError(database);
      gestionarFree(mensajeError);

      cerrarConexion(database);
      return 1;
  }

  // Implementacion de importacion de datos CSV
  const char* sqlRRPP = "CREATE TABLE rrpp(codigo INT PRIMARY KEY NOT NULL, nombre TEXT NOT NULL, zona_recogida TEXT NOT NULL, hora_recogida TEXT NOT NULL, numero_contacto TEXT NOT NULL);";
  apertura = sqlite3_exec(database, sqlRRPP, 0, 0, &mensajeError);

  if (apertura != SQLITE_OK) {
    gestionarError(database);
    gestionarFree(mensajeError);

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

    char codigo[50], nombre[50], zona_recogida[50], hora_recogida[50], numero_contacto[50];

    sscanf(line4, "%[^','],%[^','],%[^','],%[^','],%s", codigo,
      nombre,
      zona_recogida,
      hora_recogida,
      numero_contacto);

    char sql_insert[1024];

    sprintf(sql_insert, "INSERT INTO rrpp VALUES(%s,'%s','%s','%s','%s');",
      codigo,
      nombre,
      zona_recogida,
      hora_recogida,
      numero_contacto);

    aperturaInsert = sqlite3_exec(database, sql_insert, 0, 0, &mensajeError);
    
    if (apertura != SQLITE_OK) {
      gestionarFree(mensajeError);
      gestionarError(database);
      gestionarFree(errorMessage);

      cerrarConexion(database);
      return 1;
    }
  }

  fclose(fp4);
  cerrarConexion(database);
}

int inicializarUsuarios() {

  abrirConexion();
  //Eliminar tabla si existe
  const char* sentenciaUsu = "DROP TABLE IF EXISTS usuarios;";
  int resultadoUsu = sqlite3_exec(database, sentenciaUsu, NULL, NULL, &mensajeError);

  if (resultadoUsu != SQLITE_OK) {
      // Manejar el error si ocurre
      gestionarError(database);
      gestionarFree(mensajeError);
      
      cerrarConexion(database);
      return 1;
  }

  // Implementacion de importacion de datos CSV
  const char* sqlUsu = "CREATE TABLE usuarios(nombre TEXT NOT NULL, usuario TEXT NOT NULL, sexo TEXT NOT NULL, edad INT NOT NULL, email TEXT NOT NULL, contrasenya TEXT NOT NULL, admin TEXT NOT NULL);";
  apertura = sqlite3_exec(database, sqlUsu, 0, 0, &mensajeError);

  if (apertura != SQLITE_OK) {
    gestionarError(database);
    gestionarFree(mensajeError);

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

    char nombre[50], nombre_usuario[50], sexo[50], edad[50], email[50], password[50], admin[50];

    sscanf(line5, "%[^','],%[^','],%[^','],%[^','],%[^','],%[^','],%s", nombre,
      nombre_usuario,
      sexo,
      edad,
      email,
      password,
      admin);

    char sql_insert[1024];

    sprintf(sql_insert, "INSERT INTO usuarios VALUES('%s','%s','%s',%s,'%s','%s','%s');",
      nombre,
      nombre_usuario,
      sexo,
      edad,
      email,
      password,
      admin);

    aperturaInsert = sqlite3_exec(database, sql_insert, 0, 0, &mensajeError);

    if (apertura != SQLITE_OK) {
      gestionarFree(mensajeError);
      gestionarError(database);
      gestionarFree(errorMessage);

      cerrarConexion(database);
      return 1;
    }
  }

  fclose(fp5);
  cerrarConexion(database);
}

int inicializacion() {
  
  abrirConexion();

  if (!existeBD) {
    //Inicializar las tablas
    inicializarUsuarios();
    inicializarDiasDeFiesta();
    inicializarDJ();
    inicializarRRPP();
    inicializarListaEventos();
    inicializarEntradas();
    inicializarReservaLocal();
  }
  
  cerrarConexion(database);
  printf("La Base De Datos esta activa y lista para ser utilizada\n\n");

  return 0;
}

// FUNCIONES PARA LIMPIAR EL CODIGO

char* limpiarInput(char* input) {

  char* limpio = (char*) malloc(MAX_INPUT * sizeof(char));
  sscanf(input, "%s", limpio); //le quita el 'n' (si lo hay)

  clearIfNeeded(input, MAX_INPUT); //le quita el 'n' (si lo hay)
  fflush(stdout);
  fflush(stdin);

  return limpio;
}

void clearIfNeeded(char * str, int max_line) {
  // Limpia los caracteres de más introducidos
  if ((strlen(str) == max_line - 1) && (str[max_line - 2] != '\n'))
    while (getchar() != '\n');
}

    // FUNCION PARA IMPRIMIR POR CONSOLA LOS ELEMENTOS DE LA BASE DE DATOS SELECCIONADOS

static int callbackClient(void* socket_fd, int argc, char **argv, char **azColName) {
  int i;
  char buffer[1024];
  int n = 0;
  n += sprintf(buffer + n, "\e[37m\e[1m");
  for (i = 0; i < argc; i++) {
    if (i > 0) {
      n += sprintf(buffer + n, " - ");
    }
    n += sprintf(buffer + n, "%s", argv[i] ? argv[i] : "NULL");
  }
  printf("DESPUES DEL FOR\n");
  n += sprintf(buffer + n, "\n");
  n += sprintf(buffer + n, "\e[0m");
  send(*(SOCKET*)socket_fd, buffer, n, 0);
  
  return 0;
}


static int callback(void *NotUsed, int argc, char **argv, char** azColName) {
  int i;
  printf("\e[37m\e[1m");
  for (i = 0; i < argc; i++) {
    if (i > 0) {
      printf(" - ");
    }
    printf("%s", argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  printf("\e[0m");
  return 0;
}

    // COMPROBACION DE EXISTENCIA DE DIFERENTES ELEMENTOS EN LA BASE DE DATOS 

int comprobarAdmin(char* user) {
  sqlite3_stmt * statement;
  char * mensajeError = 0;
  int apertura = 0;
  int busqueda = 0;

  abrirConexion();

  if (gestionarError(database) != SQLITE_OK) {
    printf("Error en la conexión a la base de datos: %s\n", gestionarError(database));
  }

  const char* sentencia = "SELECT admin FROM usuarios WHERE usuario = ? AND admin = 'Si';";
  busqueda = sqlite3_prepare_v2(database, sentencia, -1, & statement, 0);

  sqlite3_bind_text(statement, 1, user, strlen(user), SQLITE_STATIC);

  if (busqueda != SQLITE_OK) {
    printf("Error preparing SQL statement: %s\n", gestionarError(database));
    gestionarFree(mensajeError);
    fprintf(stderr, "Error en la consulta: %s\n", mensajeError);
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 1;
  }

  busqueda = sqlite3_step(statement);

  if (mensajeError != NULL) {
    gestionarFree(mensajeError);
    //gestionarError(database);
    cerrarConexion(database);
    return 1;
  }

  if (busqueda == SQLITE_ROW) {
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 0;

  } else if (busqueda != SQLITE_OK) {
    gestionarFree(mensajeError);
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 1;

  } else {
    printf("\nNo se ha encontrado el usuario\n");
    sqlite3_finalize(statement);
    cerrarConexion(database);
  }
}

int comprobarExistencia(char* username, char* password) {
  sqlite3_stmt * statement;
  char * mensajeError = 0;
  int apertura = 0;
  int busqueda = 0;

  abrirConexion();
  if (gestionarError(database) != SQLITE_OK) {
    printf("Error en la conexión a la base de datos: %s\n", gestionarError(database));
  }

  const char* sentencia = "SELECT usuario, contrasenya FROM usuarios WHERE usuario = ? AND contrasenya = ?;";
  busqueda = sqlite3_prepare_v2(database, sentencia, -1, & statement, 0);

  sqlite3_bind_text(statement, 1, username, strlen(username), SQLITE_STATIC);
  sqlite3_bind_text(statement, 2, password, strlen(password), SQLITE_STATIC);

  comprobarAdmin(username);

  if (busqueda != SQLITE_OK) {
    printf("Error en la consulta: %s\n", gestionarError(database));
    gestionarFree(mensajeError);
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 1;
  }

  busqueda = sqlite3_step(statement);

  if (mensajeError != NULL) {
    gestionarFree(mensajeError);
    //gestionarError(database);
    cerrarConexion(database);
    return 1;
  }

  if (busqueda == SQLITE_ROW) {
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 0;

  } else if (busqueda != SQLITE_OK) {
    printf("\nNo se ha encontrado el usuario\n");
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return -1;

  } else {
    gestionarFree(mensajeError);
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 1;
  }

  cerrarConexion(database);
  return 0;
}

int comprobarUsuario(char* usuario) {
  sqlite3_stmt * statement;
  char * mensajeError = 0;
  int apertura = 0;
  int busqueda = 0;

  abrirConexion();
  if (gestionarError(database) != SQLITE_OK) {
    printf("Error en la conexión a la base de datos: %s\n", gestionarError(database));
  }

  const char* sentencia = "SELECT usuario FROM usuarios WHERE usuario = ?;";
  busqueda = sqlite3_prepare_v2(database, sentencia, -1, & statement, 0);

  sqlite3_bind_text(statement, 1, usuario, strlen(usuario), SQLITE_STATIC);

  if (busqueda != SQLITE_OK) {
    printf("Error en la consulta: %s\n", gestionarError(database));
    gestionarFree(mensajeError);
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 1;
  }

  busqueda = sqlite3_step(statement);

  if (mensajeError != NULL) {
    gestionarFree(mensajeError);
    //gestionarError(database);
    cerrarConexion(database);
    return 1;
  }

  if (busqueda == SQLITE_ROW) {
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 0;

  } else if (busqueda != SQLITE_OK) {
    printf("\nNo se ha encontrado el usuario\n");
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return -1;

  } else {
    gestionarFree(mensajeError);
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 1;
  }

  cerrarConexion(database);
  return 0;
}

int comprobarCodigoLocal(char* cod) {
  int longitud = strlen(cod);
  if (longitud > 0 && cod[longitud - 1] == ',') {
    cod[longitud - 1] = '\0';
  }

  abrirConexion();
  sqlite3_stmt * statement;
  int busqueda = 0;

  const char* sentencia = "SELECT codigo FROM dias_de_fiesta WHERE codigo = ? AND entradas = 400";

  if (gestionarError(database) != SQLITE_OK) {
    printf("Error en la conexión a la base de datos: %s\n", gestionarError(database));
    cerrarConexion(database);
    return 0;
  }

  busqueda = sqlite3_prepare_v2(database, sentencia, -1, &statement, NULL);

  if (busqueda != SQLITE_OK) {
    printf("Error al preparar la consulta: %s\n", gestionarError(database));
    gestionarFree(mensajeError);
    cerrarConexion(database);
    return 0;
  }

  sqlite3_bind_text(statement, 1, cod, strlen(cod), SQLITE_STATIC);
  busqueda = sqlite3_step(statement);

  if (busqueda == SQLITE_ROW) {
    printf("\nCODIGO ENCONTRADO\n");
    sqlite3_finalize(statement);
    cerrarConexion(database);

    return 1;
  } else if (busqueda != SQLITE_DONE) {
    fprintf(stderr, "Error en la consulta: %s\n", gestionarError(database));

    gestionarFree(mensajeError);
    sqlite3_finalize(statement);
    cerrarConexion(database);

    return 0;
  } else {
    printf("No se ha encontrado el codigo\n");
    sqlite3_finalize(statement);
    cerrarConexion(database);

    return 0;
  }
}

int comprobarCodigoRRPP(char* cod) {
  int longitud = strlen(cod);
  if (longitud > 0 && cod[longitud - 1] == ',') {
      cod[longitud - 1] = '\0';
  }

  abrirConexion();
  sqlite3_stmt * statement;
  int busqueda = 0;

  const char* sentencia = "SELECT codigo FROM rrpp WHERE codigo = ?";

  if (gestionarError(database) != SQLITE_OK) {
    printf("Error en la conexión a la base de datos: %s\n", gestionarError(database));
  }

  busqueda = sqlite3_prepare_v2(database, sentencia, -1, &statement, NULL);
  
  if (busqueda != SQLITE_OK) {
    printf("Error al ejecutar la sentencia: %s\n", gestionarError(database));
    gestionarFree(mensajeError);
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 0;
  }

  sqlite3_bind_text(statement, 1, cod, strlen(cod), SQLITE_STATIC);
  busqueda = sqlite3_step(statement);

  if (mensajeError != NULL) {
    gestionarFree(mensajeError);
    fprintf(stderr, "Error en la consulta: %s\n", mensajeError);
    cerrarConexion(database);
    return 0;
  }

  if (busqueda == SQLITE_ROW) {
    printf("\nCODIGO ENCONTRADO\n");
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 1;

  } else if (busqueda != SQLITE_OK) {
    fprintf(stderr, "Error en la consulta: %s\n", gestionarError(database));
    gestionarFree(mensajeError);
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 0;

  } else {
    printf("\nNo se ha encontrado el codigo\n");
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 0;
  }

  cerrarConexion(database);
}

int comprobarFecha(char* fecha, int evento) {
  sqlite3_stmt * statement;
  char * mensajeError = 0;
  int apertura = 0;
  int busqueda = 0;
  const char* sentencia;

  abrirConexion();
  if (gestionarError(database) != SQLITE_OK) {
    printf("Error en la conexión a la base de datos: %s\n", gestionarError(database));
  }

  //Si es un evento, la sentencia cambia a la tabla eventos
  if (evento == 0) {
    sentencia = "SELECT dia FROM eventos WHERE dia = ?;";
  } else {
    sentencia = "SELECT fecha FROM dias_de_fiesta WHERE fecha = ?;";
  }

  busqueda = sqlite3_prepare_v2(database, sentencia, -1, & statement, NULL);

  if (busqueda != SQLITE_OK) {
    printf("Error en la consulta: %s\n", gestionarError(database));
    gestionarFree(mensajeError);
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 1;
  }

  sqlite3_bind_text(statement, 1, fecha, strlen(fecha), SQLITE_STATIC);
  busqueda = sqlite3_step(statement);

  if (mensajeError != NULL) {
    gestionarFree(mensajeError);

    cerrarConexion(database);
    return 1;
  }

  if (busqueda == SQLITE_ROW) {
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 0;

  } else if (busqueda != SQLITE_OK) {
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return -1;

  } else {
    gestionarFree(mensajeError);
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 1;
  }

  cerrarConexion(database);
  return 0;
}    

int comprobarEntrada(char* codigo) {

  int longitud = strlen(codigo);
  if (longitud > 0 && codigo[longitud - 1] == ',') {
      codigo[longitud - 1] = '\0';
  }

  abrirConexion();
  sqlite3_stmt * statement;
  char * mensajeError = 0;
  int apertura = 0;
  int busqueda = 0;

  const char* sentencia = "SELECT entradas FROM dias_de_fiesta WHERE codigo = ?";

  if (gestionarError(database) != SQLITE_OK) {
    printf("Error en la conexión a la base de datos: %s\n", gestionarError(database));
  }
  busqueda = sqlite3_prepare_v2(database, sentencia, -1, & statement, 0);

  if (busqueda != SQLITE_OK) {
    printf("Error en la consulta: %s\n", gestionarError(database));
    gestionarFree(mensajeError);
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 1;
  }

  sqlite3_bind_text(statement, 1, codigo, strlen(codigo), SQLITE_STATIC);
  busqueda = sqlite3_step(statement);

  if (mensajeError != NULL) {
    gestionarFree(mensajeError);

    cerrarConexion(database);
    return 1;
  }

  if (busqueda == SQLITE_ROW) {
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 0;

  } else if (busqueda != SQLITE_OK) {
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return -1;

  } else {
    gestionarFree(mensajeError);
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 1;
  }

  cerrarConexion(database);
  return 0;
}
    
    // CARGAR/MOSTRAR ELEMENTOS DE LA BASE DE DATOS SELECCIONADOS CLIENTE
 
void mostrarLocales(SOCKET socket_fd) {
  abrirConexion();

  char* error = 0;
  int aper;

  const char* sentencia = "SELECT * FROM dias_de_fiesta WHERE entradas = 400";
  aper = sqlite3_exec(database, sentencia, callbackClient, (void*)&socket_fd, &error);

  if (aper != SQLITE_OK) {
      fprintf(stderr, "Error en la consulta SQL: %s\n", error);
      sqlite3_free(error);
  }
    
  cerrarConexion(database);
}

void mostrarFiestas(SOCKET socket_fd) {
  abrirConexion();

  char* error = 0;
  int aper;

  const char* sentencia = "SELECT * FROM dias_de_fiesta WHERE entradas > 0";
  aper = sqlite3_exec(database, sentencia, callbackClient, (void*)&socket_fd, &error);

  if (aper != SQLITE_OK) {
      fprintf(stderr, "Error en la consulta SQL: %s\n", error);
      sqlite3_free(error);
  }
  
  printf("");
  cerrarConexion(database);
}

void mostrarlistadoeventos(SOCKET socket_fd) {
	abrirConexion();
  
  char* error = 0;
  int aper;

  const char* sentencia = "SELECT * FROM eventos";
  printf("ANTES");
  aper = sqlite3_exec(database, sentencia, callbackClient, (void*)&socket_fd, &error);
  printf("DESPUES");
  if (aper != SQLITE_OK) {
      fprintf(stderr, "Error en la consulta SQL: %s\n", error);
      sqlite3_free(error);
  }

	cerrarConexion(database);
}

void mostrarDJ(SOCKET socket_fd) {
  abrirConexion();

  char* error = 0;
  int aper;

  const char* sentencia = "SELECT * FROM dj";
  aper = sqlite3_exec(database, sentencia, callbackClient, (void*)&socket_fd, &error);
  
  if (aper != SQLITE_OK) {
      fprintf(stderr, "Error en la consulta SQL: %s\n", error);
      sqlite3_free(error);
  }

	cerrarConexion(database);
}

void mostrarRRPP(SOCKET socket_fd) {
  abrirConexion();

  char* error = 0;
  int aper;

  const char* sentencia = "SELECT * FROM rrpp";
  aper = sqlite3_exec(database, sentencia, callbackClient, (void*)&socket_fd, &error);
  
  if (aper != SQLITE_OK) {
      fprintf(stderr, "Error en la consulta SQL: %s\n", error);
      sqlite3_free(error);
  }

	cerrarConexion(database);
}

// CARGAR/MOSTRAR ELEMENTOS DE LA BASE DE DATOS SELECCIONADOS ADMIN

void mostrarLocalesAdmin() {
  abrirConexion();

  char* error = 0;
  int aper;

  const char* sentencia = "SELECT * FROM dias_de_fiesta WHERE entradas = 400";
  aper = sqlite3_exec(database, sentencia, callback, 0, &error);

  if (aper != SQLITE_OK) {
      fprintf(stderr, "Error en la consulta SQL: %s\n", error);
      sqlite3_free(error);
  }
    
  cerrarConexion(database);
}

void mostrarFiestasAdmin() {
  abrirConexion();

  char* error = 0;
  int aper;

  const char* sentencia = "SELECT * FROM dias_de_fiesta WHERE entradas > 0";
  aper = sqlite3_exec(database, sentencia, callback, 0, &error);

  if (aper != SQLITE_OK) {
      fprintf(stderr, "Error en la consulta SQL: %s\n", error);
      sqlite3_free(error);
  }
  
  printf("");
  cerrarConexion(database);
}

void mostrarlistadoeventosAdmin() {
	abrirConexion();

  char* error = 0;
  int aper;

  const char* sentencia = "SELECT * FROM eventos";
  aper = sqlite3_exec(database, sentencia, callback, 0, &error);
  
  if (aper != SQLITE_OK) {
      fprintf(stderr, "Error en la consulta SQL: %s\n", error);
      sqlite3_free(error);
  }

	cerrarConexion(database);
}

void mostrarDJAdmin() {
  abrirConexion();

  char* error = 0;
  int aper;

  const char* sentencia = "SELECT * FROM dj";
  aper = sqlite3_exec(database, sentencia, callback, 0, &error);
  
  if (aper != SQLITE_OK) {
      fprintf(stderr, "Error en la consulta SQL: %s\n", error);
      sqlite3_free(error);
  }

	cerrarConexion(database);
}

void mostrarRRPPAdmin() {
  abrirConexion();

  char* error = 0;
  int aper;

  const char* sentencia = "SELECT * FROM rrpp";
  aper = sqlite3_exec(database, sentencia, callback, 0, &error);
  
  if (aper != SQLITE_OK) {
      fprintf(stderr, "Error en la consulta SQL: %s\n", error);
      sqlite3_free(error);
  }

	cerrarConexion(database);
}

    // INSERTAR DATOS BASICOS A LA BASE DE DATOS

int insertarDiaFiesta(char* fecha, char* nomDiscoteca, char* eventoEsp) {
  int entradas = 400;
  int ultimo = 0;

  const char* codigo = "";
  int longitudCodigo = strlen(codigo) + 1;
  char* codigoFinal = (char*) malloc(longitudCodigo * sizeof(char));

  ultimo = buscarUltimoCodigo() + 1;
  abrirConexion();

  sprintf(codigoFinal, "%d", ultimo);
  printf("%s\n", codigoFinal);

  char sql_insertFi[1024];

  sprintf(sql_insertFi, "INSERT INTO dias_de_fiesta VALUES('%s','%s','%s',%d,'%s');",
    codigoFinal,
    fecha,
    nomDiscoteca,
    entradas,
    eventoEsp);

  aperturaInsert = sqlite3_exec(database, sql_insertFi, 0, 0, &mensajeError);

  if (aperturaInsert != SQLITE_OK) {
    gestionarFree(mensajeError);
    gestionarError(database);
    gestionarFree(errorMessage);

    cerrarConexion(database);
    return 1;
  }

  cerrarConexion(database);
  return 0;
}

int insertarRegistro(char* nombre, char* usuario, char* sexo, int edad, char* correo, char* contra) {

  abrirConexion();

  const char* admin = "No";
  char lineRe[1024];
  sprintf(lineRe, "%s,%s,%s,%d,%s,%s,%s", nombre, usuario, sexo, edad, correo, contra, admin);

  char sql_insertRe[1024];

  sprintf(sql_insertRe, "INSERT INTO usuarios VALUES('%s','%s','%s',%d,'%s','%s','%s');",
    nombre,
    usuario,
    sexo,
    edad,
    correo,
    contra,
    admin);

  aperturaInsert = sqlite3_exec(database, sql_insertRe, 0, 0, &mensajeError);

  if (aperturaInsert != SQLITE_OK) {
    gestionarFree(mensajeError);
    //gestionarError(database);
    gestionarFree(errorMessage);

    cerrarConexion(database);
    return 1;
  }

  //printf("\nInsertado\n");
  cerrarConexion(database);
  return 0;
}


int insertarEvento(char* fecha, char* nombreDisco, char* descripcionEvento) {

  abrirConexion();
  const char* aforo = "400";

  char lineEven[1024];
  sprintf(lineEven, "%s,%s,%s,%s", fecha, descripcionEvento, nombreDisco, aforo);

  char sql_insertEven[1024];

  sprintf(sql_insertEven, "INSERT INTO eventos VALUES('%s','%s','%s',%s);",
    fecha,
    descripcionEvento,
    nombreDisco,
    aforo);

  aperturaInsert = sqlite3_exec(database, sql_insertEven, 0, 0, &mensajeError);
  
  if (aperturaInsert != SQLITE_OK) {
    gestionarFree(mensajeError);
    //gestionarError(database);
    gestionarFree(errorMessage);
 
    cerrarConexion(database);
    return 1;
  }

  cerrarConexion(database);
  return 0;
}

    // INSERTAR DATOS DE COMPRA A LA BASE DE DATOS

int insertarEntrada(char* codigoFecha, char* fechaEntrada, char* nombreDiscoteca, char* numeroEntradas, char* cuentaGmail, char* numeroTarjetaCredito, char* cvvTarjeta, char* caducidadTarjeta, char* tipoEntrada, char* precio, char* usuario) {

  abrirConexion();
  char lineEntrada[1024];
  int codigoFechaFinal = atoi(codigoFecha);
  int numeroEntradasFianl = atoi(numeroEntradas);
  float precioFinal = atof(precio);

  sscanf(lineEntrada, "%d, '%[^','], '%[^','], %d, '%[^','], '%[^','], '%[^','], '%[^','], '%[^','], %lf, '%[^',']",
        &codigoFechaFinal, fechaEntrada, nombreDiscoteca, &numeroEntradasFianl, cuentaGmail, numeroTarjetaCredito, cvvTarjeta,
        caducidadTarjeta, tipoEntrada, &precioFinal, usuario);

  char sql_insertEntrada[1024];

  sprintf(sql_insertEntrada, "INSERT INTO entradas (codigoFecha, fechaEntrada, nombreDiscoteca, numeroEntradas, cuentaGmail, numeroTarjetaCredito, cvvTarjeta, caducidadTarjeta, tipoEntrada, precio, nombreUsuario) VALUES (%d, '%s', '%s', %d, '%s', '%s', '%s', '%s', '%s', %f, '%s');",
        codigoFechaFinal, fechaEntrada, nombreDiscoteca, numeroEntradas, cuentaGmail, numeroTarjetaCredito, cvvTarjeta,
        caducidadTarjeta, tipoEntrada, &precio, usuario);

  aperturaInsert = sqlite3_exec(database, sql_insertEntrada, 0, 0, &mensajeError);

  if (aperturaInsert != SQLITE_OK) {
    gestionarFree(mensajeError);
    //gestionarError(database);
    gestionarFree(errorMessage);
 
    cerrarConexion(database);
    return 1;
  }

//printf("\nInsertado\n");
  cerrarConexion(database);
  return 0;
}
 
int insertarReservaLocal(char* codigo, char* fecha, char* nombreDiscoteca, char* aforo, char* numeroTarjeta, char* cvvTarjeta, char* caducidadTarjeta) {

  abrirConexion();
  int aforoFinal = atoi(aforo);

  char sql_insertReservarLocal[1024];

  sprintf(sql_insertReservarLocal, "INSERT INTO reservalocal (codigo, fecha, nombrediscoteca, aforo, numerotarjeta, cvvtarjeta, caducidadtarjeta) VALUES ('%s', '%s', '%s', %d, '%s', '%s', '%s');",
    codigo, fecha, nombreDiscoteca, aforoFinal, numeroTarjeta, cvvTarjeta, caducidadTarjeta);

  aperturaInsert = sqlite3_exec(database, sql_insertReservarLocal, 0, 0, &mensajeError);

  if (aperturaInsert != SQLITE_OK) {
    gestionarFree(mensajeError);
    //gestionarError(database);
    gestionarFree(errorMessage);

    cerrarConexion(database);
    return 1;
  }

  //printf("\nInsertado\n");
  cerrarConexion(database);
  return 0;
}

    // BUSCAR DATOS EN LA BASE DE DATOS

int buscarUltimoCodigo() {
  abrirConexion();

  sqlite3_stmt* statement;
  int busqueda = 0;
  const char* sentencia;
  int lastId = 0;

  if (gestionarError(database) != SQLITE_OK) {
    printf("Error en la conexión a la base de datos: %s\n", gestionarError(database));
  }

  sentencia = "SELECT MAX(codigo) FROM dias_de_fiesta;";
  busqueda = sqlite3_prepare_v2(database, sentencia, -1, &statement, 0);

  if (busqueda != SQLITE_OK) {
    printf("No se pudo preparar la consulta SQL: %s\n", gestionarError(database));
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return -1;
  }

  busqueda = sqlite3_step(statement);

  if (busqueda == SQLITE_ROW) {
    lastId = sqlite3_column_int64(statement, 0);
  }

  sqlite3_finalize(statement);
  cerrarConexion(database);

  return lastId;
}

char* buscarFechaConCodigoFecha(char* codigoFecha) {
  abrirConexion();

  sqlite3_stmt* statement;
  char* mensajeError = 0;
  int busqueda = 0;
  char* codigoEntrada = NULL;

  abrirConexion();
  if (gestionarError(database) != SQLITE_OK) {
    printf("Error en la conexión a la base de datos: %s\n", gestionarError(database));
  }

  const char* sentencia = "SELECT fecha FROM dias_de_fiesta WHERE codigo = ?";
  busqueda = sqlite3_prepare_v2(database, sentencia, -1, &statement, NULL);

  if (busqueda != SQLITE_OK) {
    printf("No se pudo preparar la consulta SQL: %s\n", gestionarError(database));
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return NULL;
  }

  sqlite3_bind_text(statement, 1, codigoFecha, -1, SQLITE_STATIC);
  busqueda = sqlite3_step(statement);

  if (busqueda == SQLITE_ROW) {
    const unsigned char* fecha = sqlite3_column_text(statement, 0);
    char* fechaEncontrada = strdup((const char*)fecha); // Copia la fecha encontrada a una nueva cadena

    sqlite3_finalize(statement);
    cerrarConexion(database);

    return fechaEncontrada;

  } else {
    sqlite3_finalize(statement);
    cerrarConexion(database);

    return NULL;
  }
}

char* buscarDiscotecaConCodigoFecha(char* codigoFecha) {
  abrirConexion();

  sqlite3_stmt* statement;
  char* mensajeError = 0;
  int busqueda = 0;
  char* nombreDiscotecaEncontrada = NULL;

  abrirConexion();
  if (gestionarError(database) != SQLITE_OK) {
    printf("Error en la conexión a la base de datos: %s\n", gestionarError(database));
  }

  const char* sentencia = "SELECT nombre FROM dias_de_fiesta WHERE codigo = ?";
  busqueda = sqlite3_prepare_v2(database, sentencia, -1, &statement, NULL);

  if (busqueda != SQLITE_OK) {
    printf("No se pudo preparar la consulta SQL: %s\n", gestionarError(database));
    exit(EXIT_FAILURE);
    sqlite3_finalize(statement);
    cerrarConexion(database);

    return NULL;
  }

  sqlite3_bind_text(statement, 1, codigoFecha, -1, SQLITE_STATIC);
  busqueda = sqlite3_step(statement);

  if (busqueda == SQLITE_ROW) {
    const unsigned char* nombreDiscoteca = sqlite3_column_text(statement, 0);
    nombreDiscotecaEncontrada = strdup((const char*)nombreDiscoteca); // Copia el nombre de la discoteca encontrada a una nueva cadena

    sqlite3_finalize(statement);
    cerrarConexion(database);

    return nombreDiscotecaEncontrada;

  } else {
    sqlite3_finalize(statement);
    cerrarConexion(database);

    return NULL;
  }
}
