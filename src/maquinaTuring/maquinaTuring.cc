#include "maquinaTuring.h"

/**
 * @brief Constructor de la clase MaquinaTuring
 * @param estados Conjunto de estados del autómata
 * @param alfabetoEntrada Alfabeto de entrada del autómata
 * @param alfabetoPila Alfabeto de la pila del autómata
 * @param topPila Símbolo inicial de la pila
 */
MaquinaTuring::MaquinaTuring(const vector<Estado*>& estados, const Alfabeto& alfabetoEntrada, const Alfabeto& alfabetoCinta, int numCintas) {
  estados_ = estados;
  sort(estados_.begin(), estados_.end(), [](Estado* a, Estado* b) { return *a < *b; });
  alfabetoEntrada_ = alfabetoEntrada;
  // Inicializo las cintas
  cintas_.resize(numCintas, Cinta(alfabetoCinta));
  if (numCintas > 1) {
    for (int i = 1; i < numCintas; ++i) {
      cintas_[i].insertar("."); // Relleno las cintas adicionales con un blanco
    }
  }

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

  // Inserto la cadena en la cinta 1
  cintas_[0].insertar(cadena);

  while (true) {
    // Leo los simbolos de las cintas
    vector<char> simbolosLeidos;
    for (Cinta& cinta : cintas_) {
      simbolosLeidos.push_back(cinta.leer());
    }

    // Obtengo la transicion para ese simbolo
    Transicion* transicion = obtenerTransicionPosible(simbolosLeidos);

    // Muestro la traza
    mostrarTraza(cadena, transicion);

    if (transicion == nullptr) {
      // No hay transicion posible
      return false;
    }

    // Ejecuto la transicion
    estadoActual_ = transicion->ejecutar(cintas_);

    if (estadoActual_->esAceptacion()) {
      mostrarTraza(cadena, nullptr);
      return true;
    }
  }
}

/**
 * @brief Método para obtener las transiciones posibles desde el estado actual
 * @param simbolosLeidos Símbolos leídos en las cintas
 * @return Transición posible o nullptr si no hay ninguna
 */
Transicion* MaquinaTuring::obtenerTransicionPosible(vector<char> simbolosLeidos) {
  Transicion* transicionPosible = nullptr;

  for (auto& transicion : estadoActual_->getTransiciones()) {
    if (transicion.esAplicable(simbolosLeidos)) {
      transicionPosible = &transicion;
      break;
    }
  }
  return transicionPosible;
}

/**
 * @brief Método para mostrar la traza de la ejecución del autómata
 * @param cadena Cadena de entrada
 * @param transicion Transición actual
 * @return void
 */
void MaquinaTuring::mostrarTraza(const string& cadena, const Transicion* transicion) {
  // Luego muestro el estado actual
  cout << left << setw(20) << estadoActual_->getId();

  // Primero muestro el id de la transición
  if (transicion == nullptr) {
    cout << setw(15) << "-" ;
  } else {
    cout << setw(15) << transicion->getId();
  }


  // Muestro las cintas
  for (size_t i = 0; i < cintas_.size(); ++i) {
    cout << setw(15) << cintas_[i];
  }
  cout << endl;
  cout << "-------------------------------------------------" << endl;
}

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
  
  // Limpio las cintas
  for (Cinta& cinta : cintas_) {
    cinta.limpiar();
  }
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
  os << "Γ -> " << MaquinaTuring.cintas_[0].getAlfabeto() << endl;
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