#include <iostream>
#include <sstream>   // para istringstream
#include <stdexcept> // para runtime_error
#include <string>
#include <vector>

#include "analizadorSintactico.h"
#include "nodo.h"


using namespace std;



// -- ANÁLIZADOR LÉXICO -- 
vector<string> analizadorLexico(string &comida) {
  vector<string> palabras;
  istringstream flujo(comida); // Pemite leer palabra por palabra
  string palabra;
  int pos = 1;

  while (flujo >> palabra) { // Separa por espacios
    if (alfabeto.count(palabra) == 0) {
      throw runtime_error("El simbolo '" + palabra + "' (posición " +
                          to_string(pos) + ") no pertenece al alfabeto");
    }
    palabras.push_back(palabra);
    pos++;
  }

  if (palabras.empty()) {
    throw runtime_error("La cadena esta vacia");
  }

  palabras.push_back("$"); // Fin de la Cadena
  return palabras;
}


// -- BIENVENIDA --
void imprimirBienvenida() {
  cout << "==========================================" << endl;
  cout << "              MEXICANITOS" << endl;
  cout << "==========================================" << endl;
  cout << "Bienvenido! Arma tu comida mexicana." << endl;
}

// -- MENU CON EL ALFABETO --
void imprimirAlfabeto() {
  // Categorias en el orden en que se arma una comida
  vector<pair<string, string>> categorias = {
      {"PROTEINA", "Proteinas (obligatoria)"},
      {"GUARN1", "Guarniciones tipo 1"},
      {"GUARN2", "Guarniciones tipo 2"},
      {"SOPA", "Sopas"},
      {"ENTRADA", "Entradas ligeras"},
      {"POSTRE", "Postres"},
      {"BEBIDA", "Bebidas (obligatoria)"}};

  cout << endl << "---------------- MENU ----------------" << endl;
  for (const auto &categoria : categorias) {
    cout << endl << categoria.second << ":" << endl;
    for (const auto &entrada : alfabeto) {
      if (entrada.second == categoria.first) {
        cout << "  - " << entrada.first << endl;
      }
    }
  }
  cout << endl << "Formato: proteina + [guarniciones] + [entrada/sopa] + [postre] + bebida" << endl;
  cout << "Ejemplo: pollo_asado + arroz_rojo + flan + agua_de_jamaica" << endl;
}

// -- PROCESAR UNA ORDEN --
// Regresa true si la orden fue valida; si no, guarda la razon en 'error'.
bool procesarOrden(string linea, string &error) {
  // Separar los signos + permite escribir con o sin espacios alrededor.
  string comidaSeparada;
  for (char caracter : linea) {
    if (caracter == '+') {
      comidaSeparada += " + ";
    } else {
      comidaSeparada += caracter;
    }
  }

  try {
    vector<string> palabras = analizadorLexico(comidaSeparada);
    cout << endl << "---------- ANALISIS LEXICO ----------" << endl << endl;
    for (const string &p : palabras) {
      cout << p << " -> " << alfabeto[p] << endl;
    }
    Nodo arbol = analizarCadena(palabras);
    cout << endl << "Cadena valida." << endl;
    cout << endl << "-------- ARBOL DE DERIVACION --------" << endl << endl;
    imprimirRaiz(arbol);
    return true;
  } catch (const runtime_error &e) {
    cout << endl << "Cadena inválida." << endl;
    cout << e.what() << endl;
    error = e.what();
    return false;
  }
}

// -- MAIN --
int main() {
  imprimirBienvenida();

  string opcion;
  while (true) {
    cout << endl << "1. Ordenar" << endl;
    cout << "2. Salir" << endl;
    cout << "Elige una opcion: ";
    if (!getline(cin, opcion) || opcion == "2") {
      break;
    }

    if (opcion != "1") {
      cout << "Opcion no valida, intenta de nuevo." << endl;
      continue;
    }

    imprimirAlfabeto();

    // Todas las ordenes de esta ronda (validas e invalidas)
    vector<string> ordenes;
    vector<string> errores; // Vacio si la orden fue valida
    string otra = "s";
    while (otra == "s" || otra == "S") {
      string linea;
      cout << endl << "Orden #" << ordenes.size() + 1 << ": ";
      if (!getline(cin, linea)) {
        break;
      }
      string error;
      procesarOrden(linea, error);
      ordenes.push_back(linea);
      errores.push_back(error);

      cout << endl << "Deseas hacer otra orden? (s/n): ";
      if (!getline(cin, otra)) {
        break;
      }
    }

    // Resumen de todas las ordenes
    cout << endl << "========== TUS ORDENES ==========" << endl;
    if (ordenes.empty()) {
      cout << "No se registro ninguna orden." << endl;
    }
    for (size_t i = 0; i < ordenes.size(); ++i) {
      cout << "Orden " << i + 1 << ": " << ordenes[i] << endl;
      if (errores[i].empty()) {
        cout << "  Valida" << endl;
      } else {
        cout << "  INVALIDA: " << errores[i] << endl;
      }
      cout << endl;
    }
  }

  cout << endl << "Gracias por visitar Mexicanitos. Hasta pronto!" << endl;
  return 0;
}
