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
Transicion::Transicion(const int& id, Estado* actual, const vector<char>& lecturaCinta, Estado* siguiente, const vector<char>& escrituraCinta, const vector<char>& movimientoCinta) {
  id_ = id;
  actual_ = actual;
  lecturaCintas_ = lecturaCinta;
  siguiente_ = siguiente;
  escrituraCintas_ = escrituraCinta;
  movimientoCintas_ = movimientoCinta;
}

/**
 * @brief Método para ejecutar la transición
 * @param cintas Cintas de la máquina de Turing
 * @return Estado siguiente después de ejecutar la transición
 */
Estado* Transicion::ejecutar(vector<Cinta>& cintas) {
  for (auto& cinta : cintas) {
    cinta.comprobarCabezal(); // Compruebo el cabezal antes de escribir
  }

  // Escribo en las cintas y muevo el cabezal
  for (size_t i = 0; i < cintas.size(); ++i) {
    cintas[i].escribir(escrituraCintas_[i]);
  }

  // Muevo los cabezales
  for (size_t i = 0; i < cintas.size(); ++i) {
    if (movimientoCintas_[i] == 'R') {
      cintas[i].moverDerecha();
    } else if (movimientoCintas_[i] == 'L') {
      cintas[i].moverIzquierda();
    } // Si es 'S' no hago nada
  }

  return siguiente_;
}

/**
 * @brief Método para comprobar si la transición es aplicable
 * @param simbolosLeidos Símbolos leídos en las cintas
 * @return true si la transición es aplicable, false en caso contrario
 */
bool Transicion::esAplicable(const vector<char>& simbolosLeidos) const {
  for (size_t i = 0; i < lecturaCintas_.size(); ++i) {
    if (lecturaCintas_[i] == simbolosLeidos[i]) {
      continue;
    }
    return false;
  }
  return true;
}

/**
 * @overload Sobrecarga del operador de salida para imprimir una transición
 */
ostream& operator<<(ostream& os, const Transicion& transicion) {
  os << "δ(" << transicion.actual_->getId() << ", ";
  // Muestro los simbolos de lectura
  for (size_t i = 0; i < transicion.lecturaCintas_.size(); ++i) {
    os << transicion.lecturaCintas_[i];
    if (i < transicion.lecturaCintas_.size() - 1) {
      os << ",";
    }
  }
  os << ") -> (" << transicion.siguiente_->getId() << ", ";
  // Muestro los simbolos de escritura
  for (size_t i = 0; i < transicion.escrituraCintas_.size(); ++i) {
    os << transicion.escrituraCintas_[i];
    if (i < transicion.escrituraCintas_.size() - 1) {
      os << ",";
    }
  }

  // Muestro los movimientos
  os << ", ";
  for (size_t i = 0; i < transicion.movimientoCintas_.size(); ++i) {
    os << transicion.movimientoCintas_[i];
    if (i < transicion.movimientoCintas_.size() - 1) {
      os << ",";
    }
  }
  os << ") ID: " << transicion.id_;
  
  return os;
}