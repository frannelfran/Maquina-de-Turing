#include "maquinaTuring.h"

/**
 * @brief Constructor de la clase MaquinaTuring
 * @param estados Conjunto de estados del autómata
 * @param alfabetoEntrada Alfabeto de entrada del autómata
 * @param alfabetoPila Alfabeto de la pila del autómata
 * @param topPila Símbolo inicial de la pila
 */
MaquinaTuring::MaquinaTuring(const vector<Estado*>& estados, const Alfabeto& alfabetoEntrada, const Alfabeto& alfabetoCinta) {
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
bool MaquinaTuring::ejecutar(string cadena) {
  // Compruebo si la cadena es válida
  if (!esValida(cadena)) {
    cerr << "Error: La cadena contiene símbolos que no pertenecen al alfabeto de entrada." << endl;
    return false;
  }

  // Inserto la cadena en la cinta
  cinta_.insertar(cadena);

  while (true) {
    char simboloLeido = cinta_.leer();

    // Obtengo la transicion para ese simbolo
    Transicion* transicion = obtenerTransicionPosible(simboloLeido);

    if (transicion == nullptr) {
      // No hay transicion posible
      return false;
    }

    // Ejecuto la transicion
    estadoActual_ = transicion->ejecutar(cinta_);

    if (estadoActual_->esAceptacion()) {
      return true;
    }
  }
}

/**
 * @brief Método para obtener las transiciones posibles desde el estado actual
 * @param simbolo Cadena de entrada
 * @return Transición posible o nullptr si no hay ninguna
 */
Transicion* MaquinaTuring::obtenerTransicionPosible(char simbolo) {
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
//void MaquinaTuring::mostrarTraza(const string& cadena, const vector<Transicion*>& transiciones) {
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
void MaquinaTuring::reiniciar() {
  // Reinicio el estado actual al estado inicial
  for (Estado* estado : estados_) {
    if (estado->esInicial()) {
      estadoActual_ = estado;
      break;
    }
  }
  cinta_.limpiar();
}

/**
 * @brief Método para comprobar si una cadena es válida para el autómata
 * @param cadena Cadena de entrada
 * @return true si la cadena es válida, false en caso contrario
 */
bool MaquinaTuring::esValida(const string& cadena) const {
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
ostream& operator<<(ostream& os, const MaquinaTuring& MaquinaTuring) {
  os << "Q -> {";
  for (auto it = MaquinaTuring.estados_.begin(); it != MaquinaTuring.estados_.end(); ++it) {
    os << (*it)->getId();
    if (next(it) != MaquinaTuring.estados_.end()) {
      os << ", ";
    }
  }
  os << "}" << endl;
  os << "Σ -> " << MaquinaTuring.alfabetoEntrada_ << endl;
  os << "Γ -> " << MaquinaTuring.cinta_.getAlfabeto() << endl;
  os << "q0 -> " << MaquinaTuring.estadoActual_->getId() << endl;
  os << "F -> {";
  for (auto it = MaquinaTuring.estados_.begin(); it != MaquinaTuring.estados_.end(); ++it) {
    if ((*it)->esAceptacion()) {
      os << (*it)->getId();
      if (next(it) != MaquinaTuring.estados_.end()) {
        os << ", ";
      }
    }
  }
  os << "}" << endl;
  
  // Transiciones
  for (Estado* estado : MaquinaTuring.estados_) {
    os << *estado << endl;
  }
  return os;
}