#include "../alfabeto/alfabeto.h"

#ifndef CINTA_H
#define CINTA_H

using namespace std;

/**
 * @class Cinta
 * @brief Clase que representa la cinta de una máquina de Turing
 */
class Cinta {
  public:
    // Constructor y destructor
    Cinta() = default;
    Cinta(const Alfabeto& alfabeto) : alfabetoCinta_(alfabeto), cabezal_(0), desplazamiento_(0) {}
    ~Cinta() = default;

    // Métodos para manipular la cinta
    char leer();
    void escribir(char simbolo);
    void moverDerecha();
    void moverIzquierda();
    void comprobarCabezal();
    void insertar(const string& cadena);
    inline void limpiar() { cinta_.clear(); cabezal_ = 0; desplazamiento_ = 0; } // Limpia la cinta
    inline bool pertenece(char simbolo) const { return alfabetoCinta_.pertenece(simbolo); }

    // Getters
    inline Alfabeto getAlfabeto() const { return alfabetoCinta_; }
    
    // Sobrecarga de operadores
    friend ostream& operator<<(ostream& os, const Cinta& cinta);

  private:
    vector<char> cinta_;
    Alfabeto alfabetoCinta_;
    int cabezal_;
    int desplazamiento_;
};

#endif // CINTA_H