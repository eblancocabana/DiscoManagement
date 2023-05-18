#include <stdio.h>
#include <locale.h>
#include "inicio.h"
#include "basedatos/baseDatos.h"
 
//PARA EJECUTAR ESTO:

// gcc main.c inicio.c reservar_local.c comprar_entradas.c seleccion_entradas.c basedatos/baseDatos.c basedatos/sqlite/sqlite3.c servidor/inicio_servidor.c -o salida.exe

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");

    printf("\n\n\n\n");
    printf("\e[34m\e[1m");
    printf("********************************\n");
    printf("*                              *\n");
    printf("*   SOUND STRATEGY PARTNERS    *\n");
    printf("*                              *\n");
    printf("********************************\n");
    printf("\e[0m");
    printf("\n"); 

    inicializacion();
    login();

    return 0;
}