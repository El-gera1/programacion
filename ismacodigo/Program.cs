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

        Console.WriteLine("--- RESULTADOS BURBUJA (C#) ---");

        foreach (int tam in tamanos) {
            int[] arr = datosMaestros.Take(tam).ToArray();
            int n = arr.Length;
            long comparaciones = 0;
            long intercambios = 0;

            Stopwatch sw = Stopwatch.StartNew();

            bool swapped = true;
            while (swapped && n > 1) {
                swapped = false;
                for (int i = 1; i < n; i++) {
                    comparaciones++;
                    if (arr[i - 1] > arr[i]) {
                        int temp = arr[i - 1];
                        arr[i - 1] = arr[i];
                        arr[i] = temp;
                        intercambios++;
                        swapped = true;
                    }
                }
                n--;
            }

            sw.Stop();

            Console.WriteLine($"Tamaño: {tam} | Tiempo: {sw.Elapsed.TotalMilliseconds:F4} ms | Intercambios: {intercambios} | Comparaciones: {comparaciones}");
        }
    }
}