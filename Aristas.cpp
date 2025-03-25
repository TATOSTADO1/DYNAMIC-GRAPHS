//CRISTHIAN ANTONIO AGUILAR VAZQUEZ 202333839
//ROBERTO NOE HERNANDEZ ROMERO 202328123
//ANGEL HERNANDEZ GONZALEZ 202327868

#include "Aristas.h"
#include <string>

using namespace std;

Aristas::Aristas(string origen, string destino, int peso) {
    this->origen = origen;
    this->destino = destino;
    this->peso = peso;
}

void Aristas::set_Origen(string origen) {
    this->origen = origen;
}

string Aristas::get_Origen() {
    return this->origen;
}

void Aristas::set_Destino(string destino) {
    this->destino = destino;
}

string Aristas::get_Destino() {
    return this->destino;
}

void Aristas::set_Peso(int peso) {
    this->peso = peso;
}

int Aristas::get_Peso() {
    return this->peso;
}

bool Aristas::operator<(const Aristas& arista) {
    return peso < arista.peso;
}
