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


// -- MAIN -- 
int main() {
  string linea;
  cout << "Ingrese una cadena: ";
  getline(cin, linea);

  try {
    vector<string> palabras = analizadorLexico(linea);
    for (const string &p : palabras)
      cout << p << " -> " << alfabeto[p] << endl;
  } catch (const runtime_error &e) {
    cout << "Cadena inválida." << endl;
    cout << e.what() << endl;
  }
  return 0;
}
