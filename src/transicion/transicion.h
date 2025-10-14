#pragma once
#include "../cinta/cinta.h"
#include <string>

#ifndef TRANSICION_H
#define TRANSICION_H

using namespace std;

// Para evitar errores con la dependencia circular
class Estado;

/**
 * @class Transicion
 * @brief Clase que representa una transición en una Máquina de Turing
 */
class Transicion {
  public:
    // Constructor y destructor
    Transicion() = default;
    Transicion(const int& id, Estado* actual, const vector<char>& lecturaCinta, Estado* siguiente, const vector<char>& escrituraCinta, const vector<char>& movimientoCinta);
    ~Transicion() = default;

    // Getters
    inline vector<char> getLecturaCintas() const { return lecturaCintas_; }
    inline vector<char> getEscrituraCintas() const { return escrituraCintas_; }
    inline vector<char> getMovimientoCintas() const { return movimientoCintas_; }
    inline int getId() const { return id_; }

    // Métodos
    Estado* ejecutar(vector<Cinta>& cintas);

    // Sobrecarga de operadores
    friend ostream& operator<<(ostream& os, const Transicion& transicion);

  private:
    int id_;
    vector<char> lecturaCintas_;
    vector<char> escrituraCintas_;
    vector<char> movimientoCintas_; // 'L' (izquierda), 'R' (derecha), 'S' (sin movimiento)
    Estado* actual_;
    Estado* siguiente_;
};

#endif // TRANSICION_H