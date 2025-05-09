
#include <iostream>
using namespace std;

struct nodo
{
    int valor;
    nodo* izquierdo;
    nodo* derecho;
    int altura;

    nodo(int _valor)
    {
        valor = _valor;
        izquierdo = derecho = nullptr;
        altura = 1;
    }
};

int obtenerAltura(nodo* nodo)
{
    return nodo ? nodo->altura : 0;
}

int obtenerBalance(nodo* nodo)
{
    //balance mayor a -1, desbalanceado hacia la derecha
    //balance mayor a 1, desbalanceado hacia la izquierda
    //balance entre 1 y -1 es aceptable
    return nodo ? obtenerAltura(nodo->izquierdo) - obtenerAltura(nodo->derecho) : 0;
}

nodo* encontrarSucesor(nodo* raiz)
{
    nodo* sucesor = raiz->izquierdo;
    while (sucesor != nullptr)
    {
        sucesor = sucesor->derecho;
    }
    return sucesor;
}

nodo* rotarDerecha(nodo* raiz)
{
    nodo* x = raiz->izquierdo;
    nodo* t = x->derecho;
    
    x->derecho = raiz;
    raiz->izquierdo = t;

    //al ser rotados hay que cambiar la altura para mantener las propiedades del AVL

    x->altura = 1 + max(obtenerAltura(x->derecho), obtenerAltura(x->izquierdo));
    raiz->altura = 1 + max(obtenerAltura(raiz->derecho), obtenerAltura(raiz->izquierdo));

    return x;
}

nodo* rotarIzquierda(nodo* raiz)
{
    nodo* x = raiz->derecho;
    nodo* t = x->izquierdo;

    x->izquierdo = raiz;
    raiz->derecho = t;

    //al ser rotados hay que cambiar la altura para mantener las propiedades del AVL
    x->altura = 1 + max(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho));
    raiz->altura = 1 + max(obtenerAltura(raiz->izquierdo), obtenerAltura(raiz->derecho));

    return x;
}

nodo* insertar(nodo* raiz, int valor)
{
    if (raiz == nullptr)
    {
        return new nodo(valor);
    }
    if (valor < raiz->valor)
    {
        //asignarle un nodo siempre
        raiz->izquierdo = insertar(raiz->izquierdo, valor);
    }
    else if (valor > raiz->valor)
    {
        //asignarle un nodo siempre
        raiz->derecho = insertar(raiz->derecho, valor);
    }
    //ojo con el else aca
    raiz->altura = 1 + max(obtenerAltura(raiz->izquierdo), obtenerAltura(raiz->derecho));
    int balance = obtenerBalance(raiz);

    if (balance > 1 && valor < raiz->izquierdo->valor)
    {
        //caso ejemplo
        //     10
        //    /
        //   8
        //  /
        // 7
        return rotarDerecha(raiz);
        //se debe devolver algo asi
        //    8
        //   / \
        //  7   10
    }
    if (balance < -1 && valor > raiz->derecho->valor)
    {
        //caso ejemplo
        //    10
        //      \
        //       12
        //         \
        //          15
        return rotarIzquierda(raiz);
        //se debe devolver algo asi
        //    12
        //   /  \
        //  10  15
    }
    if (balance > 1 && valor > raiz->izquierdo->valor)
    {
        //caso ejemplo
        //     10
        //    /
        //   7
        //    \
        //     8
        raiz->izquierdo = rotarIzquierda(raiz->izquierdo);
        //ahora quedaria asi
        //     10
        //    /
        //   8
        //  /
        // 7
        return rotarDerecha(raiz);
        //se debe devolver algo asi
        //    8
        //   / \
        //  7   10
        
    }
    if (balance < -1 && valor < raiz->derecho->valor)
    {
        //caso ejemplo
        //     10
        //       \
        //        12
        //       / 
        //     11    
        raiz->derecho = rotarDerecha(raiz->derecho);
        //deberia quedar asi
        //     10
        //       \
        //        11
        //          \
        //           12
        return rotarIzquierda(raiz);
        //se debe devolver algo asi
        //     11
        //    /  \
        //  10    12
    }
    return raiz;
}


void inorden(nodo* raiz)
{
    if (raiz != nullptr)
    {
        inorden(raiz->izquierdo);
        cout << " " << raiz->valor << " ";
        inorden(raiz->derecho);
    }
}



nodo* eliminar(nodo* raiz, int valor)
{
    if (raiz == nullptr) return nullptr;
    if (valor < raiz->valor) eliminar(raiz->izquierdo, valor);
    if (valor > raiz->valor) eliminar(raiz->derecho, valor);

    //caso que uno de sus hijos este vacio
    if (raiz->izquierdo == nullptr)
    {
        //si no tiene hijo izquierdo, guardo temporalmente su hijo derecho
        nodo* temp = raiz->derecho;
        //borro el puntero de raiz
        delete raiz;
        //retorno su hijo derecho en su lugar (podria ser null u otro valor)
        return temp;
    }
    else if (raiz->derecho == nullptr)
    {
        //si no tiene hijo derecho, guardo temporalmente su hijo izquierdo
        nodo* temp = raiz->izquierdo;
        //borro el puntero de raiz
        delete raiz;
        //retorno su hijo izquierdo en su lugar(podria ser null u otro valor)
        return temp;
    }
    else
    {
        //busco a mi sucesor (de los menores (izquierda), el mas grande(derecha) (el mayor del subarbol izquierdo))
        nodo* sucesor = encontrarSucesor(raiz);
        //mi raiz (apuntado a ser borrado) copiara el valor de su sucesor, siendo "eliminado". Mas bien reemplazado.
        raiz->valor = sucesor->valor;
        //por ultimo ahora debo eliminar al nodo que era sucesor ya que ahora su valor esta en raiz pero tambien en el subarbol izquierdo.
        //hago una llamada recursiva ya que la funcion cubre
        //caso en el que tenga un hijo, dos hijos o ninguno
        eliminar(raiz->izquierdo, sucesor->valor);
    }

    return raiz;

}
int main()
{
    nodo* raiz = new nodo(30);
    raiz = insertar(raiz, 200);
    raiz = insertar(raiz, 100);
    raiz = insertar(raiz, 13);
    raiz = insertar(raiz, 220);
    raiz = insertar(raiz, 114);

    inorden(raiz);
}
