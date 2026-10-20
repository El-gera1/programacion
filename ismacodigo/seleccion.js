const fs = require('fs');

function selectionSortBenchmark(arr) {
    let a = [...arr];
    let n = a.length;
    let comparaciones = 0;
    let intercambios = 0;
    
    let inicio = performance.now();
    
    for (let i = 0; i < n - 1; i++) {
        let minIdx = i;
        for (let j = i + 1; j < n; j++) {
            comparaciones++;
            if (a[j] < a[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx !== i) {
            let temp = a[i];
            a[i] = a[minIdx];
            a[minIdx] = temp;
            intercambios++;
        }
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

console.log("--- RESULTADOS SELECCIÓN (JAVASCRIPT) ---");

for (let tam of tamanos) {
    const datosPrueba = lineas.slice(0, tam).map(Number);
    const resultados = selectionSortBenchmark(datosPrueba);
    console.log(`Tamaño: ${tam} | Tiempo: ${resultados.tiempo.toFixed(4)} ms | Intercambios: ${resultados.intercambios} | Comparaciones: ${resultados.comparaciones}`);
}