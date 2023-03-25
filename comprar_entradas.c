#include <stdio.h>
#include "comprar_entradas.h"

#define MAX_ENTRADAS 10
#define MAX_NOMBRE 40
#define MAX_GMAIL 30

char mostrarDatosCompra(){
    printf("\nDatos necesarios:\n\t1. Comprar \n\t0. Atras\n\nElige una opcion: ");
}

int* introducirNumEntradas(){
    printf("\n\tIntroduce el numero de entradas: ");

    int inputNumEntradas[MAX_ENTRADAS];
    fgets(inputNumEntradas, MAX_ENTRADAS, stdin);
    //return *inputNumEntradas;
}

char* introducirNombreCompleto(){
    printf("\n\tIntroduce tu nombre completo: ");

    char inputNombreCompleto[MAX_NOMBRE];
    fgets(inputNombreCompleto, MAX_ENTRADAS, stdin);
    //return *inputNombreCompleto;
}

char* introducirGmail(){
    printf("\n\tIntroduce tu cuenta de gmail: ");

    char inputGmail[MAX_GMAIL];
    fgets(inputGmail, MAX_GMAIL, stdin);
    //return *inputGmail;
}

void datosCompra(){
    char opcionDatosCompra;
    int numEntradas[MAX_ENTRADAS];
    char nombreCompleto[MAX_NOMBRE];
    char gmail[MAX_GMAIL];

    do{
        opcionDatosCompra = mostrarDatosCompra();
        switch(opcionDatosCompra){
            case '1':
                printf("\n---------------------------------------------------\n");
                printf("Introducir datos de la compra");
                introducirNumEntradas();
                introducirNombreCompleto();
                introducirGmail();
                // numEntradas[MAX_ENTRADAS] = introducirNumEntradas();
                // nombreCompleto[MAX_NOMBRE] = introducirNombreCompleto();
                // gmail[MAX_GMAIL] = introducirGmail();
            break;
        }
    } while(opcionDatosCompra != 0);
}

