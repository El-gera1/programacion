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

def merge_sort_benchmark(arr):
    a = arr.copy()
    comparaciones = [0]
    intercambios = [0]  # Usamos listas para pasarlas por referencia en la recursión
    
    def merge_sort(sub_arr):
        if len(sub_arr) > 1:
            mid = len(sub_arr) // 2
            left_half = sub_arr[:mid]
            right_half = sub_arr[mid:]
            
            merge_sort(left_half)
            merge_sort(right_half)
            
            i = j = k = 0
            
            while i < len(left_half) and j < len(right_half):
                comparaciones[0] += 1
                if left_half[i] < right_half[j]:
                    sub_arr[k] = left_half[i]
                    i += 1
                else:
                    sub_arr[k] = right_half[j]
                    j += 1
                intercambios[0] += 1
                k += 1
                
            while i < len(left_half):
                sub_arr[k] = left_half[i]
                i += 1
                intercambios[0] += 1
                k += 1
                
            while j < len(right_half):
                sub_arr[k] = right_half[j]
                j += 1
                intercambios[0] += 1
                k += 1

    inicio = time.time()
    merge_sort(a)
    fin = time.time()
    
    tiempo_ms = (fin - inicio) * 1000
    return tiempo_ms, intercambios[0], comparaciones[0]

if __name__ == "__main__":
    tamanos = [100, 500, 1000, 10000, 100000]
    
    print("--- RESULTADOS MERGE SORT (PYTHON) ---")
    for tam in tamanos:
        datos_prueba = cargar_datos(tam)
        tiempo, swaps, comps = merge_sort_benchmark(datos_prueba)
        print(f"Tamaño: {tam} | Tiempo: {tiempo:.4f} ms | Intercambios: {swaps} | Comparaciones: {comps}")