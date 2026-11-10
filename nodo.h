#ifndef NODO_H
#define NODO_H

#include <iostream>
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

// -- IMPRESION DEL ARBOL --
inline void imprimirRama(const Nodo &nodo, const string &prefijo, bool ultimo) {
    string rama;
    string siguientePrefijo;
    if (ultimo) {
        rama = "`-- ";
        siguientePrefijo = prefijo + "    ";
    } else {
        rama = "|-- ";
        siguientePrefijo = prefijo + "|   ";
    }
    cout << prefijo << rama << nodo.etiqueta << '\n';
    for (size_t i = 0; i < nodo.hijos.size(); ++i) {
        imprimirRama(nodo.hijos[i], siguientePrefijo, i + 1 == nodo.hijos.size());
    }
}

inline void imprimirRaiz(const Nodo &nodo) {
    cout << nodo.etiqueta << '\n';
    for (size_t i = 0; i < nodo.hijos.size(); ++i) {
        imprimirRama(nodo.hijos[i], "", i + 1 == nodo.hijos.size());
    }
}

#endif
