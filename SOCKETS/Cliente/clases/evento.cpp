#include "evento.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

Evento::Evento() {
    this->dia = NULL;
    this->descripcion = NULL;
    this->nombre_discoteca = NULL;
    this->aforo = 0;
}

Evento::Evento(char* dia, char* descripcion, char* nombre_discoteca, int aforo) {
    this->dia = new char[strlen(dia) + 1];
    strcpy(this->dia, dia);
    this->descripcion = new char[strlen(descripcion) + 1];
    strcpy(this->descripcion, descripcion);
    this->nombre_discoteca = new char[strlen(nombre_discoteca) + 1];
    strcpy(this->nombre_discoteca, nombre_discoteca);
    this->aforo = aforo;
}

Evento::Evento(const Evento &evento) {
    this->dia = new char[strlen(evento.dia) + 1];
    strcpy(this->dia, evento.dia);
    this->descripcion = new char[strlen(evento.descripcion) + 1];
    strcpy(this->descripcion, evento.descripcion);
    this->nombre_discoteca = new char[strlen(evento.nombre_discoteca) + 1];
    strcpy(this->nombre_discoteca, evento.nombre_discoteca);
    this->aforo = evento.aforo;
}

Evento::~Evento() {
    delete[] this->dia;
    delete[] this->descripcion;
    delete[] this->nombre_discoteca;
}

char* Evento::getDia() {
    return this->dia;
}

void Evento::setDia(char* dia) {
    this->dia = new char[strlen(dia) + 1];
    strcpy(this->dia, dia);
}

char* Evento::getDescripcion() {
    return this->descripcion;
}

void Evento::setDescripcion(char* descripcion) {
    this->descripcion = new char[strlen(descripcion) + 1];
    strcpy(this->descripcion, descripcion);
}

char* Evento::getNombreDiscoteca() {
    return this->nombre_discoteca;
}

void Evento::setNombreDiscoteca(char* nombre_discoteca) {
    this->nombre_discoteca = new char[strlen(nombre_discoteca) + 1];
    strcpy(this->nombre_discoteca, nombre_discoteca);
}

int Evento::getAforo() {
    return this->aforo;
}

void Evento::setAforo(int aforo) {
    this->aforo = aforo;
}


void Evento::printEvento() {
    cout << "Fecha: " << this->dia << " - Descripcion: " << this->descripcion << " - Discoteca: " << this->nombre_discoteca << " - Aforo: " << this->aforo << endl;
}