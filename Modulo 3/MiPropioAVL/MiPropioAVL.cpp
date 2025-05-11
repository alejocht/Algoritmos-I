
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

nodo* encontrarPredecesor(nodo* raiz)
{
    while (raiz->derecho)
    {
        raiz = raiz->derecho;
    }
    return raiz;
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
    if (valor < raiz->valor) raiz->izquierdo = eliminar(raiz->izquierdo, valor);
    if (valor > raiz->valor) raiz->derecho = eliminar(raiz->derecho, valor);

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
        //busco el predecesor
        //numero mas grande del lado izquierdo, o sea de los chicos el mas grande 
        nodo* predecesor = encontrarPredecesor(raiz->izquierdo);
        //su valor lo copio en la raiz, sobreescribiendo la raiz y perdiendo el valor que queria borrar
        raiz->valor = predecesor->valor;
        //ahora el valor del predecesor esta en su lugar original y en la raiz
        //por eso elimino la version original para preservar un set de datos sin duplicidad
        raiz->izquierdo = eliminar(raiz->izquierdo, predecesor->valor);
    }

    raiz->altura = 1 + max(obtenerAltura(raiz->izquierdo), obtenerAltura(raiz->derecho));
    int balance = obtenerBalance(raiz);
    //balance mayor a 1 significa desbalance de la raiz a la izquierda y si el balance de raiz->izquierdo
    //es mayor igual a 0 significa que esta balanceado o desbalanceado en el subarbol izquierdo
    if (balance > 1 && obtenerBalance(raiz->izquierdo) >= 0)
    {
        return rotarDerecha(raiz);
    }
    //balance mayor a 1 significa desbalance de la raiz a a la izquierda
    //si balance de raiz->izuierdo es menor o igual a 0 el subarbol derecho de raiz->izquierdo
    //esta desbalanceado

    if (balance > 1 && obtenerBalance(raiz->izquierdo) <= 0)
    {
        raiz->izquierdo = rotarIzquierda(raiz->izquierdo);
        return rotarDerecha(raiz);
    }
    //balance menor a -1 significa desbalance de la raiz a la derecha
    //si el balance de la raiz derecho es mayor o igual a 0
    // el desbalance ocurre en raiz->derecha->izquierda
    if (balance < -1 && obtenerBalance(raiz->derecho) >= 0)
    {
        //error aca
        raiz->derecho = rotarDerecha(raiz->derecho);
        return rotarIzquierda(raiz);
    }
    //balance menor a -1 significa desbalance del lado derecho de la raiz
    //si el balance de la raiz derecho es menor o igual a 0
    // el desbalance ocurre en raiz->derecha->derecha
    if (balance < -1 && obtenerBalance(raiz->derecho) <= 0)
    {
        return rotarIzquierda(raiz);
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
    cout << "Demostracion previa\n";
    inorden(raiz);
    cout << "\n-----------------------------\n";
    cout << "Post Eliminacion. Deberia seguir ordenado e internamente balanceado\n";
    raiz = eliminar(raiz, 100);
    inorden(raiz);
}
