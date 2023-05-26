#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <cerrno>
#include "inicio.h"
#include "reservar_local.h"
#include "comprar_entradas.h"
//#include "basedatos/sqlite/sqlite3.h"
//#include "basedatos/baseDatos.h"
#include "seleccion_entradas.h"
#include "enviar_datos.h"
#include "recibir_datos.h"


using namespace std;

#define MAX_SELECCION 5
#define MAX_REGISTRO 20
#define MAX_LOGIN 15

#define MAX_NOMBRE 20
#define MAX_NOMBRE_USU 20
#define MAX_SEXO 20
#define MAX_EDAD 20
#define MAX_CORREO 20
#define MAX_CONTRASENYA 20

char* name;
char* username;
char* sex;
int edad;
char* correoElec;
char* password;

char mostrarLogin() {
 char inputLogin[MAX_SELECCION];
 int numLogin;
 cout << "\n---------------------------------------------------\n";
 cout << "Inicio Sesion: \n\t1. Registrarse \n\t2. Login \n\t0. Salir \n\n Elige una opcion: ";
 cin.getline(inputLogin, MAX_SELECCION);
 sscanf(inputLogin, "%d", &numLogin);

 return *inputLogin;
}

char mostrarRegistrarse() {
 char inputRegistrarse[MAX_SELECCION];
 int numRegistrarse;
 cout << "\n\t1. Aceptar \n\t0. Atras \n\n Elige una opcion: ";
 cin.getline(inputRegistrarse, MAX_SELECCION);
 sscanf(inputRegistrarse, "%d", &numRegistrarse);

 return *inputRegistrarse;
}

char mostrarMenu() {
 char inputMenu[MAX_SELECCION];
 int numMenu;
 cout << "\n---------------------------------------------------\n";
 cout << "Menu Principal: \n\t1. Informacion de eventos \n\t2. Comprar entradas \n\t3. Reservar local \n\t4. Mis reservas / compras \n\t0. Cerrar Sesion \n\n Elige una opcion: ";
 cin.getline(inputMenu, MAX_SELECCION);
 sscanf(inputMenu, "%d", &numMenu);

 return *inputMenu;
}

void rellenarCamposRegistro() {
    char inputRegis[MAX_REGISTRO];
    char nombre[MAX_NOMBRE];
    char* nombreUsu;
    char* sexo;
    char* age;
    char* correo;
    char* contrasenya;
    char* repertirContrasenya;
    int existe = 1;
    char* type;

    cout << "Menu Registro:\n\n";
    cout << "Nombre: ";
    cin.getline(inputRegis, MAX_NOMBRE);
    sscanf(inputRegis, "%s", &nombre);
    enviar_datos("limpiarInput", 1, &inputRegis, sizeof(inputRegis));
    name = recibir_datos_char();
    printf("NOMBREEEEEEE");
    printf(name);

    cout << "Nombre de Usuario: ";
    cin.getline(inputRegis, MAX_NOMBRE_USU);
    sscanf(inputRegis, "%s", &nombreUsu);
    enviar_datos("limpiarInput", 1, &inputRegis, sizeof(inputRegis));
    username = recibir_datos_char();

    cout << "Sexo: ";
    cin.getline(inputRegis, MAX_SEXO);
    sscanf(inputRegis, "%s", &sexo);
    enviar_datos("limpiarInput", 1, &inputRegis, sizeof(inputRegis));
    sex = recibir_datos_char();

    do {
        cout << "Edad: ";
        cin.getline(inputRegis, MAX_EDAD);
        sscanf(inputRegis, "%i", &edad);
        enviar_datos("limpiarInput", 1, &inputRegis, sizeof(inputRegis));
        age = recibir_datos_char();

        errno = 0;
        long int num = strtol(age, &type, 10);

        if (errno != 0 || *type != '\0') {
            cout << "'" << age << "' no es una edad valida" << endl;
        }
    } while (errno != 0 || *type != '\0');

    cout << "Correo Electronico: ";
    cin.getline(inputRegis, MAX_CORREO);
    sscanf(inputRegis, "%s", &correo);
    enviar_datos("limpiarInput", 1, &inputRegis, sizeof(inputRegis));
    correoElec = recibir_datos_char();

    cout << "Contrasenya: ";
    cin.getline(inputRegis, MAX_CONTRASENYA);
    sscanf(inputRegis, "%s", &contrasenya);
    enviar_datos("limpiarInput", 1, &inputRegis, sizeof(inputRegis));
    char* password = recibir_datos_char();


    cout << "Repetir Contrasenya: ";
    cin.getline(inputRegis, MAX_CONTRASENYA);
    sscanf(inputRegis, "%s", &repertirContrasenya);
    enviar_datos("limpiarInput", 1, &inputRegis, sizeof(inputRegis));
    char* repPass = recibir_datos_char();

    cout << "\nDatos introducidos: " << name << " - " << username << " - " << sex << " - " << age << " - " << correoElec << " - " << password << " - " << repPass << endl;
    //existe = comprobarUsuario(username); BD
    enviar_datos("comprobarUsuario", 1, &username, sizeof(username));
    existe = recibir_datos_int();

    if ((existe == -1) && (strcmp(password, repPass) != 0)) {
        cout << "Pero las contrasenyas NO coinciden" << endl;
        login();
    } else if ((existe == -1) && (strcmp(password, repPass) == 0)) {
        cout << "Valores aceptados para ser introducidos a la BD" << endl;
        cout << "\n---------------------------------------------------\n";
        cout << "Quiere registrarse?\n";
    } else if (existe == 0) {
        cout << "\nEl usuario ya existe, registro cancelado\n";
        login();
    }
}

