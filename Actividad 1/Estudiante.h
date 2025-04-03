#pragma once
#include <iostream>
#include <string>
using namespace std;

class Estudiante
{
private:
	string nombre;
public:
	Estudiante() {}
	string getNombre();
	void setNombre(string nombre);

};

