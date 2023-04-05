#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite/sqlite3.h"
#include "baseDatos.h"
#include "../inicio.h"

#define MAX_REGISTRO 20
#define MAX_LOGIN 15
#define MAX_NOMBRE_USU 20
#define MAX_CONTRASENYA 20

sqlite3* database;
int apertura;
int aperturaInsert;
int existeBD;
char* mensajeError = NULL;
char* errorMessage = NULL;

int dbExiste(char* fichero) {
  FILE* arch = fopen(fichero, "r");

  if (arch) {
    fclose(arch);
    return 1;
  }
  return 0;
}

int gestionarError(sqlite3* baseDatos) {
  fprintf(stderr, "\nSQL Error: %s\n", sqlite3_errmsg(baseDatos));
  return sqlite3_errcode(baseDatos);
}

void gestionarFree(char* str) {
  sqlite3_free(str);
}

int eliminarBD() {
  if (remove("basedatosSSR.db") != 0) {
    fprintf(stderr, "Cannot delete database: %s\n", strerror(errno));
    exit(1);
  }
}

void cerrarConexion(sqlite3* baseDatos) {
  sqlite3_close(baseDatos);
  fprintf(stdout, "\nLa Base De Datos se cerro exitosamente\n");
}

int abrirConexion() {
  existeBD = dbExiste("basedatosSSR.db");
  apertura = sqlite3_open("basedatosSSR.db", &database);
  
  if (apertura != SQLITE_OK) {
    fprintf(stderr, "No se puede abrir la Base De Datos: %s\n", gestionarError(database));
    cerrarConexion(database);
    return 0;

  } else {
    fprintf(stdout, "\nLa Base De Datos se abrio exitosamente\n");
    return 1;
  }
}

int comprobarExistencia() {

  sqlite3_stmt * statement;
  char * mensajeError = 0;
  int apertura = 0;
  int busqueda = 0;

  abrirConexion();

  char input[MAX_REGISTRO];

  printf("Usuario: ");
  fgets(input, MAX_NOMBRE_USU, stdin);

  char * username = malloc((MAX_NOMBRE_USU) * sizeof(char));
  sscanf(input, "%s", username); //le quita el 'n' (si lo hay)

  clearIfNeeded(input, MAX_NOMBRE_USU); //le quita el 'n' (si lo hay)
  fflush(stdout);
  fflush(stdin);

  printf("Contrasenya: ");
  fgets(input, MAX_CONTRASENYA, stdin);

  char * password = malloc((MAX_CONTRASENYA) * sizeof(char));
  sscanf(input, "%s", password); //le quita el 'n' (si lo hay)

  clearIfNeeded(input, MAX_CONTRASENYA); //le quita el 'n' (si lo hay)
  fflush(stdout);
  fflush(stdin);

  printf("%s, %s", username, password);

  char * sentencia = "SELECT usuario, contrasenya FROM usuarios WHERE usuario = ? AND contrasenya = ?;";
  if (sqlite3_errcode(database) != SQLITE_OK) {
    printf("Error en la conexión a la base de datos.:::%s\n",sqlite3_errmsg(database));
    // Aquí puedes agregar el código para manejar el error.
  }

  busqueda = sqlite3_prepare_v2(database, sentencia, -1, & statement, 0);
  printf("\n%i\n", busqueda);

  sqlite3_bind_text(statement, 1, username, strlen(username), SQLITE_STATIC);
  sqlite3_bind_text(statement, 2, password, strlen(password), SQLITE_STATIC);

  if (busqueda != SQLITE_OK) {
    printf("AQUI");
    printf("Error preparing SQL statement: %s\n", sqlite3_errmsg(database));
    gestionarFree(mensajeError);
    fprintf(stderr, "Error en la consulta: %s\n", mensajeError);
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 0;
  }

  printf("BIEN");

  busqueda = sqlite3_step(statement);

  if (mensajeError != NULL) {
    gestionarFree(mensajeError);
    fprintf(stderr, "Error en la consulta: %s\n", mensajeError);

    cerrarConexion(database);
    return 0;
  }

  if (busqueda == SQLITE_ROW) {
    printf("\nUSUARIO ENCONTRADO, accediendo al menu\n");
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 1;

  } else if (busqueda != SQLITE_OK) {
    fprintf(stderr, "Error en la consulta: %s\n", mensajeError);
    gestionarFree(mensajeError);
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 0;

  } else {
    printf("No se ha encontrado el usuario\n");
    sqlite3_finalize(statement);
    cerrarConexion(database);
  }

  cerrarConexion(database);
  return 0;
}

