#include <iostream>
#include <list>
#include <string>
using namespace std;
class Producto
{
public:
	Producto(string nombre, float precio);
	~Producto();
	void setNombre(string nombre);
	string getNombre();
	string ToString();

private:
	string nombre;
	float precio;
};

Producto::Producto(string nombre, float precio)
{
	this->nombre = nombre;
	this->precio = precio;
}

Producto::~Producto()
{
}

string Producto::ToString()
{
	return "Producto [ Nombre: " + this->nombre + " Precio: $" + to_string(this->precio) + " ]";
}
string Producto::getNombre()
{
	return this->nombre;
}
void Producto::setNombre(string nombre)
{
	this->nombre = nombre;
}
void agregarProducto(Producto producto, list<Producto>& productos)
{
	productos.push_front(producto);
}

void eliminarProducto(string& nombre, list<Producto>& productos)
{
	productos.remove_if([&](Producto& p) {return p.getNombre() == nombre; });
}

void imprimirInventario(list<Producto>& productos)
{
	for (Producto producto : productos)
	{
		cout << producto.ToString() << "\n";
	}
}

int main()
{
	list<Producto> inventario;
	agregarProducto(Producto("Ryzen 5 5600x", 1423.32), inventario);
	inventario.push_front(Producto("B450M Asus Prime", 143.00));
	inventario.push_front(Producto("Memoria Ram Kingston 8gb", 1423.32));
	inventario.push_front(Producto("Disco SSD SATA 2.5 inches", 23.32));
	inventario.push_front(Producto("RX 6700 XT XFX 12 gb", 2003.32));
	inventario.push_front(Producto("AeroCool geoflow mid-tower", 142.32));
	inventario.push_front(Producto("Fuente Thermaltake 750w", 300.32));
	string nombreBorrar = "Disco SSD SATA 2.5 inches";
	eliminarProducto(nombreBorrar, inventario);

	imprimirInventario(inventario);

	
}
