//CRISTHIAN ANTONIO AGUILAR VAZQUEZ 202333839
//ROBERTO NOE HERNANDEZ ROMERO 202328123
//ANGEL HERNANDEZ GONZALEZ 202327868

#include "Adyacentes.h"
#include "Grafo.h"
#include "Aristas.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <algorithm>
#include <climits>
#include <cstdlib>

using namespace std;
Grafo::Grafo() {
    this->cabeza = nullptr;
    this->num_vertices = 0;
    this->num_aristas = 0;
}

Grafo::~Grafo() {
    delete this->cabeza;
}

void Grafo::Menu_CrearMatriz() {
    string nombre, origen, destino;//SE DECLARAN LAS VARIABLES PARA ALMACENAR LOS NOMBRES DE LOS NODOS
    int op=0,p;
    while (op != 5) {
        Cambio_Pantalla();
        cout<<"Digite una opcion del menu"  << endl;
        cout << "1.- Crear Nodo" << endl;
        cout << "2.- Generar adyacencia" << endl;
        cout << "3.- Eliminar Nodo" << endl;
        cout << "4.- Eliminar adyacencia" << endl;
        cout << "5.- Regresar" << endl;
        op = Validar_Entrada();
        switch (op){
            case 1:
                cout<< "Nombre del vertice"<<endl;
            cin>>nombre;
            Insertar_Vertice(nombre);//SE SOLICITA EL NOMBRE DEL NODO Y SE LLAMA A LA FUNCION APRA CREAR EL VERTICE
            break;
            case 2:
                Mostrar_Nodos();
            cout<<"Nombre del vertice origen"<<endl;
            cin>>origen;
            cout<<"Nombre del vertice destino"<<endl;
            cin>>destino;
            cout<<"Peso"<<endl;//SE SOLICITA EL NOMBRE DE LOS NODOS Y EL PESO DE LA ARISTA

                p=Validar_Entrada();//SE VALIDA LA ENTRADA DEL PESO SEA NUMERICA
                Insertar_Arista(origen, destino, p);//SE LLAMA A LA FUNCION PARA CREAR LA ARISTA

            break;
            case 3:
                Mostrar_Nodos();//SE MUESTRA LOS NODOS PARA QUE EL USUARIO ELIJA CUAL ELIMINAR
            cout<<"Nombre del vertice"<<endl;
            cin>>nombre;
            Eliminar_Vertice(nombre);//SE LLAMA A LA FUNCION PARA ELIMINAR EL VERTICE
            break;
            case 4:
                Mostrar_Matriz();//SE MUESTRA LA MATRIZ PARA QUE EL USUARIO ELIJA LA ARISTA
            cout<<"Nombre del vertice origen"<<endl;
            cin>>origen;
            cout<<"Nombre del vertice destino"<<endl;
            cin>>destino;
            Eliminar_Arista(origen, destino);//SE LLAMA A LA FUNCION PARA ELIMINAR LA ARISTA
            break;
            case 5:
                cout<<"Regresando al menu principal"<<endl;
            break;
            default:
                cout<<"Opcion no valida"<<endl;
            break;
        }
        system("pause");
    }
}

void Grafo::Insertar_Vertice(string nombre) {
    Adyacentes* aux = cabeza;
    Adyacentes* anterior = nullptr;

    while (aux!= nullptr) {
        if (aux->get_Nombre_Adyacente() == nombre) {
            cout << "El nodo ya existe" << endl;
            return;
        }
        aux = aux->get_Siguiente();
    }

    //SE VERIFICA SI EL NOMBRE ES UN NUMERO
    bool esNumero = true;
    for (char c : nombre) {
        if (!isdigit(c)) {
            esNumero = false;
            break;
        }
    }
    aux = cabeza;
    while (aux != nullptr) {
        bool auxEsNumero = true;
        //SE VERIFICA SI EL NOMBRE DEL NODO ES UN NUMERO
        for (char c : aux->get_Nombre_Adyacente()) {
            if (!isdigit(c)) {
                auxEsNumero = false;
                break;
            }
        }
        //SE COMPARA EL NOMBRE DEL NODO A INSERTAR CON EL NOMBRE DEL NODO ACTUAL
        if ((esNumero && auxEsNumero && stoi(nombre) < stoi(aux->get_Nombre_Adyacente())) || (!esNumero && !auxEsNumero && nombre < aux->get_Nombre_Adyacente()) ||(esNumero && !auxEsNumero)) {
            break;
        }

        anterior = aux;
        aux = aux->get_Siguiente();
    }

    Adyacentes* nuevo = new Adyacentes(nombre);

    if (anterior == nullptr) {
        nuevo->set_Siguiente(cabeza);
        cabeza = nuevo;
    } else {
        nuevo->set_Siguiente(aux);
        anterior->set_Siguiente(nuevo);
    }

    num_vertices++;
}

void Grafo::Insertar_Arista(string origen, string destino, int peso) {
    Adyacentes* aux = cabeza;
    Adyacentes* origenNodo = nullptr;
    Adyacentes* destinoNodo = nullptr;

    while (aux != nullptr) {
        if (aux->get_Nombre_Adyacente() == origen) {
            origenNodo = aux;
        }
        if (aux->get_Nombre_Adyacente() == destino) {
            destinoNodo = aux;
        }
        aux = aux->get_Siguiente();
     }

    if (origenNodo == nullptr || destinoNodo == nullptr) {
        cout << "No se encontro el vertice origen o destino" << endl;
        return;
    }

    for (auto it = lista_aristas.begin(); it != lista_aristas.end(); ++it) {
        if ((it->get_Origen() == origen && it->get_Destino() == destino) || (it->get_Origen() == destino && it->get_Destino() == origen)) {
            cout << "La arista ya existe" << endl;
            return;
        }
    }

    Insertar_Adyacencia_Ordenada(origenNodo->get_Vertice(), destino, peso);
    Insertar_Adyacencia_Ordenada(destinoNodo->get_Vertice(), origen, peso);

    lista_aristas.push_back(Aristas(origen, destino, peso));
    num_aristas++;
}

