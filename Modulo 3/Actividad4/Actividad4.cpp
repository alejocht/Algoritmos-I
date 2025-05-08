
#include <iostream>
#include <string>

using namespace std;

struct Empleado {
    int id;
    string nombre;
    Empleado* izquierdo;
    Empleado* derecho;
    Empleado(int _id, string _nombre): id(_id), nombre(_nombre), izquierdo(nullptr), derecho(nullptr) {}
};

Empleado* insertar(Empleado* raiz, int id, string nombre)
{
    if (raiz == nullptr) return new Empleado(id, nombre);
    if (id < raiz->id)
    {
        raiz->izquierdo = insertar(raiz->izquierdo, id, nombre);
    }
    else
    {
        raiz->derecho = insertar(raiz->derecho, id, nombre);
    }
    return raiz;
}

void buscar(Empleado* raiz, int id)
{
    if (raiz == nullptr)
    {
        cout << "\nEmpleado no encontrado.\n";
        return;
    }
    if (raiz->id == id)
    {
        cout << "\nEmpleado encontrado: " << raiz->nombre << "\n";
        return;
    }
    if (id < raiz->id)
    {
        buscar(raiz->izquierdo, id);
    }
    else
    {
        buscar(raiz->derecho, id);
    }
}

void recorrerInorden(Empleado* raiz)
{
    if (raiz == nullptr)
    {
        return;
    }
    recorrerInorden(raiz->izquierdo);
    cout << "Empleado[ Id: " << raiz->id << " Nombre: " << raiz->nombre << " ]\n";
    recorrerInorden(raiz->derecho);
}

Empleado* encontrarMinimo(Empleado* raiz)
{
    while (raiz != nullptr && raiz->izquierdo != nullptr)
    {
        raiz = raiz->izquierdo;
    }
    return raiz;
}

Empleado* eliminar(Empleado* raiz, int id)
{
    if (raiz == nullptr)
    {
        return nullptr;
    }
    if (id < raiz->id)
    {
        raiz->izquierdo = eliminar(raiz->izquierdo, id);
    }
    else if (id > raiz->id)
    {
        raiz->derecho = eliminar(raiz->derecho, id);
    }
    else
    {
        //nodo hoja
        if (raiz->izquierdo == nullptr && raiz->derecho == nullptr)
        {
            delete raiz;
            return nullptr;
        }
        //un solo hijo
        if (raiz->izquierdo == nullptr)
        {
            Empleado* temp = raiz->derecho;
            delete raiz;
            return temp;
        }
        else if (raiz->derecho == nullptr)
        {
            Empleado* temp = raiz->izquierdo;
            delete raiz;
            return temp;
        }
        Empleado* sucesorInorden = encontrarMinimo(raiz->derecho);
        raiz->id = sucesorInorden->id;
        raiz->nombre = sucesorInorden->nombre;
        raiz->derecho = eliminar(raiz->derecho, sucesorInorden->id);


    }

    return raiz;
    
}


int main()
{
    Empleado* legajos = nullptr;
    legajos = insertar(legajos, 1, "Alejo");
    legajos = insertar(legajos, 2, "Juan Pablo II");
    legajos = insertar(legajos, 3, "Papa Francisco");
    legajos = insertar(legajos, 4, "Messi");
    legajos = insertar(legajos, 5, "Cristiano");

    cout << "ANTES:\n";
    recorrerInorden(legajos);

    legajos = eliminar(legajos, 3);
    
    cout << "DESPUES:\n";
    recorrerInorden(legajos);
    return 0;
}

