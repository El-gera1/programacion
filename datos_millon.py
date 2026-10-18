import random

def generar_archivos_prueba():
    print("Generando el archivo con 1 millón de números aleatorios...")
    millon_datos = [random.randint(1, 10000000) for _ in range(1000000)]
    with open("datos_millon.txt", "w") as f:
        for num in millon_datos:
            f.write(f"{num}\n")
    print("¡Archivo 'datos_millon.txt' creado con éxito!")

if __name__ == "__main__":
    generar_archivos_prueba()