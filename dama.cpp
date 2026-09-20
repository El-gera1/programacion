#include <iostream>
#include<string>

using namespace std;

void  logicatablero(int **a, int size)
{
    for (int i=0; i<size; i++)
    {
        if (i%2==0)
        {
            a[0][i]=0;
        }
        else a[0][i]=1;
    }
    for(int i = 0; i<size; i++)
    {
        if(i%2!=0)
        {
            a[1][i]=0;
        }
        else 
        {
            a[1][i]=1;
        }
    } 
    for (int i=0; i<size; i++)
    {
        if (i%2==0)
        {
            a[2][i]=0;
        }
        else a[2][i]=1;
    }
    for (int i = 3; i<(3+(size-6)); i++)
    {
        for (int j  = 0; j<size; j++)
        {
            a[i][j]=0;
        }
    }
    for (int i = 0; i<size; i++)
    {
        if(i%2!=0)
        {
            a[3+(size-6)][i]=0;
        }
        else
        {
            a[3+(size-6)][i]=2;
        }
    }
    for (int i = 0; i<size; i++)
    {
         if(i%2==0)
        {
            a[3+(size-5)][i]=0;
        }
        else
        a[3+(size-5)][i]=2;

    }
     for (int i = 0; i<size; i++)
    {
        if(i%2!=0)
        {
            a[3+(size-4)][i]=0;
        }
        else
        {
            a[3+(size-4)][i]=2;
        }
    }
    

}

void turnojugador(int **a, int n)
{
    int turno = 0;
    int jugador;
    int piezafila, piezacolumna;
    int movfila, movcolumna;
    int tmp;

    do
    {
        
        for (int k = 0; k < n; k++)
        {
            cout << k << " ";
        }

        cout << endl;

       
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << a[i][j] << " ";
            }

            cout << i << endl;

            for (int m = 0; m < n; m++)
            {
                cout << "----";
            }

            cout << endl;
        }

        
        if (turno % 2 == 0)
        {
            jugador = 1;
        }
        else
        {
            jugador = 2;
        }

        cout << "Turno del jugador " << jugador << endl;

        cout << "Ingrese la fila de la pieza que desea mover: ";
        cin >> piezafila;

        cout << "Ingrese la columna de la pieza que desea mover: ";
        cin >> piezacolumna;

        cout << "Ingrese la fila de la posicion a donde se movera: ";
        cin >> movfila;

        cout << "Ingrese la columna de la posicion a donde se movera: ";
        cin >> movcolumna;

        
        if (piezafila < 0 || piezafila >= n ||
            piezacolumna < 0 || piezacolumna >= n ||
            movfila < 0 || movfila >= n ||
            movcolumna < 0 || movcolumna >= n)
        {
            cout << "Posicion no valida" << endl;
            continue;
        }

        
        if (a[movfila][movcolumna] == 0)
        {
            tmp = a[piezafila][piezacolumna];

           
            a[piezafila][piezacolumna] = 0;
            a[movfila][movcolumna] = tmp;
        }
        else
        {
            cout << "Movimiento no valido" << endl;
            continue;
        }

      
        if (jugador == 1)
        {
            if (movfila - 1 >= 0 && movcolumna - 1 >= 0)
            {
                if (a[movfila - 1][movcolumna - 1] == 2)
                {
                    a[movfila - 1][movcolumna - 1] = 0;
                }
            }

            if (movfila - 1 >= 0 && movcolumna + 1 < n)
            {
                if (a[movfila - 1][movcolumna + 1] == 2)
                {
                    a[movfila - 1][movcolumna + 1] = 0;
                }
            }
        }

        
        if (jugador == 2)
        {
            if (movfila + 1 < n && movcolumna + 1 < n)
            {
                if (a[movfila + 1][movcolumna + 1] == 1)
                {
                    a[movfila + 1][movcolumna + 1] = 0;
                }
            }

            if (movfila + 1 < n && movcolumna - 1 >= 0)
            {
                if (a[movfila + 1][movcolumna - 1] == 1)
                {
                    a[movfila + 1][movcolumna - 1] = 0;
                }
            }
        }

        turno++;

    } while (true);
}

void jugadorganador(int **a, int z)
{
    int gana;
    int piezauno=0;
    int piezados=0;
    for (int i = 0; i<z; i++)
    {
        for (int j = 0; j<z; j++ )
        {
            if (a[i][j]==1)
            {
                piezauno++;
            }
        }
    }
    for (int i = 0; i<z; i++)
    {
        for (int j = 0; j<z; j++ )
        {
            if (a[i][j]==2)
            {
                piezados++;
            }
        }
    }
    if (piezauno==0)
    {
        gana=2;
    }
    if (piezados==0)
    {
        gana=1;
    }
    cout << " el ganador es el gugador : "<< gana <<endl;
}

int main()
{
    int **array=NULL,size;
    cout << " bien venido al juego de damas "<<endl<<endl;
    cout << " seleciona una dimencion para el tablero: "<<endl;
    cout<< " minimo 8x8"<< endl;
    cin >> size;

    while (size<8)
    {
        cout <<" el tamaño del tablero debe ser mayor o igual a 8x8: ";
        cin>>size;
    }
    array = new int*[size];
    for ( int i = 0; i < size; i++)
    {
        array[i] = new int [size];
    }
    cout<<endl;
    cout<<" el juego ha empezado"<<endl<<endl;
    logicatablero(array, size);
    turnojugador(array, size);
    jugadorganador(array, size);
    delete [] array;
    return 0;

}
