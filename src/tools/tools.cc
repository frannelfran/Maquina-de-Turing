#include "tools.h"

static Tools datos; // Variable global para almacenar los datos leídos

/**
 * @brief Dunción para leer el fichero de entrada y almacenar los datos en una estructura Tools
 * @param nombreFichero Nombre del fichero de entrada
 * @return Estructura Tools con los datos del fichero
 */
Tools leerFichero(const string& nombreFichero) {
  ifstream file(nombreFichero);

  if (!file.is_open()) { // Comprobar la lectura del fichero
    throw runtime_error("No se pudo abrir el fichero: " + nombreFichero);
  }

  string linea;
  // Saltar los comentarios y líneas vacías
  while (getline(file, linea)) {
    if (linea.empty() || linea[0] == '#') {
      continue;
    }
    break;
  }
  // Leo los estados
  leerEstados(istringstream(linea));

  // Leo el alfabeto de entrada
  getline(file, linea);
  leerAlfabeto(istringstream(linea));

  // Leo el alfabeto de la cinta
  getline(file, linea);
  leerAlfabeto(istringstream(linea));

  // Leo el estado inicial
  getline(file, linea);
  comprobarEstado(linea);
  for (Estado* estado : datos.estados) {
    if (estado->getId() == linea) {
      estado->setInicial();
      break;
    }
  }

  // Leo el simbolo blanco de la máquina
  getline(file, linea);
  comprobarSimboloCinta(linea[0]);

  // Leo el conjunto de estados finales
  getline(file, linea);
  leerEstadosFinales(istringstream(linea));

  // Leo las transiciones y el número de cintas
  datos.numCintas = getline(file, linea) ? stoi(linea) : 1;
  int id = 1;
  while (getline(file, linea)) {
    if (linea.empty() || linea[0] == '#') {
      continue;
    }
    leerTransiciones(istringstream(linea), id++, datos.numCintas);
  }
  return datos;
}

/**
 * @brief Función para leer el conjunto de estados
 * @param is Stream de entrada
 * @return void
 */
void leerEstados(istringstream is) {
  string linea;
  vector<Estado*> estados;
  while (is >> linea) {
    estados.push_back(new Estado(linea));
  }
  datos.estados = estados;
}

/**
 * @brief Funci´pn para leer los estados finales del fichero
 * @param is Stream de entrada
 * @return void
 */
void leerEstadosFinales(istringstream is) {
  string linea;
  while (is >> linea) {
    comprobarEstado(linea);
    for (Estado* estado : datos.estados) {
      if (estado->getId() == linea) {
        if (estado->esInicial()) {
          throw runtime_error("El estado " + linea + " es inicial y no puede ser de aceptación.");
        } else {
          estado->setAceptacion();
        }
      }
    }
  }
}

/**
 * @brief Función para leer los alfabetos del fichero
 * @param is Stream de entrada
 * @return void
 */
void leerAlfabeto(istringstream is) {
  string linea;
  Alfabeto alfabeto;
  while (is >> linea) {
    alfabeto.insertar(linea[0]);
  }
  if (datos.alfabetos.first.size() == 0) {
    datos.alfabetos.first = alfabeto;
  } else {
    datos.alfabetos.second = alfabeto;
  }
}

/**
 * @brief Función para leer las transiciones del fichero
 * @param is Stream de entrada
 * @param id Identificador de la transición
 * @return void
 */
void leerTransiciones(istringstream is, int id, int numCintas) {
  string actual, siguiente;
  vector<char> lecturaCintas, escrituraCintas, movimientoCintas;
  is >> actual;

  // Leo los simbolos de lectura
  for (int i = 0; i < numCintas; ++i) {
    char simbolo;
    is >> simbolo;
    comprobarSimboloCinta(simbolo);
    lecturaCintas.push_back(simbolo);
  }

  is >> siguiente;

  // Leo los simbolos de escritura
  for (int i = 0; i < numCintas; ++i) {
    char simbolo;
    is >> simbolo;
    comprobarSimboloCinta(simbolo);
    escrituraCintas.push_back(simbolo);
  }

  // Leo los simbolos de movimiento
  for (int i = 0; i < numCintas; ++i) {
    char simbolo;
    is >> simbolo;
    comprobarEscrituraLectura(simbolo);
    movimientoCintas.push_back(simbolo);
  }

  // Compruebo que el/los estado/s final no tiene/n transiciones
  for (Estado* e : datos.estados) {
    if (e->getId() == actual && e->esAceptacion()) {
      throw runtime_error("El estado " + actual + " es de aceptación y no puede tener transiciones.");
    }
  }
  // Compruebo los estados
  comprobarEstado(actual), comprobarEstado(siguiente);
  // Busco el estado inicial y siguiente en el conjunto de estados
  Estado* estadoSiguiente = buscarEstado(siguiente), *estadoActual = buscarEstado(actual);
  // Creo la transición y la agrego la transicion
  Transicion transicion(id, estadoActual, lecturaCintas, estadoSiguiente, escrituraCintas, movimientoCintas);
  for (Estado* e : datos.estados) {
    if (e->getId() == actual) {
      e->agregarTransicion(transicion);
      break;
    }
  }
}

/**
 * @brief Método para buscar un estado en el conjunto de estados
 * @param estado Estado a buscar
 * @return Puntero al estado si se encuentra, nullptr en caso contrario
 */
Estado* buscarEstado(const string& estado) {
  for (Estado* e : datos.estados) {
    if (e->getId() == estado) {
      return e;
    }
  }
  return nullptr;
}


/**
 * @brief Función para combrobar que los estados pertencen al conjunto de estados
 * @param actual Estado actual
 * @param siguiente Estado siguiente
 * @return void
 */
void comprobarEstado(const string& estado) {
  bool encontrado = false;
  for (Estado* e : datos.estados) {
    if (e->getId() == estado) {
      encontrado = true;
    }
  }

  if (!encontrado) {
    cerr << "Q -> {";
    for (auto it = datos.estados.begin(); it != datos.estados.end(); ++it) {
      cerr << (*it)->getId();
      if (next(it) != datos.estados.end()) {
        cerr << ", ";
      }
    }
    cerr << "}" << endl;
    throw runtime_error("El estado " + estado + " no está en el conjunto de estados.");
  }
}

/**
 * @brief Comprueba que un símbolo pertenece al alfabeto de entrada (Σ)
 */
void comprobarSimboloCinta(const char& simbolo) {
  if (simbolo == '.') return; // epsilon siempre permitido en lectura de cadena
  if (!datos.alfabetos.second.pertenece(simbolo)) {
    cerr << "Γ -> " << datos.alfabetos.second << endl;
    throw runtime_error(string("El símbolo '") + simbolo + "' no pertenece al alfabeto de la cinta (Γ).");
  }
}

/**
 * @brief Función para comprobar que el simbolo de escritura/lectura es el correcto
 * @param simbolo Símbolo a comprobar
 * @return void
 */
void comprobarEscrituraLectura(const char& simbolo) {
  if (simbolo != 'R' && simbolo != 'L' && simbolo != 'S') {
    throw runtime_error("El símbolo '" + string(1, simbolo) + "' no es un símbolo de escritura/lectura válido.");
  }
}

/**
 * @brief Función para mostrar la cabecera de la traza
 * @return void
 */
void mostrarCabecera() {
  cout << "-------------------------------------------------" << endl;
  cout << left;
  cout << setw(20) << "Estado actual" 
  << setw(15) << "Cinta"
  << setw(15) << "Transicion" << endl;
  cout << "-------------------------------------------------" << endl;
}