#  Algoritmos de Ordenamiento con pruebas de 100, 1000, 10000, y 100000 registros , que esten aleatoriamente ordenados o preordenados al inverso
# 1 metodo de la borbuja


def bubbleSort(a):
    s = len(a)

    for i in range(s):
        isSwapped = False

        for j in range(0, s - i - 1):
            if a[j] > a[j + 1]:
                a[j], a[j + 1] = a[j + 1], a[j]
                isSwapped = True

        if not isSwapped:
            break

if __name__ == "__main__":
    a = [15, 16, 11, 13, 14]
    print("Antes de ordenar los elementos del array son:")
    for j in a:
        print(j, end=" ")

    bubbleSort(a)
    print("\nDespués de ordenar los elementos del array son:")
    for j in range(len(a)):
        print("%d" % a[j], end=" ")
