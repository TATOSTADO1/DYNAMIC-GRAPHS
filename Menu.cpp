//CRISTHIAN ANTONIO AGUILAR VAZQUEZ 202333839
//ROBERTO NOE HERNANDEZ ROMERO 202328123
//ANGEL HERNANDEZ GONZALEZ 202327868

#include "Menu.h"
#include "Grafo.h"
#include <iostream>
#include <string>
#include <exception>
#include <chrono>
#include <cstdlib>

using namespace std;

void Menu::Mostrar_Menu() {
    int op = 0;
    Grafo G; //SE CREA UN OBJETO DE TIPO LISTA ESTATICA

    while (op != 9) {
        Cambio_Pantalla();

        //SE CREA UN MENU CON OPCIONES PARA MANIPULAR LA LISTA
        cout << "1.- Modificar Matriz" << endl;
        cout << "2.- Mostrar Grafo" << endl;
        cout << "3.- Mostrar Matriz" << endl;
        cout << "4.- Cardinalidad" << endl;
        cout << "5.- x adyacente a y" << endl;
        cout << "6.- Matriz cuadratica" << endl;
        cout << "7.- Matriz cubica" << endl;
        cout << "8.- Recorridos/Arboles" << endl;
        cout << "9.- Salir" << endl;

        op = Validar_Entrada();
        switch (op) {
            case 1:
                G.Menu_CrearMatriz();
                continue;//SE USA CONTINUE PARA QUE NO SE EJECUTE EL RESTO DEL CÓDIGO YA QUE SINO HAY DOS PAUSE PORQUE ES OTRO MENU
            case 2:
                G.Mostrar_Grafo();
                break;
            case 3:
                G.Mostrar_Matriz();
                break;
            case 4:
                G.Cardinalidad();
                break;
            case 5:
                G.Adyacente();
                break;
            case 6:
                G.Matriz_Cuadratica();
                G.Mostrar_Matriz_Operada(G.get_Matriz_Cuadratica());
                break;
            case 7:
                G.Matriz_Cubica();
                G.Mostrar_Matriz_Operada(G.get_Matriz_Cubica());
                break;
            case 8:
                G.Menu_Recorridos();
                continue;
            case 9:
                cout << "Saliendo gracias por usar el programa :3" << endl;
                break;
            default:
                cout << "Opcion no valida" << endl;
                break;
        }
        system("pause");//SE PAUSA EL PROGRAMA PARA QUE EL USUARIO PUEDA VER LOS RESULTADOS
    }
}

int Menu::Validar_Entrada() {
    //SE VALIDA QUE EL VALOR INGRESADO SEA UN NÚMERO
    string valor;
    int val;
    cout << "Digite una opcion del menu" << endl;
    cin >> valor;
    try {
        val = stof(valor);
    } catch (exception e) {
        //SE MUESTRA UN MENSAJE DE ERROR SI EL VALOR NO ES UN NÚMERO
        cout << "Valor no valido" << endl;
        _sleep(1000);
        val = 0;
    }
    return val;
}

void Menu::Cambio_Pantalla() {
    //SE VERIFICAN LAS FUNCIONES DEPENDIENDO DEL SISTEMA OPERATIVO
#ifdef _WIN32//SI ES WINDOWS SE LIMPIA LA PANTALLA
    system("cls");
#else //SI ES LINUX
        system("clear");
#endif
}