#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;
using namespace std::chrono;

void countingSortForRadix(vector<int>& arr, int n, int exp, long long& intercambios) {
    vector<int> output(n);
    vector<int> count(10, 0);

    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
        intercambios++;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radixSortBenchmark(const vector<int>& datosOriginales, int tam) {
    vector<int> arr(datosOriginales.begin(), datosOriginales.begin() + min((size_t)tam, datosOriginales.size()));
    int n = arr.size();
    if (n == 0) return;

    long long comparaciones = 0;
    long long intercambios = 0;

    auto inicio = high_resolution_clock::now();

    int minVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) minVal = arr[i];
    }

    int offset = 0;
    if (minVal < 0) {
        offset = abs(minVal);
        for (int i = 0; i < n; i++) arr[i] += offset;
    }

    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortForRadix(arr, n, exp, intercambios);
    }

    if (minVal < 0) {
        for (int i = 0; i < n; i++) arr[i] -= offset;
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

    cout << "--- RESULTADOS RADIX SORT (C++) ---" << endl;
    for (int tam : tamanos) {
        radixSortBenchmark(datosMaestros, tam);
    }

    return 0;
}