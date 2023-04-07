#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../basedatos/baseDatos.h"
#include "inicio_servidor.h"

#define MAX_SELECCION 5
#define MAX_NOM_DISCOTECA 10
#define MAX_FECHA 10
#define MAX_DESCRIPCION 75

char mostrarIncioServido() {
    char inputInicio[MAX_SELECCION];
    int numInicio;

    printf("\n---------------------------------------------------\n");
    printf("Menu Principal: \n\t1. Informacion de eventos \n\t2. Informacion de fiestas \n\t3. Actualizar base de datos \n\t0. Cerrar Sesion \n\n Elige una opcion: ");

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

            printf("\e[37m\e[1m");
            printf("Listado de eventos (fecha - descripcion - discoteca - aforo)\n\n");
            printf("\e[0m");

            mostrarlistadoeventos();
        break;

        case '2':
            printf("\n---------------------------------------------------\n");

            printf("\e[37m\e[1m");
            printf("Listado de dias de fiesta (codigo - fecha - nombre discoteca - entradas disponibles - evento?)\n\n");
            printf("\e[0m");

            mostrarFiestas();
        break;

        case '3':
            menuServidor();
        break;
        }

    } while (opcionInicioServidor != '0');

    return 0;
}


char mostrarMenuServidor() {
  char inputMenu[MAX_SELECCION];
  int numMenu;
  printf("\n---------------------------------------------------\n");
  printf("Actualizar la Base de Datos: \n\t1. Reiniciar BD \n\t2. Aniadir fiesta \n\t3. Aniadir evento \n\t4. Importar RRPPs \n\t5. Importar DJs \n\t0. Atras \n\n Elige una opcion: ");

  fgets(inputMenu, MAX_SELECCION, stdin);
  sscanf(inputMenu, "%d", & numMenu);

  return * inputMenu;
}


char* introducirNombreDiscoteca() {
    printf("\tIntroduce nombre de la discoteca (Back / Stage): ");

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
  int existeFecha;

  do {
    opcionMenu = mostrarMenuServidor();
    switch (opcionMenu) {
    case '1':
        printf("\n---------------------------------------------------\n");
        printf("Reiniciar BD\n\n");
        reiniciarBD();
    break;

    case '2':
        printf("\n---------------------------------------------------\n");
        printf("Aniadir fiesta:\n");

        nomDiscoteca = introducirNombreDiscoteca();
        len = strcspn(nomDiscoteca, "\n");
        nomDiscoteca[len] = '\0';

        fecha = introducirFecha();
        len = strcspn(fecha, "\n");
        fecha[len] = '\0';

        evento = "No";

        nomDiscoteca[0] = toupper(nomDiscoteca[0]);
        for (int i = 1; nomDiscoteca[i] != '\0'; i++) {
            nomDiscoteca[i] = tolower(nomDiscoteca[i]);
        }

        existeFecha = comprobarFecha(fecha, 1);

        if (((strcmp(nomDiscoteca, "Back") == 0) || (strcmp(nomDiscoteca, "Stage") == 0)) && (existeFecha == -1)) {
            if (verificarFecha(fecha)) {
                insertarDiaFiesta(fecha, nomDiscoteca, evento);
                insertarEvento(fecha, nomDiscoteca, descripcionEvento);

                printf("Fiesta introducida correctamente en La Base De Datos\n");
            } else {
                printf("Formato de fecha incorrecto\nOperacion cancelada\n");
            }
        } else if (existeFecha == 0) {
            printf("\nLa fecha introducida ya esta ocupada\nOperacion cancelada\n");
        } else {
            printf("\nNombre de la discoteca incorrecto\nOperacion cancelada\n");
        }

    break;

    case '3':
        printf("\n---------------------------------------------------\n");
        printf("Aniadir evento:\n");

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

        nomDiscoteca[0] = toupper(nomDiscoteca[0]);
        for (int i = 1; nomDiscoteca[i] != '\0'; i++) {
            nomDiscoteca[i] = tolower(nomDiscoteca[i]);
        }

        existeFecha = comprobarFecha(fecha, 0);

        if (((strcmp(nomDiscoteca, "Back") == 0) || (strcmp(nomDiscoteca, "Stage") == 0)) && (existeFecha == -1)) {
            if (verificarFecha(fecha)) {
                insertarDiaFiesta(fecha, nomDiscoteca, evento);
                insertarEvento(fecha, nomDiscoteca, descripcionEvento);

                printf("Evento introducido correctamente en La Base De Datos\n");
            } else {
                printf("Formato de fecha incorrecto\nOperacion cancelada");
            }
        } else if (existeFecha == 0) {
            printf("\nLa fecha introducida ya esta ocupada\nOperacion cancelada\n");
        } else {
            printf("\nNombre de la discoteca incorrecto\nOperacion cancelada\n");
        }

    break;

    case '4':
        printf("\n---------------------------------------------------\n");
        printf("Importar RRPPs\n\n");
        abrirConexion();
        inicializarRRPP();
        mostrarRRPP();
        printf("\nEstos son los RRPPs importados\n");
    break;
    
    case '5':
        printf("\n---------------------------------------------------\n");
        printf("Importar DJs\n\n");
        abrirConexion();
        inicializarDJ();
        mostrarDJ();
        printf("\nEstos son los DJs importados\n");
    break;
    }

  } while (opcionMenu != '0');

  return 0;
}