void Grafo::Insertar_Adyacencia_Ordenada(Adyacentes *&cabeza, const string &nombre, int peso) {
    Adyacentes* nuevo = new Adyacentes(nombre);
    nuevo->set_Peso(peso);

    Adyacentes* actual = cabeza;
    Adyacentes* anterior = nullptr;

    bool esNumeroNuevo = true;
    for (char c : nombre) {
        if (!isdigit(c)) {
            esNumeroNuevo = false;
            break;
        }
    }

    while (actual != nullptr) {
        bool esNumeroNuevo = true;
        for (char c : actual->get_Nombre_Adyacente()) {
            if (!isdigit(c)) {
                esNumeroNuevo = false;
                break;
            }
        }
        bool esNumeroActual = isdigit(actual->get_Nombre_Adyacente()[0]);

        if ((esNumeroNuevo && esNumeroActual && stoi(nombre) < stoi(actual->get_Nombre_Adyacente())) || (!esNumeroNuevo && !esNumeroActual && nombre < actual->get_Nombre_Adyacente()) ||(esNumeroNuevo && !esNumeroActual)) {
            break;
        }
        anterior = actual;
        actual = actual->get_Vertice();
    }

    nuevo->set_Vertice(actual);
    if (anterior == nullptr) {
        cabeza = nuevo;
    } else {
        anterior->set_Vertice(nuevo);
    }
}

void Grafo::Eliminar_Vertice(string nombre) {
    Adyacentes* aux = cabeza;
    Adyacentes* anterior = nullptr;

    cout << "Eliminando el Nodo: " << nombre << endl;
    Mostrar_Nodos();

    while (aux != nullptr) {
        Adyacentes* ady = aux->get_Vertice();
        Adyacentes* antAdy = nullptr;

        while (ady != nullptr) {
            if (ady->get_Nombre_Adyacente() == nombre) {
                if (antAdy == nullptr) {
                    aux->set_Vertice(ady->get_Vertice());
                } else {
                    antAdy->set_Vertice(ady->get_Vertice());
                }

                delete ady;
                break;
            }
            antAdy = ady;
            ady = ady->get_Vertice();
        }
        aux = aux->get_Siguiente();
    }

    aux = cabeza;

    for (auto it = lista_aristas.begin(); it != lista_aristas.end();) {
        if (it->get_Origen() == nombre || it->get_Destino() == nombre) {
            it = lista_aristas.erase(it);
            num_aristas--;
        } else {
            ++it;
        }
    }

    while (aux != nullptr) {
        Adyacentes* temp = aux->get_Siguiente();

        if (aux->get_Nombre_Adyacente() == nombre) {

            if (anterior == nullptr) {
                cabeza = temp;
            } else {
                anterior->set_Siguiente(temp);
            }

            delete aux;
            num_vertices--;

            cout << "Nodo eliminado: " << nombre << endl;
            Mostrar_Nodos();
            return;
        }

        anterior = aux;
        aux = temp;
    }
    cout << "Vertice no encontrado: " << nombre << endl;
}


