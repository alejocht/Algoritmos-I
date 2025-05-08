

#include <iostream>
#include <vector>
using namespace std;

struct Paquete
{
    int codigo;
    Paquete* izquierdo;
    Paquete* derecho;
    int altura;

    Paquete(int _codigo) : codigo(_codigo), izquierdo(nullptr), derecho(nullptr), altura(1){}
};

int obtenerAltura(Paquete* nodo)
{
    return nodo ? nodo->altura : 0;
}

int obtenerBalance(Paquete* nodo)
{
    return nodo ? obtenerAltura(nodo->izquierdo) - obtenerAltura(nodo->derecho) : 0;
}

Paquete* rotarDerecha(Paquete* d)
{
    Paquete* nuevaRaiz = d->izquierdo;
    Paquete* temporal = nuevaRaiz->derecho;

    //rotacion
    nuevaRaiz->derecho = d;
    d->izquierdo = temporal;

    d->altura = 1 + max(obtenerAltura(d->izquierdo), obtenerAltura(d->derecho));
    nuevaRaiz->altura = 1 + max(obtenerAltura(nuevaRaiz->izquierdo), obtenerAltura(nuevaRaiz->derecho));

    return nuevaRaiz;
}

Paquete* rotarIzquierda(Paquete* d)
{
    Paquete* nuevaRaiz = d->derecho;
    Paquete* temporal = nuevaRaiz->izquierdo;

    nuevaRaiz->izquierdo = d;
    d->derecho = temporal;

    d->altura = 1 + max(obtenerAltura(d->izquierdo), obtenerAltura(d->derecho));
    nuevaRaiz->altura = 1 + max(obtenerAltura(nuevaRaiz->izquierdo), obtenerAltura(nuevaRaiz->derecho));

    return nuevaRaiz;
}

Paquete* insertar(Paquete* raiz, int codigoNuevo)
{
    if (raiz == nullptr)
        return new Paquete(codigoNuevo);

    if (codigoNuevo < raiz->codigo)
    {
        raiz->izquierdo = insertar(raiz->izquierdo, codigoNuevo);
    }
    else if (codigoNuevo > raiz->codigo)
    {
        raiz->derecho = insertar(raiz->derecho, codigoNuevo);
    }
    else return raiz; //evita duplicados

    raiz->altura = 1 + max(obtenerAltura(raiz->izquierdo), obtenerAltura(raiz->derecho));
    int balance = obtenerBalance(raiz);
    //simple derecha. izquierda izquierda raiz
    if (balance > 1 && codigoNuevo < raiz->izquierdo->codigo)
    {
        return rotarDerecha(raiz);
    }
    //simple izquierda. raiz derecha derecha
    if (balance < -1 && codigoNuevo > raiz->derecho->codigo)
    {
        return rotarIzquierda(raiz);
    }
    //izquierda derecha. izquierda derecha raiz
    if (balance > 1 && codigoNuevo > raiz->izquierdo->codigo)
    {
        raiz->izquierdo = rotarIzquierda(raiz->izquierdo);
        return rotarDerecha(raiz);
    }
    //derecha izquierda. raiz derecha izquierda
    if (balance < -1 && codigoNuevo < raiz->derecho->codigo)
    {
        raiz->derecho = rotarDerecha(raiz->derecho);
        return rotarIzquierda(raiz);
    }

    return raiz; //no necesita rotaciones
}

Paquete* paqueteMinimo(Paquete* raiz)
{
    while (raiz->izquierdo)
    {
        raiz = raiz->izquierdo;
    }
    return raiz;
}

Paquete* eliminar(Paquete* raiz, int codigo)
{
    if (raiz == nullptr) return raiz;
    if (codigo < raiz->codigo)
    {
        raiz->izquierdo = eliminar(raiz->izquierdo, codigo);
    }
    else if (codigo > raiz->codigo)
    {
        raiz->derecho = eliminar(raiz->derecho, codigo);
    }
    else
    {
        // caso que sea este nodo el que hay que eliminar
        //caso hoja
        if (raiz->izquierdo == nullptr && raiz->derecho == nullptr)
        {
            delete raiz;
            return nullptr;
        }
        //un solo hijo
        if (raiz->izquierdo == nullptr)
        {
            Paquete* temp = raiz->derecho;
            delete raiz;
            return temp;
        }
        if (raiz->derecho == nullptr)
        {
            Paquete* temp = raiz->izquierdo;
            delete raiz;
            return temp;
        }
        //mas de un hijo
        Paquete* sucesor = paqueteMinimo(raiz->derecho);
        raiz->codigo = sucesor->codigo;
        raiz->derecho = eliminar(raiz->derecho, sucesor->codigo);
        raiz->altura = 1 + max(obtenerAltura(raiz->izquierdo), obtenerAltura(raiz->derecho));
        int balance = obtenerBalance(raiz);

        if (balance > 1 && obtenerBalance(raiz->izquierdo) >= 0)
        {
            return rotarDerecha(raiz);
        }
        if (balance > 1 && obtenerBalance(raiz->izquierdo) < 0)
        {
            raiz->izquierdo = rotarIzquierda(raiz->izquierdo);
            return rotarDerecha(raiz);
        }

        if (balance < -1 && obtenerBalance(raiz->derecho) <= 0)
            return rotarIzquierda(raiz);

        // RL
        if (balance < -1 && obtenerBalance(raiz->derecho) > 0)
        {
            raiz->derecho = rotarDerecha(raiz->derecho);
            return rotarIzquierda(raiz);
        }

       
    }
    return raiz;
}

void mostrarInorden(Paquete* nodo)
{
    if (nodo != nullptr)
    {
        mostrarInorden(nodo->izquierdo);
        cout << nodo->codigo << " ";
        mostrarInorden(nodo->derecho);
    }
    
}

int main()
{
    Paquete* raiz = new Paquete(100);
    raiz = insertar(raiz, 300);
    raiz = insertar(raiz, 1200);
    raiz = insertar(raiz, 400);
    raiz = insertar(raiz, 360);
    raiz = insertar(raiz, 1500);
    raiz = insertar(raiz, 1230);
    raiz = insertar(raiz, 1315);
    eliminar(raiz, 1500);
    mostrarInorden(raiz);
}
