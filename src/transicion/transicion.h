#pragma once
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
    Transicion(const int& id, Estado* actual, const char& lecturaCinta, Estado* siguiente, const char& escrituraCinta, const char& movimientoCinta);
    ~Transicion() = default;

    // Getters
    inline char getLecturaCinta() const { return lecturaCinta_; }
    inline char getEscrituraCinta() const { return escrituraCinta_; }
    inline char getMovimientoCinta() const { return movimientoCinta_; }
    inline int getId() const { return id_; }

    // Métodos
    Estado* ejecutar(Cinta& cinta);

    // Sobrecarga de operadores
    friend ostream& operator<<(ostream& os, const Transicion& transicion);

  private:
    int id_;
    char lecturaCinta_;
    char escrituraCinta_;
    char movimientoCinta_; // 'L' (izquierda), 'R' (derecha)
    Estado* actual_;
    Estado* siguiente_;
};

#endif // TRANSICION_H