void Grafo::Eliminar_Arista(string origen, string destino) {
    Adyacentes* aux = cabeza;
    Adyacentes* anterior = nullptr;
    Adyacentes* origenNodo = nullptr;
    Adyacentes* destinoNodo = nullptr;

    while (aux!= nullptr) {
        if (aux->get_Nombre_Adyacente() == origen) {
            origenNodo = aux;
        }
        if (aux->get_Nombre_Adyacente() == destino) {
            destinoNodo = aux;
        }
        aux = aux->get_Siguiente();
    }

    if (origenNodo != nullptr && destinoNodo != nullptr) {

        Adyacentes* ady = origenNodo->get_Vertice();
        anterior = nullptr;
        while (ady != nullptr) {//SE RECORRE LA LISTA DE ADYACENCIA DEL NODO ORIGEN PARA ENCONTRAR LA ARISTA HACIA EL NODO DESTINO
            if (ady->get_Nombre_Adyacente() == destino) {
                if (anterior == nullptr) {
                    origenNodo->set_Vertice(ady->get_Vertice());//SI EL NODO ANTERIOR ES NULO SE ASIGNA EL SIGUIENTE COMO NUEVO VERTICE
                } else {
                    anterior->set_Vertice(ady->get_Vertice());//SI EL NODO ANTERIOR NO ES NULO SE ASIGNA EL SIGUIENTE COMO NUEVO VERTICE
                }
                delete ady;
                break;
            }
            anterior = ady;
            ady = ady->get_Vertice();
        }

        ady = destinoNodo->get_Vertice();
        anterior = nullptr;

        while (ady != nullptr) {//SE RECORRE LA LISTA DE ADYACENCIA DEL NODO DESTINO PARA ENCONTRAR LA ARISTA HACIA EL NODO ORIGEN
            if (ady->get_Nombre_Adyacente() == origen) {
                if (anterior == nullptr) {

                    destinoNodo->set_Vertice(ady->get_Vertice());
                } else {
                    anterior->set_Vertice(ady->get_Vertice());
                }
                delete ady;
                num_aristas--;
                break;
            }
            anterior = ady;
            ady = ady->get_Vertice();
        }
    }

    for (auto it = lista_aristas.begin(); it != lista_aristas.end(); ++it) {//SE RECORRE LA LISTA DE ARISTAS PARA ENCONTRAR LA ARISTA
        if (it->get_Origen() == origen && it->get_Destino() == destino || it->get_Origen() == destino && it->get_Destino() == origen) {
            lista_aristas.erase(it);//SI SE ENCUENTRA LA ARISTA SE ELIMINA
            return;
        }
    }
    cout << "No se encontro la arista" << endl;//SI NO SE ENCONTRO LA ARISTA SE MUESTRA EL MENSAJE
}

    void Grafo::Mostrar_Grafo() {
        Adyacentes* aux = cabeza;

        if(aux==nullptr){//SE VERIFICA QUE EXISTAN NODOS
            cout<<"No hay nodos"<<endl;
            return;
        }

        while (aux != nullptr) {//SE RECORRE LA LISTA DE NODOS
            cout << aux->get_Nombre_Adyacente() << " -> ";
            Adyacentes* ady = aux->get_Vertice();
            while (ady != nullptr) {//SE RECORRE LA LISTA DE ADYACENCIA DE CADA NODO
                cout << ady->get_Nombre_Adyacente() << " -> ";
                ady = ady->get_Vertice();
            }
            cout << "NULL" << endl;
            aux = aux->get_Siguiente();
        }
    }

    void Grafo::Mostrar_Matriz() {
        Adyacentes* aux = cabeza;
        matriz.clear();
        vertices.clear();
        matriz.resize(num_vertices, vector(num_vertices, 0));

        cout<<"Matriz de adyacencia"<<endl;
        if(aux==nullptr){//SE VERIFICA QUE EXISTAN NODOS
            cout<<"No hay nodos"<<endl;
            return;
        }

        while (aux != nullptr) {//SE RECORRE LA LISTA DE NODOS PARA OBTENER LOS NOMBRES DE LOS NODOS
            vertices.push_back(aux->get_Nombre_Adyacente());
            aux = aux->get_Siguiente();
        }
        aux = cabeza;
        for (int i = 0; i < num_vertices; i++) {//SE RECORRE LA LISTA DE NODOS PARA OBTENER LA MATRIZ DE ADYACENCIA
            Adyacentes* ady = aux->get_Vertice();
            while (ady != nullptr) {//SE RECORRE LA LISTA DE ADYACENCIA DE CADA NODO
                for (int j = 0; j < num_vertices; j++) {
                    if (vertices[j] == ady->get_Nombre_Adyacente()) {
                        matriz[i][j] = ady->get_Peso();//SE ASIGNA EL PESO DE LA ARISTA A LA MATRIZ
                    }
                }
                ady = ady->get_Vertice();
            }
            aux = aux->get_Siguiente();
        }
    
        cout << "\t";
        for (int i = 0; i <num_vertices; i++) {
            cout << vertices[i] << "\t";//SE MUESTRA EL NOMBRE DE LOS NODOS EN FILA
        }
        cout << endl;
    for (int i = 0; i <num_vertices; i++) {
            cout << vertices[i] << "\t";//SE MUESTRA EL NOMBRE DE LOS NODOS EN COLUMNA
        for (int j = 0; j <num_vertices; j++) {
                cout << matriz[i][j] << "\t";//SE MUESTRA LA MATRIZ DE ADYACENCIA
            }
            cout << endl;
        }
    }

