const fs = require('fs');

function countingSortBenchmark(arr) {
    let a = [...arr];
    let n = a.length;
    if (n === 0) return { tiempo: 0, intercambios: 0, comparaciones: 0 };

    let comparaciones = 0;
    let intercambios = 0;

    let inicio = performance.now();

    let minVal = Math.min(...a);
    let maxVal = Math.max(...a);
    let k = maxVal - minVal + 1;

    let count = new Array(k).fill(0);
    let output = new Array(n);

    for (let i = 0; i < n; i++) {
        count[a[i] - minVal]++;
    }

    for (let i = 1; i < k; i++) {
        count[i] += count[i - 1];
    }

    for (let i = n - 1; i >= 0; i--) {
        output[count[a[i] - minVal] - 1] = a[i];
        count[a[i] - minVal]--;
        intercambios++;
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

console.log("--- RESULTADOS COUNTING SORT (JAVASCRIPT) ---");

for (let tam of tamanos) {
    const datosPrueba = lineas.slice(0, tam).map(Number);
    const resultados = countingSortBenchmark(datosPrueba);
    console.log(`Tamaño: ${tam} | Tiempo: ${resultados.tiempo.toFixed(4)} ms | Intercambios: ${resultados.intercambios} | Comparaciones: ${resultados.comparaciones}`);
}