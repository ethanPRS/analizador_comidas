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
        // Si ya no quedan palabras, no se menciona la marca interna '$'
        if (categoriaActual() == "FIN") {
            throw std::runtime_error("Error sintáctico: la cadena terminó y se esperaba " + descripcion);
        }
        throw std::runtime_error("Error sintáctico en el símbolo '" + palabras[pos] +
      "' (posición " + std::to_string(pos + 1) + "): se esperaba " + descripcion);

    }
}

// -- ENVOLVER A NODO -- 
Nodo envolver(string etiqueta, Nodo hijo) {
    return Nodo{etiqueta, {hijo}};
}

Nodo analizarAcomp();


// -- MENSAJE CUANDO NO LLEGA LA BEBIDA --
string razonFaltaBebida(const string &categoria) {
    if (categoria == "PROTEINA") return "solo se permite una proteina, y va al inicio";
    if (categoria == "GUARN1")   return "las guarniciones tipo 1 van antes que las de tipo 2, "
                                        "antes de entradas/sopas/postres, y solo se permite una";
    if (categoria == "GUARN2")   return "solo se permite una guarnicion tipo 2, "
                                        "y va antes de entradas/sopas/postres";
    if (categoria == "SOPA" || categoria == "ENTRADA")
                                 return "solo se permite una entrada o sopa, y va antes del postre";
    if (categoria == "POSTRE")   return "solo se permite un postre";
    if (categoria == "Y")        return "hay un '+' de mas";
    if (categoria == "FIN")      return "falta la bebida al final";
    return "se esperaba una bebida";
}

Nodo analizarComida() {
    Nodo comida = Nodo{"<Comida>", {}};

    //PROTEINA (OBLIGATORIA)
    comida.hijos.push_back(envolver("<Proteina>", match("PROTEINA", "una proteina")));

    // + (después de la proteína siempre va un +)
    comida.hijos.push_back(match("Y", "el separador '+' y una bebida"));
    
    //ACOMPANAMIENTO (OPCIONAL)
    if (categoriaActual() == "GUARN1" || categoriaActual() == "GUARN2" || categoriaActual() == "ENTRADA" || categoriaActual() == "SOPA" || categoriaActual() == "POSTRE") {
        comida.hijos.push_back(analizarAcomp());
        comida.hijos.push_back(match("Y", "el separador '+' y una bebida"));
    }

    //BEBIDA (OBLIGATORIA)
    if (categoriaActual() != "BEBIDA") {
        throw runtime_error("Error sintáctico en el símbolo '" + palabras[pos] +
            "' (posición " + to_string(pos + 1) + "): " + razonFaltaBebida(categoriaActual()));
    }
    comida.hijos.push_back(envolver("<Bebida>", match("BEBIDA", "una bebida")));

    return comida;

}

// -- SIGUIENTE CATEGORIA SIN CONSUMIR --
string categoriaSiguiente() {
    if (static_cast<size_t>(pos + 1) >= palabras.size()) {
        return "FIN";
    }
    return alfabeto.at(palabras[pos + 1]);
}

bool iniciaComplemento(const string &categoria) {
    return categoria == "SOPA" || categoria == "ENTRADA" || categoria == "POSTRE";
}

// -- ENTRADA: SOPA O ENTRADA LIGERA --
Nodo analizarEntrada() {
    Nodo entrada{"<Entrada>", {}};
    if (categoriaActual() == "SOPA") {
        entrada.hijos.push_back(envolver("<Sopa>", match("SOPA", "una sopa")));
    } else {
        entrada.hijos.push_back(envolver("<EntradaLigera>", match("ENTRADA", "una entrada ligera")));
    }
    return entrada;
}

// -- COMPLEMENTO: ENTRADA, POSTRE O ENTRADA + POSTRE --
Nodo analizarComplemento() {
    Nodo complemento{"<Complemento>", {}};
    if (categoriaActual() == "SOPA" || categoriaActual() == "ENTRADA") {
        complemento.hijos.push_back(analizarEntrada());
        if (categoriaActual() == "Y" && categoriaSiguiente() == "POSTRE") {
            complemento.hijos.push_back(match("Y", "el separador '+'"));
            complemento.hijos.push_back(envolver("<Postre>", match("POSTRE", "un postre")));
        }
    } else {
        complemento.hijos.push_back(envolver("<Postre>", match("POSTRE", "una entrada o un postre")));
    }
    return complemento;
}

// -- GUARNICIONES: TIPO 1, TIPO 2 O TIPO 1 + TIPO 2 --
Nodo analizarGuarniciones() {
    Nodo guarniciones{"<Guarniciones>", {}};
    if (categoriaActual() == "GUARN1") {
        guarniciones.hijos.push_back(envolver("<Guarnicion1>", match("GUARN1", "una guarnicion de tipo 1")));
        if (categoriaActual() == "Y" && categoriaSiguiente() == "GUARN2") {
            guarniciones.hijos.push_back(match("Y", "el separador '+'"));
            guarniciones.hijos.push_back(envolver("<Guarnicion2>", match("GUARN2", "una guarnicion de tipo 2")));
        }
    } else {
        guarniciones.hijos.push_back(envolver("<Guarnicion2>", match("GUARN2", "una guarnicion")));
    }
    return guarniciones;
}

// -- ACOMPANAMIENTOS --
Nodo analizarAcomp() {
    Nodo acomp{"<Acompanamientos>", {}};
    if (categoriaActual() == "GUARN1" || categoriaActual() == "GUARN2") {
        acomp.hijos.push_back(analizarGuarniciones());
        if (categoriaActual() == "Y" && iniciaComplemento(categoriaSiguiente())) {
            acomp.hijos.push_back(match("Y", "el separador '+'"));
            acomp.hijos.push_back(analizarComplemento());
        }
    } else if (iniciaComplemento(categoriaActual())) {
        acomp.hijos.push_back(analizarComplemento());
    } else {
        throw runtime_error("Error sintáctico en el símbolo '" + palabras[pos] +
            "' (posición " + to_string(pos + 1) + "): se esperaba guarnicion, entrada o postre");
    }
    return acomp;
}

// -- ANALIZAR LA CADENA COMPLETA --
Nodo analizarCadena(const vector<string> &tokens) {
    // El analizador agrega exactamente una marca de fin interna.
    if (tokens.empty() || tokens.back() != "$") {
        throw runtime_error("Falta la marca interna de fin de cadena");
    }
    for (size_t i = 0; i + 1 < tokens.size(); ++i) {
        if (tokens[i] == "$") {
            throw runtime_error("El símbolo '$' (posición " + to_string(i + 1) +
                ") esta reservado para el fin interno de la cadena");
        }
    }
    palabras = tokens;
    pos = 0;
    Nodo arbol = analizarComida();
    if (categoriaActual() != "FIN" || static_cast<size_t>(pos) != palabras.size() - 1) {
        throw runtime_error("Error sintáctico en el símbolo '" + palabras[pos] +
            "' (posición " + to_string(pos + 1) + "): no se permiten componentes despues de la bebida");
    }
    return arbol;
}



#endif