arr = []

for f1 in range(3):
    print("filas")

    num1 = int(input("Ingresa el primer numero: "))
    num2 = int(input("Ingresa el segundo numero: "))
    num3 = int(input("Ingresa el tercer numero: "))

    sf = num1 + num2 + num3

    arr.append(sf)

total = arr[0] + arr[1] + arr[2]

print("arreglo", arr, "— total:", total)