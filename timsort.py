import os
import time

RUN = 32

def cargar_datos(cantidad):
    """Lee 'cantidad' de elementos del archivo maestro."""
    datos = []
    with open("datos_millon.txt", "r") as f:
        for _ in range(cantidad):
            linea = f.readline()
            if not linea:
                break
            datos.append(int(linea.strip()))
    return datos

def tim_sort_benchmark(arr):
    a = arr.copy()
    n = len(a)
    comparaciones = [0]
    intercambios = [0]
    
    def insertion_sort(left, right):
        for i in range(left + 1, right + 1):
            temp = a[i]
            j = i - 1
            while j >= left:
                comparaciones[0] += 1
                if a[j] > temp:
                    a[j + 1] = a[j]
                    intercambios[0] += 1
                    j -= 1
                else:
                    break
            a[j + 1] = temp

    def merge(l, m, r):
        len1, len2 = m - l + 1, r - m
        left = a[l:m + 1]
        right = a[m + 1:r + 1]

        i = j = 0
        k = l

        while i < len1 and j < len2:
            comparaciones[0] += 1
            if left[i] <= right[j]:
                a[k] = left[i]
                i += 1
            else:
                a[k] = right[j]
                j += 1
            intercambios[0] += 1
            k += 1

        while i < len1:
            a[k] = left[i]
            i += 1
            intercambios[0] += 1
            k += 1

        while j < len2:
            a[k] = right[j]
            j += 1
            intercambios[0] += 1
            k += 1

    inicio = time.time()

    # 1. Ordenar pequeños subarreglos de tamaño RUN
    for i in range(0, n, RUN):
        insertion_sort(i, min(i + RUN - 1, n - 1))

    # 2. Mezclar subarreglos
    size = RUN
    while size < n:
        for left in range(0, n, 2 * size):
            mid = min(n - 1, left + size - 1)
            right = min((left + 2 * size - 1), (n - 1))
            if mid < right:
                merge(left, mid, right)
        size = 2 * size

    fin = time.time()
    tiempo_ms = (fin - inicio) * 1000

    return tiempo_ms, intercambios[0], comparaciones[0]

if __name__ == "__main__":
    tamanos = [100, 500, 1000, 10000, 100000]
    
    print("--- RESULTADOS TIM SORT (PYTHON) ---")
    for tam in tamanos:
        datos_prueba = cargar_datos(tam)
        tiempo, swaps, comps = tim_sort_benchmark(datos_prueba)
        print(f"Tamaño: {tam} | Tiempo: {tiempo:.4f} ms | Intercambios: {swaps} | Comparaciones: {comps}")