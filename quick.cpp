#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>

using namespace std;
using namespace std::chrono;

int partition(vector<int>& arr, int low, int high, long long& comparaciones, long long& intercambios) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        comparaciones++;
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
            intercambios++;
        }
    }
    swap(arr[i + 1], arr[high]);
    intercambios++;
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high, long long& comparaciones, long long& intercambios) {
    if (low < high) {
        int pi = partition(arr, low, high, comparaciones, intercambios);
        quickSort(arr, low, pi - 1, comparaciones, intercambios);
        quickSort(arr, pi + 1, high, comparaciones, intercambios);
    }
}

void quickSortBenchmark(const vector<int>& datosOriginales, int tam) {
    vector<int> arr(datosOriginales.begin(), datosOriginales.begin() + min((size_t)tam, datosOriginales.size()));
    long long comparaciones = 0;
    long long intercambios = 0;

    auto inicio = high_resolution_clock::now();
    if (!arr.empty()) {
        quickSort(arr, 0, arr.size() - 1, comparaciones, intercambios);
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

    cout << "--- RESULTADOS QUICK SORT (C++) ---" << endl;
    for (int tam : tamanos) {
        quickSortBenchmark(datosMaestros, tam);
    }

    return 0;
}