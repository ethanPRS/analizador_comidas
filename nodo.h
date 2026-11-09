#ifndef NODO_H
#define NODO_H

#include <string>
#include <vector>

using namespace std;

struct Nodo {
  string etiqueta;
  vector<Nodo> hijos;
};

// Crear una hoja (terminal)
inline Nodo hoja(string palabra) {
  return Nodo{palabra, {}};
}

#endif
