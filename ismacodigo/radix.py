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

def counting_sort_for_radix(arr, exp):
    n = len(arr)
    output = [0] * n
    count = [0] * 10
    intercambios_locales = 0
    
    for i in range(n):
        index = (arr[i] // exp)
        count[index % 10] += 1
        
    for i in range(1, 10):
        count[i] += count[i - 1]
        
    for i in range(n - 1, -1, -1):
        index = (arr[i] // exp)
        output[count[index % 10] - 1] = arr[i]
        count[index % 10] -= 1
        intercambios_locales += 1
        
    for i in range(n):
        arr[i] = output[i]
        
    return intercambios_locales

def radix_sort_benchmark(arr):
    a = arr.copy()
    if not a:
        return 0, 0, 0
    
    comparaciones = 0  # No hay comparaciones relativas
    intercambios = 0
    
    inicio = time.time()
    
    max_val = max(a)
    
    # Manejar posibles números negativos si los hubiera en el archivo maestro
    min_val = min(a)
    if min_val < 0:
        # Desplazar temporalmente a positivos para Radix estándar
        offset = abs(min_val)
        a = [x + offset for x in a]
        max_val = max(a)
        
    exp = 1
    while max_val // exp > 0:
        intercambios += counting_sort_for_radix(a, exp)
        exp *= 10
        
    if min_val < 0:
        a = [x - offset for x in a]
        
    fin = time.time()
    tiempo_ms = (fin - inicio) * 1000
    
    return tiempo_ms, intercambios, comparaciones

if __name__ == "__main__":
    tamanos = [100, 500, 1000, 10000, 100000]
    
    print("--- RESULTADOS RADIX SORT (PYTHON) ---")
    for tam in tamanos:
        datos_prueba = cargar_datos(tam)
        tiempo, swaps, comps = radix_sort_benchmark(datos_prueba)
        print(f"Tamaño: {tam} | Tiempo: {tiempo:.4f} ms | Intercambios: {swaps} | Comparaciones: {comps}")