

#include <iostream>
#include "Estudiante.h"
int main()
{
	Estudiante estudiante1;
	Estudiante estudiante2;
	Estudiante estudiante3;
	Estudiante estudiante4;
	Estudiante estudiante5;

	estudiante1.setNombre("Alejo");
	estudiante2.setNombre("Maria");
	estudiante3.setNombre("Juan");
	estudiante4.setNombre("Sebastian");
	estudiante5.setNombre("Milagros");
	
	Estudiante estudiantes[5];
	
	estudiantes[0] = estudiante1;
	estudiantes[1] = estudiante2;
	estudiantes[2] = estudiante3;
	estudiantes[3] = estudiante4;
	estudiantes[4] = estudiante5;

	int numeroPresionado;
	cout << "ingrese el indice de estudiante que desea buscar: " << endl;
	while (!(cin >> numeroPresionado) || numeroPresionado < 0 || numeroPresionado > 4)
	{
		cout << "Ingreso Incorrecto. Vuelva a intentarlo";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	
	cout << "Estudiante [ NOMBRE: " << estudiantes[numeroPresionado].getNombre() << " ]";

	return 0;
}
