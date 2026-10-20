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

        Console.WriteLine("--- RESULTADOS SELECCIÓN (C#) ---");

        foreach (int tam in tamanos) {
            int[] arr = datosMaestros.Take(tam).ToArray();
            int n = arr.Length;
            long comparaciones = 0;
            long intercambios = 0;

            Stopwatch sw = Stopwatch.StartNew();

            for (int i = 0; i < n - 1; i++) {
                int minIdx = i;
                for (int j = i + 1; j < n; j++) {
                    comparaciones++;
                    if (arr[j] < arr[minIdx]) {
                        minIdx = j;
                    }
                }
                if (minIdx != i) {
                    int temp = arr[i];
                    arr[i] = arr[minIdx];
                    arr[minIdx] = temp;
                    intercambios++;
                }
            }

            sw.Stop();

            Console.WriteLine($"Tamaño: {tam} | Tiempo: {sw.Elapsed.TotalMilliseconds:F4} ms | Intercambios: {intercambios} | Comparaciones: {comparaciones}");
        }
    }
}