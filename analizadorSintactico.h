#ifndef ANALIZADOR_SINTACTICO_H
#define ANALIZADOR_SINTACTICO_H
#include <vector>
#include <string>
#include <stdexcept>

#include "nodo.h"
#include "alfabeto.h"
using namespace std;

inline std::vector<std::string> palabras;
inline int pos = 0;

// -- CATEGORIA ACTUAL -- 
string categoriaActual() {
  return alfabeto.at(palabras[pos]);
}

// -- COMPARAR CATEGORIAS -- 
Nodo match(string categoriaEsperada, string descripcion) {
    if (categoriaActual() == categoriaEsperada) {
        string palabraActual = palabras[pos];
        pos++;
        return hoja(palabraActual);
    } else {
        throw std::runtime_error("Error sintáctico en el símbolo '" + palabras[pos] +
      "' (posición " + std::to_string(pos + 1) + "): se esperaba " + descripcion);

    }
}

// -- ENVOLVER A NODO -- 
Nodo envolver(string etiqueta, Nodo hijo) {
    return Nodo{etiqueta, {hijo}};
}

Nodo analizarAcomp();


Nodo analizarComida() {
    Nodo comida = Nodo{"<Comida>", {}};

    //PROTEINA (OBLIGATORIA)
    comida.hijos.push_back(envolver("<Proteina>", match("PROTEINA", "una proteina")));

    //ACOMPANAMIENTO (OPCIONAL)
    if (categoriaActual() == "GUARN1" || categoriaActual() == "GUARN2" || categoriaActual() == "ENTRADA" || categoriaActual() == "SOPA" || categoriaActual() == "POSTRE") {
        comida.hijos.push_back(analizarAcomp());
    }

    //BEBIDA (OBLIGATORIA)
    comida.hijos.push_back(envolver("<Bebida>", match("BEBIDA", "una bebida")));

    return comida;

}



#endif