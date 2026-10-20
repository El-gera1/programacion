import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Merge {
    private static long comparaciones = 0;
    private static long intercambios = 0;

    public static void main(String[] args) {
        int[] tamanos = {100, 500, 1000, 10000, 100000};
        
        System.out.println("--- RESULTADOS MERGE SORT (JAVA) ---");
        
        for (int tamanoPrueba : tamanos) {
            ArrayList<Integer> datos = new ArrayList<>();
            
            try (BufferedReader br = new BufferedReader(new FileReader("datos_millon.txt"))) {
                String linea;
                int contador = 0;
                while ((linea = br.readLine()) != null && contador < tamanoPrueba) {
                    datos.add(Integer.parseInt(linea.trim()));
                    contador++;
                }
            } catch (IOException e) {
                System.out.println("Error al leer el archivo para el tamaño " + tamanoPrueba);
                continue;
            }

            int[] arr = datos.stream().mapToInt(i -> i).toArray();
            comparaciones = 0;
            intercambios = 0;

            long inicio = System.nanoTime();
            mergeSort(arr, 0, arr.length - 1);
            long fin = System.nanoTime();

            double tiempoMs = (fin - inicio) / 1_000_000.0;

            System.out.println("Tamaño: " + tamanoPrueba + " | Tiempo: " + tiempoMs + " ms | Intercambios: " + intercambios + " | Comparaciones: " + comparaciones);
        }
    }

    private static void mergeSort(int[] arr, int izq, int der) {
        if (izq < der) {
            int medio = izq + (der - izq) / 2;
            mergeSort(arr, izq, medio);
            mergeSort(arr, medio + 1, der);
            merge(arr, izq, medio, der);
        }
    }

    private static void merge(int[] arr, int izq, int medio, int der) {
        int n1 = medio - izq + 1;
        int n2 = der - medio;

        int[] izqArr = new int[n1];
        int[] derArr = new int[n2];

        for (int i = 0; i < n1; ++i) izqArr[i] = arr[izq + i];
        for (int j = 0; j < n2; ++j) derArr[j] = arr[medio + 1 + j];

        int i = 0, j = 0, k = izq;

        while (i < n1 && j < n2) {
            comparaciones++;
            if (izqArr[i] <= derArr[j]) {
                arr[k] = izqArr[i];
                i++;
            } else {
                arr[k] = derArr[j];
                j++;
            }
            intercambios++;
            k++;
        }

        while (i < n1) {
            arr[k] = izqArr[i];
            i++;
            intercambios++;
            k++;
        }

        while (j < n2) {
            arr[k] = derArr[j];
            j++;
            intercambios++;
            k++;
        }
    }
}