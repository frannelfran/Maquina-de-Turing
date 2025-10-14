#include "tools/tools.h"
#include "maquinaTuring/maquinaTuring.h"
#include <iostream>

using namespace std;

/**
 * @brief Función principal del programa
 * @param argc Número de argumentos
 * @param argv Vector de argumentos
 * @return Código de salida
 */

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Uso: " << argv[0] << " <fichero_entrada>" << endl;
    return 1;
  }

  try {
    string nombreFichero = argv[1];
    Tools datos = leerFichero(nombreFichero);
    cout << "Fichero leído correctamente." << endl;
    // Creo la máquina de Turing con los datos leídos
    MaquinaTuring mt(datos.estados, datos.alfabetos.first, datos.alfabetos.second, datos.numCintas);
    
    cout << mt;
    string cadena;
    
    while (true) {
      cout << "Cadena ? (0 para salir) ";
      cin >> cadena;
      if (cadena == "0") {
        break;
      }
      mostrarCabecera();
      if (mt.ejecutar(cadena)) {
        cout << "La cadena " << cadena << " pertenece al lenguaje." << endl;
      } else {
        cout << "La cadena " << cadena << " no pertenece al lenguaje." << endl;
      }
      mt.reiniciar();
    }

    return 0;
  } catch (const exception& e) {
    cerr << "Error: " << e.what() << endl;
    return 1;
  }
}