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

def shell_sort_benchmark(arr):
    a = arr.copy()
    n = len(a)
    comparaciones = 0
    intercambios = 0
    
    inicio = time.time()
    
    # Secuencia de brechas inicial (n / 2)
    gap = n // 2
    while gap > 0:
        for i in range(gap, n):
            temp = a[i]
            j = i
            while j >= gap:
                comparaciones += 1
                if a[j - gap] > temp:
                    a[j] = a[j - gap]
                    intercambios += 1
                    j -= gap
                else:
                    break
            a[j] = temp
        gap //= 2
        
    fin = time.time()
    tiempo_ms = (fin - inicio) * 1000
    
    return tiempo_ms, intercambios, comparaciones

if __name__ == "__main__":
    tamanos = [100, 500, 1000, 10000, 100000]
    
    print("--- RESULTADOS SHELL SORT (PYTHON) ---")
    for tam in tamanos:
        datos_prueba = cargar_datos(tam)
        tiempo, swaps, comps = shell_sort_benchmark(datos_prueba)
        print(f"Tamaño: {tam} | Tiempo: {tiempo:.4f} ms | Intercambios: {swaps} | Comparaciones: {comps}")