// ...
void iniciarSesion() {
    int existe = 1;
    char input[MAX_REGISTRO];

    cout << "Usuario: ";
    cin.getline(input, MAX_NOMBRE_USU);
    enviar_datos("limpiarInput", 1, &input, sizeof(input));
    char* us = recibir_datos_char();

    cout << "Contrasenya: ";
    cin.getline(input, MAX_CONTRASENYA);
    enviar_datos("limpiarInput", 1, &input, sizeof(input));
    char* pa = recibir_datos_char();

    enviar_datos("comprobarExistencia", 2, us, sizeof(us), pa, sizeof(pa));
    existe = recibir_datos_int();
    enviar_datos("comprobarAdmin", 1, us, sizeof(us));
    int admin = recibir_datos_int();
    if ((existe == 0) && ( admin== 0)) {
        cout << "\nADMIN ENCONTRADO, accediendo al menu\n";
    } else if ((existe == 0)) {
        cout << "\nUSUARIO ENCONTRADO, accediendo al menu\n";
        menu();
    } else {
        // Hacer algo si no se encuentra el usuario o la contraseña es incorrecta
    }
}

int registrarse() {
    char opcionRegistrarse;

    rellenarCamposRegistro();

    do {
        opcionRegistrarse = mostrarRegistrarse();
        switch (opcionRegistrarse) {
            case '1':
                enviar_datos("insertarRegistro", 7, name, sizeof(name), username, sizeof(username), sex, sizeof(sex), edad, sizeof(edad), correoElec, sizeof(correoElec), password, sizeof(password));
                login();
                break;
        }
    } while (opcionRegistrarse != '0');

    return 0;
}

int login() {
    char opcionLogin;

    do {
        opcionLogin = mostrarLogin();
        switch (opcionLogin) {
            case '1':
                cout << "\n---------------------------------------------------\n";
                registrarse();
                break;

            case '2':
                cout << "\n---------------------------------------------------\n";
                iniciarSesion();
                break;
        }
    } while (opcionLogin != '0');

    if (opcionLogin == '0') {
        exit(0);
    }

    return 0;
}

int menu() {
    char opcionMenu;

    do {
        opcionMenu = mostrarMenu();
        switch (opcionMenu) {
            case '1':
                cout << "\n---------------------------------------------------\n";
                cout << "\e[37m\e[1m";
                cout << "Listado de eventos (fecha - descripcion - nombre discoteca - aforo)\n\n";
                cout << "\e[0m";
                //mostrarlistadoeventos(); BD
                enviar_datos("mostrarlistadoeventos", 0);
                break;

            case '2':
                cout << "\n---------------------------------------------------\n";
                cout << "\e[37m\e[1m";
                cout << "Menu compra de entrada (codigo - fecha - nombre discoteca - aforo - evento?)\n\n";
                cout << "\e[0m";
                //mostrarFiestas(); BD
                enviar_datos("mostrarFiestas", 0);
                menuListadoDiasDisponibles();
                break;

            case '3':
                cout << "\n---------------------------------------------------\n";
                reservarLocal();
                break;

            case '4':
                cout << "\n---------------------------------------------------\n";
                cout << "Listado de mis reservas\n\n";
                break;
        }
    } while (opcionMenu != '0');

    return 0;
}
