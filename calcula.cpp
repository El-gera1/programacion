#include <iostream>
using namespace std;
//Gerardo Guillermo De jesus Sarmiento hernandez 
//4/09/2026
//calculadora
int main() {
    float n1, n2; //declarar variables
    int op;
 //pones las opciones
    cout << "Opciones" << endl;
    cout << "1: Suma" << endl;
    cout << "2: Resta" << endl;
    cout << "3: Multiplicacion" << endl;
    cout << "4: Division" << endl;
    cout << "5: salir" << endl;
    cout << "Opcion: ";
    cin >> op;
     
    switch (op)
    {
    case 1:  {
        cout << "Ingresa #1: ";
        cin >> n1;
        cout << "Ingresa #2: ";
        cin >> n2;
        cout << "La suma es: " << (n1 + n2) << endl;
    } 
    case 2:   {
        cout << "Ingresa #1: ";
        cin >> n1;
        cout << "Ingresa #2: ";
        cin >> n2;
        cout << "La resta es: " << (n1 - n2) << endl;
    } 
    case 3:   {
        cout << "Ingresa #1: ";
        cin >> n1;
        cout << "Ingresa #2: ";
        cin >> n2;
        cout << "La multiplicacion es: " << (n1 * n2) << endl;
    } 
    case 4:    {
        cout << "Ingresa #1: ";
        cin >> n1;
        cout << "Ingresa #2: ";
        cin >> n2;
        
            cout << "La division es: " << (n1 / n2) << endl;
        } 
    
    case 5:  {
        cout << "bay" << endl;
    }
    }   
    
}
