import random
import time


def burbuja(lista):
    n = len(lista)

    for i in range(n - 1):
        for j in range(n - 1 - i):
            if lista[j] > lista[j + 1]:
                lista[j], lista[j + 1] = lista[j + 1], lista[j]


cantidades = [100, 1000, 10000, 100000]

for cantidad in cantidades:

    print("\nRegistros:", cantidad)


    aleatorios = list(range(cantidad))
    random.shuffle(aleatorios)

    inicio = time.perf_counter()
    burbuja(aleatorios)
    fin = time.perf_counter()

    print("Aleatorio:", fin - inicio, "segundos")

  
    ordenados = list(range(cantidad))

    inicio = time.perf_counter()
    burbuja(ordenados)
    fin = time.perf_counter()

    print("Ordenado:", fin - inicio, "segundos")

    inversos = list(range(cantidad, 0, -1))

    inicio = time.perf_counter()
    burbuja(inversos)
    fin = time.perf_counter()

    print("Inverso:", fin - inicio, "segundos")