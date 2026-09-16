#include <iostream>
#include <vector>

using namespace std;


void selection(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        int small = i;
        for (int j = i + 1; j < n; j++) {
            if (a[small] > a[j]) {
                small = j;
            }
        }
        int temp = a[i];
        a[i] = a[small];
        a[small] = temp;
    }
}

void printArr(const vector<int>& a) {
    for (size_t i = 0; i < a.size(); i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main() {
    vector<int> a = {65, 26, 13, 23, 12};
    
    cout << "arreglo antes de ser ordenado: " << endl;
    printArr(a);
    
    selection(a);
    
    cout << "\narreglo despues de ser ordenado: " << endl;
    printArr(a);
    
    return 0;
}