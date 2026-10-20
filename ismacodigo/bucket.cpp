#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>

using namespace std;
using namespace std::chrono;

void bucketSortBenchmark(const vector<int>& datosOriginales, int tam) {
    vector<int> arr(datosOriginales.begin(), datosOriginales.begin() + min((size_t)tam, datosOriginales.size()));
    int n = arr.size();
    if (n <= 1) return;

    long long comparaciones = 0;
    long long intercambios = 0;

    auto inicio = high_resolution_clock::now();

    int minVal = arr[0], maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    long long rango = (long long)maxVal - minVal + 1;
    int numBuckets = max(1, min(n, 100));
    vector<vector<int>> buckets(numBuckets);

    for (int num : arr) {
        int index;
        if (rango == 1) {
            index = 0;
        } else {
            index = (int)(((long long)(num - minVal) * (numBuckets - 1)) / (maxVal - minVal));
        }
        buckets[index].push_back(num);
        intercambios++;
    }

    int k = 0;
    for (auto& bucket : buckets) {
        // Insertion sort local
        for (size_t i = 1; i < bucket.size(); i++) {
            int key = bucket[i];
            int j = i - 1;
            while (j >= 0) {
                comparaciones++;
                if (bucket[j] > key) {
                    bucket[j + 1] = bucket[j];
                    intercambios++;
                    j--;
                } else {
                    break;
                }
            }
            bucket[j + 1] = key;
        }

        for (int num : bucket) {
            arr[k++] = num;
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

    cout << "--- RESULTADOS BUCKET SORT (C++) ---" << endl;
    for (int tam : tamanos) {
        bucketSortBenchmark(datosMaestros, tam);
    }

    return 0;
}