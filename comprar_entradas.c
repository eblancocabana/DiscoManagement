#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comprar_entradas.h"
#include "basedatos/sqlite/sqlite3.h"
#include "basedatos/baseDatos.h"
#include "inicio.h"

#define MAX_SELECCION 5

#define MAX_ENTRADAS 10
#define MAX_NOMBRE 40
#define MAX_GMAIL 30

#define MAX_NUM_TARJETA 20
#define MAX_CVV 5
#define MAX_CADUCIDAD 10

#define MAX_COD_RRPP 5

char opcionDatosCompra;
char opcionPagoEntrada;
char opcionConfirmarPago;
char opcionConfirmarCompra;

char mostrarDatosCompra(){
    printf("\nDatos necesarios:\n\t1. Comprar \n\t0. Atras\n\nElige una opcion: ");

    char inputDatosCompra[MAX_SELECCION];
    int numDatosCompra;

    fgets(inputDatosCompra, MAX_SELECCION, stdin);
    sscanf(inputDatosCompra, "%d", &numDatosCompra);

    return *inputDatosCompra;
}

int introducirNumEntradas(){
    printf("\n\tIntroduce el numero de entradas: ");

    char inputNumEntradas[MAX_ENTRADAS];
    int numEntradas;

    fgets(inputNumEntradas, MAX_ENTRADAS, stdin);
    
    sscanf(inputNumEntradas, "%d", &numEntradas);
    return numEntradas;
}

char* introducirNombreCompleto(){
    printf("\tIntroduce tu nombre completo: ");

    //char inputNombreCompleto[MAX_NOMBRE];
    char* inputNombreCompleto = (char*) malloc(MAX_NOMBRE * sizeof(char));
    fgets(inputNombreCompleto, MAX_NOMBRE, stdin);
    return inputNombreCompleto;
}

char* introducirGmail(){
    printf("\tIntroduce tu cuenta de gmail: ");

    //char inputGmail[MAX_GMAIL];
    char* inputGmail = (char*) malloc(MAX_GMAIL * sizeof(char));
    fgets(inputGmail, MAX_GMAIL, stdin);
    return inputGmail;
}

void datosCompra(){
    // char opcionDatosCompra;
    int numEntradas;
    char* nombreCompleto;
    char* gmail;

    do{
        opcionDatosCompra = mostrarDatosCompra();
        switch(opcionDatosCompra){
            case '1':
                printf("\n---------------------------------------------------\n");
                printf("Introducir datos de la compra");
                numEntradas = introducirNumEntradas();
                nombreCompleto = introducirNombreCompleto();
                gmail = introducirGmail();

                int len = strcspn(nombreCompleto, "\n");
                nombreCompleto[len] = '\0';

                len = strcspn(gmail, "\n");
                gmail[len] = '\0';

                pagarEntrada();
            break;
        }
    } while(opcionDatosCompra != '0');
}

char mostrarPagarEntrada(){
    printf("\nPagar entrada:\n\t1. Confirmar \n\t0. Atras\n\nElige una opcion: ");

    char inputPagarEntrada[MAX_SELECCION];
    int numPagarEntrada;

    fgets(inputPagarEntrada, MAX_SELECCION, stdin);
    sscanf(inputPagarEntrada, "%d", &numPagarEntrada);

    return *inputPagarEntrada;
}

char* introducirNumTarjeta() {
    printf("\n\tIntroduce el numero de tarjeta (sin espacios): ");

    //char inputNumTarjeta[MAX_NUM_TARJETA];
    char* inputNumTarjeta = (char*) malloc(MAX_NUM_TARJETA * sizeof(char));
    fgets(inputNumTarjeta, MAX_NUM_TARJETA, stdin);
    return inputNumTarjeta;
}

char* introducirCaducidadTarjeta() {
    printf("\tIntroduce la caducidad de tarjeta (mm/aa): ");

    //char inputCaducidad[MAX_CADUCIDAD];
    char* inputCaducidad = (char*) malloc(MAX_CADUCIDAD * sizeof(char));
    fgets(inputCaducidad, MAX_CADUCIDAD, stdin);
    return inputCaducidad;
}

