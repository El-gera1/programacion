using System;
using System.IO;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;

class Program {
    const int RUN = 32;
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

        Console.WriteLine("--- RESULTADOS TIM SORT (C#) ---");

        foreach (int tam in tamanos) {
            int[] arr = datosMaestros.Take(tam).ToArray();
            int n = arr.Length;
            if (n == 0) continue;

            comparaciones = 0;
            intercambios = 0;

            Stopwatch sw = Stopwatch.StartNew();

            TimSort(arr, n);

            sw.Stop();

            Console.WriteLine($"Tamaño: {tam} | Tiempo: {sw.Elapsed.TotalMilliseconds:F4} ms | Intercambios: {intercambios} | Comparaciones: {comparaciones}");
        }
    }

    static void InsertionSort(int[] arr, int left, int right) {
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

    static void Merge(int[] arr, int l, int m, int r) {
        int len1 = m - l + 1, len2 = r - m;
        int[] left = new int[len1];
        int[] right = new int[len2];

        Array.Copy(arr, l, left, 0, len1);
        Array.Copy(arr, m + 1, right, 0, len2);

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

    static void TimSort(int[] arr, int n) {
        for (int i = 0; i < n; i += RUN) {
            InsertionSort(arr, i, Math.Min((i + RUN - 1), (n - 1)));
        }

        for (int size = RUN; size < n; size = 2 * size) {
            for (int left = 0; left < n; left += 2 * size) {
                int mid = left + size - 1;
                int right = Math.Min((left + 2 * size - 1), (n - 1));

                if (mid < right) {
                    Merge(arr, left, mid, right);
                }
            }
        }
    }
}