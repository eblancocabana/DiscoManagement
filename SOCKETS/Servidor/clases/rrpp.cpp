#include "rrpp.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

RRPP::RRPP() {
    this->codigo_rrpp = 0;
    this->nombre = NULL;
    this->zona_recogida = NULL;
    this->hora_recogida = NULL;
    this->numero_contacto = NULL;
}

RRPP::RRPP(int codigo_rrpp, char* nombre, char* zona_recogida, char* hora_recogida, char* numero_contacto) {
    this->codigo_rrpp = codigo_rrpp;
    this->nombre = new char[strlen(nombre) + 1];
    strcpy(this->nombre, nombre);
    this->zona_recogida = new char[strlen(zona_recogida) + 1];
    strcpy(this->zona_recogida, zona_recogida);
    this->hora_recogida = new char[strlen(hora_recogida) + 1];
    strcpy(this->hora_recogida, hora_recogida);
    this->numero_contacto = new char[strlen(numero_contacto) + 1];
    strcpy(this->numero_contacto, numero_contacto);
}

RRPP::RRPP(const RRPP &rrpp) {
    this->codigo_rrpp = rrpp.codigo_rrpp;
    this->nombre = new char[strlen(rrpp.nombre) + 1];
    strcpy(this->nombre, rrpp.nombre);
    this->zona_recogida = new char[strlen(rrpp.zona_recogida) + 1];
    strcpy(this->zona_recogida, rrpp.zona_recogida);
    this->hora_recogida = new char[strlen(rrpp.hora_recogida) + 1];
    strcpy(this->hora_recogida, rrpp.hora_recogida);
    this->numero_contacto = new char[strlen(rrpp.numero_contacto) + 1];
    strcpy(this->numero_contacto, rrpp.numero_contacto);
}

RRPP::~RRPP() {
    delete[] this->nombre;
    delete[] this->zona_recogida;
    delete[] this->hora_recogida;
    delete[] this->numero_contacto;
}

int RRPP::getCodigoRRPP() {
    return this->codigo_rrpp;
}

void RRPP::setCodigoRRPP(int codigo_rrpp) {
    this->codigo_rrpp = codigo_rrpp;
}

char* RRPP::getNombre() {
    return this->nombre;
}

void RRPP::setNombre(char* nombre) {
    this->nombre = new char[strlen(nombre) + 1];
    strcpy(this->nombre, nombre);
}

char* RRPP::getZonaRecogida() {
    return this->zona_recogida;
}

void RRPP::setZonaRecogida(char* zona_recogida) {
    this->zona_recogida = new char[strlen(zona_recogida) + 1];
    strcpy(this->zona_recogida, zona_recogida);
}

char* RRPP::getHoraRecogida() {
    return this->hora_recogida;
}

void RRPP::setHoraRecogida(char* hora_recogida) {
    this->hora_recogida = new char[strlen(hora_recogida) + 1];
    strcpy(this->hora_recogida, hora_recogida);
}

char* RRPP::getNumeroContacto() {
    return this->numero_contacto;
}

void RRPP::setNumeroContacto(char* numero_contacto) {
    this->numero_contacto = new char[strlen(numero_contacto) + 1];
    strcpy(this->numero_contacto, numero_contacto);
}


void RRPP::printRRPP() {
    cout << "RRPP(" << this->codigo_rrpp << ") " << this->nombre << " - Recogida: " << this->zona_recogida << ", " << this->hora_recogida << " - tlfn: " << this->numero_contacto << endl;
}


