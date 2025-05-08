
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void buscarProductoSecuencial(string lista[], int tam, string productoBuscado)
{
	int contador = 0;
	for (int i = 0; i < tam; i++)
	{
		contador++;
		if (lista[i] == productoBuscado)
		{
			cout << "Producto encontrado en el indice: " << i << ". Comparaciones realizadas: " << contador <<".";
			return;
		}
	}
	cout << "Producto no encontrado. Comparaciones realizadas: " << contador <<".";
	return;
}

void buscarProductoBusquedaBinaria(string lista[], int inicio, int final, string productoBuscado)
{
	//mientras que el inicio sea menor o igual al final
	int contador = 0;
	while (inicio <= final)
	{
		contador++;
		//calculamos el medio
		int medio = inicio + (final - inicio) / 2;
		//evaluamos si nuestro producto es el medio
		if (lista[medio] == productoBuscado)
		{
			cout << "Producto encontrado en el indice: " << medio << ". Comparaciones realizadas: " << contador << ".";
			return;
		}
		if (lista[medio] < productoBuscado)
		{
		    //si el valor que queremos es mas grande que el valor medio, tenemos que situar el inicio despues del medio
			inicio = medio + 1;
		}
		else
		{
			//si el valor que queremos es mas chico que el valor medio, tenemos que situar el final despues del medio
			final = medio - 1;
		}
	}
	cout << "Producto no encontrado. Comparaciones realizadas: " << contador << ".";
	return;
}

int main()
{
	string productos[] = { "Coca Cola", "Arroz","Leche","Huevo","Papel Higienico","Servilleta", "Detergente", "Lavandina", "Bateria AA" };
	int tam = sizeof(productos) / sizeof(productos[0]);
	sort(productos, productos + tam);
	string productoInput;
	while (true)
	{
		cout << "Ingrese el nombre del producto que desea buscar: \n";
		cin >> productoInput;
		cout << "\n------------------------Resultado Secuencial--------------------------------\n";
		buscarProductoSecuencial(productos, tam, productoInput);
		cout << "\n------------------------Resultado Busqueda Binaria--------------------------\n";
		buscarProductoBusquedaBinaria(productos, 0, tam-1, productoInput);
		cout << "\n----------------------------------------------------------------------------\n";
	}

}
