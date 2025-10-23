# Maquina-de-Turing
Este es un programa que simula el funcionamiento de una `Máquina de turing` multicinta con las siguientes características:

- Movimientos `simultáneos`.
- Los movimientos pueden ser `derecha` (R), `izquierda` (L) y con la posibilidad de `no movimiento` (S).
- Cinta infinita en `ambas` direcciones.

# Estructura de directorios

```bash
.
├── README.md
├── data
│   ├── Ejemplo2_MT.txt
│   ├── Ejemplo3_MT.txt
│   ├── Ejemplo4_MT.txt
│   └── Ejemplo_MT.txt
├── makefile
└── src
    ├── alfabeto
    │   ├── alfabeto.cc
    │   └── alfabeto.h
    ├── cinta
    │   ├── cinta.cc
    │   └── cinta.h
    ├── estado
    │   ├── estado.cc
    │   └── estado.h
    ├── main.cc
    ├── maquinaTuring
    │   ├── maquinaTuring.cc
    │   └── maquinaTuring.h
    ├── tools
    │   ├── tools.cc
    │   └── tools.h
    └── transicion
        ├── transicion.cc
        └── transicion.h
```

# Estructura del programa
La siguiente sección describe de forma breve las clases principales usadas en el simulador, sus responsabilidades y los métodos más importantes.

## Clases y métodos

### Alfabeto
Clase que representa un conjunto de símbolos válidos.
```c++
class Alfabeto {
    public:
      Alfabeto() = default;
      ~Alfabeto() = default;
      inline void insertar(char simbolo);
      inline bool pertenece(char simbolo) const;
      inline size_t size() const;
      friend ostream& operator<<(ostream& os, const Alfabeto& alfabeto);
    private:
      set<char> simbolos_;
};
```

- **constructores / destructor**: constructor por defecto y destructor por defecto.
- **insertar(char simbolo)**: inserta un símbolo en el alfabeto.
- **pertenece(char simbolo) const**: devuelve true si el símbolo pertenece al alfabeto.
- **size() const**: devuelve el número de símbolos en el alfabeto.

*Propósito*: Validar símbolos de entrada y de cinta.


### Cinta
Representa una cinta de la máquina de Turing (implementada como un vector dinámico) y el cabezal que lee/escribe.

```c++
class Cinta {
    public:
      Cinta() = default;
      Cinta(const Alfabeto& alfabeto);
      ~Cinta() = default;
      char leer();
      void escribir(char simbolo);
      void moverDerecha();
      void moverIzquierda();
      void comprobarCabezal();
      void insertar(const string& cadena);
      inline void limpiar();
      inline bool pertenece(char simbolo) const;
      inline Alfabeto getAlfabeto() const;
      friend ostream& operator<<(ostream& os, const Cinta& cinta);
    private:
      vector<char> cinta_;
      Alfabeto alfabetoCinta_;
      int cabezal_;
      int desplazamiento_;
};
```

- **Cinta(const Alfabeto& alfabeto)**: inicializa la cinta asociada a un alfabeto.
- **leer()**: devuelve el símbolo en la posición actual del cabezal.
- **escribir(char simbolo)**: escribe un símbolo en la posición actual del cabezal.
- **moverDerecha()**: mueve el cabezal una posición a la derecha.
- **moverIzquierda()**: mueve el cabezal una posición a la izquierda.
- **comprobarCabezal()**: asegura que la posición del cabezal es válida (extiende la cinta si es necesario).
- **insertar(const string& cadena)**: inserta una cadena en la cinta (por ejemplo en la inicialización).
- **limpiar()**: vacía la cinta y reinicia el cabezal y desplazamiento.
- **pertenece(char simbolo) const**: delega en el `Alfabeto` asociado para comprobar pertenencia.

*Propósito*: Modelar la memoria (cinta) donde la máquina lee, escribe y se desplaza.
 
### Estado
Representa un estado de la máquina de Turing y su conjunto de transiciones salientes.

```c++

class Estado {
    public:
        Estado() = default;
        Estado(const string& id, const bool& inicial = false, const bool& aceptacion = false);
      inline string getId() const;
      inline bool esInicial() const;
      inline bool esAceptacion() const;
      inline vector<Transicion>& getTransiciones();
      inline void setInicial();
      inline void setAceptacion();
      void agregarTransicion(const Transicion& transicion);
      friend ostream& operator<<(ostream& os, const Estado& estado);
    private:
      string id_;
      vector<Transicion> transiciones_;
      bool inicial_;
      bool aceptacion_;
};
```

