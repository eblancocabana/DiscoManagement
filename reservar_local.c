#include <stdio.h>
#include "reservar_local.h"

#define MAX_SELECCION 5
#define MAX_NOMBRE_DISCOTECA 20
#define MAX_FECHA 15

char mostrarListado() {
    printf("\nListado de dias disponible: (fecha - nombre discoteca - numero de invitados - precio - DJ)\n");
    cargarLocales();
    printf("\n---------------------------------------------------\n");
    printf("\nListado de dias disponible:\n\t1. Realizar reserva \n\t0. Atras\n\nElige una opcion: ");

    char inputReservaLocal[MAX_SELECCION];
    int numReservaLocal;

    fgets(inputReservaLocal, MAX_SELECCION, stdin);
    sscanf(inputReservaLocal, "%d", &numReservaLocal);

    return *inputReservaLocal;
}

char* elegirFecha() {
    printf("\n\tIntroduce la fecha: ");

    char inputFecha[MAX_FECHA];
    fgets(inputFecha, MAX_SELECCION, stdin);
    //return *inputFecha;
}

char* elegirDiscoteca() {
    printf("\tIntroduce el nombre de la discoteca: ");

    char inputDiscoteca[MAX_FECHA];
    fgets(inputDiscoteca, MAX_SELECCION, stdin);
    //return *inputDiscoteca;
}

void reservarLocal() {
    char opcionReserva;
    char nombreDiscoteca[MAX_NOMBRE_DISCOTECA];
    char fechaReserva[MAX_FECHA];

    do {
        opcionReserva = mostrarListado();
        switch (opcionReserva) {
            case '1': 
                printf("\n---------------------------------------------------\n");
                printf("Introducir fecha y nombre de discoteca");

                elegirFecha();
                elegirDiscoteca();
                //fechaReserva = elegirFecha();
                //nombreDiscoteca = elegirDiscoteca();

                //pagarReserva();
            break;
        }

    } while (opcionReserva != '0');
}

void cargarLocales() {

}

char mostrarPagarReserva() {

}

void pagarReserva() {

}
