#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>

using namespace std;
using namespace std::chrono;

void insertionSortBenchmark(const vector<int>& datosOriginales, int tam) {
    vector<int> arr(datosOriginales.begin(), datosOriginales.begin() + min((size_t)tam, datosOriginales.size()));
    int n = arr.size();
    long long comparaciones = 0;
    long long intercambios = 0;

    auto inicio = high_resolution_clock::now();

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            comparaciones++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                intercambios++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }

    auto fin = high_resolution_clock::now();
    auto duracion = duration_cast<microseconds>(fin - inicio);
    double tiempoMs = duracion.count() / 1000.0;

    cout << "Tamaño: " << tam 
         << " | Tiempo: " << tiempoMs << " ms"
         << " | Intercambios: " << intercambios 
         << " | Comparaciones: " << comparaciones << endl;
}

int main() {
    vector<int> datosMaestros;
    ifstream archivo("datos_millon.txt");
    string linea;

    while (getline(archivo, linea)) {
        if (!linea.empty()) {
            datosMaestros.push_back(stoi(linea));
        }
    }
    archivo.close();

    vector<int> tamanos = {100, 500, 1000, 10000, 100000};

    cout << "--- RESULTADOS INSERCIÓN (C++) ---" << endl;
    for (int tam : tamanos) {
        insertionSortBenchmark(datosMaestros, tam);
    }

    return 0;
}