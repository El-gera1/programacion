const fs = require('fs');

function insertionSortBenchmark(arr) {
    let a = [...arr];
    let n = a.length;
    let comparaciones = 0;
    let intercambios = 0;
    
    let inicio = performance.now();
    
    for (let i = 1; i < n; i++) {
        let key = a[i];
        let j = i - 1;
        
        while (j >= 0) {
            comparaciones++;
            if (a[j] > key) {
                a[j + 1] = a[j];
                intercambios++;
                j--;
            } else {
                break;
            }
        }
        a[j + 1] = key;
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

console.log("--- RESULTADOS INSERCIÓN (JAVASCRIPT) ---");

for (let tam of tamanos) {
    const datosPrueba = lineas.slice(0, tam).map(Number);
    const resultados = insertionSortBenchmark(datosPrueba);
    console.log(`Tamaño: ${tam} | Tiempo: ${resultados.tiempo.toFixed(4)} ms | Intercambios: ${resultados.intercambios} | Comparaciones: ${resultados.comparaciones}`);
}