const fs = require('fs');

function bucketSortBenchmark(arr) {
    let a = [...arr];
    let n = a.length;
    if (n <= 1) return { tiempo: 0, intercambios: 0, comparaciones: 0 };

    let comparaciones = 0;
    let intercambios = 0;

    let inicio = performance.now();

    let minVal = Math.min(...a);
    let maxVal = Math.max(...a);
    let rango = maxVal - minVal + 1;

    let numBuckets = Math.max(1, Math.min(n, 100));
    let buckets = Array.from({ length: numBuckets }, () => []);

    for (let num of a) {
        let index;
        if (rango === 1) {
            index = 0;
        } else {
            index = Math.floor(((num - minVal) * (numBuckets - 1)) / (maxVal - minVal));
        }
        buckets[index].push(num);
        intercambios++;
    }

    let sortedArray = [];
    for (let bucket of buckets) {
        // Insertion sort local
        for (let i = 1; i < bucket.length; i++) {
            let key = bucket[i];
            let j = i - 1;
            while (j >= 0) {
                comparaciones++;
                if (bucket[j] > key) {
                    bucket[j + 1] = bucket[j];
                    intercambios++;
                    j--;
                } else {
                    break;
                }
            }
            bucket[j + 1] = key;
        }
        sortedArray.push(...bucket);
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

console.log("--- RESULTADOS BUCKET SORT (JAVASCRIPT) ---");

for (let tam of tamanos) {
    const datosPrueba = lineas.slice(0, tam).map(Number);
    const resultados = bucketSortBenchmark(datosPrueba);
    console.log(`Tamaño: ${tam} | Tiempo: ${resultados.tiempo.toFixed(4)} ms | Intercambios: ${resultados.intercambios} | Comparaciones: ${resultados.comparaciones}`);
}