void Grafo::Mostrar_Nodos() {
    Adyacentes* aux = cabeza;
    cout << "Nodos: ";
    while (aux != nullptr) {
            cout << aux->get_Nombre_Adyacente() << " ";
        aux = aux->get_Siguiente();
    }
    cout << endl;
}


    void Grafo::Cardinalidad() {
        cout << "Numero de vertices: " << num_vertices << endl;//SE MUESTRA EL NUMERO DE VERTICES
        cout << "Numero de aristas: " << num_aristas << endl;//SE MUESTRA EL NUMERO DE ARISTAS
    }

    void Grafo::Adyacente() {
        string origen, destino;
    Adyacentes* aux = cabeza;
    Adyacentes* origenNodo = nullptr;
    Adyacentes* destinoNodo = nullptr;
    if(aux==nullptr){
        cout<<"No hay nodos"<<endl;
        return;
    }
        cout << "Nombre del vertice origen" << endl;
        cin >> origen;
        cout << "Nombre del vertice destino" << endl;
        cin >> destino;

        while (aux != nullptr) {//SE RECORRE LA LISTA DE NODOS PARA ENCONTRAR EL NODO ORIGEN Y DESTINO
            if (aux->get_Nombre_Adyacente() == origen) {
                origenNodo = aux;
            }
            if (aux->get_Nombre_Adyacente() == destino) {
                destinoNodo = aux;
            }
            aux = aux->get_Siguiente();
        }

        if(origenNodo==nullptr || destinoNodo==nullptr){//SI NO SE ENCUENTRA EL NODO ORIGEN O DESTINO SE MUESTRA EL MENSAJE Y SE REGRESA
            cout<<"No se encontro el vertice origen o destino"<<endl;
            return;
        }

        if (origenNodo != nullptr && destinoNodo != nullptr) {//SI SE ENCUENTRA EL NODO ORIGEN Y DESTINO SE RECORRE LA LISTA DE ADYACENCIA DEL NODO ORIGEN PARA VERIFICAR SI SON ADYACENTES
            Adyacentes* ady = origenNodo->get_Vertice();
            while (ady != nullptr) {//SE RECORRE LA LISTA DE ADYACENCIA
                if (ady->get_Nombre_Adyacente() == destino) {//SI ENTRE LOS ADYACENTES AL NODO ESTA EL VERTICE DESTINO SE MUESTRA EL MENSAJE
                    cout << "Si son adyacentes" << endl;
                    return;
                }
                ady = ady->get_Vertice();
            }
        }
        cout << "No son adyacentes" << endl;
    }

    void Grafo::Matriz_Cuadratica() {
        matriz_cuadratica.clear();
        Adyacentes* aux = cabeza;
        matriz.resize(num_vertices, vector<int>(num_vertices, 0));

        if(aux==nullptr){
            cout<<"No hay nodos"<<endl;
            return;
        }

        while (aux != nullptr) {
            vertices.push_back(aux->get_Nombre_Adyacente());
            aux = aux->get_Siguiente();
        }

        aux = cabeza;
        for (int i = 0; i < num_vertices; i++) {
            Adyacentes* ady = aux->get_Vertice();
            while (ady != nullptr) {
                for (int j = 0; j < num_vertices; j++) {
                    if (vertices[j] == ady->get_Nombre_Adyacente()) {
                        matriz[i][j] = ady->get_Peso();//SE ASIGNA EL PESO DE LA ARISTA A LA MATRIZ
                    }
                }
                ady = ady->get_Vertice();
            }
            aux = aux->get_Siguiente();
        }

       matriz_cuadratica.resize(num_vertices, vector<int>(num_vertices, 0));
        for (int i = 0; i < num_vertices; i++) {
            for (int j = 0; j < num_vertices; j++) {
                for (int k = 0; k < num_vertices; k++) {
                    matriz_cuadratica[i][j] += matriz[i][k] * matriz[k][j];//SE MULTIPLICA LA MATRIZ POR SI MISMA
                }
            }
        }
    }

    vector<vector<int>> Grafo::get_Matriz_Cuadratica() {
        return matriz_cuadratica;
    }

void Grafo::Matriz_Cubica() {
    matriz_cubica.clear();
    Matriz_Cuadratica();
    matriz_cubica.resize(num_vertices, vector<int>(num_vertices, 0));
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            for (int k = 0; k < num_vertices; k++) {
                matriz_cubica[i][j] += matriz_cuadratica[i][k] * matriz[k][j];//SE MULTIPLICA LA MATRIZ CUADRATICA POR LA MATRIZ ORIGINAL
            }
        }
    }
}

vector<vector<int>> Grafo::get_Matriz_Cubica() {
    return matriz_cubica;
}

