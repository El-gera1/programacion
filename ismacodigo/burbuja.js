const fs = require('fs');

function bubbleSortBenchmark(arr) {
    let a = [...arr];
    let n = a.length;
    let comparaciones = 0;
    let intercambios = 0;
    
    let inicio = performance.now();
    let swapped = true;
    while (swapped && n > 1) {
        swapped = false;
        for (let i = 1; i < n; i++) {
            comparaciones++;
            if (a[i - 1] > a[i]) {
                let temp = a[i - 1];
                a[i - 1] = a[i];
                a[i] = temp;
                intercambios++;
                swapped = true;
            }
        }
        n--;
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

console.log("--- RESULTADOS BURBUJA (JAVASCRIPT) ---");

for (let tam of tamanos) {
    const datosPrueba = lineas.slice(0, tam).map(Number);
    const resultados = bubbleSortBenchmark(datosPrueba);
    console.log(`Tamaño: ${tam} | Tiempo: ${resultados.tiempo.toFixed(4)} ms | Intercambios: ${resultados.intercambios} | Comparaciones: ${resultados.comparaciones}`);
}