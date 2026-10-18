import os
import random
import time

def asegurar_archivo():
    """Verifica si el archivo maestro existe; si no, lo genera automáticamente."""
    if not os.path.exists("datos_millon.txt"):
        print("El archivo 'datos_millon.txt' no se encontró. Generándolo automáticamente...")
        with open("datos_millon.txt", "w") as f:
            for _ in range(1000000):
                f.write(f"{random.randint(1, 10000000)}\n")
        print("¡Archivo generado con éxito!\n")

def cargar_datos(cantidad):
    """Asegura que el archivo exista y lee 'cantidad' de elementos."""
    asegurar_archivo()
    datos = []
    with open("datos_millon.txt", "r") as f:
        for _ in range(cantidad):
            linea = f.readline()
            if not linea:
                break
            datos.append(int(linea.strip()))
    return datos

def bubble_sort_benchmark(arr):
    a = arr.copy()
    n = len(a)
    comparaciones = 0
    intercambios = 0
    
    inicio = time.time()
    
    swapped = True
    while swapped and n > 1:
        swapped = False
        for i in range(1, n):
            comparaciones += 1
            if a[i - 1] > a[i]:
                a[i - 1], a[i] = a[i], a[i - 1]
                intercambios += 1
                swapped = True
        n -= 1
        
    fin = time.time()
    tiempo_ms = (fin - inicio) * 1000
    
    return tiempo_ms, intercambios, comparaciones

if __name__ == "__main__":
    # Tamaños de prueba actualizados hasta 100,000
    tamanos = [100, 500, 1000, 10000, 100000]
    
    print("--- RESULTADOS BURBUJA (PYTHON) ---")
    for tam in tamanos:
        datos_prueba = cargar_datos(tam)
        tiempo, swaps, comps = bubble_sort_benchmark(datos_prueba)
        print(f"Tamaño: {tam} | Tiempo: {tiempo:.4f} ms | Intercambios: {swaps} | Comparaciones: {comps}")