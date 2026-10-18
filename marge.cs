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

        Console.WriteLine("--- RESULTADOS MERGE SORT (C#) ---");

        foreach (int tam in tamanos) {
            int[] arr = datosMaestros.Take(tam).ToArray();
            comparaciones = 0;
            intercambios = 0;

            Stopwatch sw = Stopwatch.StartNew();
            MergeSort(arr, 0, arr.Length - 1);
            sw.Stop();

            Console.WriteLine($"Tamaño: {tam} | Tiempo: {sw.Elapsed.TotalMilliseconds:F4} ms | Intercambios: {intercambios} | Comparaciones: {comparaciones}");
        }
    }

    static void MergeSort(int[] arr, int izq, int der) {
        if (izq < der) {
            int medio = izq + (der - izq) / 2;
            MergeSort(arr, izq, medio);
            MergeSort(arr, medio + 1, der);
            Merge(arr, izq, medio, der);
        }
    }

    static void Merge(int[] arr, int izq, int medio, int der) {
        int n1 = medio - izq + 1;
        int n2 = der - medio;

        int[] izqArr = new int[n1];
        int[] derArr = new int[n2];

        Array.Copy(arr, izq, izqArr, 0, n1);
        Array.Copy(arr, medio + 1, derArr, 0, n2);

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
}