int inicializarDiasDeFiesta() {
  //Eliminar tabla si existe
  char* sentenciaDDF = "DROP TABLE IF EXISTS dias_de_fiesta;";

  int resultadoDDF = sqlite3_exec(database, sentenciaDDF, NULL, NULL, &mensajeError);

  if (resultadoDDF != SQLITE_OK) {
      // Manejar el error si ocurre
      gestionarError(database);
      gestionarFree(mensajeError);

      cerrarConexion(database);
      return 1;
  }

  // Implementacion de importacion de datos CSV
    char * sql = "CREATE TABLE dias_de_fiesta(codigo TEXT PRIMARY KEY NOT NULL, fecha DATE NOT NULL, nombre TEXT NOT NULL, entradas INT NOT NULL, especial TEXT NOT NULL)";
    apertura = sqlite3_exec(database, sql, 0, 0, &mensajeError);

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
        gestionarError(database);
        gestionarFree(errorMessage);

        cerrarConexion(database);
        return 1;
      }
    }

    fclose(fp);
}

int inicializarDJ() {
  //Eliminar tabla si existe
  char* sentenciaDJ = "DROP TABLE IF EXISTS dj;";

  int resultadoDJ = sqlite3_exec(database, sentenciaDJ, NULL, NULL, &mensajeError);

  if (resultadoDJ != SQLITE_OK) {
      // Manejar el error si ocurre
      gestionarError(database);
      gestionarFree(mensajeError);

      cerrarConexion(database);
      return 1;
  }

  // Implementacion de importacion de datos CSV
  char * sql2 = "CREATE TABLE dj(identificador INT PRIMARY KEY NOT NULL, nombre_comercial TEXT NOT NULL, genero_musical TEXT NOT NULL, fecha_nacimiento TEXT NOT NULL, numero_contacto TEXT NOT NULL);";
    apertura = sqlite3_exec(database, sql2, 0, 0, &mensajeError);
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
}

int inicializarListaEventos() {
  //Eliminar tabla si existe
  char* sentenciaLE = "DROP TABLE IF EXISTS eventos;";

  int resultadoLE = sqlite3_exec(database, sentenciaLE, NULL, NULL, &mensajeError);

  if (resultadoLE != SQLITE_OK) {
      // Manejar el error si ocurre
      gestionarError(database);
      gestionarFree(mensajeError);

      cerrarConexion(database);
      return 1;
  }

  // Implementacion de importacion de datos CSV
  char * sql3 = "CREATE TABLE eventos(dia TEXT NOT NULL, descripcion TEXT NOT NULL, nombre_discoteca TEXT NOT NULL, aforo INT NOT NULL);";
    apertura = sqlite3_exec(database, sql3, 0, 0, &mensajeError);
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

      char Dia[50], Descripcion[50], nombre_discoteca[50], Aforo[50];

      sscanf(line3, "%[^','],%[^','],%[^','],%s", Dia,
        Descripcion,
        nombre_discoteca,
        Aforo);

      char sql_insert[1024];

      sprintf(sql_insert, "INSERT INTO eventos VALUES('%s','%s','%s',%s);",
        Dia,
        Descripcion,
        nombre_discoteca,
        Aforo);

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
}

