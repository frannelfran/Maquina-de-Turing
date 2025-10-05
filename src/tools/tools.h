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
};

Tools leerFichero(const string& nombreFichero); // Leo el fichero para obtener los datos
void leerEstados(istringstream is); // Leo los estados del fichero
void leerEstadosFinales(istringstream is); // Leo los estados finales del fichero
void leerAlfabeto(istringstream is); // Leo el alfabeto del fichero
void leerTransiciones(istringstream is, int id); // Leo las transiciones del fichero
void comprobarEstado(const string& estado); // Compruebo que el estado es válido
void comprobarSimbolo(const char& simbolo); // Compruebo que el símbolo es válido
void comprobarEscrituraLectura(const char& simbolo); // Compruebo que el símbolo es de escritura/lectura válido
Estado* buscarEstado(const string& estado); // Buscar un estado en el conjunto de estados
void mostrarCabecera(); // Muestro el inicio de la traza

#endif // TOOLS_H