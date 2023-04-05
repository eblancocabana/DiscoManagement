#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <stdbool.h>

#include "inicio.h"

#include "reservar_local.h"

#include "basedatos/sqlite/sqlite3.h"

#include "basedatos/baseDatos.h"

#define MAX_SELECCION 5
#define MAX_REGISTRO 20
#define MAX_LOGIN 15

#define MAX_NOMBRE 20
#define MAX_NOMBRE_USU 20
#define MAX_SEXO 20
#define MAX_EDAD 20
#define MAX_CORREO 20
#define MAX_CONTRASENYA 20

char mostrarLogin() {
  char inputLogin[MAX_SELECCION];
  int numLogin;
  printf("\nInicio Sesion: \n\t1. Registrarse \n\t2. Login \n\t0. Salir \n\n Elige una opcion: ");

  fgets(inputLogin, MAX_SELECCION, stdin);
  sscanf(inputLogin, "%d", & numLogin);

  return * inputLogin;
}

char mostrarRegistrarse() {
  char inputRegistrarse[MAX_SELECCION];
  int numRegistrarse;
  printf("\n\t1. Aceptar \n\t0. Atras \n\n Elige una opcion: ");

  fgets(inputRegistrarse, MAX_SELECCION, stdin);
  sscanf(inputRegistrarse, "%d", & numRegistrarse);

  return * inputRegistrarse;
}

char mostrarMenu() {
  char inputMenu[MAX_SELECCION];
  int numMenu;
  printf("\nMenu Principal: \n\t1. Informacion de eventos \n\t2. Comprar entradas \n\t3. Reservar local \n\t4. Mis reservas / compras \n\t0. Cerrar Sesion \n\n Elige una opcion: ");

  fgets(inputMenu, MAX_SELECCION, stdin);
  sscanf(inputMenu, "%d", & numMenu);

  return * inputMenu;
}

char rellenarCamposRegistro() {
  char inputRegis[MAX_REGISTRO];
  char * nombre;
  char * nombreUsu;
  char * sexo;
  int edad;
  char * correo;
  char * contrasenya;
  char * repertirContrasenya;

  printf("Menu Registro:\n\n");

  printf("Nombre: ");
  fgets(inputRegis, MAX_NOMBRE, stdin);
  sscanf(inputRegis, "%s", & nombre);

  printf("Nombre de Usuario: ");
  fgets(inputRegis, MAX_NOMBRE_USU, stdin);
  sscanf(inputRegis, "%s", & nombreUsu);

  printf("Sexo: ");
  fgets(inputRegis, MAX_SEXO, stdin);
  sscanf(inputRegis, "%s", & sexo);

  printf("Edad: ");
  fgets(inputRegis, MAX_EDAD, stdin);
  sscanf(inputRegis, "%i", & edad);

  printf("Correo Electronico: ");
  fgets(inputRegis, MAX_CORREO, stdin);
  sscanf(inputRegis, "%s", & correo);

  printf("Contrasenya: ");
  fgets(inputRegis, MAX_CONTRASENYA, stdin);
  sscanf(inputRegis, "%s", & contrasenya);

  printf("Repetir Contrasenya: ");
  fgets(inputRegis, MAX_CONTRASENYA, stdin);
  sscanf(inputRegis, "%s", & repertirContrasenya);

  return * inputRegis;
}

char iniciarSesion() {
  int existe = 0;
  existe = comprobarExistencia();

  if (existe == 1) {
    menu();
  } else {
    comprobarExistencia();
  }
}

void clearIfNeeded(char * str, int max_line) {
  // Limpia los caracteres de más introducidos
  if ((strlen(str) == max_line - 1) && (str[max_line - 2] != '\n'))
    while (getchar() != '\n');
}


int registrarse() {
  char opcionRegistrarse;

  rellenarCamposRegistro();

  do {
    opcionRegistrarse = mostrarRegistrarse();
    switch (opcionRegistrarse) {
    case '1':
      printf("\n---------------------------------------------------\n");
      login();
      break;
    }
  } while (opcionRegistrarse != '0');

  return 0;
}

int login() {
  char opcionLogin;

  do {
    opcionLogin = mostrarLogin();
    switch (opcionLogin) {
    case '1':
      printf("\n---------------------------------------------------\n");
      registrarse();
      break;

    case '2':
      printf("\n---------------------------------------------------\n");
      iniciarSesion();
      break;
    }

  } while (opcionLogin != '0');

  if (opcionLogin == 0) {
    exit(0);
  }

  return 0;
}

int menu() {
  char opcionMenu;

  do {
    opcionMenu = mostrarMenu();
    switch (opcionMenu) {
    case '1':
      printf("\n---------------------------------------------------\n");
      printf("Listado de eventos\n\n");
      mostrarlistadoeventos();
      break;

    case '2':
      printf("\n---------------------------------------------------\n");
      printf("Menu de compra de entrada\n\n");
      break;

    case '3':
      printf("\n---------------------------------------------------\n");
      printf("Reservar el local\n\n");
      reservarLocal();
      break;

    case '4':
      printf("\n---------------------------------------------------\n");
      printf("Listado de mis reservas\n\n");
      break;
    }

  } while (opcionMenu != '0');

  return 0;
}