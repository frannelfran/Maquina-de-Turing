#pragma once
#include "../alfabeto/alfabeto.h"
#include "../transicion/transicion.h" // Incluir primero Transicion
#include "../estado/estado.h"         // Luego Estado
#include <fstream> // Para manejo de archivos
#include <stdexcept> // Para las excepciones
#include <sstream> // Para istringstream

#ifndef TOOLS_H
#define TOOLS_H

/**
 * @struct Tools
 * @brief Estructura para almacenar los datos del fichero de entrada
 */
struct Tools {
  pair<Alfabeto, Alfabeto> alfabetos;
  vector<Estado*> estados;
  int numCintas = 1;
};

Tools leerFichero(const string& nombreFichero); // Leo el fichero para obtener los datos
void leerEstados(istringstream is); // Leo los estados del fichero
void leerEstadosFinales(istringstream is); // Leo los estados finales del fichero
void leerAlfabeto(istringstream is); // Leo el alfabeto del fichero
void leerTransiciones(istringstream is, int id, int numCintas); // Leo las transiciones del fichero
void comprobarEstado(const string& estado); // Compruebo que el estado es válido
void comprobarSimboloCinta(const char& simbolo); // Compruebo que el símbolo es válido
void comprobarEscrituraLectura(const char& simbolo); // Compruebo que el símbolo es de escritura/lectura válido
vector<char> leerSimbolosLectura(istringstream& is, int numCintas); // Leo los simbolos de lectura de las cintas
vector<pair<char, char>> leerMovimientos(istringstream& is, int numCintas); // Leo los movimientos junto con los simbolos de escritura
Estado* buscarEstado(const string& estado); // Buscar un estado en el conjunto de estados

#endif // TOOLS_H