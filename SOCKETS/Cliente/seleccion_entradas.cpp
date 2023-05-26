#include <iostream>
#include <string>
#include "seleccion_entradas.h"
#include "comprar_entradas.h"
//#include "basedatos/sqlite/sqlite3.h"
//#include "basedatos/baseDatos.h"
#include "inicio.h"
#include "enviar_datos.h"
#include "recibir_datos.h"

#define MAX_SELECCION 5
#define MAX_REGISTRO 20
#define MAX_CODIGO 5

#define SEGUNDOS 2
#define PRECIO_CONS_1 10
#define PRECIO_CONS_2 15
#define PRECIO_CONS_3 20
#define PRECIO_RES 25

using namespace std;

int codigoFecha = 0;
int tipoEntrada = 0;
double precio = 0;

char introducirTipoEntrada() {
    cout << "\n---------------------------------------------------\n";
    cout << "Tipos de entrada:\n";
    cout << "\t1. Una consumicion (" << PRECIO_CONS_1 << " euro)\n";
    cout << "\t2. Dos consumiciones (" << PRECIO_CONS_2 << " euro)\n";
    cout << "\t3. Tres consumiciones (" << PRECIO_CONS_3 << " euro)\n";
    cout << "\t4. Reservado (" << PRECIO_RES << " euro)\n";
    cout << "\t0. Atras\n\n";
    cout << "Elige una opcion: ";

    char inputDatosCompra[MAX_SELECCION];
    int numDatosCompra;

    cin.getline(inputDatosCompra, MAX_SELECCION);

    return *inputDatosCompra;
}

void tipoEntradaSeleccionada() {
    char opcionTipoEntrada;
    do {
        opcionTipoEntrada = introducirTipoEntrada();
        switch (opcionTipoEntrada) {
            case '1':
                cout << "Ha seleccionado entradas con " << opcionTipoEntrada << " consumicion, con un precio de: " << PRECIO_CONS_1 << " euro\n";
                tipoEntrada = 1;
                precio = 10;
                datosCompra(codigoFecha, tipoEntrada, precio);
                break;

            case '2':
                cout << "Ha seleccionado entradas con " << opcionTipoEntrada << " consumiciones, con un precio de: " << PRECIO_CONS_2 << " euro\n";
                tipoEntrada = 2;
                precio = 15;
                datosCompra(codigoFecha, tipoEntrada, precio);
                break;

            case '3':
                cout << "Ha seleccionado entradas con " << opcionTipoEntrada << " consumiciones, con un precio de: " << PRECIO_CONS_3 << " euro\n";
                tipoEntrada = 3;
                precio = 20;
                datosCompra(codigoFecha, tipoEntrada, precio);
                break;

            case '4':
                cout << "Ha seleccionado entradas para reservado, con un precio de: " << PRECIO_RES << " euro\n";
                tipoEntrada = 4;
                precio = 25;
                datosCompra(codigoFecha, tipoEntrada, precio);
                break;
        }
    } while (opcionTipoEntrada != '0');
}

void mostrarDiasDisponibles() {
    cout << "\n----------------------------------------------------------\n";
    cout << "Entrada 1\n\n";
    cout << "Codigo de la fecha: " << "No me apetece" << endl;
    cout << "Fecha: " << "El dia que Sabin se duche" << endl;
    cout << "Nombre de la discoteca: " << "StackOverflow" << endl;
    cout << "Entradas disponibles: " << 666 << endl;
    cout << "Evento especial: " << "NO" << endl;
    cout << "\n----------------------------------------------------------\n";
}

char introducirCodioDia() {

    cout << "\nOpcion comprar entrada" << endl;
    cout << "\t1. Introducir identificacion de entrada (codigo)\n";
    cout << "\t0. Atras\n\n";
    cout << "Elige una opcion: ";

    char inputDatosCompra[MAX_SELECCION];
    int numDatosCompra;

    cin.getline(inputDatosCompra, MAX_SELECCION);

    return *inputDatosCompra;
}

void menuListadoDiasDisponibles() {
    char opcionMenuCalendario;
    char inputCod[MAX_REGISTRO];
    int codigo;
    char* cod;
    char* type;
    char strNum[3];
    char strCodigo[4];
    char auxCodigo[16];

    do {
        opcionMenuCalendario = introducirCodioDia();
        switch (opcionMenuCalendario) {
            case '1':
                cout << "\n---------------------------------------------------\n";

                do {
                    cout << "Codigo de la entrada: ";
                    cin.getline(inputCod, MAX_CODIGO);

                    sscanf(inputCod, "%d", &codigo);
                    //BD
                    //cod = limpiarInput(inputCod);
                    enviar_datos("limpiarInput", 1, &inputCod, sizeof(inputCod));
                    cod = recibir_datos<char*>();

                    errno = 0;
                    long int num = strtol(cod, &type, 10); //CodigoFecha
                    codigoFecha = num;
                    if (errno != 0 || *type != '\0') {
                        cout << "'" << cod << "' no es una entrada valida\n";
                    }

                } while (errno != 0 || *type != '\0');

                if (codigo < 100) {
                    sprintf(strNum, "%d", codigo);

                    char strCodigo[4] = {'0', '\0'};
                    strcat(strCodigo, strNum);
                    //BD
                    enviar_datos("comprobarCodigoEntrada", 1, strCodigo, strlen(strCodigo));
                    int resultado = recibir_datos_int();
                    if ( resultado== 0) {
                        cout << "Entrada con codigo: '" << strCodigo << "' seleccionada correctamente\n";
                        tipoEntradaSeleccionada();
                    } else if ( resultado== -1) {
                        cout << "El codigo de entrada seleccionado no existe\nOperacion cancelada\n";

                    } else {
                        cout << "Codigo seleccionado incorrectamente\nOperacion cancelada\n";
                        menu();
                    }

                } else {
                    sprintf(auxCodigo, "%d", codigo);
                    //BD
                    enviar_datos("comprobarCodigoEntrada", 1, auxCodigo, strlen(auxCodigo));
                    
                    int resultado = recibir_datos_int();
                    if (resultado== 0) {
                        cout << "Entrada con codigo: '" << auxCodigo << "' seleccionada correctamente\n";
                        tipoEntradaSeleccionada();
                    } else if ( resultado== -1) {
                        cout << "El codigo de entrada seleccionado no existe\nOperacion cancelada\n";

                    } else {
                        cout << "Codigo seleccionado incorrectamente\nOperacion cancelada\n";
                        menu();
                    }
                }
                break;
        }
    } while (opcionMenuCalendario != '0');
}