int inicializarRRPP() {
  //Eliminar tabla si existe
  char* sentenciaRRPP = "DROP TABLE IF EXISTS rrpp;";

  int resultadoRRPP = sqlite3_exec(database, sentenciaRRPP, NULL, NULL, &mensajeError);

  if (resultadoRRPP != SQLITE_OK) {
      // Manejar el error si ocurre
      gestionarError(database);
      gestionarFree(mensajeError);

      cerrarConexion(database);
      return 1;
  }

  // Implementacion de importacion de datos CSV
  char * sql4 = "CREATE TABLE rrpp(codigo INT PRIMARY KEY NOT NULL, nombre TEXT NOT NULL, zona_recogida TEXT NOT NULL, hora_recogida TEXT NOT NULL, numero_contacto TEXT NOT NULL);";
    apertura = sqlite3_exec(database, sql4, 0, 0, &mensajeError);
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
}

int inicializarUsuarios() {
  //Eliminar tabla si existe
  char* sentenciaUsu = "DROP TABLE IF EXISTS usuarios;";

  int resultadoUsu = sqlite3_exec(database, sentenciaUsu, NULL, NULL, &mensajeError);

  if (resultadoUsu != SQLITE_OK) {
      // Manejar el error si ocurre
      gestionarError(database);
      gestionarFree(mensajeError);
      
      cerrarConexion(database);
      return 1;
  }

  // Implementacion de importacion de datos CSV
  char * sql5 = "CREATE TABLE usuarios(nombre TEXT NOT NULL, usuario TEXT NOT NULL, sexo TEXT NOT NULL, edad INT NOT NULL, email TEXT NOT NULL, contrasenya TEXT NOT NULL);";
    apertura = sqlite3_exec(database, sql5, 0, 0, &mensajeError);
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
  }
  
  cerrarConexion(database);
  printf("Se mantendra cerrada hasta cualquier cambio\n");

  return 0;
}

void clearIfNeeded(char * str, int max_line) {
  // Limpia los caracteres de más introducidos
  if ((strlen(str) == max_line - 1) && (str[max_line - 2] != '\n'))
    while (getchar() != '\n');
}

void seleccionarRRPP(){
    abrirConexion();

    char* error = 0;
    int st;
    char* sql = "SELECT * FROM rrpp";
    st = sqlite3_exec(database, sql, callback, 0, &error);
    if (st != SQLITE_OK) {
        fprintf(stderr, "Error en la consulta SQL: %s\n", error);
        sqlite3_free(error);
    }
    
    cerrarConexion(database);
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
  int i;

  for (i = 0; i < argc; i++) {
    if (i > 0) {
      printf(" - ");
    }
    printf("%s", argv[i] ? argv[i] : "NULL");
  }
  printf("\n");

  return 0;
}


void cargarLocales() {
  abrirConexion();

  char* error = 0;
  int st;
  char* sql = "SELECT * FROM dias_de_fiesta WHERE entradas = 400";
  st = sqlite3_exec(database, sql, callback, 0, &error);
    if (st != SQLITE_OK) {
        fprintf(stderr, "Error en la consulta SQL: %s\n", error);
        sqlite3_free(error);
    }
    
  cerrarConexion(database);
}

void mostrarFiestas() {
  abrirConexion();

  char* error = 0;
  int st;
  char* sql = "SELECT * FROM dias_de_fiesta";
  st = sqlite3_exec(database, sql, callback, 0, &error);
    if (st != SQLITE_OK) {
        fprintf(stderr, "Error en la consulta SQL: %s\n", error);
        sqlite3_free(error);
    }
    
  cerrarConexion(database);
}

