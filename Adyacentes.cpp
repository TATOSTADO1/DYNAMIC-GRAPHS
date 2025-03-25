//
// Created by Noé Hernández on 23/02/2025.
//

#include "Adyacentes.h"

Adyacentes::Adyacentes(string nombre_adyacente) {
    this->nombre_adyacente = nombre_adyacente;
    this->vertice = nullptr;
    this->siguiente = nullptr;
}

Adyacentes::~Adyacentes() {
    while (this->vertice != nullptr) {
        Adyacentes* temp = this->vertice;
        this->vertice = this->vertice->get_Siguiente();
        delete temp;
    }
    this->siguiente = nullptr;
}

void Adyacentes::set_Nombre_Adyacente(string nombre_adyacente) {
    this->nombre_adyacente = nombre_adyacente;
}

string Adyacentes::get_Nombre_Adyacente() {
    return this->nombre_adyacente;
}

void Adyacentes::set_Vertice(Adyacentes *vertice) {
    this->vertice = vertice;
}

Adyacentes *&Adyacentes::get_Vertice() {
    return this->vertice;
}

void Adyacentes::set_Siguiente(Adyacentes *siguiente) {
    this->siguiente = siguiente;
}

Adyacentes *Adyacentes::get_Siguiente() {
    return this->siguiente;
}

void Adyacentes::set_Peso(int peso) {
    this->peso = peso;
}

int Adyacentes::get_Peso() {
    return this->peso;
}