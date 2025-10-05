#include "transicion.h"
#include "../estado/estado.h"

/**
 * @brief Constructor de la clase Transicion
 * @param id Identificador de la transición
 * @param actual Estado actual desde el cual se realiza la transición
 * @param lecturaCinta Símbolo que se lee en la cinta
 * @param siguiente Estado al cual se transita
 * @param escrituraCinta Símbolo que se escribe en la cinta
 * @param movimientoCinta Movimiento de la cabeza de la cinta ('L' para izquierda, 'R' para derecha)
 */
Transicion::Transicion(const int& id, Estado* actual, const char& lecturaCinta, Estado* siguiente, const char& escrituraCinta, const char& movimientoCinta) {
  id_ = id;
  actual_ = actual;
  lecturaCinta_ = lecturaCinta;
  siguiente_ = siguiente;
  escrituraCinta_ = escrituraCinta;
  movimientoCinta_ = movimientoCinta;
}

/**
 * @overload Sobrecarga del operador de salida para imprimir una transición
 */
ostream& operator<<(ostream& os, const Transicion& transicion) {
  os << "(" << transicion.actual_->getId() << ", " << transicion.lecturaCadena_ << ", " << transicion.lecturaPila_ << ") -> (" 
     << transicion.siguiente_->getId() << ", " << transicion.apilar_ << ") " << transicion.id_;
  return os;
}