char* introducirCVVTar() {
    printf("\tIntroduce el CVV de tarjeta: ");

    //char inputCVV[MAX_CVV];
    char* inputCVV = (char*) malloc(MAX_CVV * sizeof(char));
    fgets(inputCVV, MAX_CVV, stdin);
    return inputCVV;
}

void pagarEntrada(){
    //char opcionPagoEntrada;
    char* numTarjeta;
    char* cvvTarjeta;
    char* caducidadTarjeta;

    do{
        opcionPagoEntrada = mostrarPagarEntrada();
        switch(opcionPagoEntrada){
            case '1':
                printf("\n---------------------------------------------------\n");
                printf("Introducir datos de la tarjeta");
                numTarjeta = introducirNumTarjeta();
                cvvTarjeta = introducirCVVTar();
                caducidadTarjeta = introducirCaducidadTarjeta();

                int len = strcspn(numTarjeta, "\n");
                numTarjeta[len] = '\0';

                len = strcspn(cvvTarjeta, "\n");
                cvvTarjeta[len] = '\0';

                len = strcspn(caducidadTarjeta, "\n");
                caducidadTarjeta[len] = '\0';

                confirmarPago();
            break;
        }
    } while(opcionPagoEntrada != '0');
}

char mostrarConfirmarPago(){
    printf("\nConfirmar pago:\n\t1. Confirmar pago (RRPP)\n\t0. Atras\n\nElige una opcion: ");

    char inputConfirmarPago[MAX_SELECCION];
    int numConfirmarPago;

    fgets(inputConfirmarPago, MAX_SELECCION, stdin);
    sscanf(inputConfirmarPago, "%d", &numConfirmarPago);

    return *inputConfirmarPago;
}

char confirmarPagoCompra(){
    printf("\nConfirmar pago:\n\t1. Confirmar\n\t0. Atras\n\nElige una opcion: ");

    char inputConfirmarCompra[MAX_SELECCION];
    int numConfirmarCompra;

    fgets(inputConfirmarCompra, MAX_SELECCION, stdin);
    sscanf(inputConfirmarCompra, "%d", &numConfirmarCompra);

    return *inputConfirmarCompra;
}

int introducirCodigoRRPP() {
    printf("\n\tIntroduce el codigo del RRPP: ");

    //char inputCodRRPP[MAX_COD_RRPP];
    char* inputCodRRPP = (char*) malloc(MAX_COD_RRPP * sizeof(char));
    int cdRRPP;
    fgets(inputCodRRPP, MAX_COD_RRPP, stdin);
    sscanf(inputCodRRPP, "%d", &cdRRPP);
    return cdRRPP;
}

void confirmarPago(){
    //char opcionConfirmarPago;
    int codigoRRPP;

    do{
        opcionConfirmarPago = mostrarConfirmarPago();
        switch(opcionConfirmarPago){
            case '1':
                printf("\n---------------------------------------------------\n");
                mostrarRRPP();
                printf("\n---------------------------------------------------\n");
                printf("Introducir Codigo de RRPP");
                codigoRRPP = introducirCodigoRRPP();
                comprobarCodigoRRPP(codigoRRPP);

                confirmarCompra();
            break;
            //case '2':
                
        }   

    } while(opcionConfirmarPago != '0');

}

void confirmarCompra(){
    //char opcionConfirmarCompra;

    do {
        opcionConfirmarCompra = confirmarPagoCompra();
        switch (opcionConfirmarCompra) {
            case '1':
                printf("\nEL PAGO HA SIDO CONFIRMADO");
                printf("\n---------------------------------------------------\n");
                opcionDatosCompra = '0';
                opcionPagoEntrada = '0';
                opcionConfirmarPago = '0';
                opcionConfirmarCompra = '0';
                menu();
            break;
        }
    } while (opcionConfirmarCompra != '0');
    
}



