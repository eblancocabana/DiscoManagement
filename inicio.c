#include <stdio.h>
#include "inicio.h"

#define MAX_SELECCION 5

char mostrarMenu() {
    char linea[MAX_SELECCION];
    int num;
    printf("\nMenu Principal: \n\t1. Informacion de eventos \n\t2. Comprar entradas \n\t3. Reservar local \n\t4. Mis reservas / compras \n\t0. Salir \n\n Elige una opcion: ");

    fgets(linea, MAX_SELECCION, stdin);
    sscanf(linea, "%d", &num);

    return *linea;
}

int menu() {
    char opcion;

    do {
        opcion = mostrarMenu();
        switch (opcion) {
            case '1': 
                printf("\n---------------------------------------------------\n");
                printf("Listado de eventos\n\n");
            break;
                
            case '2': 
                printf("\n---------------------------------------------------\n");
                printf("Menu de compra de entrada\n\n");
            break;

            case '3': 
                printf("\n---------------------------------------------------\n");
                printf("Reservar el local\n\n");
            break;

            case '4':
                printf("\n---------------------------------------------------\n"); 
                printf("Listado de mis reservas\n\n");
            break;
        }

    } while (opcion != '0');

    return 0;
}