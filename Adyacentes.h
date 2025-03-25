//CRISTHIAN ANTONIO AGUILAR VAZQUEZ 202333839
//ROBERTO NOE HERNANDEZ ROMERO 202328123
//ANGEL HERNANDEZ GONZALEZ 202327868

#ifndef ADYACENTES_H
#define ADYACENTES_H
#include <string>
    using namespace std;

class Adyacentes {
    private:
        string nombre_adyacente;//NOMBRE DEL NODO ADYACENTE
        int peso;//PESO ENTRE NODO Y NODOS ADYACENTES
        Adyacentes *vertice;//APUNTADOR A LOS NODOS ADYACENTES
        Adyacentes *siguiente;//APUNTADOR AL SIGUIENTE NODO
    public:
        Adyacentes(string nombre_adyacente);
        ~Adyacentes();
        void set_Nombre_Adyacente(string nombre_adyacente);
        string get_Nombre_Adyacente();
        void set_Vertice(Adyacentes *vertice);

        Adyacentes *&get_Vertice();
        void set_Siguiente(Adyacentes *siguiente);
        Adyacentes *get_Siguiente();
        void set_Peso(int peso);
        int get_Peso();
    };
#endif //ADYACENTES_H