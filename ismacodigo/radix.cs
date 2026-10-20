using System;
using System.IO;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;

class Program {
    static long intercambios = 0;

    static void Main() {
        List<int> datosMaestros = new List<int>();

        foreach (string linea in File.ReadLines("datos_millon.txt")) {
            if (int.TryParse(linea.Trim(), out int num)) {
                datosMaestros.Add(num);
            }
        }

        int[] tamanos = { 100, 500, 1000, 10000, 100000 };

        Console.WriteLine("--- RESULTADOS RADIX SORT (C#) ---");

        foreach (int tam in tamanos) {
            int[] arr = datosMaestros.Take(tam).ToArray();
            int n = arr.Length;
            if (n == 0) continue;

            intercambios = 0;
            long comparaciones = 0;

            Stopwatch sw = Stopwatch.StartNew();

            int minVal = arr[0];
            for (int i = 1; i < n; i++) {
                if (arr[i] < minVal) minVal = arr[i];
            }

            int offset = 0;
            if (minVal < 0) {
                offset = Math.Abs(minVal);
                for (int i = 0; i < n; i++) arr[i] += offset;
            }

            int maxVal = arr[0];
            for (int i = 1; i < n; i++) {
                if (arr[i] > maxVal) maxVal = arr[i];
            }

            for (int exp = 1; maxVal / exp > 0; exp *= 10) {
                CountingSortForRadix(arr, n, exp);
            }

            if (minVal < 0) {
                for (int i = 0; i < n; i++) arr[i] -= offset;
            }

            sw.Stop();

            Console.WriteLine($"Tamaño: {tam} | Tiempo: {sw.Elapsed.TotalMilliseconds:F4} ms | Intercambios: {intercambios} | Comparaciones: {comparaciones}");
        }
    }

    static void CountingSortForRadix(int[] arr, int n, int exp) {
        int[] output = new int[n];
        int[] count = new int[10];

        for (int i = 0; i < n; i++) {
            count[(arr[i] / exp) % 10]++;
        }

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            int digit = (arr[i] / exp) % 10;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
            intercambios++;
        }

        Array.Copy(output, 0, arr, 0, n);
    }
}