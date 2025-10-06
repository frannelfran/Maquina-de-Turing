#include "automata.h"

/**
 * @brief Constructor de la clase Automata
 * @param estados Conjunto de estados del autómata
 * @param alfabetoEntrada Alfabeto de entrada del autómata
 * @param alfabetoPila Alfabeto de la pila del autómata
 * @param topPila Símbolo inicial de la pila
 */
Automata::Automata(const vector<Estado*>& estados, const Alfabeto& alfabetoEntrada, const Alfabeto& alfabetoCinta) {
  estados_ = estados;
  sort(estados_.begin(), estados_.end(), [](Estado* a, Estado* b) { return *a < *b; });
  alfabetoEntrada_ = alfabetoEntrada;
  cinta_ = Cinta(alfabetoCinta);

  // Inicializo el estado actual al estado inicial
  for (Estado* estado : estados_) {
    if (estado->esInicial()) {
      estadoActual_ = estado;
      break;
    }
  }
}

/**
 * @brief Método para ejecutar el autómata con una cadena de entrada
 * @param cadena Cadena de entrada
 * @return true si la cadena es aceptada, false en caso contrario
 */
bool Automata::ejecutar(string cadena) {
  return true;
}

/**
 * @brief Método para obtener las transiciones posibles desde el estado actual
 * @param simbolo Cadena de entrada
 * @return Transición posible o nullptr si no hay ninguna
 */
Transicion* Automata::obtenerTransicionesPosibles(char simbolo) {
  Transicion* transicionPosible = nullptr;
  
  for (auto& transicion : estadoActual_->getTransiciones()) {
    if (transicion.getLecturaCinta() == simbolo || transicion.getLecturaCinta() == '.') {
      transicionPosible = &transicion;
      break;
    }
  }
  return transicionPosible;
}

/**
 * @brief Método para mostrar la traza de la ejecución del autómata
 * @param cadena Cadena de entrada
 * @param transiciones Vector de transiciones disponibles
 * @return void
 */
//void Automata::mostrarTraza(const string& cadena, const vector<Transicion*>& transiciones) {
//  cout << left
//  << setw(15) << estadoActual_->getId()
//  << setw(15) << (cadena.empty() ? "-" : cadena)
//  << setw(15) << (pilaStr.empty() ? "-" : pilaStr);
//
//  if (transiciones.empty()) {
//    // Miro si es la transición final
//    if (cadena.empty() && pila_.empty()) {
//      cout << setw(15) << "w∈L";
//    } else {
//      cout << setw(15) << "∄";
//    }
//    cout << "\n------------------------------------------------------------" << endl;
//    return;
//  }
//
//  // Mostrar las transiciones posibles
//  for (auto it = transiciones.begin(); it != transiciones.end(); ++it) {
//    cout << left
//    << setw(0) << (*it)->getId();
//    if (next(it) != transiciones.end()) {
//      cout << ", ";
//    }
//  }
//  cout << "\n------------------------------------------------------------" << endl;
//}

/**
 * @brief Método para reiniciar el autómata a su estado inicial
 * @return void
 */
void Automata::reiniciar() {
  // Reinicio el estado actual al estado inicial
  for (Estado* estado : estados_) {
    if (estado->esInicial()) {
      estadoActual_ = estado;
      break;
    }
  }
}

/**
 * @brief Método para comprobar si una cadena es válida para el autómata
 * @param cadena Cadena de entrada
 * @return true si la cadena es válida, false en caso contrario
 */
bool Automata::esValida(const string& cadena) const {
  for (char simbolo : cadena) {
    if (!alfabetoEntrada_.pertenece(simbolo) && simbolo != '.') {
      return false;
    }
  }
  return true;
}

/**
 * @overload Sobrecarga del operador << para mostrar el autómata
 */
ostream& operator<<(ostream& os, const Automata& automata) {
  os << "Q -> {";
  for (auto it = automata.estados_.begin(); it != automata.estados_.end(); ++it) {
    os << (*it)->getId();
    if (next(it) != automata.estados_.end()) {
      os << ", ";
    }
  }
  os << "}" << endl;
  os << "Σ -> " << automata.alfabetoEntrada_ << endl;
  os << "Γ -> " << automata.cinta_.getAlfabeto() << endl;
  os << "q0 -> " << automata.estadoActual_->getId() << endl;
  os << "F -> {";
  for (auto it = automata.estados_.begin(); it != automata.estados_.end(); ++it) {
    if ((*it)->esAceptacion()) {
      os << (*it)->getId();
      if (next(it) != automata.estados_.end()) {
        os << ", ";
      }
    }
  }
  os << "}" << endl;
  
  // Transiciones
  for (Estado* estado : automata.estados_) {
    os << *estado << endl;
  }
  return os;
}