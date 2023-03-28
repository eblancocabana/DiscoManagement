#include <stdio.h>
#include "reservar_local.h"

#define MAX_SELECCION 5
#define MAX_NOMBRE_DISCOTECA 20
#define MAX_FECHA 15

#define MAX_NUMERO_TARJETA 20
#define MAX_CVV 3
#define MAX_CADUCIDAD 5

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

                pagarReserva();
            break;
        }

    } while (opcionReserva != '0');
}

void cargarLocales() {

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

char* introducirCaducidadTarjeta() {
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
                introducirCaducidadTarjeta();
                // numeroTarjeta[MAX_NUMERO_TARJETA] = introducirNumeroTarjeta();
                // cvvTarjeta[MAX_CVV] = introducirCVVTarjeta();
                // caducidadTarjeta[MAX_CADUCIDAD] = introducirCaducidadTarjeta();

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
