
function selection(a) {
    let n = a.length;
    for (let i = 0; i < n; i++) {
        let small = i;
        for (let j = i + 1; j < n; j++) {
            if (a[small] > a[j]) {
                small = j;
            }
        }
        let temp = a[i];
        a[i] = a[small];
        a[small] = temp;
    }
}

function printArr(a) {
    console.log(a.join(" "));
}

let a = [65, 26, 13, 23, 12];

console.log("arreglo antes de ser ordenado: ");
printArr(a);

selection(a);

console.log("\narreglo despues de ser ordenado: ");
printArr(a);