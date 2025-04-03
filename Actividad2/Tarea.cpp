#include "Tarea.h"

Tarea::Tarea(std::string descripcion) { this->descripcion = descripcion; }
std::string Tarea::getDescripcion() { return this->descripcion; }
void Tarea::setDescripcion(std::string descripcion) { this->descripcion = descripcion; }
