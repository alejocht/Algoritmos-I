// BusquedaIndexada.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void busquedaIndexada(vector<int> arreglo, vector<int> indice, int enteroInput)
{
    int bloque = -1;
	for (int i = 0; i < indice.size()-1; i++)
	{
		if (enteroInput >= indice[i] && enteroInput < indice[i + 1])
		{
			bloque = i;
			break;
		}
	}
	if (bloque == -1)
	{
		cout << "Numero no encontrado." << endl;
		return;
	}

	int inicio = bloque * 4;
	int fin = min((int)arreglo.size(), inicio + 4);
	int contador = 0;
	for (int i = inicio; i < fin; i++)
	{
		contador++;
		if (arreglo[i] == enteroInput)
		{
			cout << "Numero encontrado en la posicion: " << i << " Comparaciones Realizadas: " << contador << endl;
			return;
		}
	}

	cout << "Numero no encontrado. Comparaciones Realizadas: " << contador << endl;
}

int main()
{
	vector<int> numeros = { 1,2,3,4,5,6,7,8,9,10};
	vector<int> indice = { 1,5,9,13};
	int clave;

	while (true)
	{
		cout << "Ingrese un numero: \n";
		cin >> clave;
		busquedaIndexada(numeros, indice, clave);
	}
	return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
