#include <iostream>
#include <string>
#include <string.h>
#include <cctype>
#include <ctime>

extern "C" {
    #include "../basedatos/sqlite/sqlite3.h"
    #include "../basedatos/baseDatos.h"
    #include "../estructuras/entrada_est.h"
    }

#include "inicio_servidor.h"

#define MAX_SELECCION 5
#define MAX_NOM_DISCOTECA 10
#define MAX_FECHA 10
#define MAX_DESCRIPCION 75

using namespace std;

char mostrarIncioServido() {
  std::string inputInicio;
  int numInicio;

  cout << "\n---------------------------------------------------\n";
  cout << "Menu Principal: \n\t1. Informacion de eventos \n\t2. Informacion de fiestas \n\t3. Actualizar base de datos \n\t0. Cerrar Sesion \n\n Elige una opcion: ";

  std::getline(cin, inputInicio);
  sscanf(inputInicio.c_str(), "%d", & numInicio);

  return * inputInicio.c_str();
}

int inicioServidor() {
  char opcionInicioServidor;

  do {
    opcionInicioServidor = mostrarIncioServido();
    switch (opcionInicioServidor) {
    case '1':
      cout << "\n---------------------------------------------------\n";

      cout << "\e[37m\e[1m";
      cout << "Listado de eventos (fecha - descripcion - discoteca - aforo)\n\n";
      cout << "\e[0m";

      mostrarlistadoeventos();
      break;

    case '2':
      cout << "\n---------------------------------------------------\n";

      cout << "\e[37m\e[1m";
      cout << "Listado de dias de fiesta (codigo - fecha - nombre discoteca - entradas disponibles - evento?)\n\n";
      cout << "\e[0m";

      mostrarFiestas();
      break;

    case '3':
      menuServidor();
      break;
    }

  } while (opcionInicioServidor != '0');

  return 0;
}

char mostrarMenuServidor() {
  std::string inputMenu;
  int numMenu;
  cout << "\n---------------------------------------------------\n";
  cout << "Actualizar la Base de Datos: \n\t1. Reiniciar BD \n\t2. Aniadir fiesta \n\t3. Aniadir evento \n\t4. Importar RRPPs \n\t5. Importar DJs \n\t0. Atras \n\n Elige una opcion: ";

  std::getline(cin, inputMenu);
  sscanf(inputMenu.c_str(), "%d", & numMenu);

  return * inputMenu.c_str();
}

char * introducirNombreDiscoteca() {
  cout << "\tIntroduce nombre de la discoteca (Back / Stage): ";

  char * inputDiscoteca = new char[MAX_NOM_DISCOTECA];
  cin.getline(inputDiscoteca, MAX_NOM_DISCOTECA);
  return inputDiscoteca;
}

char * introducirFecha() {
  cout << "\tIntroduce la fecha (dd/mm/aa): ";

  char * inputFecha = new char[MAX_FECHA];
  cin.getline(inputFecha, MAX_FECHA);
  return inputFecha;
}

char * introducirDescripcion() {
  cout << "\tIntroduce la descripcion del evento (max 70 letras): ";

  char * inputDescripcion = new char[MAX_DESCRIPCION];
  cin.getline(inputDescripcion, MAX_DESCRIPCION);
  return inputDescripcion;
}

int menuServidor() {
  char opcionMenu;
  char* nomDiscoteca;
  char* fecha;
  char* descripcionEvento;
  const char* evento;
  int len;
  int existeFecha;

  do {
    opcionMenu = mostrarMenuServidor();
    switch (opcionMenu) {
    case '1':
      reiniciarBD();
      cout << "\nLa Base De Datos se ha reiniciado con los valores de fabrica correctamente\n";
      
      break;

    case '2':
      cout << "\n---------------------------------------------------\n";
      cout << "Aniadir fiesta:\n";

      nomDiscoteca = introducirNombreDiscoteca();
      len = strcspn(nomDiscoteca, "\n");
      nomDiscoteca[len] = '\0';

      fecha = introducirFecha();
      len = strcspn(fecha, "\n");
      fecha[len] = '\0';

      evento = "No";

      nomDiscoteca[0] = toupper(nomDiscoteca[0]);
      for (int i = 1; nomDiscoteca[i] != '\0'; i++) {
        nomDiscoteca[i] = tolower(nomDiscoteca[i]);
      }

        existeFecha = comprobarFecha(fecha, 1);
        if (((strcmp(nomDiscoteca, "Back") == 0) || (strcmp(nomDiscoteca, "Stage") == 0)) && (existeFecha == -1)) {
            int verificacionFecha = 0;
            verificacionFecha = verificarFecha(fecha);
            if (verificacionFecha) {
                
                char* eventoFinal = NULL;
                strcpy(eventoFinal, evento);
                insertarDiaFiesta(fecha, nomDiscoteca, eventoFinal);
          cout << "Fiesta introducida correctamente en La Base De Datos\n";

        } else {
          cout << "Formato de fecha incorrecto\nOperacion cancelada\n";
        }
        
      } else if (existeFecha == 0) {
        cout << "\nLa fecha introducida ya esta ocupada\nOperacion cancelada\n";
      } else {
        cout << "\nNombre de la discoteca incorrecto\nOperacion cancelada\n";
      }

      break;

    case '3':
      cout << "\n---------------------------------------------------\n";
      cout << "Aniadir evento:\n";

      nomDiscoteca = introducirNombreDiscoteca();
      len = strcspn(nomDiscoteca, "\n");
      nomDiscoteca[len] = '\0';

      fecha = introducirFecha();
      len = strcspn(fecha, "\n");
      fecha[len] = '\0';

      descripcionEvento = introducirDescripcion();
      len = strcspn(descripcionEvento, "\n");
      descripcionEvento[len] = '\0';

      evento = "Si";

      nomDiscoteca[0] = toupper(nomDiscoteca[0]);
      for (int i = 1; nomDiscoteca[i] != '\0'; i++) {
        nomDiscoteca[i] = tolower(nomDiscoteca[i]);
      }

      existeFecha = comprobarFecha(fecha, 0);

      if (((strcmp(nomDiscoteca, "Back") == 0) || (strcmp(nomDiscoteca, "Stage") == 0)) && (existeFecha == -1)) {
        int verificacionFecha = 0;
        verificacionFecha = verificarFecha(fecha);

        if (verificacionFecha) {
          char* eventoFinal = NULL;
          strcpy(eventoFinal, evento);
          insertarDiaFiesta(fecha, nomDiscoteca, eventoFinal);
          insertarEvento(fecha, nomDiscoteca, descripcionEvento);
          printf("Evento introducido correctamente en La Base De Datos\n");

        } else {
          printf("Formato de fecha incorrecto\nOperacion cancelada");
        }

      } else if (existeFecha == 0) {
        printf("\nLa fecha introducida ya esta ocupada\nOperacion cancelada\n");
      } else {
        printf("\nNombre de la discoteca incorrecto\nOperacion cancelada\n");
      }

      break;

    case '4':
      printf("\n---------------------------------------------------\n");
      printf("Importar RRPPs\n\n");

      abrirConexion();
      inicializarRRPP();
      mostrarRRPP();

      printf("\nEstos son los RRPPs importados\n");

      break;

    case '5':
      printf("\n---------------------------------------------------\n");
      printf("Importar DJs\n\n");

      abrirConexion();
      inicializarDJ();
      mostrarDJ();

      printf("\nEstos son los DJs importados\n");

      break;
    }

  } while (opcionMenu != '0');

  return 0;
}