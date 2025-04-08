
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

void agregarConexion(unordered_map<string, vector<pair<string, int>>>* grafo, string ciudad1, string ciudad2, int kilometros)
{
    (*grafo)[ciudad1].push_back(make_pair(ciudad2, kilometros));
    (*grafo)[ciudad2].push_back(make_pair(ciudad1, kilometros));
}

void mostrarGrafo(unordered_map<string, vector<pair<string, int>>>* grafo)
{
    for (auto ciudad : (*grafo))
    {
        //first guarda la clave string de ciudad
        cout << ciudad.first << " esta conectada con:\n";
        //second guarda el vector de pares ciudad-km
        for (auto conexion : ciudad.second)
        {
            cout << " -" << conexion.first << " (" << conexion.second << " Km)\n";
        }
        cout << endl;
    }
}

int main()
{
    unordered_map<string,vector<pair<string, int>>> grafo;

    agregarConexion(&grafo, "Madrid", "Barcelona", 620);
    agregarConexion(&grafo, "Madrid", "Valencia", 350);
    agregarConexion(&grafo, "Madrid", "Sevilla", 530);
    agregarConexion(&grafo, "Barcelona", "Sevilla", 1000);

    mostrarGrafo(&grafo);

}
