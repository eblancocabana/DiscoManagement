#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../basedatos/baseDatos.h"
#include "inicio_servidor.h"

#define MAX_SELECCION 5
#define MAX_NOM_DISCOTECA 10
#define MAX_FECHA 10
#define MAX_DESCRIPCION 75

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


char* introducirNombreDiscoteca() {
    printf("\n\tIntroduce nombre de la discoteca (Back / Stage): ");

    char* inputDiscoteca = (char*) malloc(MAX_NOM_DISCOTECA * sizeof(char));
    fgets(inputDiscoteca, MAX_NOM_DISCOTECA, stdin);
    return inputDiscoteca;
}

char* introducirFecha() {
    printf("\tIntroduce la fecha (dd/mm/aa): ");

    char* inputFecha = (char*) malloc(MAX_FECHA * sizeof(char));
    fgets(inputFecha, MAX_FECHA, stdin);
    return inputFecha;
}

char* introducirDescripcion() {
    printf("\tIntroduce la descripcion del evento (max 70 letras): ");

    char* inputDescripcion = (char*) malloc(MAX_DESCRIPCION * sizeof(char));
    fgets(inputDescripcion, MAX_DESCRIPCION, stdin);
    return inputDescripcion;
}


int menuServidor() {
  char opcionMenu;
  char* nomDiscoteca;
  char* fecha;
  char* descripcionEvento;
  char* evento;
  int len;

  do {
    opcionMenu = mostrarMenuServidor();
    switch (opcionMenu) {
    case '1':
        printf("\n---------------------------------------------------\n");
        printf("Reiniciar BD\n\n");
      
    break;

    case '2':
        printf("\n---------------------------------------------------\n");
        printf("Aniadir fiesta");

        nomDiscoteca = introducirNombreDiscoteca();
        len = strcspn(nomDiscoteca, "\n");
        nomDiscoteca[len] = '\0';

        fecha = introducirFecha();
        len = strcspn(fecha, "\n");
        fecha[len] = '\0';

        evento = "No";

        for (int i = 0; nomDiscoteca[i] != '\0'; i++) {
            nomDiscoteca[i] = toupper(nomDiscoteca[i]);
        }

        if ((strcmp(nomDiscoteca, "BACK") == 0) || (strcmp(nomDiscoteca, "STAGE") == 0)) {
            printf("Las cadenas son iguales\n");
            insertarDiaFiesta(fecha, nomDiscoteca, evento);
        } else {
            printf("Valores incorrectos\n");
        }

    break;

    case '3':
        printf("\n---------------------------------------------------\n");
        printf("Aniadir evento\n\n");

        nomDiscoteca = introducirNombreDiscoteca();
        len = strcspn(nomDiscoteca, "\n");
        nomDiscoteca[len] = '\0';

        fecha = introducirFecha();
        len = strcspn(fecha, "\n");
        fecha[len] = '\0';

        descripcionEvento = introducirDescripcion();
        len = strcspn(descripcionEvento, "\n");
        descripcionEvento[len] = '\0';

        evento = "Si";

        if ((strcmp(nomDiscoteca, "BACK") == 0) || (strcmp(nomDiscoteca, "STAGE") == 0)) {
            printf("Las cadenas son iguales\n");
            //insertarDiaFiesta(fecha, nomDiscoteca, evento);
            //insertarEvento(fecha, nomDiscoteca, descripcionEvento);
        }

    break;

    case '4':
        printf("\n---------------------------------------------------\n");
        printf("Importar RRPPs\n\n");
        inicializarRRPP();
    break;
    
    case '5':
        printf("\n---------------------------------------------------\n");
        printf("Importar DJs\n\n");
        inicializarDJ();
    break;
    }

  } while (opcionMenu != '0');

  return 0;
}

