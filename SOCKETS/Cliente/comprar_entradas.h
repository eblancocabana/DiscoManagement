#ifndef COMPRAR_ENTRADAS_H
#define COMPRAR_ENTRADAS_H

void datosCompra(int codFecha, int tipoEntrada, double precio);

int introducirNumEntradas();
char* introducirNombreCompleto();
char* introducirGmail();

void pagarEntrada();
char mostrarPagarEntrada();

char* introducirNumTarjeta();
char* introducirCaducidadTarjeta();
char* introducirCVVTarjeta();

void confirmarPago();
char mostrarConfirmarPago();

int introducirCodigoRRPP();

void confirmarCompra();
char confirmarPagoCompra();


#endif