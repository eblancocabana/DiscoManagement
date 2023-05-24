#include "Entrada.h"
#include <iostream>

using namespace std;

Entrada::Entrada() {
 this->codigoFecha = 0;
 this->fechaEntrada = "";
 this->nombreDiscoteca = "";
 this->numeroEntradas = 0;
 this->cuentaGmail = "";
 this->numeroTarjetaCredito = "";
 this->cvvTarjeta = "";
 this->caducidadTarjeta = "";
 this->tipoEntrada = "";
 this->precio = 0.0;
}

Entrada::Entrada(int codigoFecha, string fechaEntrada, string nombreDiscoteca, int numeroEntradas,
                 string cuentaGmail, string numeroTarjetaCredito, string cvvTarjeta,
                 string caducidadTarjeta, string tipoEntrada, double precio) {
 this->codigoFecha = codigoFecha;
 this->fechaEntrada = fechaEntrada;
 this->nombreDiscoteca = nombreDiscoteca;
 this->numeroEntradas = numeroEntradas;
 this->cuentaGmail = cuentaGmail;
 this->numeroTarjetaCredito = numeroTarjetaCredito;
 this->cvvTarjeta = cvvTarjeta;
 this->caducidadTarjeta = caducidadTarjeta;
 this->tipoEntrada = tipoEntrada;
 this->precio = precio;
}

