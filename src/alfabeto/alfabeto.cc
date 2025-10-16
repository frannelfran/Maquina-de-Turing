#include "alfabeto.h"

/**
 * @overload Sobrecarga del operador de salida pàra mostrar el alfabeto
 */
ostream& operator<<(ostream& os, const Alfabeto& alfabeto) {
  os << "Σ -> {";
  for (auto it = alfabeto.simbolos_.begin(); it != alfabeto.simbolos_.end(); ++it) {
    os << *it;
    if (next(it) != alfabeto.simbolos_.end()) {
      os << ", ";
    }
  }
  os << "}";
  return os;
}