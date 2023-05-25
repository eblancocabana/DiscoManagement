#include "dj.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;


Dj::Dj() {
    this->id_dj = 0;
    this->nombre_dj = NULL;
    this->genero_musical = NULL;
    this->fecha_nacimiento = NULL;
    this->numero_contacto = NULL;
}

Dj::Dj(int id_dj, char* nombre_dj, char* genero_musical, char* fecha_nacimiento, char* numero_contacto) {
    this->id_dj = id_dj;
    this->nombre_dj = new char[strlen(nombre_dj) + 1];
    strcpy(this->nombre_dj, nombre_dj);
    this->genero_musical = new char[strlen(genero_musical) + 1];
    strcpy(this->genero_musical, genero_musical);
    this->fecha_nacimiento = new char[strlen(fecha_nacimiento) + 1];
    strcpy(this->fecha_nacimiento, fecha_nacimiento);
    this->numero_contacto = new char[strlen(numero_contacto) + 1];
    strcpy(this->numero_contacto, numero_contacto);
}

Dj::Dj(const Dj &dj) {
    this->id_dj = dj.id_dj;
    this->nombre_dj = new char[strlen(dj.nombre_dj) + 1];
    strcpy(this->nombre_dj, dj.nombre_dj);
    this->genero_musical = new char[strlen(dj.genero_musical) + 1];
    strcpy(this->genero_musical, dj.genero_musical);
    this->fecha_nacimiento = new char[strlen(dj.fecha_nacimiento) + 1];
    strcpy(this->fecha_nacimiento, dj.fecha_nacimiento);
    this->numero_contacto = new char[strlen(dj.numero_contacto) + 1];
    strcpy(this->numero_contacto, dj.numero_contacto);
}

Dj::~Dj() {
    delete[] this->nombre_dj;
    delete[] this->genero_musical;
    delete[] this->fecha_nacimiento;
    delete[] this->numero_contacto;
}

int Dj::getID() {
    return this->id_dj;
}

void Dj::setID(int id) {
    this->id_dj = id;
}

char* Dj::getNombre() {
    return this->nombre_dj;
}

void Dj::setNombre(char* nombre) {
    this->nombre_dj = new char[strlen(nombre) + 1];
    strcpy(this->nombre_dj, nombre);
}

char* Dj::getGenero() {
    return this->genero_musical;
}

void Dj::setGenero(char* genero) {
    this->genero_musical = new char[strlen(genero) + 1];
    strcpy(this->genero_musical, genero);
}

char* Dj::getFecha() {
    return this->fecha_nacimiento;
}

void Dj::setFecha(char* fecha) {
    this->fecha_nacimiento = new char[strlen(fecha) + 1];
    strcpy(this->fecha_nacimiento, fecha);
}

char* Dj::getNumero() {
    return this->numero_contacto;
}

void Dj::setNumero(char* numero) {
    this->numero_contacto = new char[strlen(numero) + 1];
    strcpy(this->numero_contacto, numero);
}


void Dj::printDJ() {
    cout << "DJ(" << this->id_dj << ") " << this->nombre_dj << " [" << this->fecha_nacimiento << "] - Genero: " << this->genero_musical << " - tlfn: " << this->numero_contacto << endl;
}
