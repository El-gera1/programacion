#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>

using namespace std;
using namespace std::chrono;

void heapify(vector<int>& arr, int n, int i, long long& comparaciones, long long& intercambios) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        comparaciones++;
        if (arr[left] > arr[largest]) {
            largest = left;
        }
    }

    if (right < n) {
        comparaciones++;
        if (arr[right] > arr[largest]) {
            largest = right;
        }
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        intercambios++;
        heapify(arr, n, largest, comparaciones, intercambios);
    }
}

void heapSort(vector<int>& arr, long long& comparaciones, long long& intercambios) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, comparaciones, intercambios);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        intercambios++;
        heapify(arr, i, 0, comparaciones, intercambios);
    }
}

void heapSortBenchmark(const vector<int>& datosOriginales, int tam) {
    vector<int> arr(datosOriginales.begin(), datosOriginales.begin() + min((size_t)tam, datosOriginales.size()));
    long long comparaciones = 0;
    long long intercambios = 0;

    auto inicio = high_resolution_clock::now();
    heapSort(arr, comparaciones, intercambios);
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

    cout << "--- RESULTADOS HEAP SORT (C++) ---" << endl;
    for (int tam : tamanos) {
        heapSortBenchmark(datosMaestros, tam);
    }

    return 0;
}