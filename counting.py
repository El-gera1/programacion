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

def counting_sort_benchmark(arr):
    a = arr.copy()
    if not a:
        return 0, 0, 0
    
    comparaciones = 0  # No hay comparaciones relativas entre elementos
    intercambios = 0   # Se cuentan las asignaciones/movimientos de valores
    
    inicio = time.time()
    
    min_val = min(a)
    max_val = max(a)
    k = max_val - min_val + 1
    
    count = [0] * k
    output = [0] * len(a)
    
    # Contar frecuencias
    for num in a:
        count[num - min_val] += 1
        
    # Acumular sumas para determinar posiciones
    for i in range(1, k):
        count[i] += count[i - 1]
        
    # Construir el arreglo ordenado de salida
    for i in range(len(a) - 1, -1, -1):
        num = a[i]
        output[count[num - min_val] - 1] = num
        count[num - min_val] -= 1
        intercambios += 1
        
    fin = time.time()
    tiempo_ms = (fin - inicio) * 1000
    
    return tiempo_ms, intercambios, comparaciones

if __name__ == "__main__":
    tamanos = [100, 500, 1000, 10000, 100000]
    
    print("--- RESULTADOS COUNTING SORT (PYTHON) ---")
    for tam in tamanos:
        datos_prueba = cargar_datos(tam)
        tiempo, swaps, comps = counting_sort_benchmark(datos_prueba)
        print(f"Tamaño: {tam} | Tiempo: {tiempo:.4f} ms | Intercambios: {swaps} | Comparaciones: {comps}")