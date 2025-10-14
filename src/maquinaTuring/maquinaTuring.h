#pragma once
#include "../alfabeto/alfabeto.h"
#include "../transicion/transicion.h"
#include "../estado/estado.h"
#include <vector> // Para std::vector
#include <algorithm> // Para sort

#ifndef MAQUINATURING_H
#define MAQUINATURING_H

/**
 * @class MaquinaTuring
 * @brief Clase que representa un autómata
 */
class MaquinaTuring {
  public:
    // Constructor y destructor
    MaquinaTuring(const vector<Estado*>& estados, const Alfabeto& alfabetoEntrada, const Alfabeto& alfabetoCinta, int numCintas);
    ~MaquinaTuring() = default;

    // Sobrecarga de operadores
    friend ostream& operator<<(ostream& os, const MaquinaTuring& maquina);

    // Métodos
    bool ejecutar(string cadena);
    bool esValida(const string& cadena) const;
    void reiniciar();
    void mostrarTraza(const string& cadena, const Transicion* transicion);
    Transicion* obtenerTransicionPosible(vector<char> simbolosLeidos);

  private:
    vector<Estado*> estados_;
    Alfabeto alfabetoEntrada_;
    vector<Cinta> cintas_;
    Estado* estadoActual_;
};

#endif // MAQUINATURING_H