#pragma once
#include "../alfabeto/alfabeto.h"
#include "../transicion/transicion.h"
#include "../estado/estado.h"
#include <iomanip> // Para std::setw
#include <vector> // Para std::vector
#include <algorithm> // Para sort

#ifndef AUTOMATA_H
#define AUTOMATA_H

/**
 * @class Automata
 * @brief Clase que representa un autómata
 */
class Automata {
  public:
    // Constructor y destructor
    Automata(const vector<Estado*>& estados, const Alfabeto& alfabetoEntrada, const Alfabeto& alfabetoCinta);
    ~Automata() = default;

    // Sobrecarga de operadores
    friend ostream& operator<<(ostream& os, const Automata& automata);

    // Métodos
    bool ejecutar(string cadena);
    bool esValida(const string& cadena) const;
    void reiniciar();
    void mostrarTraza(const string& cadena, const vector<Transicion*>& transiciones) {}
    vector<Transicion*> obtenerTransicionesPosibles(char simbolo, vector<Transicion*> transicionesUsadas);

  private:
    vector<Estado*> estados_;
    Alfabeto alfabetoEntrada_;
    Alfabeto alfabetoCinta_;
    Cinta cinta_;
    Estado* estadoActual_;
};

#endif // AUTOMATA_H