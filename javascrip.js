let r = 3;
let c = 3;

let arr = [1, 2, 3, 4, 5, 6, 7, 8, 9];
let TwoDarr = Array.from({length: r}, () => new Array(c).fill(0));
for (let x = 0; x < r; x++){
    for (let y = 0; y < c; y++){
        let  k = x * r + y;
        TwoDarr[x][y] = arr[k];
    }
}
console.log("matriz 2d ");
for (let row of TwoDarr) {
    console.log(row.join(" "));
}
