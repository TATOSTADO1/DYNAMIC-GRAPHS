//CRISTHIAN ANTONIO AGUILAR VAZQUEZ 202333839
//ROBERTO NOE HERNANDEZ ROMERO 202328123
//ANGEL HERNANDEZ GONZALEZ 202327868

#ifndef ARISTAS_H
#define ARISTAS_H

#include <string>

using namespace std;

class Aristas {//CLASE ARISTAS
private:
    string origen;
    string destino;
    int peso;//PESO DE LA ARISTA
public:
    Aristas(string,string,int);
    void set_Origen(string origen);
    string get_Origen();
    void set_Destino(string destino);
    string get_Destino();
    void set_Peso(int peso);
    int get_Peso();
    bool operator<(const Aristas&);//SOBRECARGA DE OPERADOR < PARA ORDENAR LAS ARISTAS

};
#endif //ARISTAS_H