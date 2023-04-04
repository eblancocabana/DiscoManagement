#ifndef _INICIO_
#define _INICIO_

char mostrarLogin();
char mostrarRegistrarse();
char mostrarMenu();

char iniciarSesion();
int login();

int registrarse();
char rellenarCamposRegistro();

int menu();
void clearIfNeeded(char *str, int max_line);

#endif