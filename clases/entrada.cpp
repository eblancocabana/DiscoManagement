#include "entrada.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

Entrada::Entrada() {
    this->codigoFecha = 0;
    this->fechaEntrada = NULL;
    this->nombreDiscoteca = NULL;
    this->numeroEntradas = 0;
    this->cuentaGmail = NULL;
    this->numeroTarjetaCredito = NULL;
    this->cvvTarjeta = NULL;
    this->caducidadTarjeta = NULL;
    this->tipoEntrada = NULL;
    this->precio = 0;
    this->usuario = NULL;
}

Entrada::Entrada(int codigoFecha, char* fechaEntrada, char* nombreDiscoteca, int numeroEntradas, char* cuentaGmail, char* numeroTarjetaCredito, char* cvvTarjeta, char* caducidadTarjeta, char* tipoEntrada, double precio, char* usuario) {
    this->codigoFecha = codigoFecha;
    this->fechaEntrada = new char[strlen(fechaEntrada) + 1];
    strcpy(this->fechaEntrada, fechaEntrada);
    this->nombreDiscoteca = new char[strlen(nombreDiscoteca) + 1];
    strcpy(this->nombreDiscoteca, nombreDiscoteca);
    this->numeroEntradas = numeroEntradas;
    this->cuentaGmail = new char[strlen(cuentaGmail) + 1];
    strcpy(this->cuentaGmail, cuentaGmail);
    this->numeroTarjetaCredito = new char[strlen(numeroTarjetaCredito) + 1];
    strcpy(this->numeroTarjetaCredito, numeroTarjetaCredito);
    this->cvvTarjeta = new char[strlen(cvvTarjeta) + 1];
    strcpy(this->cvvTarjeta, cvvTarjeta);
    this->caducidadTarjeta = new char[strlen(caducidadTarjeta) + 1];
    strcpy(this->caducidadTarjeta, caducidadTarjeta);
    this->tipoEntrada = new char[strlen(tipoEntrada) + 1];
    strcpy(this->tipoEntrada, tipoEntrada);
    this->precio = precio;
    this->usuario = new char[strlen(usuario) + 1];
    strcpy(this->usuario, usuario);
}

Entrada::Entrada(const Entrada &entrada) {
    this->codigoFecha = entrada.codigoFecha;
    this->fechaEntrada = new char[strlen(entrada.fechaEntrada) + 1];
    strcpy(this->fechaEntrada, entrada.fechaEntrada);
    this->nombreDiscoteca = new char[strlen(entrada.nombreDiscoteca) + 1];
    strcpy(this->nombreDiscoteca, entrada.nombreDiscoteca);
    this->numeroEntradas = entrada.numeroEntradas;
    this->cuentaGmail = new char[strlen(entrada.cuentaGmail) + 1];
    strcpy(this->cuentaGmail, entrada.cuentaGmail);
    this->numeroTarjetaCredito = new char[strlen(entrada.numeroTarjetaCredito) + 1];
    strcpy(this->numeroTarjetaCredito, entrada.numeroTarjetaCredito);
    this->cvvTarjeta = new char[strlen(entrada.cvvTarjeta) + 1];
    strcpy(this->cvvTarjeta, entrada.cvvTarjeta);
    this->caducidadTarjeta = new char[strlen(entrada.caducidadTarjeta) + 1];
    strcpy(this->caducidadTarjeta, entrada.caducidadTarjeta);
    this->tipoEntrada = new char[strlen(entrada.tipoEntrada) + 1];
    strcpy(this->tipoEntrada, entrada.tipoEntrada);
    this->precio = entrada.precio;
    this->usuario = new char[strlen(entrada.usuario) + 1];
    strcpy(this->usuario, entrada.usuario);
}

Entrada::~Entrada() {
    delete[] this->fechaEntrada;
    delete[] this->nombreDiscoteca;
    delete[] this->cuentaGmail;
    delete[] this->numeroTarjetaCredito;
    delete[] this->cvvTarjeta;
    delete[] this->caducidadTarjeta;
    delete[] this->tipoEntrada;
    delete[] this->usuario;
}


int Entrada::getCodigoFecha() {
    return this->codigoFecha;
}

void Entrada::setCodigoFecha(int codigoFecha){
    this->codigoFecha = codigoFecha;
}

char* Entrada::getFechaEntrada() {
    return this->fechaEntrada;
}

void Entrada::setFechaEntrada(char* fechaEntrada) {
    this->fechaEntrada = fechaEntrada;
}

char* Entrada::getNombreDiscoteca() {
    return this->nombreDiscoteca;
}

void Entrada::setNombreDiscoteca(char* nombreDiscoteca) {
    this->nombreDiscoteca = nombreDiscoteca;
}

int Entrada::getNumeroEntradas() {
    return this->numeroEntradas;
}

void Entrada::setNumeroEntradas(int numeroEntradas) {
    this->numeroEntradas = numeroEntradas;
}

char* Entrada::getCuentaGmail() {
    return this->cuentaGmail;
}

void Entrada::setCuentaGmail(char* cuentaGmail) {
    this->cuentaGmail = cuentaGmail;
}

char* Entrada::getNumeroTarjetaCredito() {
    return this->numeroTarjetaCredito;
}

void Entrada::setNumeroTarjetaCredito(char* numeroTarjetaCredito) {
    this->numeroTarjetaCredito = numeroTarjetaCredito;
}

char* Entrada::getCvvTarjeta() {
    return this->cvvTarjeta;
}

void Entrada::setCvvTarjeta(char* cvvTarjeta) {
    this->cvvTarjeta = cvvTarjeta;
}

char* Entrada::getCaducidadTarjeta() {
    return this->caducidadTarjeta;
}

void Entrada::setCaducidadTarjeta(char* caducidadTarjeta) {
    this->caducidadTarjeta = caducidadTarjeta;
}

char* Entrada::getTipoEntrada() {
    return this->tipoEntrada;
}

void Entrada::setTipoEntrada(char* tipoEntrada) {
    this->tipoEntrada = tipoEntrada;
}

double Entrada::getPrecio() {
    return this->precio;
}

void Entrada::setPrecio(double precio) {
    this->precio = precio;
}

char* Entrada::getUsuario() {
    return this->usuario;
}

void Entrada::setUsuario(char* usuario) {
    this->usuario = usuario;
}

void Entrada::printEntrada() {
    cout << "Entrada(" << this->codigoFecha << ") - Discoteca: " << this->nombreDiscoteca << " - Fecha: " << this->fechaEntrada << " - Tipo entrada: " << this->tipoEntrada << " - Numero entradas: " << this->numeroEntradas << " - Precio: " << this->precio << endl;
}


