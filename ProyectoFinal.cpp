#include <climits>
#include <iostream>
#include <vector>

using namespace std;

// Estructura que almacena la lista completa de rutas válidas halladas junto con
// su distancia[cite: 7].
struct Ruta {
  vector<int> nodos;
  int distancia;
};

// Estructura auxiliar para el Árbol Binario (Requerimiento de recorridos)
struct NodoArbol {
  char dato;
  NodoArbol *izquierdo;
  NodoArbol *derecho;

  NodoArbol(char valor) {
    dato = valor;
    izquierdo = nullptr;
    derecho = nullptr;
  }
};

// Función para insertar nodos en el Árbol Binario de Búsqueda
NodoArbol *insertarNodo(NodoArbol *raiz, char valor) {
  if (raiz == nullptr) {
    return new NodoArbol(valor);
  }
  if (valor < raiz->dato) {
    raiz->izquierdo = insertarNodo(raiz->izquierdo, valor);
  } else if (valor > raiz->dato) {
    raiz->derecho = insertarNodo(raiz->derecho, valor);
  }
  return raiz;
}

// Recorrido Preorden: Raíz -> Izquierda -> Derecha
void mostrarPreorden(NodoArbol *nodo) {
  if (nodo == nullptr)
    return;
  cout << nodo->dato << " ";
  mostrarPreorden(nodo->izquierdo);
  mostrarPreorden(nodo->derecho);
}

// Recorrido Inorden: Izquierda -> Raíz -> Derecha
void mostrarInorden(NodoArbol *nodo) {
  if (nodo == nullptr)
    return;
  mostrarInorden(nodo->izquierdo);
  cout << nodo->dato << " ";
  mostrarInorden(nodo->derecho);
}

// Recorrido Postorden: Izquierda -> Derecha -> Raíz
void mostrarPostorden(NodoArbol *nodo) {
  if (nodo == nullptr)
    return;
  mostrarPostorden(nodo->izquierdo);
  mostrarPostorden(nodo->derecho);
  cout << nodo->dato << " ";
}

// Devuelve el índice numérico de un vértice según su letra[cite: 1].
int obtenerIndice(char vertice, const vector<char> &nombresVertices) {
  for (int i = 0; i < nombresVertices.size(); i++) {
    if (nombresVertices[i] == vertice)
      return i;
  }
  return -1;
}

// Algoritmo DFS con Backtracking para exploración exhaustiva[cite: 5].
void explorarRutas(int nodoActual, int nodoDestino, vector<bool> &visitado,
                   vector<int> &rutaActual, int distanciaAcumulada,
                   const vector<vector<int>> &matrizAdy,
                   vector<Ruta> &todasLasRutas, int numVertices) {

  // Marcamos el nodo actual como visitado y lo añadimos a la secuencia[cite:
  // 5].
  visitado[nodoActual] = true;
  rutaActual.push_back(nodoActual);

  // Registro de Camino Simple: Si llegamos al destino, guardamos la ruta[cite:
  // 5].
  if (nodoActual == nodoDestino) {
    todasLasRutas.push_back({rutaActual, distanciaAcumulada});
  } else {
    // Exploración recursiva por nodos adyacentes no visitados[cite: 5].
    for (int i = 0; i < numVertices; i++) {
      if (matrizAdy[nodoActual][i] > 0 && !visitado[i]) {
        explorarRutas(i, nodoDestino, visitado, rutaActual,
                      distanciaAcumulada + matrizAdy[nodoActual][i], matrizAdy,
                      todasLasRutas, numVertices);
      }
    }
  }

  // Desmarcado (Backtracking): Retiramos el nodo para evaluar ramas
  // alternativas[cite: 5].
  visitado[nodoActual] = false;
  rutaActual.pop_back();
}

