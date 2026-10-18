#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>

using namespace std;
using namespace std::chrono;

void selectionSortBenchmark(const vector<int>& datosOriginales, int tam) {
    vector<int> arr(datosOriginales.begin(), datosOriginales.begin() + min((size_t)tam, datosOriginales.size()));
    int n = arr.size();
    long long comparaciones = 0;
    long long intercambios = 0;

    auto inicio = high_resolution_clock::now();

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            comparaciones++;
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            int temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
            intercambios++;
        }
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

    cout << "--- RESULTADOS SELECCIÓN (C++) ---" << endl;
    for (int tam : tamanos) {
        selectionSortBenchmark(datosMaestros, tam);
    }

    return 0;
}