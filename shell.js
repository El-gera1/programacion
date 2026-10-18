const fs = require('fs');

function shellSortBenchmark(arr) {
    let a = [...arr];
    let n = a.length;
    let comparaciones = 0;
    let intercambios = 0;
    
    let inicio = performance.now();
    
    let gap = Math.floor(n / 2);
    while (gap > 0) {
        for (let i = gap; i < n; i++) {
            let temp = a[i];
            let j = i;
            while (j >= gap) {
                comparaciones++;
                if (a[j - gap] > temp) {
                    a[j] = a[j - gap];
                    intercambios++;
                    j -= gap;
                } else {
                    break;
                }
            }
            a[j] = temp;
        }
        gap = Math.floor(gap / 2);
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

console.log("--- RESULTADOS SHELL SORT (JAVASCRIPT) ---");

for (let tam of tamanos) {
    const datosPrueba = lineas.slice(0, tam).map(Number);
    const resultados = shellSortBenchmark(datosPrueba);
    console.log(`Tamaño: ${tam} | Tiempo: ${resultados.tiempo.toFixed(4)} ms | Intercambios: ${resultados.intercambios} | Comparaciones: ${resultados.comparaciones}`);
}