//CRISTHIAN ANTONIO AGUILAR VAZQUEZ 202333839
//ROBERTO NOE HERNANDEZ ROMERO 202328123
//ANGEL HERNANDEZ GONZALEZ 202327868

#ifndef GRAFO_H
#define GRAFO_H

#include "Adyacentes.h"
#include "Aristas.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;
class Grafo {
private:
    Adyacentes *cabeza;
    int num_vertices=0;
    int num_aristas=0;//ALMACENA EL NUMERO DE ARISTAS
    vector<vector<int>> matriz;//ALMACENA LA MATRIZ DE ADYACENCIA
    vector<string> vertices;
    vector<vector<int>> matriz_cuadratica;
    vector<vector<int>> matriz_cubica;
    vector<Aristas> lista_aristas;//VECTOR DE OBJETOS DE TIPO ARISTAS SE USAN PARA KRUSKAL

public:
    Grafo();
    ~Grafo();
    void Menu_CrearMatriz();//MENU PARA AGREGAR NODOS Y ARISTAS O ELIMINARLOS
    void Insertar_Vertice(string);//SE AGREGA UN NODO
    void Insertar_Arista(string, string,int);//SE AGREGA UNA ARISTA
    void Insertar_Adyacencia_Ordenada(Adyacentes*& cabeza, const string& nombre, int peso) ;

    void Eliminar_Vertice(string);
    void Eliminar_Arista(string, string);
    void Mostrar_Grafo();//MUESTRA LAS LISTAS DE ADYACENCIA DE CADA NODO
    void Mostrar_Matriz();//MUESTRA LA MATRIZ DE ADYACENCIA
    void Mostrar_Nodos();//MUESTRA TODOS LOS NODOS ALMACENADOS
    void Cardinalidad();//MUESTRA EL NUMERO DE VERTICES Y ARISTAS
    void Adyacente();//VERIFICA SI DOS NODOS SON ADYACENTES
    void Matriz_Cuadratica();
    vector<vector<int>> get_Matriz_Cuadratica();
    void Matriz_Cubica();
    vector<vector<int>> get_Matriz_Cubica();
    void Mostrar_Matriz_Operada(vector<vector<int>> matriz);
    void Recorrido_Ancho();//RECORRIDO POR AMPLITUD
    void Recorrido_Profundidad();//RECORRIDO POR PROFUNDIDAD
    void Menu_Recorridos();//MENU PARA ELEGIR EL TIPO DE RECORRIDO
    string Buscar(unordered_map<string, string> &, string);//FUNCION PARA BUSCAR EL PADRE DE UN NODO
    void Unir(unordered_map<string, string> &,  string, string);//FUNCION PARA UNIR DOS NODOS
    //ALGORITMOS DE ARBOLES DE EXPANSION MINIMA
    void Kruskal();
    void PRIM();
    void Menu_Dijkstra();
    void Dijkstra_Inicio();//ALGORITMO DE DIJKSTRA PERO SOLO DE UN NODO INICIAL HACIA LOS DEMAS NODOS
    // Declaración de la sobrecarga del operador <
    void Dijkstra_Inicio_Final();//ALGORITMO DE DIJKSTRA DE UN NODO INICIAL A UN NODO FINAL
    void Cambio_Pantalla();
    int Validar_Entrada();
};

#endif //GRAFO_H