int main() {
  int numVertices; // Almacena la cantidad de nodos ingresados por el
                   // usuario[cite: 7].

  // RF-01: Ingreso Dinámico de Vértices (n >= 2)[cite: 5].
  cout << "Ingrese la cantidad de vertices (n >= 2): ";
  cin >> numVertices;
  if (numVertices < 2) {
    cout << "Error: Se requieren al menos 2 vertices." << endl;
    return 1;
  }

  vector<char> nombresVertices(numVertices);
  NodoArbol *raizArbol = nullptr; // Raíz para los recorridos de árbol

  for (int i = 0; i < numVertices; i++) {
    cout << "Ingrese la letra identificadora para el vertice " << i + 1 << ": ";
    cin >> nombresVertices[i];
    // Insertamos el vértice en nuestro árbol binario para los recorridos
    raizArbol = insertarNodo(raizArbol, nombresVertices[i]);
  }

  // Matriz n x n que almacena el peso entero entre nodos; 0 indica ausencia de
  // arista[cite: 4, 7].
  vector<vector<int>> matrizAdy(numVertices, vector<int>(numVertices, 0));

  int numAristas;
  cout << "\nIngrese la cantidad de aristas dirigidas: ";
  cin >> numAristas;

  // RF-02: Registro Guiado de Aristas[cite: 5].
  for (int i = 0; i < numAristas; i++) {
    char origen, destino;
    int peso;
    cout << "Arista " << i + 1 << " - Origen: ";
    cin >> origen;
    cout << "Arista " << i + 1 << " - Destino: ";
    cin >> destino;

    int idxOrigen = obtenerIndice(origen, nombresVertices);
    int idxDestino = obtenerIndice(destino, nombresVertices);

    if (idxOrigen != -1 && idxDestino != -1) {
      // RF-03: Asignación de Pesos Positivos y Validación[cite: 5].
      do {
        cout << "Peso positivo para " << origen << " -> " << destino << ": ";
        cin >> peso;
        if (peso <= 0)
          cout << "El peso debe ser mayor a 0. Intente de nuevo." << endl;
      } while (peso <= 0);

      matrizAdy[idxOrigen][idxDestino] = peso;
    } else {
      cout << "Vertices invalidos. Arista omitida." << endl;
    }
  }

  // --- SECCIÓN NUEVA: RECORRIDOS DE ÁRBOL ---
  cout << "\n--- Recorridos del Arbol Binario de Vertices ---" << endl;
  cout << "Preorden: ";
  mostrarPreorden(raizArbol);
  cout << "\nInorden: ";
  mostrarInorden(raizArbol);
  cout << "\nPostorden: ";
  mostrarPostorden(raizArbol);
  cout << "\n------------------------------------------------\n";

  vector<bool> visitado(numVertices, false);
  vector<int> rutaActual;
  vector<Ruta> todasLasRutas;

  int nodoInicial = 0;
  int nodoTerminal = numVertices - 1;

  cout << "\n--- Evaluando Conectividad y Rutas ---" << endl;
  explorarRutas(nodoInicial, nodoTerminal, visitado, rutaActual, 0, matrizAdy,
                todasLasRutas, numVertices);

  // RF-04: Verificación de Conectividad explícita[cite: 5].
  if (todasLasRutas.empty()) {
    cout << "No existen caminos conectados desde "
         << nombresVertices[nodoInicial] << " hasta "
         << nombresVertices[nodoTerminal] << "." << endl;
  } else {
    int distMinima = INT_MAX;
    int distMaxima = -1;
    int idxMin = -1, idxMax = -1;

    // RF-05: Listado Exhaustivo de Caminos y determinación de extremos[cite: 5,
    // 8].
    for (int i = 0; i < todasLasRutas.size(); i++) {
      cout << "Ruta " << i + 1 << ": ";
      for (int j = 0; j < todasLasRutas[i].nodos.size(); j++) {
        cout << nombresVertices[todasLasRutas[i].nodos[j]];
        if (j < todasLasRutas[i].nodos.size() - 1)
          cout << " -> ";
      }
      cout << " | Distancia Acumulada: " << todasLasRutas[i].distancia << endl;

      if (todasLasRutas[i].distancia < distMinima) {
        distMinima = todasLasRutas[i].distancia;
        idxMin = i;
      }
      if (todasLasRutas[i].distancia > distMaxima) {
        distMaxima = todasLasRutas[i].distancia;
        idxMax = i;
      }
    }

    // RF-06: Identificación visual de ruta más corta y más larga[cite: 5].
    cout << "\n--- Resultados de Optimizacion ---" << endl;
    cout << "CAMINO MAS CORTO (Minima): ";
    for (int nodo : todasLasRutas[idxMin].nodos)
      cout << nombresVertices[nodo] << " ";
    cout << "con " << distMinima << " unidades." << endl;

    cout << "CAMINO MAS LARGO (Maxima): ";
    for (int nodo : todasLasRutas[idxMax].nodos)
      cout << nombresVertices[nodo] << " ";
    cout << "con " << distMaxima << " unidades." << endl;
  }

  return 0;
}
