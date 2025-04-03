
#include <iostream>
#include <queue>
using namespace std;



class Turno
{
private:
    string nombreDoctor;
    string nombrePaciente;
public:
    Turno(string medico, string paciente) { this->nombreDoctor = medico; this->nombrePaciente = paciente; }
    string ToString() { return  "TURNO [ Nombre Medico: " + this->nombreDoctor + " Nombre Paciente: " + this->nombrePaciente + " ]\n";}
};

int main()
{
    queue<Turno> cola;
    cola.push(Turno("Dr. Fernandez", "Gomez Silvana"));
    cola.push(Turno("Dr. Fernandez", "Lopez Juan"));
    cola.push(Turno("Dr. Fernandez", "Mendoza Sebastian"));
    cola.push(Turno("Dr. Fernandez", "Montes Alfredo"));
    cola.push(Turno("Dr. Fernandez", "Beder German"));

    cout << "Orden de Atencion:\n";
    while (!cola.empty())
    {
        cout << cola.front().ToString();
        cola.pop();
    }
}
