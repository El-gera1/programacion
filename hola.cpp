#include <iostream>

int main() {
    int r = 3;
    int c = 3;
    int arr[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int TwoDArr[3][3];
    for (int x = 0; x < r; x++) {
        for (int y = 0; y < c; y++) {
            int k = x * c + y;
            TwoDArr[x][y] = arr[k]; 
        }
    }
    std::cout << "Matriz 2D \n";
    for (int x = 0; x < r; x++) {
        for (int y = 0; y < c; y++) {
            std::cout << TwoDArr[x][y] << " ";
        }
        std::cout << "\n";
    }
    return 0;
}