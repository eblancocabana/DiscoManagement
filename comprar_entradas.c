#include <stdio.h>
#include "comprar_entradas.h"

#define MAX_SELECCION 5

#define MAX_ENTRADAS 10
#define MAX_NOMBRE 40
#define MAX_GMAIL 30

#define MAX_NUM_TARJETA 20
#define MAX_CVV 3
#define MAX_CADUCIDAD 5

#define MAX_COD_RRPP 2

char mostrarDatosCompra(){
    printf("\nDatos necesarios:\n\t1. Comprar \n\t0. Atras\n\nElige una opcion: ");

    char inputDatosCompra[MAX_SELECCION];
    int numDatosCompra;

    fgets(inputDatosCompra, MAX_SELECCION, stdin);
    sscanf(inputDatosCompra, "%d", &numDatosCompra);

    return *inputDatosCompra;
}

int* introducirNumEntradas(){
    printf("\n\tIntroduce el numero de entradas: ");

    char inputNumEntradas[MAX_ENTRADAS];
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

    char inputNumTarjeta[MAX_NUM_TARJETA];
    fgets(inputNumTarjeta, MAX_NUM_TARJETA, stdin);
    //return *inputNumeroTarjeta;
}

char* introducirCaducidadTarjeta() {
    printf("\tIntroduce la caducidad de tarjeta (mm/aa): ");

    char inputCaducidad[MAX_CADUCIDAD];
    fgets(inputCaducidad, MAX_CADUCIDAD, stdin);
    //return *inputCaducidad;
}

char* introducirCVVTar() {
    printf("\tIntroduce el CVV de tarjeta: ");

    char inputCVV[MAX_CVV];
    fgets(inputCVV, MAX_CVV, stdin);
    //return *inputCVV;
}

void pagarEntrada(){
    char opcionPagoEntrada;
    char numTarjeta[MAX_NUM_TARJETA];
    char cvvTarjeta[MAX_CVV];
    char caducidadTarjeta[MAX_CADUCIDAD];

    do{
        opcionPagoEntrada = mostrarPagarEntrada();
        switch(opcionPagoEntrada){
            case '1':
                printf("\n---------------------------------------------------\n");
                printf("Introducir datos de la tarjeta");
                introducirNumTarjeta();
                introducirCaducidadTarjeta();
                introducirCVVTar();
                // numeroTarjeta[MAX_NUMERO_TARJETA] = introducirNumeroTarjeta();
                // cvvTarjeta[MAX_CVV] = introducirCVVTar();
                // caducidadTarjeta[MAX_CADUCIDAD] = introducirCaducidadTarjeta();
            break;
        }
    } while(opcionPagoEntrada != 0);
}

char mostrarConfirmarPago(){
    printf("\nConfirmar pago:\n\t1. Confirmar pago (RRPP)\n\t2. Confirmar pago (PDF)\n\t0. Atras\n\nElige una opcion: ");

    char inputConfirmarPago[MAX_SELECCION];
    int numConfirmarPago;

    fgets(inputConfirmarPago, MAX_SELECCION, stdin);
    sscanf(inputConfirmarPago, "%d", &numConfirmarPago);

    return *inputConfirmarPago;
}

char confirmarPagoCompra(){
    printf("\nConfirmar pago:\n\t1. Confirmar \n\t0. Atras\n\nElige una opcion: ");

    char inputConfirmarCompra[MAX_SELECCION];
    int numConfirmarCompra;

    fgets(inputConfirmarCompra, MAX_SELECCION, stdin);
    sscanf(inputConfirmarCompra, "%d", &numConfirmarCompra);

    return *inputConfirmarCompra;
}

char* introducirCodigoRRPP() {
    printf("\n\tIntroduce el codigo del RRPP: ");

    char inputCodRRPP[MAX_COD_RRPP];
    fgets(inputCodRRPP, MAX_COD_RRPP, stdin);
    //return *inputCodRRPP;
}

void confirmarPago(){
    char opcionConfirmarPago;
    char codigoRRPP[MAX_COD_RRPP];

    do{
        opcionConfirmarPago = mostrarConfirmarPago();
        switch(opcionConfirmarPago){
            case '1':
                printf("\n---------------------------------------------------\n");
                printf("Introducir Codigo de RRPP");
                introducirCodigoRRPP();
                // codigoRRPP[MAX_COD_RRPP] = introducirCodigoRRPP();

                confirmarCompra();
            break;
            //case '2':
                
        }   

    }while(opcionConfirmarPago != 0);

}

void confirmarCompra(){
    char opcionConfirmarCompra;

    do {
        opcionConfirmarCompra = confirmarPagoCompra();
        switch (opcionConfirmarCompra) {
            case '1':
                printf("\nEL PAGO HA SIDO CONFIRMADO");
            break;
        }
    } while (opcionConfirmarCompra != '0');
    
}



