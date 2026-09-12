#include <iostream>
#include <cstdlib> // Necesario para usar system("cls")

using namespace std;

// Gerardo Guillermo De jesus Sarmiento hernandez 
// 4/09/2026
// calculadora

int main() {
    float n1, n2; // Declarar variables
    int op;
    
    do {
        system("cls"); // Limpiar pantalla
    
        // Mostrar opciones
        cout << "Opciones" << endl;
        cout << "1: Suma" << endl;
        cout << "2: Resta" << endl;
        cout << "3: Multiplicacion" << endl;
        cout << "4: Division" << endl;
        cout << "5: Salir" << endl;
        cout << "Opcion: ";
        cin >> op;
        
        switch (op) {
            case 1: {
                cout << "Ingresa #1: ";
                cin >> n1;
                cout << "Ingresa #2: ";
                cin >> n2;
                cout << "La suma es: " << (n1 + n2) << endl;
                break; // Detiene la ejecucion del switch
            } 
            case 2: {
                cout << "Ingresa #1: ";
                cin >> n1;
                cout << "Ingresa #2: ";
                cin >> n2;
                cout << "La resta es: " << (n1 - n2) << endl;
                break;
            } 
            case 3: {
                cout << "Ingresa #1: ";
                cin >> n1;
                cout << "Ingresa #2: ";
                cin >> n2;
                cout << "La multiplicacion es: " << (n1 * n2) << endl;
                break;
            } 
            case 4: {
                cout << "Ingresa #1: ";
                cin >> n1;
                cout << "Ingresa #2: ";
                cin >> n2;
                if (n2 != 0) {
                    cout << "La division es: " << (n1 / n2) << endl;
                } else {
                    cout << "Error: No se puede dividir entre cero." << endl;
                }
            break;
            } 
            case 5: {
                cout << "bay" << endl;
                break;
            }
            default: {
                cout << "Opcion no valida." << endl;
                break;
            }
        }   

        
        if (op != 5) {
            system("pause");
        }

    } while (op != 5); 
    return 0;
}