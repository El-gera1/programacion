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

        Console.WriteLine("--- RESULTADOS SHELL SORT (C#) ---");

        foreach (int tam in tamanos) {
            int[] arr = datosMaestros.Take(tam).ToArray();
            int n = arr.Length;
            long comparaciones = 0;
            long intercambios = 0;

            Stopwatch sw = Stopwatch.StartNew();

            int gap = n / 2;
            while (gap > 0) {
                for (int i = gap; i < n; i++) {
                    int temp = arr[i];
                    int j = i;
                    while (j >= gap) {
                        comparaciones++;
                        if (arr[j - gap] > temp) {
                            arr[j] = arr[j - gap];
                            intercambios++;
                            j -= gap;
                        } else {
                            break;
                        }
                    }
                    arr[j] = temp;
                }
                gap /= 2;
            }

            sw.Stop();

            Console.WriteLine($"Tamaño: {tam} | Tiempo: {sw.Elapsed.TotalMilliseconds:F4} ms | Intercambios: {intercambios} | Comparaciones: {comparaciones}");
        }
    }
}