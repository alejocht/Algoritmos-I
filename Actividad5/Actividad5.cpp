
#include <iostream>
#include <string>
using namespace std;

class Nodo {
private:
    int valor;
    Nodo* izquierdo;
    Nodo* derecho;
public:
    Nodo(int valor);
    string ToString();
    Nodo* getIzquierdo();
    Nodo* getDerecho();
    int getValor();
    void setIzquierdo(Nodo* valor);
    void setDerecho(Nodo* valor);
};

Nodo::Nodo(int valor)
{
    this->valor = valor;
    this->izquierdo = this->derecho = nullptr;
}

void Nodo::setIzquierdo(Nodo* nodo)
{
    this->izquierdo = nodo;
}

void Nodo::setDerecho(Nodo* nodo)
{
    this->derecho = nodo;
}

int Nodo::getValor()
{
    return this->valor;
}

Nodo* Nodo::getIzquierdo()
{
    return this->izquierdo;
}

Nodo* Nodo::getDerecho()
{
    return this->derecho;
}

string Nodo::ToString()
{
    return std::to_string(this->valor);
}

Nodo* crearNodo(int valor)
{
    Nodo* nodo = new Nodo(valor);
    return nodo;
}

void recorrerInorden(Nodo* nodo)
{
    if (nodo != nullptr)
    {
        recorrerInorden(nodo->getIzquierdo());
        cout << nodo->ToString() << " ";
        recorrerInorden(nodo->getDerecho());
    }
}

bool esteNumeroExiste(Nodo* nodo, int valorBuscado)
{
    if (nodo != nullptr)
    {
        if (esteNumeroExiste(nodo->getIzquierdo(), valorBuscado)){return true;};
        if (nodo->getValor() == valorBuscado) { return true; }
        if (esteNumeroExiste(nodo->getDerecho(), valorBuscado)) { return true; };
    }

    return false;
}

int main()
{
    Nodo raiz = Nodo(1);
    raiz.setDerecho(new Nodo(3));
    raiz.setIzquierdo(new Nodo(2));
    raiz.getIzquierdo()->setIzquierdo(new Nodo(10));
    raiz.getIzquierdo()->setDerecho(new Nodo(4));
    raiz.getDerecho()->setDerecho(new Nodo(13));
    raiz.getDerecho()->setIzquierdo(new Nodo(20));

    recorrerInorden(&raiz);
    if (esteNumeroExiste(&raiz, 20))
    {
        cout << "Encontrado!\n";
    }
    else {
        cout << "No encontrado.\n";
    }


    delete raiz.getIzquierdo()->getIzquierdo();
    delete raiz.getIzquierdo()->getDerecho();
    delete raiz.getDerecho()->getIzquierdo();
    delete raiz.getDerecho()->getDerecho();
    delete raiz.getDerecho();
    delete raiz.getIzquierdo();




}
