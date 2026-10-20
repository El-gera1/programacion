const fs = require('fs');

function quickSortBenchmark(arr) {
    let a = [...arr];
    let comparaciones = 0;
    let intercambios = 0;

    function partition(low, high) {
        let pivot = a[high];
        let i = low - 1;

        for (let j = low; j < high; j++) {
            comparaciones++;
            if (a[j] <= pivot) {
                i++;
                let temp = a[i];
                a[i] = a[j];
                a[j] = temp;
                intercambios++;
            }
        }

        let temp = a[i + 1];
        a[i + 1] = a[high];
        a[high] = temp;
        intercambios++;

        return i + 1;
    }

    function quickSort(low, high) {
        if (low < high) {
            let pi = partition(low, high);
            quickSort(low, pi - 1);
            quickSort(pi + 1, high);
        }
    }

    let inicio = performance.now();
    if (a.length > 0) {
        quickSort(0, a.length - 1);
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

console.log("--- RESULTADOS QUICK SORT (JAVASCRIPT) ---");

for (let tam of tamanos) {
    const datosPrueba = lineas.slice(0, tam).map(Number);
    const resultados = quickSortBenchmark(datosPrueba);
    console.log(`Tamaño: ${tam} | Tiempo: ${resultados.tiempo.toFixed(4)} ms | Intercambios: ${resultados.intercambios} | Comparaciones: ${resultados.comparaciones}`);
}