void Grafo::Mostrar_Matriz_Operada(vector<vector<int>> matriz) {

    cout << "\t";
    for (int i = 0; i <num_vertices; i++) {
        cout << vertices[i] << "\t";
    }
    cout << endl;
        for (int i = 0; i <num_vertices; i++) {//SE MUESTRA EL NOMBRE DE LOS NODOS
        cout << vertices[i] << "\t";
            for (int j = 0; j <num_vertices; j++) {//SE MUESTRA LA MATRIZ
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
}

void Grafo::Menu_Recorridos() {//MENU PARA ELEGIR EL TIPO DE RECORRIDO
    Adyacentes *aux = cabeza;
    if (aux==nullptr){
        cout<<"No hay nodos"<<endl;
        system("pause");
        return;
    }
    int op=0;
    while (op != 6) {
        Cambio_Pantalla();
        cout << "1.- Recorrido a lo ancho" << endl;
        cout << "2.- Recorrido a lo profundo" << endl;
        cout << "3.- Arbol Kruskal" << endl;
        cout << "4.- Arbol PRIM" << endl;
        cout<< "5.- Dijkstra"<<endl;
        cout << "6.- Regresar" << endl;
        op = Validar_Entrada();
        switch (op){
            case 1:
                Recorrido_Ancho();
            break;
            case 2:
                Recorrido_Profundidad();
            break;
            case 3:
                Kruskal();
            break;
            case 4:
                PRIM();
            break;
            case 5:
                Menu_Dijkstra();
            continue;
            case 6:
                cout<<"Regresando al menu principal"<<endl;
            break;
            default:
                cout<<"Opcion no valida"<<endl;
            break;
        }
        system("pause");
    }
}

void Grafo::Recorrido_Ancho() {
    unordered_map<string, bool> visitados;
    vector<Adyacentes*> cola;
    Adyacentes* aux = cabeza;
    Adyacentes* origenNodo = nullptr;

    if(aux==nullptr){
        cout<<"No hay nodos"<<endl;
        return;
    }

    cout << "Seleccione el nodo origen: ";
    string origen;
    cin >> origen;

    while (aux != nullptr) {//SE RECORRE LA LISTA DE NODOS PARA ENCONTRAR EL NODO ORIGEN
        if (aux->get_Nombre_Adyacente() == origen) {
            origenNodo = aux;
            break;
        }
        aux = aux->get_Siguiente();
    }

    if (origenNodo == nullptr) {
        cout << "Nodo origen no encontrado" << endl;
        return;
    }
    visitados[origen] = true;
    cola.push_back(origenNodo);
    cout << "Recorrido en anchura: ";

    while (!cola.empty()) {//SE RECORRE LA LISTA DE NODOS
        Adyacentes* vertice = cola.front();//SE DIRECCIONA AL PRIMER NODO DE LA COLA
        cola.erase(cola.begin());//SE ELIMINA EL PRIMER NODO DE LA COLA

        cout << vertice->get_Nombre_Adyacente() << " -> ";//SE MUESTRA EL NOMBRE DEL NODO

        Adyacentes* ady = vertice->get_Vertice();//SE RECORRE LA LISTA DE ADYACENCIA DEL NODO PARA ENCONTRAR LOS NODOS ADYACENTES
        while (ady != nullptr) {
            string nombreAdy = ady->get_Nombre_Adyacente();//SE OBTIENE EL NOMBRE DEL NODO ADYACENTE
            if (!visitados[nombreAdy]) {//SI EL NODO NO HA SIDO VISITADO SE MARCA COMO VISITADO
                visitados[nombreAdy] = true;

                Adyacentes* nodoReal = cabeza;
                while (nodoReal != nullptr) {//SE RECORRE LA LISTA DE NODOS PARA ENCONTRAR EL NODO ADYACENTE
                    if (nodoReal->get_Nombre_Adyacente() == nombreAdy) {//SI SE ENCUENTRA EL NODO ADYACENTE SE AGREGA A LA COLA
                        cola.push_back(nodoReal);
                        break;
                    }
                    nodoReal = nodoReal->get_Siguiente();
                }
            }
            ady = ady->get_Vertice();
        }
    }
    cout << "NULL" << endl;
}

void Grafo::Recorrido_Profundidad() {
    unordered_map<string, bool> visitados;
    vector<Adyacentes*> pila;
    Adyacentes* aux = cabeza;
    Adyacentes* origenNodo = nullptr;

    if(aux==nullptr){
        cout<<"No hay nodos"<<endl;
        return;
    }

    cout << "Seleccione el nodo origen: ";
    string origen;
    cin >> origen;

    while (aux != nullptr) {//SE RECORRE LA LISTA DE NODOS PARA ENCONTRAR EL NODO ORIGEN
        if (aux->get_Nombre_Adyacente() == origen) {
            origenNodo = aux;
            break;
        }
        aux = aux->get_Siguiente();
    }

    if (origenNodo == nullptr) {
        cout << "Nodo origen no encontrado" << endl;
        return;
    }
    visitados[origen] = true;
    pila.push_back(origenNodo);
    cout << "Recorrido en profundidad: ";

    while (!pila.empty()) {//SE RECORRE HASTA QUE LA PILA ESTE VACIA
        Adyacentes* vertice = pila.back();//SE DIRECCIONA AL ULTIMO NODO DE LA PILA
        pila.pop_back();//SE ELIMINA EL ULTIMO NODO DE LA PILA

        cout << vertice->get_Nombre_Adyacente() << " -> ";

        Adyacentes* ady = vertice->get_Vertice();
        while (ady != nullptr) {
            string nombreAdy = ady->get_Nombre_Adyacente();//SE OBTIENE EL NOMBRE DEL NODO ADYACENTE
            if (!visitados[nombreAdy]) {
                visitados[nombreAdy] = true;//SI EL NODO NO HA SIDO VISITADO SE MARCA COMO VISITADO

                Adyacentes* nodoReal = cabeza;
                while (nodoReal != nullptr) {//SE RECORRE LA LISTA DE NODOS PARA ENCONTRAR EL NODO ADYACENTE
                    if (nodoReal->get_Nombre_Adyacente() == nombreAdy) {
                        pila.push_back(nodoReal);//SI SE ENCUENTRA EL NODO ADYACENTE SE AGREGA A LA PILA
                        break;
                    }
                    nodoReal = nodoReal->get_Siguiente();
                }
            }
            ady = ady->get_Vertice();
        }
    }
    cout << "NULL" << endl;
}

//FUNCION PARA ENCONTRAR EL PADRE (RAIZ) DE UN CONJUNTO DE VERTICES
string Grafo::Buscar(unordered_map<string, string>& Padres,  string x) {
    if (Padres[x] == x) {
        return x;
    }
    return Padres[x] = Buscar(Padres, Padres[x]);  // Compresión de caminos
}

//FUNCION PARA UNIR DOS CONJUNTOS DE VERTICES
void Grafo::Unir(unordered_map<string, string>& Padres, string x, string y) {
    string raiz_x = Buscar(Padres, x);
    string raiz_y = Buscar(Padres, y);

    //SI LAS RAICES DE LOS CONJUNTOS SON DIFERENTES SE UNEN LOS CONJUNTOS
    if (raiz_x != raiz_y) {
        Padres[raiz_x] = raiz_y;
    }
}

void Grafo::Kruskal() {
    vector<Aristas> Arbol_Expansion_Minima;
    unordered_map<string, string> Padres;
    Adyacentes *aux = cabeza;
    //SE INICIALIZAN LOS PADRES DE CADA VERTICE DONDE EL PADRE DE CADA VERTICE ES EL MISMO VERTICE
    while (aux!= nullptr) {
        Padres[aux->get_Nombre_Adyacente()] = aux->get_Nombre_Adyacente();
        aux = aux->get_Siguiente();
    }

    //SE ORDENAN LAS ARISTAS POR PESO
    sort(lista_aristas.begin(), lista_aristas.end());

    //SE RECORREN LAS ARISTAS PARA ENCONTRAR EL ARBOL DE EXPANSION MINIMA
    for (int i = 0; i < lista_aristas.size(); ++i) {
        Aristas& arista = lista_aristas[i];
        string raiz_1 = Buscar(Padres, arista.get_Origen());//SE OBTIENE LA RAIZ DEL VERTICE ORIGEN
        string raiz_2 = Buscar(Padres, arista.get_Destino());//SE OBTIENE LA RAIZ DEL VERTICE DESTINO

        //SI LAS RAICES DE LOS VERTICES SON DISJUNTAS SE AGREGAN AL ARBOL DE EXPANSION MINIMA
        if (raiz_1 != raiz_2) {
            Arbol_Expansion_Minima.push_back(arista);//SE AGREGA LA ARISTA AL ARBOL DE EXPANSION MINIMA
            Unir(Padres, raiz_1, raiz_2);//SE UNEN LOS CONJUNTOS DE VERTICES
        }
    }

    cout << "Arbol de Expansion Minima Kruskal:" << endl;
    for (int i = 0; i < Arbol_Expansion_Minima.size(); ++i) {
        Aristas& arista = Arbol_Expansion_Minima[i];//SE MUESTRA EL ARBOL DE EXPANSION MINIMA
        cout << arista.get_Origen() << " - " << arista.get_Destino() << " : " << arista.get_Peso() << endl;
    }

}

void Grafo::PRIM() {
    unordered_map<string, bool> visitados;
    vector<string> nodos_visitados;
    Adyacentes* aux = cabeza;
    Adyacentes* origenNodo = nullptr;

    if (aux == nullptr) {
        cout << "No hay nodos" << endl;
        return;
    }

    cout << "Seleccione el nodo origen: ";
    string origen;
    cin >> origen;

    while (aux != nullptr) {//SE RECORRE LA LISTA DE NODOS PARA ENCONTRAR EL NODO ORIGEN
        if (aux->get_Nombre_Adyacente() == origen) {
            origenNodo = aux;
            break;
        }
        aux = aux->get_Siguiente();
    }

    if (origenNodo == nullptr) {
        cout << "Nodo origen no encontrado" << endl;
        return;
    }

    visitados[origen] = true;
    nodos_visitados.push_back(origen);
    cout << "Arbol de Expansion Minima PRIM:" << endl;
    while (true) {
        string nodo_min_origen;//SE INICIALIZAN LAS VARIABLES PARA GUARDAR EL NODO ORIGEN Y DESTINO CON EL PESO MENOR
        string nodo_min_destino;
        int menor = INT_MAX;//SE INICIALIZA EL PESO MENOR CON EL VALOR MAXIMO


        for ( string& nodo_actual : nodos_visitados) {//SE RECORREN LOS NODOS VISITADOS YA QUE EN CADA ITERACION SE DEBE DE BUSCAR EL NODO CON EL PESO MENOR DE TODOS LOS NODOS VISITADOS
            Adyacentes* vertice = cabeza;
            while (vertice != nullptr && vertice->get_Nombre_Adyacente() != nodo_actual) {//SE RECORRE LA LISTA DE NODOS PARA ENCONTRAR EL NODO ACTUAL
                vertice = vertice->get_Siguiente();
            }

            Adyacentes* ady = vertice;

            while (ady != nullptr) {//SE RECORRE LA LISTA DE ADYACENCIA DEL NODO ACTUAL PARA ENCONTRAR EL NODO CON EL PESO MENOR
                if (!visitados[ady->get_Nombre_Adyacente()] && ady->get_Peso() < menor) {//SI EL NODO NO HA SIDO VISITADO Y EL PESO DE LA ARISTA ES MENOR AL PESO MENOR
                    menor = ady->get_Peso();
                    nodo_min_origen = nodo_actual;//SE ASIGNA EL NODO ACTUAL COMO NODO ORIGEN
                    nodo_min_destino = ady->get_Nombre_Adyacente();//SE ASIGNA EL NODO ADYACENTE COMO NODO DESTINO
                }
                ady = ady->get_Vertice();
            }
        }

        if (nodo_min_destino.empty()) break;//SI NO SE ENCONTRO UN NODO DESTINO SE SALE DEL CICLO Y SE TERMINA EL RECORRIDO PARA EVITAR UN CICLO INFINITO

        cout << nodo_min_origen << " -> " << nodo_min_destino << " : " << menor << endl;//SE MUESTRA EL NODO ORIGEN Y DESTINO
        visitados[nodo_min_destino] = true;//SE MARCA EL NODO DESTINO COMO VISITADO
        nodos_visitados.push_back(nodo_min_destino);//SE AGREGA EL NODO DESTINO A LOS NODOS VISITADOS PARA QUE EN LA SIGUIENTE ITERACION SE BUSQUE EL NODO CON EL PESO MENOR ENTRE LOS NODOS VISITADOS
    }
}

void Grafo::Menu_Dijkstra() {
    int op=0;
while (op!=3) {
    Cambio_Pantalla();
    cout<<"1.- Seleccionar solo nodo de inicio"<<endl;
    cout<<"2.- Seleccionar nodo de inicio y fin"<<endl;
    cout<<"3.- Regresar"<<endl;
    op=Validar_Entrada();
    switch (op){
        case 1:
            Dijkstra_Inicio();
        break;
        case 2:
            Dijkstra_Inicio_Final();
        break;
        case 3:
            cout<<"Regresando al menu de recorridos"<<endl;
        break;
        default:
            cout<<"Opcion no valida"<<endl;
        break;
    }
    system("pause");
}
}

void Grafo::Dijkstra_Inicio() {//FUNCION PARA ENCONTRAR EL CAMINO MAS CORTO DESDE UN NODO DE INICIO HASTA TODOS LOS DEMAS NODOS
    string origen;
    cout<<"Selecciona el nodo origen"<<endl;
    cin>>origen;
    Adyacentes *aux = cabeza;
    Adyacentes *origenNodo = nullptr;
    while (aux!= nullptr) {
        if (aux->get_Nombre_Adyacente() == origen) {
            origenNodo = aux;
        }
        aux = aux->get_Siguiente();
    }
    if (origenNodo == nullptr) {
        cout << "No se encontro el vertice origen" << endl;
        return;
    }

    unordered_map<string, int> distancias;
    unordered_map<string, string> padres;
    unordered_map<string, bool> procesado;
    vector<pair<string, int>> distancias_por_recorrer;

    aux = cabeza;
    while (aux != nullptr) {//SE INICIALIZAN LAS DISTANCIAS DE CADA NODO CON EL VALOR MAXIMO
        distancias[aux->get_Nombre_Adyacente()] = INT_MAX;
        aux = aux->get_Siguiente();
    }
    distancias[origen] = 0;//SE INICIALIZA LA DISTANCIA DEL NODO DE INICIO CON EL VALOR DE 0

    Adyacentes *nodo_actual = origenNodo;
    distancias_por_recorrer.push_back(make_pair(origen, 0));//SE AGREGA EL NODO DE INICIO A LA LISTA DE NODOS POR RECORRER

    while (!distancias_por_recorrer.empty()) {
        sort(distancias_por_recorrer.begin(), distancias_por_recorrer.end());//SE ORDENA LA LISTA DE NODOS POR RECORRER POR LA DISTANCIA

        string nodo_actual = distancias_por_recorrer.front().first;//DESPUES DE ORDENAR SE OBTIENE EL NOMRE DEL NODO CON LA DISTANCIA MENOR
        int distancia_actual = distancias_por_recorrer.front().second;//SE OBTIENE LA DISTANCIA DEL NODO CON LA DISTANCIA MENOR
        distancias_por_recorrer.erase(distancias_por_recorrer.begin());//SE ELIMINA EL NODO DE LA LISTA DE NODOS POR RECORRER

        if (procesado[nodo_actual]) continue;//SI EL NODO YA HA SIDO PROCESADO SE CONTINUA CON EL SIGUIENTE NODO
        procesado[nodo_actual] = true;//SE MARCA EL NODO ACTUAL COMO PROCESADO

        Adyacentes* nodo = cabeza;
        while (nodo != nullptr) {//SE RECORRE LA LISTA DE NODOS PARA ENCONTRAR EL NODO ACTUAL
            if (nodo->get_Nombre_Adyacente() == nodo_actual) {//SI SE ENCUENTRA EL NODO ACTUAL SE RECORRE LA LISTA DE ADYACENCIA
                Adyacentes* ady = nodo->get_Vertice();
                while (ady != nullptr) {
                    if (distancias[ady->get_Nombre_Adyacente()] > distancia_actual + ady->get_Peso()) {//SI LA DISTANCIA DEL NODO ADYACENTE ES MAYOR A LA DISTANCIA ACTUAL MAS EL PESO DE LA ARISTA
                        distancias[ady->get_Nombre_Adyacente()] = distancia_actual + ady->get_Peso();//SE ACTUALIZA LA DISTANCIA DEL NODO ADYACENTE
                        padres[ady->get_Nombre_Adyacente()] = nodo_actual;//SE ACTUALIZA EL PADRE DEL NODO ADYACENTE
                        distancias_por_recorrer.push_back(make_pair(ady->get_Nombre_Adyacente(), distancias[ady->get_Nombre_Adyacente()]));//SE AGREGA EL NODO ADYACENTE A LA LISTA DE NODOS POR RECORRER YA QUE AL CAMBIAR LA DISTANCIA SE DEBE DE VOLVER A RECORRER
                    }
                    ady = ady->get_Vertice();
                }
                break;
            }
            nodo = nodo->get_Siguiente();
        }
    }

    cout << "Caminos  desde el nodo " << origen << ":" << endl;

    for (auto& par : distancias) {//SE MUESTRA EL CAMINO MAS CORTO DESDE EL NODO DE INICIO HASTA TODOS LOS DEMAS NODOS
        string nodo = par.first;
        vector<string> camino;
        while (nodo != origen) {//SE RECORRE EL CAMINO DESDE EL ULTIMO NODO HASTA EL NODO DE INICIO
            camino.push_back(nodo);
            nodo = padres[nodo];
        }
        camino.push_back(origen);

        cout << "Camino mas corto  de " << origen << "->" << par.first << ": " << par.second << " : ";//SE MUESTRA EL CAMINO MAS CORTO
        for (int i = camino.size() - 1; i >= 0; --i) {
            if (i!=0) {
                cout << camino[i] << "->";
            }else{
                cout<<camino[i];
            }
        }
        cout <<endl;
    }
}

//SOBRECARGAMOS EL OPERADOR < PARA ORDENAR LA LISTA DE NODOS POR RECORRER POR LA DISTANCIA
bool operator<(const pair<string, int>& a, const pair<string, int>& b) {
    return a.second < b.second;
}


void Grafo::Dijkstra_Inicio_Final() {
    string origen,destino;
    cout<<"Selecciona el nodo origen"<<endl;
    cin>>origen;
    cout<<"Selecciona el nodo destino"<<endl;
    cin>>destino;
    Adyacentes *aux = cabeza;
    Adyacentes *origenNodo = nullptr;
    Adyacentes *destinoNodo = nullptr;

    while (aux != nullptr) {//SE RECORRE LA LISTA DE NODOS PARA ENCONTRAR EL NODO ORIGEN Y DESTINO
        if (aux->get_Nombre_Adyacente() == origen) {
            origenNodo = aux;
        }
        if (aux->get_Nombre_Adyacente() == destino) {
            destinoNodo = aux;
        }
        aux = aux->get_Siguiente();
    }

    if (origenNodo == nullptr || destinoNodo == nullptr) {
        cout << "No se encontro el vertice origen o destino" << endl;
        return;
    }

    vector<pair<string, int>> distancias_por_recorrer;
    unordered_map<string, int> distancias;
    unordered_map<string, string> padres;
    unordered_map<string, bool> procesado;

     aux = cabeza;
    while (aux != nullptr) {//SE INICIALIZAN LAS DISTANCIAS DE CADA NODO CON EL VALOR MAXIMO
        distancias[aux->get_Nombre_Adyacente()] = INT_MAX;
        aux = aux->get_Siguiente();
    }
    distancias[origen] = 0;

    Adyacentes *nodo_actual = origenNodo;
    distancias_por_recorrer.push_back(make_pair(origen, 0));//SE AGREGA EL NODO DE INICIO A LA LISTA DE NODOS POR RECORRER

    while (nodo_actual != nullptr) {
        Adyacentes *ady = nodo_actual->get_Vertice();
        while (ady != nullptr) {//SE RECORRE LA LISTA DE ADYACENCIA DEL NODO ACTUAL
            if (distancias[ady->get_Nombre_Adyacente()] > distancias[nodo_actual->get_Nombre_Adyacente()] + ady->get_Peso()) {//SI LA DISTANCIA DEL NODO ADYACENTE ES MAYOR A LA DISTANCIA ACTUAL MAS EL PESO DE LA ARISTA
                distancias[ady->get_Nombre_Adyacente()] = distancias[nodo_actual->get_Nombre_Adyacente()] + ady->get_Peso();//SE ACTUALIZA LA DISTANCIA DEL NODO ADYACENTE
                padres[ady->get_Nombre_Adyacente()] = nodo_actual->get_Nombre_Adyacente();//SE ACTUALIZA EL PADRE DEL NODO ADYACENTE
                distancias_por_recorrer.push_back(make_pair(ady->get_Nombre_Adyacente(), distancias[ady->get_Nombre_Adyacente()]));//SE AGREGA EL NODO ADYACENTE A LA LISTA DE NODOS POR RECORRER YA QUE AL CAMBIAR LA DISTANCIA SE DEBE DE VOLVER A RECORRER
            }
            ady = ady->get_Vertice();
        }
        procesado[nodo_actual->get_Nombre_Adyacente()] = true;

        nodo_actual = nullptr;
        for (int i = 0; i < distancias_por_recorrer.size(); ++i) {//SE RECORRE LA LISTA DE NODOS POR RECORRER
            if (!procesado[distancias_por_recorrer[i].first]) {//SI EL NODO NO HA SIDO PROCESADO SE ASIGNA COMO NODO ACTUAL
                nodo_actual = cabeza;
                while (nodo_actual != nullptr) {
                    if (nodo_actual->get_Nombre_Adyacente() == distancias_por_recorrer[i].first) {//SE BUSCA EL NODO ACTUAL EN LA LISTA DE NODOS POR RECORRER
                        break;//SE SALE DEL CICLO YA QUE SI ENCONTRAMOS EL NODO ACTUAL SIGNIFICA QUE ES EL NODO QUE DEBEMOS PROCESAR PARA IR AL SIGUIENTE NODO
                    }
                    nodo_actual = nodo_actual->get_Siguiente();
                }
                break;
            }
        }
    }

    cout << "Camino mas corto de " << origen << " ----- " << destino << ": " << distancias[destino] << endl;//SE MUESTRA EL PESO DEL CAMINO MAS CORTO

    string nodo = destino;
    vector<string> camino;
    while (nodo != origen) {//SE ALMACENA EL CAMINO MAS CORTO DESDE EL NODO DE INICIO HASTA EL NODO DESTINO EN UN VECTOR ESTO LO SABEMOS POR EL UNORDERED_MAP PADRES
        camino.push_back(nodo);
        nodo = padres[nodo];//YA QUE EL PADRE DE CADA NODO ES EL NODO ANTERIOR
    }
    camino.push_back(origen);
    for (int i = camino.size() - 1; i >= 0; --i) {//SE MUESTRA CADA NODO DEL CAMINO MAS CORTO
        cout << camino[i] << " -> ";
    }
    cout << "NULL" << endl;
}

int Grafo::Validar_Entrada() {
    //SE VALIDA QUE EL VALOR INGRESADO SEA UN NÚMERO
    string valor;
    int val;
    cin >> valor;
    try {
        val = stoi(valor);
    } catch (exception e) {
        //SE MUESTRA UN MENSAJE DE ERROR SI EL VALOR NO ES UN NÚMERO
        cout << "Valor no valido" << endl;
        _sleep(1000);
        val = 0;
    }
    return val;
}

void Grafo::Cambio_Pantalla() {
    //SE VERIFICAN LAS FUNCIONES DEPENDIENDO DEL SISTEMA OPERATIVO
#ifdef _WIN32//SI ES WINDOWS SE LIMPIA LA PANTALLA
    system("cls");
#else //SI ES LINUX
    system("clear");
#endif
}