void mostrarlistadoeventos(){
	abrirConexion();

  char* error = 0;
  int st;
  char* sql = "SELECT * FROM listaeventos";
    st = sqlite3_exec(database, sql, callback, 0, &error);
    if (st != SQLITE_OK) {
        fprintf(stderr, "Error en la consulta SQL: %s\n", error);
        sqlite3_free(error);
    }

	cerrarConexion(database);
}

int comprobarCodigoLocal(int cod) {
  sqlite3_stmt * statement;
  int busqueda = 0;
  abrirConexion();

  char * sentencia = "SELECT codigo FROM dias_de_fiesta WHERE codigo = ? AND entradas = 400";
  if (sqlite3_errcode(database) != SQLITE_OK) {
    printf("Error en la conexión a la base de datos.:::%s\n",sqlite3_errmsg(database));
  }

  busqueda = sqlite3_prepare_v2(database, sentencia, -1, &statement, 0);
  sqlite3_bind_int(statement, 1, cod);
  
  if (busqueda != SQLITE_OK) {
    printf("Error preparing SQL statement: %s\n", sqlite3_errmsg(database));
    gestionarFree(mensajeError);
    fprintf(stderr, "Error en la consulta: %s\n", mensajeError);
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 0;
  }

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
    fprintf(stderr, "Error en la consulta: %s\n", mensajeError);
    gestionarFree(mensajeError);
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 0;

  } else {
    printf("No se ha encontrado el usuario\n");
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 0;
  }

  cerrarConexion(database);
}

int comprobarCodigoRRPP(int cod) {
  sqlite3_stmt * statement;
  int busqueda = 0;
  abrirConexion();

  char * sentencia = "SELECT codigo FROM rrpp WHERE codigo = ?";
  if (sqlite3_errcode(database) != SQLITE_OK) {
    printf("Error en la conexión a la base de datos.:::%s\n",sqlite3_errmsg(database));
  }

  busqueda = sqlite3_prepare_v2(database, sentencia, -1, &statement, 0);
  sqlite3_bind_int(statement, 1, cod);
  
  if (busqueda != SQLITE_OK) {
    printf("Error preparing SQL statement: %s\n", sqlite3_errmsg(database));
    gestionarFree(mensajeError);
    fprintf(stderr, "Error en la consulta: %s\n", mensajeError);
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 0;
  }

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
    fprintf(stderr, "Error en la consulta: %s\n", mensajeError);
    gestionarFree(mensajeError);
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 0;

  } else {
    printf("No se ha encontrado el usuario\n");
    sqlite3_finalize(statement);
    cerrarConexion(database);
    return 0;
  }

  cerrarConexion(database);
}

int insertarDiaFiesta(char* fecha, char* nomDiscoteca, char* eventoEsp) {

  int codigo = 2000; int entradas = 400;
  char lineFi[1024];

  sscanf(lineFi, "%[^','],%[^','],%[^','],%[^','],%s",
    codigo,
    fecha, 
    nomDiscoteca,
    entradas,
    eventoEsp);

  char sql_insertFi[1024];

  sprintf(sql_insertFi, "INSERT INTO dias_de_fiesta VALUES('%s','%s','%s',%s,'%s');",
    codigo,
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
}

int insertarEvento() {

  char lineEven[1024];
  char Dia[50], Descripcion[50], nombre_discoteca[50], Aforo[50];

  sscanf(lineEven, "%[^','],%[^','],%[^','],%s", Dia,
    Descripcion,
    nombre_discoteca,
    Aforo);

  char sql_insertEven[1024];

  sprintf(sql_insertEven, "INSERT INTO eventos VALUES('%s','%s','%s',%s);",
    Dia,
    Descripcion,
    nombre_discoteca,
    Aforo);

  aperturaInsert = sqlite3_exec(database, sql_insertEven, 0, 0, &mensajeError);
  
  if (apertura != SQLITE_OK) {
    gestionarFree(mensajeError);
    gestionarError(database);
    gestionarFree(errorMessage);
 
    cerrarConexion(database);
    return 1;
  }
}
