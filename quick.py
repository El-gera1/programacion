import os
import time
import sys

# Aumentar el límite de recursión por seguridad con 100,000 elementos
sys.setrecursionlimit(200000)

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

def quick_sort_benchmark(arr):
    a = arr.copy()
    comparaciones = [0]
    intercambios = [0]
    
    def partition(low, high):
        pivot = a[high]
        i = low - 1
        for j in range(low, high):
            comparaciones[0] += 1
            if a[j] <= pivot:
                i += 1
                a[i], a[j] = a[j], a[i]
                intercambios[0] += 1
        a[i + 1], a[high] = a[high], a[i + 1]
        intercambios[0] += 1
        return i + 1

    def quick_sort(low, high):
        if low < high:
            pi = partition(low, high)
            quick_sort(low, pi - 1)
            quick_sort(pi + 1, high)

    inicio = time.time()
    if len(a) > 0:
        quick_sort(0, len(a) - 1)
    fin = time.time()
    
    tiempo_ms = (fin - inicio) * 1000
    return tiempo_ms, intercambios[0], comparaciones[0]

if __name__ == "__main__":
    tamanos = [100, 500, 1000, 10000, 100000]
    
    print("--- RESULTADOS QUICK SORT (PYTHON) ---")
    for tam in tamanos:
        datos_prueba = cargar_datos(tam)
        tiempo, swaps, comps = quick_sort_benchmark(datos_prueba)
        print(f"Tamaño: {tam} | Tiempo: {tiempo:.4f} ms | Intercambios: {swaps} | Comparaciones: {comps}")