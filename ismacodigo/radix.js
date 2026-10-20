const fs = require('fs');

function radixSortBenchmark(arr) {
    let a = [...arr];
    let n = a.length;
    if (n === 0) return { tiempo: 0, intercambios: 0, comparaciones: 0 };

    let comparaciones = 0;
    let intercambios = 0;

    let inicio = performance.now();

    let minVal = Math.min(...a);
    let offset = 0;
    if (minVal < 0) {
        offset = Math.abs(minVal);
        a = a.map(x => x + offset);
    }

    let maxVal = Math.max(...a);

    function countingSortForRadix(exp) {
        let output = new Array(n);
        let count = new Array(10).fill(0);

        for (let i = 0; i < n; i++) {
            let digit = Math.floor(a[i] / exp) % 10;
            count[digit]++;
        }

        for (let i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (let i = n - 1; i >= 0; i--) {
            let digit = Math.floor(a[i] / exp) % 10;
            output[count[digit] - 1] = a[i];
            count[digit]--;
            intercambios++;
        }

        for (let i = 0; i < n; i++) {
            a[i] = output[i];
        }
    }

    let exp = 1;
    while (Math.floor(maxVal / exp) > 0) {
        countingSortForRadix(exp);
        exp *= 10;
    }

    if (minVal < 0) {
        a = a.map(x => x - offset);
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

console.log("--- RESULTADOS RADIX SORT (JAVASCRIPT) ---");

for (let tam of tamanos) {
    const datosPrueba = lineas.slice(0, tam).map(Number);
    const resultados = radixSortBenchmark(datosPrueba);
    console.log(`Tamaño: ${tam} | Tiempo: ${resultados.tiempo.toFixed(4)} ms | Intercambios: ${resultados.intercambios} | Comparaciones: ${resultados.comparaciones}`);
}