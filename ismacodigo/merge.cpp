#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>

using namespace std;
using namespace std::chrono;

void merge(vector<int>& arr, int izq, int medio, int der, long long& comparaciones, long long& intercambios) {
    int n1 = medio - izq + 1;
    int n2 = der - medio;

    vector<int> izqArr(n1);
    vector<int> derArr(n2);

    for (int i = 0; i < n1; i++) izqArr[i] = arr[izq + i];
    for (int j = 0; j < n2; j++) derArr[j] = arr[medio + 1 + j];

    int i = 0, j = 0, k = izq;

    while (i < n1 && j < n2) {
        comparaciones++;
        if (izqArr[i] <= derArr[j]) {
            arr[k] = izqArr[i];
            i++;
        } else {
            arr[k] = derArr[j];
            j++;
        }
        intercambios++;
        k++;
    }

    while (i < n1) {
        arr[k] = izqArr[i];
        i++;
        intercambios++;
        k++;
    }

    while (j < n2) {
        arr[k] = derArr[j];
        j++;
        intercambios++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int izq, int der, long long& comparaciones, long long& intercambios) {
    if (izq < der) {
        int medio = izq + (der - izq) / 2;
        mergeSort(arr, izq, medio, comparaciones, intercambios);
        mergeSort(arr, medio + 1, der, comparaciones, intercambios);
        merge(arr, izq, medio, der, comparaciones, intercambios);
    }
}

void mergeSortBenchmark(const vector<int>& datosOriginales, int tam) {
    vector<int> arr(datosOriginales.begin(), datosOriginales.begin() + min((size_t)tam, datosOriginales.size()));
    long long comparaciones = 0;
    long long intercambios = 0;

    auto inicio = high_resolution_clock::now();
    mergeSort(arr, 0, arr.size() - 1, comparaciones, intercambios);
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

    cout << "--- RESULTADOS MERGE SORT (C++) ---" << endl;
    for (int tam : tamanos) {
        mergeSortBenchmark(datosMaestros, tam);
    }

    return 0;
}