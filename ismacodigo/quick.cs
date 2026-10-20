using System;
using System.IO;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;

class Program {
    static long comparaciones = 0;
    static long intercambios = 0;

    static void Main() {
        List<int> datosMaestros = new List<int>();

        foreach (string linea in File.ReadLines("datos_millon.txt")) {
            if (int.TryParse(linea.Trim(), out int num)) {
                datosMaestros.Add(num);
            }
        }

        int[] tamanos = { 100, 500, 1000, 10000, 100000 };

        Console.WriteLine("--- RESULTADOS QUICK SORT (C#) ---");

        foreach (int tam in tamanos) {
            int[] arr = datosMaestros.Take(tam).ToArray();
            comparaciones = 0;
            intercambios = 0;

            Stopwatch sw = Stopwatch.StartNew();
            if (arr.Length > 0) {
                QuickSort(arr, 0, arr.Length - 1);
            }
            sw.Stop();

            Console.WriteLine($"Tamaño: {tam} | Tiempo: {sw.Elapsed.TotalMilliseconds:F4} ms | Intercambios: {intercambios} | Comparaciones: {comparaciones}");
        }
    }

    static void QuickSort(int[] arr, int low, int high) {
        if (low < high) {
            int pi = Partition(arr, low, high);
            QuickSort(arr, low, pi - 1);
            QuickSort(arr, pi + 1, high);
        }
    }

    static int Partition(int[] arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            comparaciones++;
            if (arr[j] <= pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                intercambios++;
            }
        }

        int temp2 = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp2;
        intercambios++;

        return i + 1;
    }
}