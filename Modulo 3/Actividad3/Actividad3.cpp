
#include <iostream>
#include <string>

using namespace std;

struct Libro {
    string nombre;
    Libro* izquierdo;
    Libro* derecho;
    Libro(string _nombre) : nombre(_nombre), izquierdo(nullptr), derecho(nullptr){}
};

Libro* insertar(Libro* raiz, string nombre)
{
    if (raiz == nullptr) return new Libro(nombre);
    if (raiz->nombre > nombre)
    {
        raiz->izquierdo = insertar(raiz->izquierdo, nombre);
    }
    else
    {
        raiz->derecho = insertar(raiz->derecho, nombre);
    }
    return raiz;
}

void buscar(Libro* raiz, string nombre, int& contador)
{
    if (raiz == nullptr)
    {
        contador++;
        cout << "\nLibro no encontrado.\n";
        return;
    }
    if (raiz->nombre == nombre)
    {
        contador++;
        cout << "\nLibro encontrado.\n"; 
        return;
    }
    if (nombre < raiz->nombre)
    {
        contador++;
        buscar(raiz->izquierdo, nombre, contador);
    }
    else
    {
        contador++;
        buscar(raiz->derecho, nombre, contador);
    }
}

void mostrarInOrder(Libro* raiz)
{
    if (raiz != nullptr)
    {
        mostrarInOrder(raiz->izquierdo);
        cout << "\n" << raiz->nombre << "\n";
        mostrarInOrder(raiz->derecho);
    }   
}

int main()
{
    Libro* catalogo = nullptr;
    while (true)
    {
        cout << "----Elija una opcion----\n";
        cout << "1. insertar\n" << "2. buscar\n" << "3. mostrar\n" << "0. salir\n";
        int opc;
        cin >> opc;
        string nombre;
        int contador = 0;
        switch (opc)
        {
            case 1:
                cout << "Ingrese el libro nuevo:\n";
                cin >> nombre;
                catalogo = insertar(catalogo, nombre);
            break;

            case 2:
                cout << "Ingrese libro buscado:\n";
                cin >> nombre;
                buscar(catalogo, nombre, contador);
            break;

            case 3:
                mostrarInOrder(catalogo);
            break;
            case 0:
                return 0;
            break;
        }

    }

}

