#include "reservalocal.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

ReservaLocal::ReservaLocal() {
    this->codigo = NULL;
    this->fecha = NULL;
    this->nombreDiscoteca = NULL;
    this->aforo = 0;
    this->numeroTarjeta = NULL;
    this->cvvTarjeta = NULL;
    this->caducidadTarjeta = NULL;
}

ReservaLocal::ReservaLocal(char* codigo, char* fecha, char* nombreDiscoteca, int aforo, char* numeroTarjeta, char* cvvTarjeta, char* caducidadTarjeta) {
    this->codigo = new char[strlen(codigo)+1];
    strcpy(this->codigo, codigo);
    this->fecha = new char[strlen(fecha) + 1];
    strcpy(this->fecha, fecha);
    this->nombreDiscoteca = new char[strlen(nombreDiscoteca) + 1];
    strcpy(this->nombreDiscoteca, nombreDiscoteca);
    this->aforo = aforo;
    this->numeroTarjeta = new char[strlen(numeroTarjeta) + 1];
    strcpy(this->numeroTarjeta, numeroTarjeta);
    this->cvvTarjeta = new char[strlen(cvvTarjeta) + 1];
    strcpy(this->cvvTarjeta, cvvTarjeta);
    this->caducidadTarjeta = new char[strlen(caducidadTarjeta) + 1];
    strcpy(this->caducidadTarjeta, caducidadTarjeta);
}

ReservaLocal::ReservaLocal(const ReservaLocal &reservaLocal) {
    this->codigo = new char[strlen(reservaLocal.codigo)+1];
    strcpy(this->codigo, reservaLocal.codigo);
    this->fecha = new char[strlen(reservaLocal.fecha) + 1];
    strcpy(this->fecha, reservaLocal.fecha);
    this->nombreDiscoteca = new char[strlen(reservaLocal.nombreDiscoteca) + 1];
    strcpy(this->nombreDiscoteca, reservaLocal.nombreDiscoteca);
    this->aforo = reservaLocal.aforo;
    this->numeroTarjeta = new char[strlen(reservaLocal.numeroTarjeta) + 1];
    strcpy(this->numeroTarjeta, reservaLocal.numeroTarjeta);
    this->cvvTarjeta = new char[strlen(reservaLocal.cvvTarjeta) + 1];
    strcpy(this->cvvTarjeta, reservaLocal.cvvTarjeta);
    this->caducidadTarjeta = new char[strlen(reservaLocal.caducidadTarjeta) + 1];
    strcpy(this->caducidadTarjeta, reservaLocal.caducidadTarjeta);
}

ReservaLocal::~ReservaLocal() {
    delete[] this->fecha;
    delete[] this->nombreDiscoteca;
    delete[] this->numeroTarjeta;
    delete[] this->cvvTarjeta;
    delete[] this->caducidadTarjeta;
}

char* ReservaLocal::getCodigo() {
    return this->codigo;
}

void ReservaLocal::setCodigo(char* codigo){
    this->codigo = new char[strlen(codigo)+1];
    strcpy(this->codigo, codigo);
}

char* ReservaLocal::getFecha() {
    return this->fecha;
}

void ReservaLocal::setFecha(char* fecha) {
    this->fecha = new char[strlen(fecha)+1];
    strcpy(this->fecha, fecha);
}

char* ReservaLocal::getNombreDiscoteca() {
    return this->nombreDiscoteca;
}

void ReservaLocal::setNombreDiscoteca(char* nombreDiscoteca) {
    this->nombreDiscoteca = new char[strlen(nombreDiscoteca)+1];
    strcpy(this->nombreDiscoteca, nombreDiscoteca);
}

int ReservaLocal::getAforo() {
    return this->aforo;
}

void ReservaLocal::setAforo(int aforo) {
    this->aforo = aforo;
}

char* ReservaLocal::getNumeroTarjeta() {
    return this->numeroTarjeta;
}

void ReservaLocal::setNumeroTarjeta(char* numeroTarjeta) {
    this->numeroTarjeta = new char[strlen(numeroTarjeta)+1];
    strcpy(this->numeroTarjeta, numeroTarjeta);
}

char* ReservaLocal::getCvvTarjeta() {
    return this->cvvTarjeta;
}

void ReservaLocal::setCvvTarjeta(char* cvvTarjeta) {
    this->cvvTarjeta = new char[strlen(cvvTarjeta)+1];
    strcpy(this->cvvTarjeta, cvvTarjeta);
}

char* ReservaLocal::getCaducidadTarjeta() {
    return this->caducidadTarjeta;
}

void ReservaLocal::setCaducidadTarjeta(char* caducidadTarjeta) {
    this->caducidadTarjeta = new char[strlen(caducidadTarjeta)+1];
    strcpy(this->caducidadTarjeta, caducidadTarjeta);
}

void ReservaLocal::printReservaLocal() {
    cout << "Reserva Local(" << this->codigo << ") - Discoteca: " << this->nombreDiscoteca << " - Fecha: " << this->fecha << " - Aforo: " << this->aforo << endl;
}
