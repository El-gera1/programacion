#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>

using namespace std;
using namespace std::chrono;

const int RUN = 32;

void insertionSort(vector<int>& arr, int left, int right, long long& comparaciones, long long& intercambios) {
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left) {
            comparaciones++;
            if (arr[j] > temp) {
                arr[j + 1] = arr[j];
                intercambios++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = temp;
    }
}

void merge(vector<int>& arr, int l, int m, int r, long long& comparaciones, long long& intercambios) {
    int len1 = m - l + 1, len2 = r - m;
    vector<int> left(len1), right(len2);

    for (int i = 0; i < len1; i++) left[i] = arr[l + i];
    for (int i = 0; i < len2; i++) right[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;

    while (i < len1 && j < len2) {
        comparaciones++;
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        intercambios++;
        k++;
    }

    while (i < len1) {
        arr[k] = left[i];
        i++;
        intercambios++;
        k++;
    }

    while (j < len2) {
        arr[k] = right[j];
        j++;
        intercambios++;
        k++;
    }
}

void timSortBenchmark(const vector<int>& datosOriginales, int tam) {
    vector<int> arr(datosOriginales.begin(), datosOriginales.begin() + min((size_t)tam, datosOriginales.size()));
    int n = arr.size();
    if (n == 0) return;

    long long comparaciones = 0;
    long long intercambios = 0;

    auto inicio = high_resolution_clock::now();

    for (int i = 0; i < n; i += RUN) {
        insertionSort(arr, i, min((i + RUN - 1), (n - 1)), comparaciones, intercambios);
    }

    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = min((left + 2 * size - 1), (n - 1));

            if (mid < right) {
                merge(arr, left, mid, right, comparaciones, intercambios);
            }
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

    cout << "--- RESULTADOS TIM SORT (C++) ---" << endl;
    for (int tam : tamanos) {
        timSortBenchmark(datosMaestros, tam);
    }

    return 0;
}