- **Estado(const string& id, const bool& inicial = false, const bool& aceptacion = false)**: crea un estado con su identificador y banderas.
- **getId() const**: devuelve el identificador del estado.
- **esInicial() const / esAceptacion() const**: indican si el estado es inicial o de aceptación.
- **getTransiciones()**: devuelve la referencia al vector de transiciones salientes.
- **setInicial() / setAceptacion()**: marcan el estado como inicial o de aceptación.
- **agregarTransicion(const Transicion& transicion)**: añade una transición a la lista del estado.

*Propósito*: organizar los nodos del autómata y almacenar las transiciones que salen de cada uno.

### Transicion
Representa una transición entre dos estados con lecturas, escrituras y movimientos en una o más cintas.
```c++
class Transicion {
    public:
        Transicion() = default;
        Transicion(const int& id, Estado* actual, const vector<char>& lecturaCinta, Estado* siguiente, const vector<char>& escrituraCinta, const vector<char>& movimientoCinta);
      ~Transicion() = default;
      inline int getId() const;
      Estado* ejecutar(vector<Cinta>& cintas);
      bool esAplicable(const vector<char>& simbolosLeidos) const;
      friend ostream& operator<<(ostream& os, const Transicion& transicion);
    private:
      int id_;
      vector<char> lecturaCintas_;
      vector<char> escrituraCintas_;
      vector<char> movimientoCintas_;
      Estado* actual_;
      Estado* siguiente_;
};
```

- **Transicion(id, Estado actual, lecturaCinta, Estado siguiente, escrituraCinta, movimientoCinta)**: constructor que define la transición.
- **getId() const**: devuelve el identificador de la transición.
- **ejecutar(vector<Cinta>& cintas)**: aplica la transición sobre las cintas (escritura y movimiento) y devuelve el estado siguiente.
- **esAplicable(const vector<char>& simbolosLeidos) const**: comprueba si la transición puede aplicarse según los símbolos leídos en las cintas.

*Propósito*: encapsular la regla de paso (condición y efecto) entre estados.

### MaquinaTuring
Clase que coordina los estados, el alfabeto, las cintas y la ejecución de la máquina.

```c++
class MaquinaTuring {
  public:
    MaquinaTuring(const vector<Estado*>& estados, const Alfabeto& alfabetoEntrada, const Alfabeto& alfabetoCinta, int numCintas);
    ~MaquinaTuring() = default;
    friend ostream& operator<<(ostream& os, const MaquinaTuring& maquina);
    bool ejecutar(string cadena);
    bool esValida(const string& cadena) const;
    void reiniciar();
    void mostrarTraza(const string& cadena, const Transicion* transicion);
    Transicion* obtenerTransicionPosible(vector<char> simbolosLeidos);
  private:
    vector<Estado*> estados_;
    Alfabeto alfabetoEntrada_;
    vector<Cinta> cintas_;
    Estado* estadoActual_;
};
```
- **MaquinaTuring(const vector<Estado>& estados, const Alfabeto& alfabetoEntrada, const Alfabeto& alfabetoCinta, int numCintas)**: constructor que inicializa la máquina con sus estados, alfabetos y número de cintas.
- **ejecutar(string cadena)**: ejecuta la máquina sobre una cadena de entrada; devuelve true si la cadena es aceptada.
- **esValida(const string& cadena) const**: valida que la cadena de entrada está compuesta por símbolos del alfabeto de entrada.
- **reiniciar()**: reinicia el estado actual y limpia las cintas para una nueva ejecución.
- **mostrarTraza(const string& cadena, const Transicion transicion)**: método para imprimir (trazar) el paso actual con la transición aplicada.
- **obtenerTransicionPosible(vector<char> simbolosLeidos)**: busca y devuelve una transición aplicable según los símbolos leídos en las cintas.

*Propósito*: orquestar la simulación paso a paso, seleccionar transiciones aplicables y determinar aceptación.

## Compilación del programa
Para compilar este programa he creado un archivo `makefile` para automatizar el trabajo, solo basta con ejecutar lo siguiente:
```bash
make
```
Para borrar el ejecutable generado basta con ejecutar lo siguiente:
```bash
make clean
```

