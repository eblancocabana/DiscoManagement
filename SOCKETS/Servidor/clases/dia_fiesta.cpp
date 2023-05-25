#include "dia_fiesta.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

DiasFiesta::DiasFiesta() {
    this->codigo_fecha = 0;
    this->fecha = NULL;
    this->nombre_discoteca = NULL;
    this->entradas_disponibles = 0;
    this->evento_especial = NULL;
}

DiasFiesta::DiasFiesta(int codigo_fecha, char* fecha, char* nombre_discoteca, int entradas_disponibles, char* evento_especial) {
    this->codigo_fecha = codigo_fecha;
    this->fecha = new char[strlen(fecha) + 1];
    strcpy(this->fecha, fecha);
    this->nombre_discoteca = new char[strlen(nombre_discoteca) + 1];
    strcpy(this->nombre_discoteca, nombre_discoteca);
    this->entradas_disponibles = entradas_disponibles;
    this->evento_especial = new char[strlen(evento_especial) + 1];
    strcpy(this->evento_especial, evento_especial);
}

DiasFiesta::DiasFiesta(const DiasFiesta &diasfiesta) {
    this->codigo_fecha = diasfiesta.codigo_fecha;
    this->fecha = new char[strlen(diasfiesta.fecha) + 1];
    strcpy(this->fecha, diasfiesta.fecha);
    this->nombre_discoteca = new char[strlen(diasfiesta.nombre_discoteca) + 1];
    strcpy(this->nombre_discoteca, diasfiesta.nombre_discoteca);
    this->entradas_disponibles = diasfiesta.entradas_disponibles;
    this->evento_especial = new char[strlen(diasfiesta.evento_especial) + 1];
    strcpy(this->evento_especial, diasfiesta.evento_especial);
}

DiasFiesta::~DiasFiesta() {
    delete[] this->fecha;
    delete[] this->nombre_discoteca;
    delete[] this->evento_especial;
}

int DiasFiesta::getCodigoFecha() {
    return this->codigo_fecha;
}

void DiasFiesta::setCodigoFecha(int codigo_fecha) {
    this->codigo_fecha = codigo_fecha;
}

char* DiasFiesta::getFecha() {
    return this->fecha;
}

void DiasFiesta::setFecha(char* fecha) {
    this->fecha = new char[strlen(fecha) + 1];
    strcpy(this->fecha, fecha);
}

char* DiasFiesta::getNombreDiscoteca() {
    return this->nombre_discoteca;
}

void DiasFiesta::setNombreDiscoteca(char* nombre_discoteca) {
    this->nombre_discoteca = new char[strlen(nombre_discoteca) + 1];
    strcpy(this->nombre_discoteca, nombre_discoteca);
}

int DiasFiesta::getEntradasDisponibles() {
    return this->entradas_disponibles;
}

void DiasFiesta::setEntradasDisponibles(int entradas_disponibles) {
    this->entradas_disponibles = entradas_disponibles;
}

char* DiasFiesta::getEventoEspecial() {
    return this->evento_especial;
}

void DiasFiesta::setEventoEspecial(char* evento_especial) {
    this->evento_especial = new char[strlen(evento_especial) + 1];
    strcpy(this->evento_especial, evento_especial);
}


void DiasFiesta::printDiasFiesta() {
    cout << "Dia de Fiesta(" << this->codigo_fecha << ") " << " - Fecha: " << this->fecha << " - Discoteca: " << this->nombre_discoteca << " - Entradas disponibles: " << this->entradas_disponibles << " - Evento: " << this->evento_especial << endl;
}

