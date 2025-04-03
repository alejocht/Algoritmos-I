#pragma once
#include <iostream>
class Tarea
{
private:
	std::string descripcion;
public:
	Tarea(std::string descripcion);
	std::string getDescripcion();
	void setDescripcion(std::string descripcion);
};

