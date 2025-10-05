#pragma once
#include <iostream>
#include <vector>
#include "../transicion/transicion.h" // Incluir primero Transicion

#ifndef ESTADO_H
#define ESTADO_H

using namespace std;

/**
 * @class Estado
 * @brief Clase que representa un estado en un autómata
 */
class Estado {
  public:
    // Constructor y destructor
    Estado() = default;
    Estado(const string& id, const bool& inicial = false, const bool& aceptacion = false) : id_(id), inicial_(inicial), aceptacion_(aceptacion) {}

    // Getters
    inline string getId() const { return id_; }
    inline bool esInicial() const { return inicial_; }
    inline bool esAceptacion() const { return aceptacion_; }
    inline vector<Transicion>& getTransiciones() { return transiciones_; }

    // Setters
    inline void setInicial() { inicial_ = true; }
    inline void setAceptacion() { aceptacion_ = true; }

    // Métodos
    void agregarTransicion(const Transicion& transicion);

    // Sobrecarga de operadores
    friend ostream& operator<<(ostream& os, const Estado& estado);
    friend bool operator<(const Estado& e, const Estado& other) { return e.id_ < other.id_; }

  private:
    string id_;
    vector<Transicion> transiciones_;
    bool inicial_;
    bool aceptacion_;
};

#endif // ESTADO_H