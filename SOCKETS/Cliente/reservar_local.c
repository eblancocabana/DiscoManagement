#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reservar_local.h"
#include "basedatos/baseDatos.h"
#include "inicio.h"

#define MAX_SELECCION 5
#define MAX_NOMBRE_DISCOTECA 20
#define MAX_FECHA 15
#define MAX_CODIGO 10

#define MAX_NUMERO_TARJETA 25
#define MAX_CVV 5
#define MAX_CADUCIDAD 10

char opcionReserva;
char opcionPagoReserva;
char opcionConfirmarReserva;


char mostrarListado() {
    printf("\e[37m\e[1m");
    printf("\nListado de dias disponible: (codigo - fecha - nombre discoteca - aforo - evento?)\n\n");
    printf("\e[0m");
    //BD
    mostrarLocales(); // Se van a mostrar aquellos dias en los que todavia no se hayan comprado entradas
    printf("\nOpcion reserva:\n\t1. Realizar reserva \n\t0. Atras\n\nElige una opcion: ");

    char inputReservaLocal[MAX_SELECCION];
    //int numReservaLocal;

    fgets(inputReservaLocal, MAX_SELECCION, stdin);
    //sscanf(inputReservaLocal, "%d", &numReservaLocal);

    return *inputReservaLocal;
}

int elegirCodigo() {
    printf("\n\tIntroduce el codigo del local: ");
    char inputCodigo[MAX_CODIGO];
    int numCodigo;

    fgets(inputCodigo, MAX_CODIGO, stdin);
    sscanf(inputCodigo, "%d", &numCodigo);
    return numCodigo;
}

void reservarLocal() {
    //char opcionReserva;
    int codLocal;
    int existe = 0;

    do {
        opcionReserva = mostrarListado();
        switch (opcionReserva) {
            case '1': 
                printf("\n---------------------------------------------------\n");
                printf("Introducir fecha y nombre de discoteca");

                codLocal = elegirCodigo();
                //BD
                existe = comprobarCodigoLocal(codLocal);

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

    char* inputNumeroTarjeta = (char*) malloc(MAX_NUMERO_TARJETA * sizeof(char));
    fgets(inputNumeroTarjeta, MAX_NUMERO_TARJETA, stdin);
    return inputNumeroTarjeta;
}

char* introducirCVVTarjeta() {
    printf("\tIntroduce el CVV de tarjeta: ");

    char* inputCVV = (char*) malloc(MAX_CVV * sizeof(char));
    fgets(inputCVV, MAX_CVV, stdin);
    return inputCVV;
}

char* introducirCaduTarjeta() {
    printf("\tIntroduce la caducidad de tarjeta (mm/aa): ");

    char* inputCaducidad = (char*) malloc(MAX_CADUCIDAD * sizeof(char));
    fgets(inputCaducidad, MAX_CADUCIDAD, stdin);
    return inputCaducidad;
}

void pagarReserva() {
    //char opcionPagoReserva;
    char* numeroTarjeta;
    char* cvvTarjeta;
    char* caducidadTarjeta;

    do {
        opcionPagoReserva = mostrarPagarReserva();
        switch (opcionPagoReserva) {
            case '1': 
                printf("\n---------------------------------------------------\n");
                printf("Introducir datos de la tarjeta");
                
                numeroTarjeta = introducirNumeroTarjeta();
                cvvTarjeta = introducirCVVTarjeta();
                caducidadTarjeta = introducirCaduTarjeta();

                int len = strcspn(numeroTarjeta, "\n");
                numeroTarjeta[len] = '\0';

                len = strcspn(cvvTarjeta, "\n");
                cvvTarjeta[len] = '\0';

                len = strcspn(caducidadTarjeta, "\n");
                caducidadTarjeta[len] = '\0';

                confirmarReserva();
            break;
        }

    } while (opcionPagoReserva != '0');
}


void confirmarReserva() {
    // char opcionConfirmarReserva;

    do {
        opcionConfirmarReserva = confirmarPagoReserva();
        switch (opcionConfirmarReserva) {
            case '1':
                printf("\nEL PAGO HA SIDO CONFIRMADO");
                menu();
                opcionConfirmarReserva = '0';
                opcionPagoReserva = '0';
                opcionReserva = '0';
            break;
        }
    } while (opcionConfirmarReserva != '0');
    
}
