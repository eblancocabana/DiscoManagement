#include <stdio.h>

int main() {
    int opcion;
    printf("Bienvenido al menú\n");
    printf("1. Registrar\n");
    printf("2. Iniciar sesión\n");
    printf("Elija una opción: ");
    scanf("%d", &opcion);
    
    switch(opcion) {
        case 1:
            // Código para registrar
            char nombre[50];
            char nombreUsuario[50];
            char sexo;
            int edad;
            char correo[50];
            char contrasena[50];
            char repetirContrasena[50];
            
            printf("Nombre: ");
            scanf("%s", nombre);
            
            printf("Nombre de usuario: ");
            scanf("%s", nombreUsuario);
            
            printf("Sexo (M/F): ");
            scanf(" %c", &sexo);
            
            printf("Edad: ");
            scanf("%d", &edad);
            
            printf("Correo: ");
            scanf("%s", correo);
            
            printf("Contraseña: ");
            scanf("%s", contrasena);
            
            printf("Repetir contraseña: ");
            scanf("%s", repetirContrasena);
            
           // Aquí puedes agregar código para validar la información ingresada y guardarla en una base de datos o archivo
           
           break;
        case 2:
           // Código para iniciar sesión
           int opcionSesion;
           printf("\nInformación de eventos\n");
           printf("\nComprar entradas\n");
           printf("\nReservar local\n");
           printf("\nMis reservas\n");
           
           // Aquí puedes agregar código para manejar las opciones del menú después de iniciar sesión
           
           break;
        default:
          // Código para manejar una opción inválida
          break;
    }
    
    return 0;
}