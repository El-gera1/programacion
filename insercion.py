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

def insertion_sort_benchmark(arr):
    a = arr.copy()
    n = len(a)
    comparaciones = 0
    intercambios = 0  # En inserción se cuentan como desplazamientos/movimientos
    
    inicio = time.time()
    
    for i in range(1, n):
        key = a[i]
        j = i - 1
        
        while j >= 0:
            comparaciones += 1
            if a[j] > key:
                a[j + 1] = a[j]
                intercambios += 1
                j -= 1
            else:
                break
                
        a[j + 1] = key
        
    fin = time.time()
    tiempo_ms = (fin - inicio) * 1000
    
    return tiempo_ms, intercambios, comparaciones

if __name__ == "__main__":
    tamanos = [100, 500, 1000, 10000, 100000]
    
    print("--- RESULTADOS INSERCIÓN (PYTHON) ---")
    for tam in tamanos:
        datos_prueba = cargar_datos(tam)
        tiempo, swaps, comps = insertion_sort_benchmark(datos_prueba)
        print(f"Tamaño: {tam} | Tiempo: {tiempo:.4f} ms | Intercambios: {swaps} | Comparaciones: {comps}")