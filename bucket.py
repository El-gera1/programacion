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

def bucket_sort_benchmark(arr):
    a = arr.copy()
    n = len(a)
    if n <= 1:
        return 0.0, 0, 0
    
    comparaciones = [0]
    intercambios = [0]
    
    inicio = time.time()
    
    min_val = min(a)
    max_val = max(a)
    rango = max_val - min_val + 1
    
    # Definir número de cubetas (por ejemplo, basado en la raíz cuadrada de n o un tamaño fijo)
    num_buckets = max(1, min(n, 100))
    buckets = [[] for _ in range(num_buckets)]
    
    # Distribuir elementos en cubetas
    for num in a:
        # Calcular el índice de la cubeta
        # Normalizamos el valor al rango [0, num_buckets - 1]
        if rango == 1:
            index = 0
        else:
            index = int((num - min_val) * (num_buckets - 1) / (max_val - min_val))
        buckets[index].append(num)
        intercambios[0] += 1  # Movimiento hacia la cubeta
        
    # Ordenar cada cubeta (usando Inserción y contando sus métricas internas)
    sorted_array = []
    for bucket in buckets:
        # Insertion sort local para la cubeta
        for i in range(1, len(bucket)):
            key = bucket[i]
            j = i - 1
            while j >= 0:
                comparaciones[0] += 1
                if bucket[j] > key:
                    bucket[j + 1] = bucket[j]
                    intercambios[0] += 1
                    j -= 1
                else:
                    break
            bucket[j + 1] = key
        sorted_array.extend(bucket)
        
    fin = time.time()
    tiempo_ms = (fin - inicio) * 1000
    
    return tiempo_ms, intercambios[0], comparaciones[0]

if __name__ == "__main__":
    tamanos = [100, 500, 1000, 10000, 100000]
    
    print("--- RESULTADOS BUCKET SORT (PYTHON) ---")
    for tam in tamanos:
        datos_prueba = cargar_datos(tam)
        tiempo, swaps, comps = bucket_sort_benchmark(datos_prueba)
        print(f"Tamaño: {tam} | Tiempo: {tiempo:.4f} ms | Intercambios: {swaps} | Comparaciones: {comps}")