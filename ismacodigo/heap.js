const fs = require('fs');

function heapSortBenchmark(arr) {
    let a = [...arr];
    let n = a.length;
    let comparaciones = 0;
    let intercambios = 0;

    function heapify(n, i) {
        let largest = i;
        let left = 2 * i + 1;
        let right = 2 * i + 2;

        if (left < n) {
            comparaciones++;
            if (a[left] > a[largest]) {
                largest = left;
            }
        }

        if (right < n) {
            comparaciones++;
            if (a[right] > a[largest]) {
                largest = right;
            }
        }

        if (largest !== i) {
            let temp = a[i];
            a[i] = a[largest];
            a[largest] = temp;
            intercambios++;
            heapify(n, largest);
        }
    }

    let inicio = performance.now();

    for (let i = Math.floor(n / 2) - 1; i >= 0; i--) {
        heapify(n, i);
    }

    for (let i = n - 1; i > 0; i--) {
        let temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        intercambios++;
        heapify(i, 0);
    }

    let fin = performance.now();

    return {
        tiempo: fin - inicio,
        intercambios: intercambios,
        comparaciones: comparaciones
    };
}

const tamanos = [100, 500, 1000, 10000, 100000];
const contenido = fs.readFileSync('datos_millon.txt', 'utf-8');
const lineas = contenido.split('\n').filter(Boolean);

console.log("--- RESULTADOS HEAP SORT (JAVASCRIPT) ---");

for (let tam of tamanos) {
    const datosPrueba = lineas.slice(0, tam).map(Number);
    const resultados = heapSortBenchmark(datosPrueba);
    console.log(`Tamaño: ${tam} | Tiempo: ${resultados.tiempo.toFixed(4)} ms | Intercambios: ${resultados.intercambios} | Comparaciones: ${resultados.comparaciones}`);
}