import time

def cargar_aleatorio(cantidad):
    datos = []
    try:
        with open("datos_millon.txt", "r") as f:
            for _ in range(cantidad):
                linea = f.readline()
                if not linea: break
                datos.append(int(linea.strip()))
    except FileNotFoundError:
        datos = list(range(cantidad, 0, -1)) # Fallback si no está el archivo
    return datos

def generar_ordenado(cantidad):
    return list(range(cantidad))

def generar_inverso(cantidad):
    return list(range(cantidad, 0, -1))

# Ejemplo de prueba con un algoritmo eficiente (Merge Sort) y uno lento (Burbuja)
def bubble_sort(arr):
    a = arr.copy()
    n = len(a)
    comparaciones = 0
    intercambios = 0
    inicio = time.time()
    for i in range(n):
        for j in range(0, n - i - 1):
            comparaciones += 1
            if a[j] > a[j + 1]:
                a[j], a[j + 1] = a[j + 1], a[j]
                intercambios += 1
    fin = time.time()
    return (fin - inicio) * 1000, intercambios, comparaciones

if __name__ == "__main__":
    tamanos = [100, 1000, 10000, 100000] # Usa 100000 con cuidado en Burbuja por el tiempo
    print("=== PRUEBAS POR ESCENARIOS (BURBUJA DE EJEMPLO) ===")
    
    for tam in tamanos:
        print(f"\n--- TAMAÑO: {tam} ---")
        
        # 1. Aleatorio
        arr_rand = cargar_aleatorio(tam)
        t, s, c = bubble_sort(arr_rand)
        print(f"[Aleatorio] Tiempo: {t:.4f} ms | Intercambios: {s} | Comparaciones: {c}")
        
        # 2. Ordenado
        arr_ord = generar_ordenado(tam)
        t, s, c = bubble_sort(arr_ord)
        print(f"[Ordenado]  Tiempo: {t:.4f} ms | Intercambios: {s} | Comparaciones: {c}")
        
        # 3. Inverso
        arr_inv = generar_inverso(tam)
        t, s, c = bubble_sort(arr_inv)
        print(f"[Inverso]   Tiempo: {t:.4f} ms | Intercambios: {s} | Comparaciones: {c}")