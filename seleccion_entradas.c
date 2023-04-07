#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "seleccion_entradas.h"
#include "comprar_entradas.h"
#include "basedatos/sqlite/sqlite3.h"
#include "basedatos/baseDatos.h"
#include "inicio.h"

#define MAX_SELECCION 5
#define MAX_REGISTRO 20
#define MAX_CODIGO 5

#define SEGUNDOS 2
#define PRECIO_CONS_1 10
#define PRECIO_CONS_2 15
#define PRECIO_CONS_3 20
#define PRECIO_RES 25

char introducirTipoEntrada(){
    printf("\n---------------------------------------------------\n");
    printf("Tipos de entrada:\n");
        printf("\t1. Una consumicion (%i euro) \n", PRECIO_CONS_1);
        printf("\t2. Dos consumiciones (%i euro) \n", PRECIO_CONS_2);
        printf("\t3. Tres consumiciones (%i euro) \n", PRECIO_CONS_3);
        printf("\t4. Reservado (%i euro) \n", PRECIO_RES);
    printf("\t5. Atras\n\n");
    printf("Elige una opcion: ");


    char inputDatosCompra[MAX_SELECCION];
    int numDatosCompra;

    fgets(inputDatosCompra, MAX_SELECCION, stdin);

    return *inputDatosCompra;
}

void tipoEntradaSeleccionada(){
    char opcionTipoEntrada;
    do{
        opcionTipoEntrada = introducirTipoEntrada();
        switch(opcionTipoEntrada){
            case '1':
                printf("Ha seleccionado entradas con %c consumicion, con un precio de: %i euro\n", opcionTipoEntrada, PRECIO_CONS_1);
                //sleep(SEGUNDOS);
                datosCompra();
            break;

            case '2':
                printf("Ha seleccionado entradas con %c consumiciones, con un precio de: %i euro\n", opcionTipoEntrada, PRECIO_CONS_2);
                //sleep(SEGUNDOS);
                datosCompra();
            break;

            case '3':
                printf("Ha seleccionado entradas con %c consumiciones, con un precio de: %i euro\n", opcionTipoEntrada, PRECIO_CONS_3);
                //sleep(SEGUNDOS);
                datosCompra();
            break;

            case '4':
                printf("Ha seleccionado entradas para reservado, con un precio de: %i euro\n", PRECIO_RES);
                //sleep(SEGUNDOS);
                datosCompra();
            break;
            
            case '5':
                printf("Atras...\n");
                //sleep(SEGUNDOS);
                menuListadoDiasDisponibles();
            break;
        }
    } while (opcionTipoEntrada != '0');
}

void mostrarDiasDisponibles(){
    printf("\n----------------------------------------------------------\n");

    printf("Entrada 1\n\n");
    printf("Codigo de la fecha: %s\n", "No me apetece");
    printf("Fecha: %s\n", "El dia que Sabin se duche");
    printf("Nombre de la discoteca: %s\n", "StackOverflow");
    printf("Entradas disponibles: %i\n", 666);
    printf("Evento especial: %s\n", "NO");
    printf("\n----------------------------------------------------------\n");
}

char introducirCodioDia(){

    printf("\nOpcion comprar entrada");
    printf("\n\t1. Introducir identificacion de entrada (codigo)\n");
    printf("\t0. Atras\n\n");
    printf("Elige una opcion: ");

    char inputDatosCompra[MAX_SELECCION];
    int numDatosCompra;

    fgets(inputDatosCompra, MAX_SELECCION, stdin);

    return *inputDatosCompra;
}

void menuListadoDiasDisponibles(){
    char opcionMenuCalendario;
    char inputCod[MAX_REGISTRO];
    int codigo;
    char* cod;
    char* type;
    char strNum[3];
    char strCodigo[4];
    char auxCodigo[16];

    do{
        opcionMenuCalendario = introducirCodioDia();
        switch(opcionMenuCalendario){
            case '1':
                printf("\n---------------------------------------------------\n");

                do {
                    printf("Codigo de la entrada: ");
                    fgets(inputCod, MAX_CODIGO, stdin);

                    sscanf(inputCod, "%d", &codigo);
                    cod = limpiarInput(inputCod);

                    errno = 0;
                    long int num = strtol(cod, &type, 10);

                    if (errno != 0 || *type != '\0') {
                        printf("'%s' no es una entrada valida\n", cod);
                    }

                } while (errno != 0 || *type != '\0');

                if (codigo < 100) {
                    sprintf(strNum, "%d", codigo);

                    char strCodigo[4] = {'0', '\0'};
                    strcat(strCodigo, strNum);

                    if (comprobarEntrada(strCodigo) == 0) {
                        printf("Entrada con codigo: '%s' seleccionada correctamente\n", strCodigo);
                        tipoEntradaSeleccionada();

                    } else if (comprobarEntrada(strCodigo) == -1) {
                        printf("El codigo de entrada seleccionado no existe\nOperacion cancelada\n");

                    } else {
                        printf("Codigo seleccionado incorrectamente\nOperacion cancelada\n");
                        menu();
                    }
                    
                } else {
                    sprintf(auxCodigo, "%d", codigo);   

                    if (comprobarEntrada(auxCodigo) == 0) {
                        printf("Entrada con codigo: '%i' seleccionada correctamente\n", auxCodigo);
                        tipoEntradaSeleccionada();

                    } else if (comprobarEntrada(auxCodigo) == -1) {
                        printf("El codigo de entrada seleccionado no existe\nOperacion cancelada\n");

                    } else {
                        printf("Codigo seleccionado incorrectamente\nOperacion cancelada\n");
                        menu();
                    }
                }
            break;
        }
    } while (opcionMenuCalendario != '0');
}