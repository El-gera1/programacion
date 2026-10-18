using System;
using System.IO;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;

class Program {
    static void Main() {
        List<int> datosMaestros = new List<int>();

        foreach (string linea in File.ReadLines("datos_millon.txt")) {
            if (int.TryParse(linea.Trim(), out int num)) {
                datosMaestros.Add(num);
            }
        }

        int[] tamanos = { 100, 500, 1000, 10000, 100000 };

        Console.WriteLine("--- RESULTADOS BUCKET SORT (C#) ---");

        foreach (int tam in tamanos) {
            int[] arr = datosMaestros.Take(tam).ToArray();
            int n = arr.Length;
            if (n <= 1) continue;

            long comparaciones = 0;
            long intercambios = 0;

            Stopwatch sw = Stopwatch.StartNew();

            int minVal = arr[0];
            int maxVal = arr[0];
            for (int i = 1; i < n; i++) {
                if (arr[i] < minVal) minVal = arr[i];
                if (arr[i] > maxVal) maxVal = arr[i];
            }

            long rango = (long)maxVal - minVal + 1;
            int numBuckets = Math.Max(1, Math.Min(n, 100));
            List<int>[] buckets = new List<int>[numBuckets];
            for (int i = 0; i < numBuckets; i++) {
                buckets[i] = new List<int>();
            }

            foreach (int num in arr) {
                int index;
                if (rango == 1) {
                    index = 0;
                } else {
                    index = (int)(((long)(num - minVal) * (numBuckets - 1)) / (maxVal - minVal));
                }
                buckets[index].Add(num);
                intercambios++;
            }

            int k = 0;
            foreach (var bucket in buckets) {
                // Insertion sort local
                for (int i = 1; i < bucket.Count; i++) {
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

                foreach (int num in bucket) {
                    arr[k++] = num;
                }
            }

            sw.Stop();

            Console.WriteLine($"Tamaño: {tam} | Tiempo: {sw.Elapsed.TotalMilliseconds:F4} ms | Intercambios: {intercambios} | Comparaciones: {comparaciones}");
        }
    }
}