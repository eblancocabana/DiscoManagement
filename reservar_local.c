#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reservar_local.h"
#include "basedatos/baseDatos.h"

#define MAX_SELECCION 5
#define MAX_NOMBRE_DISCOTECA 20
#define MAX_FECHA 15

#define MAX_NUMERO_TARJETA 20
#define MAX_CVV 3
#define MAX_CADUCIDAD 5


char mostrarListado() {
    printf("\nListado de dias disponible: (fecha - nombre discoteca - numero de invitados - precio - DJ)\n");
    cargarLocales(); // Se van a mostrar aquellos dias en los que todavia no se hayan comprado entradas
    printf("\n--------------------------------------------------------------------------------------------\n");
    printf("\nListado de dias disponible:\n\t1. Realizar reserva \n\t0. Atras\n\nElige una opcion: ");

    char inputReservaLocal[MAX_SELECCION];
    int numReservaLocal;

    fgets(inputReservaLocal, MAX_SELECCION, stdin);
    sscanf(inputReservaLocal, "%d", &numReservaLocal);

    return *inputReservaLocal;
}

char* elegirFecha() {
    printf("\n\tIntroduce la fecha (dd-mm): ");

    char* inputFecha = (char*) malloc(MAX_FECHA * sizeof(char));
    fgets(inputFecha, MAX_FECHA, stdin);
    return inputFecha;
}

char* elegirDiscoteca() {
    printf("\tIntroduce el nombre de la discoteca: ");

    char* inputDiscoteca = (char*) malloc(MAX_NOMBRE_DISCOTECA * sizeof(char));
    fgets(inputDiscoteca, MAX_NOMBRE_DISCOTECA, stdin);
    return inputDiscoteca;
}

void reservarLocal() {
    char opcionReserva;
    char* nombreDiscoteca;
    char* fechaReserva;

    do {
        opcionReserva = mostrarListado();
        switch (opcionReserva) {
            case '1': 
                printf("\n---------------------------------------------------\n");
                printf("Introducir fecha y nombre de discoteca");

                fechaReserva = elegirFecha();
                nombreDiscoteca = elegirDiscoteca();

                int len = strcspn(fechaReserva, "\n");
                fechaReserva[len] = '\0';

                len = strcspn(nombreDiscoteca, "\n");
                nombreDiscoteca[len] = '\0';

                printf("\n%s, %s", fechaReserva, nombreDiscoteca);

                pagarReserva();
            break;
        }

    } while (opcionReserva != '0');
}


char mostrarPagarReserva() {
    printf("\nPagar reserva:\n\t1. Confirmar \n\t0. Atras\n\nElige una opcion: ");

    char inputPagarReserva[MAX_SELECCION];
    int numPagarReserva;

    fgets(inputPagarReserva, MAX_SELECCION, stdin);
    sscanf(inputPagarReserva, "%d", &numPagarReserva);

    return *inputPagarReserva;
}

char confirmarPagoReserva() {
    printf("\nConfirmar pago:\n\t1. Confirmar \n\t0. Atras\n\nElige una opcion: ");

    char inputConfirmarReserva[MAX_SELECCION];
    int numConfirmarReserva;

    fgets(inputConfirmarReserva, MAX_SELECCION, stdin);
    sscanf(inputConfirmarReserva, "%d", &numConfirmarReserva);

    return *inputConfirmarReserva;
}

char* introducirNumeroTarjeta() {
    printf("\n\tIntroduce el numero de tarjeta (sin espacios): ");

    char inputNumeroTarjeta[MAX_NUMERO_TARJETA];
    fgets(inputNumeroTarjeta, MAX_NUMERO_TARJETA, stdin);
    //return *inputNumeroTarjeta;
}

char* introducirCVVTarjeta() {
    printf("\tIntroduce el CVV de tarjeta: ");

    char inputCVV[MAX_CVV];
    fgets(inputCVV, MAX_CVV, stdin);
    //return *inputCVV;
}

char* introducirCaduTarjeta() {
    printf("\tIntroduce la caducidad de tarjeta (mm/aa): ");

    char inputCaducidad[MAX_CADUCIDAD];
    fgets(inputCaducidad, MAX_CADUCIDAD, stdin);
    //return *inputCaducidad;
}

void pagarReserva() {
    char opcionPagoReserva;
    char numeroTarjeta[MAX_NUMERO_TARJETA];
    char cvvTarjeta[MAX_CVV];
    char caducidadTarjeta[MAX_CADUCIDAD];

    do {
        opcionPagoReserva = mostrarPagarReserva();
        switch (opcionPagoReserva) {
            case '1': 
                printf("\n---------------------------------------------------\n");
                printf("Introducir datos de la tarjeta");
                introducirNumeroTarjeta();
                introducirCVVTarjeta();
                introducirCaduTarjeta();
                // numeroTarjeta[MAX_NUMERO_TARJETA] = introducirNumeroTarjeta();
                // cvvTarjeta[MAX_CVV] = introducirCVVTarjeta();
                // caducidadTarjeta[MAX_CADUCIDAD] = introducirCaduTarjeta();

                confirmarReserva();
            break;
        }

    } while (opcionPagoReserva != '0');
}


void confirmarReserva() {
    char opcionConfirmarReserva;

    do {
        opcionConfirmarReserva = confirmarPagoReserva();
        switch (opcionConfirmarReserva) {
            case '1':
                printf("\nEL PAGO HA SIDO CONFIRMADO");
            break;
        }
    } while (opcionConfirmarReserva != '0');
    
}
