import time

# Cargar aleatorios del archivo maestro
def cargar_aleatorio(cantidad):
    datos = []
    with open("datos_millon.txt", "r") as f:
        for _ in range(cantidad):
            linea = f.readline()
            if not linea: break
            datos.append(int(linea.strip()))
    return datos

# Generar ordenado (0 a N)
def generar_ordenado(cantidad):
    return list(range(cantidad))

# Generar inverso (N a 0)
def generar_inverso(cantidad):
    return list(range(cantidad, 0, -1))

print("=== ESTRUCTURA DE PRUEBAS COMPLETA APROBADA ===")
print("1. Caso Aleatorio (Cargado de datos_millon.txt)")
print("2. Caso Ordenado (Bucle 0 a N)")
print("3. Caso Inverso (Bucle N a 0)")