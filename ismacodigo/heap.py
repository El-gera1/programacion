import os
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

def heap_sort_benchmark(arr):
    a = arr.copy()
    n = len(a)
    comparaciones = 0
    intercambios = 0
    
    def heapify(n, i):
        nonlocal comparaciones, intercambios
        largest = i
        left = 2 * i + 1
        right = 2 * i + 2
        
        if left < n:
            comparaciones += 1
            if a[left] > a[largest]:
                largest = left
                
        if right < n:
            comparaciones += 1
            if a[right] > a[largest]:
                largest = right
                
        if largest != i:
            a[i], a[largest] = a[largest], a[i]
            intercambios += 1
            heapify(n, largest)

    inicio = time.time()
    
    # Construir el max heap
    for i in range(n // 2 - 1, -1, -1):
        heapify(n, i)
        
    # Extraer elementos uno por uno del heap
    for i in range(n - 1, 0, -1):
        a[i], a[0] = a[0], a[i]
        intercambios += 1
        heapify(i, 0)
        
    fin = time.time()
    tiempo_ms = (fin - inicio) * 1000
    
    return tiempo_ms, intercambios, comparaciones

if __name__ == "__main__":
    tamanos = [100, 500, 1000, 10000, 100000]
    
    print("--- RESULTADOS HEAP SORT (PYTHON) ---")
    for tam in tamanos:
        datos_prueba = cargar_datos(tam)
        tiempo, swaps, comps = heap_sort_benchmark(datos_prueba)
        print(f"Tamaño: {tam} | Tiempo: {tiempo:.4f} ms | Intercambios: {swaps} | Comparaciones: {comps}")