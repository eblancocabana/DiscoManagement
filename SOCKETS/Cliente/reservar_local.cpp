#include <iostream>
#include <string>
#include <cstring>
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

void enviar_datos(string nombre_funcion, int num_args, ...) {
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

    string inputReservaLocal;
    getline(cin, inputReservaLocal);

    return inputReservaLocal[0];
}

int elegirCodigo() {
    cout << "\n\tIntroduce el codigo del local: ";
    string inputCodigo;
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

    string inputPagarReserva;
    int numPagarReserva;

    getline(cin, inputPagarReserva);
    sscanf(inputPagarReserva.c_str(), "%d", &numPagarReserva);

    return inputPagarReserva[0];
}

char confirmarPagoReserva() {
    cout << "\nConfirmar pago:\n\t1. Confirmar \n\t0. Atras\n\nElige una opcion: ";

    string inputConfirmarReserva;
    int numConfirmarReserva;

    getline(cin, inputConfirmarReserva);
    sscanf(inputConfirmarReserva.c_str(), "%d", &numConfirmarReserva);

    return inputConfirmarReserva[0];
}

string introducirNumeroTarjeta() {
    cout << "\n\tIntroduce el numero de tarjeta (sin espacios): ";

    string inputNumeroTarjeta;
    getline(cin, inputNumeroTarjeta);
    return inputNumeroTarjeta;
}

string introducirCVVTarjeta() {
    cout << "\tIntroduce el CVV de tarjeta: ";

    string inputCVV;
    getline(cin, inputCVV);
    return inputCVV;
}

string introducirCaduTarjeta() {
    cout << "\tIntroduce la caducidad de tarjeta (mm/aa): ";

    string inputCaducidad;
    getline(cin, inputCaducidad);
    return inputCaducidad;
}

void pagarReserva() {
    string numeroTarjeta;
    string cvvTarjeta;
    string caducidadTarjeta;

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
