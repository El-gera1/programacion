const fs = require('fs');

function mergeSortBenchmark(arr) {
    let a = [...arr];
    let comparaciones = 0;
    let intercambios = 0;
    
    function merge(left, right) {
        let resultArray = [], lIndex = 0, rIndex = 0;
        
        while (lIndex < left.length && rIndex < right.length) {
            comparaciones++;
            if (left[lIndex] < right[rIndex]) {
                resultArray.push(left[lIndex]);
                lIndex++;
            } else {
                resultArray.push(right[rIndex]);
                rIndex++;
            }
            intercambios++;
        }
        
        while (lIndex < left.length) {
            resultArray.push(left[lIndex]);
            lIndex++;
            intercambios++;
        }
        
        while (rIndex < right.length) {
            resultArray.push(right[rIndex]);
            rIndex++;
            intercambios++;
        }
        
        return resultArray;
    }
    
    function mergeSort(unsortedArray) {
        if (unsortedArray.length <= 1) {
            return unsortedArray;
        }
        const middle = Math.floor(unsortedArray.length / 2);
        const left = unsortedArray.slice(0, middle);
        const right = unsortedArray.slice(middle);
        
        return merge(mergeSort(left), mergeSort(right));
    }
    
    let inicio = performance.now();
    let ordenado = mergeSort(a);
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

console.log("--- RESULTADOS MERGE SORT (JAVASCRIPT) ---");

for (let tam of tamanos) {
    const datosPrueba = lineas.slice(0, tam).map(Number);
    const resultados = mergeSortBenchmark(datosPrueba);
    console.log(`Tamaño: ${tam} | Tiempo: ${resultados.tiempo.toFixed(4)} ms | Intercambios: ${resultados.intercambios} | Comparaciones: ${resultados.comparaciones}`);
}