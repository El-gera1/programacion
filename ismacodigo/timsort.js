const fs = require('fs');

const RUN = 32;

function timSortBenchmark(arr) {
    let a = [...arr];
    let n = a.length;
    let comparaciones = 0;
    let intercambios = 0;

    function insertionSort(left, right) {
        for (let i = left + 1; i <= right; i++) {
            let temp = a[i];
            let j = i - 1;
            while (j >= left) {
                comparaciones++;
                if (a[j] > temp) {
                    a[j + 1] = a[j];
                    intercambios++;
                    j--;
                } else {
                    break;
                }
            }
            a[j + 1] = temp;
        }
    }

    function merge(l, m, r) {
        let len1 = m - l + 1, len2 = r - m;
        let left = a.slice(l, m + 1);
        let right = a.slice(m + 1, r + 1);

        let i = 0, j = 0, k = l;

        while (i < len1 && j < len2) {
            comparaciones++;
            if (left[i] <= right[j]) {
                a[k] = left[i];
                i++;
            } else {
                a[k] = right[j];
                j++;
            }
            intercambios++;
            k++;
        }

        while (i < len1) {
            a[k] = left[i];
            i++;
            intercambios++;
            k++;
        }

        while (j < len2) {
            a[k] = right[j];
            j++;
            intercambios++;
            k++;
        }
    }

    let inicio = performance.now();

    for (let i = 0; i < n; i += RUN) {
        insertionSort(i, Math.min((i + RUN - 1), (n - 1)));
    }

    for (let size = RUN; size < n; size = 2 * size) {
        for (let left = 0; left < n; left += 2 * size) {
            let mid = left + size - 1;
            let right = Math.min((left + 2 * size - 1), (n - 1));

            if (mid < right) {
                merge(left, mid, right);
            }
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

console.log("--- RESULTADOS TIM SORT (JAVASCRIPT) ---");

for (let tam of tamanos) {
    const datosPrueba = lineas.slice(0, tam).map(Number);
    const resultados = timSortBenchmark(datosPrueba);
    console.log(`Tamaño: ${tam} | Tiempo: ${resultados.tiempo.toFixed(4)} ms | Intercambios: ${resultados.intercambios} | Comparaciones: ${resultados.comparaciones}`);
}