## Ejecución del programa
Para que este programa pueda realizar su correcto funcionamiento se le debe pasar un fichero en formato `.txt` con los datos del autómata, el fichero tendrá la siguiente estructura:
```txt
# Comentarios
q1 q2 q3 … # conjunto Q
a1 a2 a3 … # conjunto Σ
A1 A2 A3 … # conjunto Γ
q1 # estado inicial
b # símbolo blanco
q2 q3 # conjunto F
n # número de cintas
q1 a1 q2 a2 m # función de transición : δ (q1, a1) = (q2, a2, m) 2
... # cada una de las transiciones en una línea distinta

1. Los símbolos contenidos en Γ estarán formados por un único carácter.
2. La estructura de las transiciones se modificará, si es necesario, para adaptarse a las características de la MT a implementar.
```
Teniendo lo anterior en cuenta, basta con ejecutar lo siguiente:
```bash
./turing ./data/<fichero_entrada>
```

## Cosas a tener en cuenta‼️
1. Los ficheros deberán estar alojados en el directorio `/data`.
2. Los ficheros de error para comprobar el funcionamiento del programa se encuentran en `/data/error`.
3. La cadena se introducirá por terminal cuando el programa lo pida.
4. Si se quiere terminar la ejecución del programa, cuando se solicite la cadena, pulsar `ENTER`.
5. Para introducir otro fichero se debe terminar con la ejecución del programa.

## Ejemplo de prueba con el fichero Ejemplo_MT.txt
El fichero `Ejemplo_MT.txt` especifica un autómata para reconocer el lenguaje de cadenas binarias con
con un número impar de 0's.

### Ejecución
```bash
./turing ./data/Ejemplo_MT.txt
```
### Visualización
Cuando se ejecute, se mostrará toda la información recogida en el fichero. Para este caso la salida sería la siguiente:

```txt
Q -> {q0, q1, q2}
Σ -> {0, 1}
Γ -> {., 0, 1}
q0 -> q0
F -> {q2}
---- Transiciones del estado q0 ----
δ(q0, 0) -> (q1, 0, R) ID: 1
δ(q0, 1) -> (q0, 1, R) ID: 2

---- Transiciones del estado q1 ----
δ(q1, 0) -> (q0, 0, R) ID: 3
δ(q1, 1) -> (q1, 1, R) ID: 4
δ(q1, .) -> (q2, ., R) ID: 5

---- Transiciones del estado q2 ----
```

### Traza
Y a continuación se solicitará una cadena para introducir por terminal, una vez introducida, se mostrará la traza que sigue la Máquina de Turing para comprobar si la cadena pertenece o no pertenece al lenguaje. La traza muestra el `estado actual`, la `cinta` y el ID de la `transición` posible. Para la cadena `0100` sería la siguiente:

```txt
-------------------------------------------------
Estado actual: q0
Cinta 1: [0]100
transición: 1
-------------------------------------------------
-------------------------------------------------
Estado actual: q1
Cinta 1: 0[1]00
transición: 4
-------------------------------------------------
-------------------------------------------------
Estado actual: q1
Cinta 1: 01[0]0
transición: 3
-------------------------------------------------
-------------------------------------------------
Estado actual: q0
Cinta 1: 010[0]
transición: 1
-------------------------------------------------
-------------------------------------------------
Estado actual: q1
Cinta 1: 0100[.]
transición: 5
-------------------------------------------------
-------------------------------------------------
Estado actual: q2
Cinta 1: 0100.[.]
transición: -
-------------------------------------------------
```

Para la cadena `0101` la traza sería la siguiente:

```txt
-------------------------------------------------
Estado actual: q0
Cinta 1: [0]101
transición: 1
-------------------------------------------------
-------------------------------------------------
Estado actual: q1
Cinta 1: 0[1]01
transición: 4
-------------------------------------------------
-------------------------------------------------
Estado actual: q1
Cinta 1: 01[0]1
transición: 3
-------------------------------------------------
-------------------------------------------------
Estado actual: q0
Cinta 1: 010[1]
transición: 2
-------------------------------------------------
-------------------------------------------------
Estado actual: q0
Cinta 1: 0101[.]
transición: -
-------------------------------------------------
La cadena 0101 no pertenece al lenguaje.
```