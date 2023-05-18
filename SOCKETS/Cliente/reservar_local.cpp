#include <iostream>
#include <char*>
#include <cchar*>
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

using namespace std;

char opcionReserva;
char opcionPagoReserva;
char opcionConfirmarReserva;

void enviar_datos(char* nombre_funcion, int num_args, ...) {
    va_list args;
    va_start(args, num_args);

    if (nombre_funcion == "mostrarLocales") {
        mostrarLocales();
    } else if (nombre_funcion == "comprobarCodigoLocal") {
        int codLocal = va_arg(args, int);
        comprobarCodigoLocal(codLocal);
    }

    va_end(args);
}

char mostrarListado() {
    cout << "\nListado de dias disponible: (codigo - fecha - nombre discoteca - aforo - evento?)\n\n";
    //BD
    enviar_datos("mostrarLocales", 0);
    cout << "\nOpcion reserva:\n\t1. Realizar reserva \n\t0. Atras\n\nElige una opcion: ";

    char* inputReservaLocal;
    getline(cin, inputReservaLocal);

    return inputReservaLocal[0];
}

int elegirCodigo() {
    cout << "\n\tIntroduce el codigo del local: ";
    char* inputCodigo;
    int numCodigo;

    getline(cin, inputCodigo);
    sscanf(inputCodigo.c_str(), "%d", &numCodigo);
    return numCodigo;
}

void reservarLocal() {
    int codLocal;
    int existe = 0;

    do {
        opcionReserva = mostrarListado();
        switch (opcionReserva) {
            case '1': 
                cout << "\n---------------------------------------------------\n";
                cout << "Introducir fecha y nombre de discoteca";

                codLocal = elegirCodigo();
                //BD
                existe = enviar_datos("comprobarCodigoLocal", 1, codLocal);

                pagarReserva();
            break;
        }

    } while (opcionReserva != '0');
}


char mostrarPagarReserva() {
    cout << "\nPagar reserva:\n\t1. Confirmar \n\t0. Atras\n\nElige una opcion: ";

    char* inputPagarReserva;
    int numPagarReserva;

    getline(cin, inputPagarReserva);
    sscanf(inputPagarReserva.c_str(), "%d", &numPagarReserva);

    return inputPagarReserva[0];
}

char confirmarPagoReserva() {
    cout << "\nConfirmar pago:\n\t1. Confirmar \n\t0. Atras\n\nElige una opcion: ";

    char* inputConfirmarReserva;
    int numConfirmarReserva;

    getline(cin, inputConfirmarReserva);
    sscanf(inputConfirmarReserva.c_str(), "%d", &numConfirmarReserva);

    return inputConfirmarReserva[0];
}

char* introducirNumeroTarjeta() {
    cout << "\n\tIntroduce el numero de tarjeta (sin espacios): ";

    char* inputNumeroTarjeta;
    getline(cin, inputNumeroTarjeta);
    return inputNumeroTarjeta;
}

char* introducirCVVTarjeta() {
    cout << "\tIntroduce el CVV de tarjeta: ";

    char* inputCVV;
    getline(cin, inputCVV);
    return inputCVV;
}

char* introducirCaduTarjeta() {
    cout << "\tIntroduce la caducidad de tarjeta (mm/aa): ";

    char* inputCaducidad;
    getline(cin, inputCaducidad);
    return inputCaducidad;
}

void pagarReserva() {
    char* numeroTarjeta;
    char* cvvTarjeta;
    char* caducidadTarjeta;

    do {
        opcionPagoReserva = mostrarPagarReserva();
        switch (opcionPagoReserva) {
            case '1': 
                cout << "\n---------------------------------------------------\n";
                cout << "Introducir datos de la tarjeta";
                
                numeroTarjeta = introducirNumeroTarjeta();
                cvvTarjeta = introducirCVVTarjeta();
                caducidadTarjeta = introducirCaduTarjeta();

                int len = numeroTarjeta.find('\n');
                numeroTarjeta = numeroTarjeta.substr(0, len);

                len = cvvTarjeta.find('\n');
                cvvTarjeta = cvvTarjeta.substr(0, len);

                len = caducidadTarjeta.find('\n');
                caducidadTarjeta = caducidadTarjeta.substr(0, len);

                confirmarReserva();
            break;
        }

    } while (opcionPagoReserva != '0');
}


void confirmarReserva() {
    do {
        opcionConfirmarReserva = confirmarPagoReserva();
        switch (opcionConfirmarReserva) {
            case '1':
                cout << "\nEL PAGO HA SIDO CONFIRMADO";
                menu();
                opcionConfirmarReserva = '0';
                opcionPagoReserva = '0';
                opcionReserva = '0';
            break;
        }
    } while (opcionConfirmarReserva != '0');
}
