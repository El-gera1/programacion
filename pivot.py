def partition(a, l, h):
    # Selecciona el elemento pivote
    pvt = a[h]
    # j es el índice de los elementos que son menores que el pivote
    j = l - 1
    for k in range(l, h):
        if a[k] < pvt:  # Corregido: faltaban los dos puntos ':'
            j += 1
            swap(a, j, k)
    swap(a, j + 1, h)  # Corregido: para colocar el pivote en su lugar correcto es j + 1
    return j + 1


def swap(a, j, k):  # Corregido: decía 'awap'
    a[j], a[k] = a[k], a[j]


def qcksort(a, l, h):
    if l < h:  # Corregido: faltaba la condición de parada para evitar un bucle infinito
        pi = partition(a, l, h)
        qcksort(a, l, pi - 1)
        qcksort(a, pi + 1, h)  # Corregido: la sintaxis de los parámetros decía 'pi, + 1, h'


if __name__ == "__main__":
    a = [10, 7, 8, 9, 1, 5]
    size = len(a)

    print("El arreglo antes de ordenarlo: ")
    for v in a:
        print(v, end=" ")
    print()

    qcksort(a, 0, size - 1)

    print("El arreglo despues de ordenarlo: ")
    for v in a:
        print(v, end=" ")
