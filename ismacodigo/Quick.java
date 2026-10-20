import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Quick {
    private static long comparaciones = 0;
    private static long intercambios = 0;

    public static void main(String[] args) {
        int[] tamanos = {100, 500, 1000, 10000, 100000};
        
        System.out.println("--- RESULTADOS QUICK SORT (JAVA) ---");
        
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
            if (arr.length > 0) {
                quickSort(arr, 0, arr.length - 1);
            }
            long fin = System.nanoTime();

            double tiempoMs = (fin - inicio) / 1_000_000.0;

            System.out.println("Tamaño: " + tamanoPrueba + " | Tiempo: " + tiempoMs + " ms | Intercambios: " + intercambios + " | Comparaciones: " + comparaciones);
        }
    }

    private static void quickSort(int[] arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    private static int partition(int[] arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            comparaciones++;
            if (arr[j] <= pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                intercambios++;
            }
        }

        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        intercambios++;

        return i + 1;
    }
}