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
        cout << "6: iningresa una letra para identifir si es una vocal" << endl;
        cout << "7: iningresa 3 numeros para  identificar si el tercero es igual que la suma del primero y el segundo" << endl;
        cout << "8: iningresa 3 numeros para  identificar si el tercero es igual que la multiplicacion del primero y el segundo" << endl;
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
                int mes;
            cout << "Ingrese un número del 1 al 12: ";
            cin >> mes;
            switch (mes) {
                case 1: cout << "Enero" << endl; break;
                case 2: cout << "Febrero" << endl; break;
                case 3: cout << "Marzo" << endl; break;
                case 4: cout << "Abril" << endl; break;
                case 5: cout << "Mayo" << endl; break;
                case 6: cout << "Junio" << endl; break;
                case 7: cout << "Julio" << endl; break;
                case 8: cout << "Agoato" << endl; break;
                case 9: cout << "Septiembre" << endl; break;
                case 10: cout << "Octubre" << endl; break;
                case 11: cout << "Noviembre" << endl; break;
                case 12: cout << "Diciembre" << endl; break;
                default: cout << "Número fuera del rango (1-12)." << endl; break;
                break;
               }
            }
            case 4:{
                double num;
                cout << "Ingrese un número: ";
                cin >> num;
                if (num > 0)
                cout << " el numero es positivo " << endl;
                else if (num < 0)
                cout << " el numero es negativo " << endl;
                else 
                cout << " el numero es cero " << endl;
                break;
            }
            case 5:{
                int num;
                cout << " ingrese un numero: " << endl;
                cin >> num;
                if (num > 100)
                cout <<"el numero es mayor que 100 "<< endl;
                else 
                cout <<" el numero es menor que 100 "<< endl;
                break;

            }
            case 6:{
                char letra;
                cout << " ingresa  una letra miniscula: " << endl; 
                cin >> letra;
                if (letra == 'a' or letra == 'e' or letra ==  'i' or letra == 'o' or letra ==  'u' )
                cout << "la letra ingresada es una vocal" << endl;
                else 
                cout <<" la letra ingresada no es una vocal"<< endl;
                break;
            }
            case 7:{
                int a, b , c, total;

                cout << " ingresa  el 1 numeros "<< endl;
                cin  >> a;
                cout << " ingresa el 2 numero"<< endl;
                cin >>  b;
                cout << " ingresa el 3 numero "<< endl;
                cin >> c;
                total = a + b;
                if (total == c)
                cout << " la suma del primero y del sugundo es igual al tercer numero " << endl;
                else 
                cout << " la suma no es igual al tecer numero "<< endl;
                break;
            }
            case 8:{
                int a, b , c;
                cout << " ingresa  el 1 numeros "<< endl;
                cin  >> a;
                cout << " ingresa el 2 numero"<< endl;
                cin >>  b;
                cout << " ingresa el 3 numero "<< endl;
                cin >> c;
                if (a * b== c)
                cout << " la muntiplicacion del primero y del sugundo es igual al tercer numero " << endl;
                else 
                cout << " la multiplicacion no es igual al tecer numero "<< endl;
                break;

            }
            default:
            cout << " opcion no valida "<< endl;
            break;
        }

    return 0;
}

