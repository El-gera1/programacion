#include <iostream>
#include <cstdlib> // Necesario para usar system("cls")

using namespace std;

// Gerardo Guillermo De jesus Sarmiento hernandez 
// 4/09/2026
// calculadora

int main() {
    int op;
    
        system("cls"); // Limpiar pantalla
    
        // Mostrar opciones
        cout << "1: ingresa un numero para saber si  es  par o inpar " << endl;
        cout << "2: ingresa un numero del 1 al 7 para los dias de la semena " << endl;
        cout << "3: ingresa un numero del 1 al 12 para los meses" << endl;
        cout << "4: ingresa unn numero para saber si es posoitivo o negativo" << endl;
        cout << "5: ingresa un numero para saber si es mayor que 100" << endl;
        cout << "6: iningresa un numero para saber si es mayor que 100" << endl;
        cout << "Opcion: ";
        cin >> op;
        
        switch (op) {
            case 1: {
                int n1;
                cout << "Ingresa #1: ";
                cin >> n1;
                if (n1 % 2 == 0)
                cout << "El número es PAR." << endl;
                 else
                cout << "El número es IMPAR." << endl;
                break; 
            } 
            case 2: {
                int dia;
            cout << "Ingrese un número del 1 al 7: ";
            cin >> dia;
            switch (dia) {
                case 1: cout << "Lunes" << endl; break;
                case 2: cout << "Martes" << endl; break;
                case 3: cout << "Miércoles" << endl; break;
                case 4: cout << "Jueves" << endl; break;
                case 5: cout << "Viernes" << endl; break;
                case 6: cout << "Sábado" << endl; break;
                case 7: cout << "Domingo" << endl; break;
                default: cout << "Número fuera del rango (1-7)." << endl; break;
                break;
               }
            }
            case 3: {
                
            }
         }
            
        
        
   
     return 0;
}
