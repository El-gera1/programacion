import os
import random
import time

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

def selection_sort_benchmark(arr):
    a = arr.copy()
    n = len(a)
    comparaciones = 0
    intercambios = 0
    
    inicio = time.time()
    
    for i in range(n - 1):
        min_idx = i
        for j in range(i + 1, n):
            comparaciones += 1
            if a[j] < a[min_idx]:
                min_idx = j
                
        if min_idx != i:
            # Intercambiar el elemento mínimo con el primero de la parte no ordenada
            a[i], a[min_idx] = a[min_idx], a[i]
            intercambios += 1
            
    fin = time.time()
    tiempo_ms = (fin - inicio) * 1000
    
    return tiempo_ms, intercambios, comparaciones

if __name__ == "__main__":
    tamanos = [100, 500, 1000, 10000, 100000]
    
    print("--- RESULTADOS SELECCIÓN (PYTHON) ---")
    for tam in tamanos:
        datos_prueba = cargar_datos(tam)
        tiempo, swaps, comps = selection_sort_benchmark(datos_prueba)
        print(f"Tamaño: {tam} | Tiempo: {tiempo:.4f} ms | Intercambios: {swaps} | Comparaciones: {comps}")
        