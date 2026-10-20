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

        Console.WriteLine("--- RESULTADOS COUNTING SORT (C#) ---");

        foreach (int tam in tamanos) {
            int[] arr = datosMaestros.Take(tam).ToArray();
            int n = arr.Length;
            if (n == 0) continue;

            long comparaciones = 0;
            long intercambios = 0;

            Stopwatch sw = Stopwatch.StartNew();

            int minVal = arr[0];
            int maxVal = arr[0];
            for (int i = 1; i < n; i++) {
                if (arr[i] < minVal) minVal = arr[i];
                if (arr[i] > maxVal) maxVal = arr[i];
            }

            int k = maxVal - minVal + 1;
            int[] count = new int[k];
            int[] output = new int[n];

            for (int i = 0; i < n; i++) {
                count[arr[i] - minVal]++;
            }

            for (int i = 1; i < k; i++) {
                count[i] += count[i - 1];
            }

            for (int i = n - 1; i >= 0; i--) {
                output[count[arr[i] - minVal] - 1] = arr[i];
                count[arr[i] - minVal]--;
                intercambios++;
            }

            sw.Stop();

            Console.WriteLine($"Tamaño: {tam} | Tiempo: {sw.Elapsed.TotalMilliseconds:F4} ms | Intercambios: {intercambios} | Comparaciones: {comparaciones}");
        }
    }
}