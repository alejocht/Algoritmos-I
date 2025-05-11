

#include <iostream>
#include <iomanip>

//enumeracion de colores posibles
enum Color {ROJO, NEGRO};
template <typename T> //declaro tipo de dato generico
class Nodo
{
public:
	T clave;
	Color color;
	Nodo* izquierdo;
	Nodo* derecho;
	Nodo* padre;

	Nodo(T clave) : clave(clave), color(ROJO), izquierdo(nullptr), derecho(nullptr) {}
};

template <typename T> //declaro tipo de dato generico
class ArbolRojoNegro {
private:
	Nodo<T>* raiz;

	void rotacionIzquierda(Nodo<T>* raiz);
	void rotacionDerecha(Nodo<T>* raiz);
	void arreglarInsercion(Nodo<T>* raiz);
	void arreglarBorrado(Nodo<T>* raiz);
	void transplantar(Nodo<T>* u, Nodo<T>* v);
	Nodo<T>* minValorNodo(Nodo<T>* nodo);
	void imprimirHelper(Nodo<T>* nodo, std::string indent, bool ultimo) const;
public:
	ArbolRojoNegro() : raiz(nullptr);
	void insertar(const T& clave);
	void borrar(const T& clave);
	void inOrden()const;
	void inOrden(Nodo<T>* nodo)const;
	void imprimir()const;
};

//implementacion de funciones
template <typename T> //declaro tipo de dato generico
void ArbolRojoNegro<T>::rotacionIzquierda(Nodo<T>* raiz)
{
	Nodo<T>* y = x->derecha;         // El hijo derecho de x se convierte en y
	x->derecha = y->izquierda;      // El subárbol izquierdo de y se convierte en el hijo derecho de x
	if (y->izquierda != nullptr)    // Si y tiene un subárbol izquierdo, actualiza su padre
		y->izquierda->padre = x;
	y->padre = x->padre;            // Actualiza el padre de y
	if (x->padre == nullptr)        // Si x es la raíz del árbol
		raiz = y;                   // y se convierte en la nueva raíz
	else if (x == x->padre->izquierda) // Si x es el hijo izquierdo de su padre
		x->padre->izquierda = y;    // Actualiza el hijo izquierdo del padre
	else
		x->padre->derecha = y;      // Actualiza el hijo derecho del padre
	y->izquierda = x;               // x se convierte en el hijo izquierdo de y
	x->padre = y;                   // Actualiza el padre de x
}

int main()
{
    std::cout << "Hello World!\n";
}

