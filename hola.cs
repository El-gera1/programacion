using System;

class Program 
{
    static void Main() 
    {
        int r = 3;
        int c = 3;

        int[] arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int[,] TwoDArr = new int[r, c];

        for (int x = 0; x < r; x++) 
        {
            for (int y = 0; y < c; y++) 
            {
                int k = x * c + y;
                TwoDArr[x, y] = arr[k];
            }
        }

        Console.WriteLine("Matriz 2D ");
        for (int x = 0; x < r; x++) 
        {
            for (int y = 0; y < c; y++) 
            {
                Console.Write(TwoDArr[x, y] + " ");
            }
            Console.WriteLine();
        }
    }
}