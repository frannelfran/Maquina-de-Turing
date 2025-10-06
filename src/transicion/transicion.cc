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
 * @brief Método para ejecutar la transición
 * @param cinta Cinta de la máquina de Turing
 * @return Estado siguiente después de ejecutar la transición
 */
Estado* Transicion::ejecutar(Cinta& cinta) {
  // Escribo en la cinta
  cinta.escribir(escrituraCinta_);
  
  // Muevo la cabeza de la cinta
  if (movimientoCinta_ == 'R') {
    cinta.moverDerecha();
  } else if (movimientoCinta_ == 'L') {
    cinta.moverIzquierda();
  } // Si es 'S' no hago nada
  
  // Retorno el estado siguiente
  return siguiente_;
}

/**
 * @overload Sobrecarga del operador de salida para imprimir una transición
 */
ostream& operator<<(ostream& os, const Transicion& transicion) {
  os << "(" << transicion.actual_->getId() << ", " << transicion.lecturaCinta_ << ")";
  os << " -> (" << transicion.siguiente_->getId() << ", " << transicion.escrituraCinta_ << ", " << transicion.movimientoCinta_ << ")";
  os << " [ID: " << transicion.id_ << "]";
  return os;
}