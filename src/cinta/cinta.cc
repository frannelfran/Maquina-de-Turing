#include "cinta.h"

/**
 * @brief Método para insertar una cadena en la cinta
 * @param cadena Cadena a insertar
 * @return void
 */
void Cinta::insertar(const string& cadena) {
  for (char simbolo : cadena) {
    if (!pertenece(simbolo)) {
      throw invalid_argument("El símbolo '" + string(1, simbolo) + "' no pertenece al alfabeto de la cinta.");
    } else {
      cinta_.push_back(simbolo);
    }
  }
}

/**
 * @brief Método para comprobar el cabezal y ajustar la cinta si es necesario
 * @return void
 */
void Cinta::comprobarCabezal() {
  if (cabezal_ < 0) {
    cinta_.insert(cinta_.begin(), '_'); // Añadir blanco si nos salimosm por la izquierda
    cabezal_ = 0;
    desplazamiento_++;
  } else if (cabezal_ >= cinta_.size()) {
    cinta_.push_back('_'); // Añadir blanco si nos salimos por la derecha
    cabezal_ = cinta_.size() - 1;
    desplazamiento_++;
  }
}

/**
 * @brief Método para lee el simbolo en la posicion actual del cabezal
 * @return char simbolo en la posicion actual del cabezal
 */
char Cinta::leer() {
  comprobarCabezal(); // Compruebo el cabezal antes de leer
  return cinta_[cabezal_];
}

/**
 * @brief Método para escribir un simbolo en la cinta en la posicion actual del cabezal
 * @param simbolo simbolo a escribir
 * @return void
 */
void Cinta::escribir(char simbolo) {
  comprobarCabezal(); // Compruebo el cabezal antes de escribir
  cinta_[cabezal_] = simbolo;
}

/**
 * @brief Método para mover el cabezal a la derecha
 * @return void
 */
void Cinta::moverDerecha() {
  cabezal_++;
  comprobarCabezal(); // Compruebo el cabezal después de mover
}

/**
 * @brief Método para mover el cabezal a la izquierda
 * @return void
 */
void Cinta::moverIzquierda() {
  cabezal_--;
  comprobarCabezal(); // Compruebo el cabezal después de mover
}

/**
 * @overload Sobrecarga del operador <<
 */
ostream& operator<<(ostream& os, const Cinta& cinta) {
  for (int i = 0; i < cinta.cinta_.size(); ++i) {
    if (i == cinta.cabezal_) {
      os << "[" << cinta.cinta_[i] << "]"; // Indicar la posicion del cabezal
    } else {
      os << cinta.cinta_[i];
    }
  }
  return os;
}