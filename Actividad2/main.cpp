

#include <iostream>
#include "Tarea.h"
#include <stack>
using namespace std;
// LIFO Last In First Out
int main()
{
	stack<Tarea> tareas;
	tareas.push(Tarea("Pagina principal de youtube\n"));
	tareas.push(Tarea("video 1 de youtube\n"));
	tareas.push(Tarea("video 2 de youtube\n"));
	tareas.push(Tarea("ajustes de youtube\n"));

	cout << "si yo quiero usar el boton de la flechita para atras para regresar a la pagina anterior este seria su camino'\n";
	while (!tareas.empty())
	{
		cout << tareas.top().getDescripcion();
		tareas.pop();
	}

}
