#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../basedatos/baseDatos.h"
#include "inicio_servidor.h"

#define MAX_SELECCION 5

char mostrarIncioServido() {
    char inputInicio[MAX_SELECCION];
    int numInicio;
    printf("\nMenu Principal: \n\t1. Informacion de eventos \n\t2. Informacio de fiestas \n\t3. Actualizar base de datos \n\t0. Cerrar Sesion \n\n Elige una opcion: ");

    fgets(inputInicio, MAX_SELECCION, stdin);
    sscanf(inputInicio, "%d", &numInicio);

    return *inputInicio;
}


int inicioServidor() {
    char opcionInicioServidor;

    do {
        opcionInicioServidor = mostrarIncioServido();
        switch (opcionInicioServidor) {
        case '1':
            printf("\n---------------------------------------------------\n");
            printf("Listado de eventos\n\n");
            mostrarlistadoeventos();
        break;

        case '2':
            printf("\n---------------------------------------------------\n");
            printf("Listado de dias de fiesta (cod - fecha - discoteca - entradas - evento?\n\n");
            mostrarFiestas();
        break;

        case '3':
            printf("\n---------------------------------------------------\n");
            printf("Actualizar base de datos\n\n");
            menuServidor();
        break;
        }

    } while (opcionInicioServidor != '0');

    return 0;
}


char mostrarMenuServidor() {
  char inputMenu[MAX_SELECCION];
  int numMenu;
  printf("\nActualizar la Base de Datos: \n\t1. Reiniciar BD \n\t2. Aniadir fiesta \n\t3. Aniadir evento \n\t4. Importar RRPPs \n\t5. Importar DJs \n\t0. Atras \n\n Elige una opcion: ");

  fgets(inputMenu, MAX_SELECCION, stdin);
  sscanf(inputMenu, "%d", & numMenu);

  return * inputMenu;
}

int menuServidor() {
  char opcionMenu;

  do {
    opcionMenu = mostrarMenuServidor();
    switch (opcionMenu) {
    case '1':
      printf("\n---------------------------------------------------\n");
      printf("Reiniciar BD\n\n");
      
    break;

    case '2':
      printf("\n---------------------------------------------------\n");
      printf("Aniadir fiesta\n\n");

    break;

    case '3':
      printf("\n---------------------------------------------------\n");
      printf("Aniadir evento\n\n");
      
    break;

    case '4':
      printf("\n---------------------------------------------------\n");
      printf("Importar RRPPs\n\n");

    break;
    
    case '5':
      printf("\n---------------------------------------------------\n");
      printf("Importar DJs\n\n");

    break;
    }

  } while (opcionMenu != '0');

  return 0;
}

