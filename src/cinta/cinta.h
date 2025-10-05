#include <iostream>
#include <vector>

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
    Cinta(const string& contenido) : cinta_(contenido.begin(), contenido.end()), cabezal_(0), desplazamiento_(0) {}
    ~Cinta() = default;

    // Métodos para manipular la cinta
    char leer() const;
    char escribir(char simbolo);
    void moverDerecha();
    void moverIzquierda();
    
    // Sobrecarga de operadores
    friend ostream& operator<<(ostream& os, const Cinta& cinta);

  private:
    vector<char> cinta_;
    int cabezal_;
    int desplazamiento_;
};

#endif // CINTA_H