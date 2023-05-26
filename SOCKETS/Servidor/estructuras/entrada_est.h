#ifndef ENTRADA_EST_H
#define ENTRADA_EST_H

typedef struct {
    int codigoFecha;
    char* fechaEntrada;
    char* nombreDiscoteca;
    int numeroEntradas;
    char* cuentaGmail;
    char* numeroTarjetaCredito;
    char* cvvTarjeta;
    char* caducidadTarjeta;
    char* tipoEntrada;
    double precio;
    char* usuario;

} EntradaEst;

#endif