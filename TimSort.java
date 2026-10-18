import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class TimSort {
    private static final int RUN = 32;
    private static long comparaciones = 0;
    private static long intercambios = 0;

    public static void main(String[] args) {
        int[] tamanos = {100, 500, 1000, 10000, 100000};
        
        System.out.println("--- RESULTADOS TIM SORT (JAVA) ---");
        
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
            timSort(arr, arr.length);
            long fin = System.nanoTime();

            double tiempoMs = (fin - inicio) / 1_000_000.0;

            System.out.println("Tamaño: " + tamanoPrueba + " | Tiempo: " + tiempoMs + " ms | Intercambios: " + intercambios + " | Comparaciones: " + comparaciones);
        }
    }

    private static void insertionSort(int[] arr, int left, int right) {
        for (int i = left + 1; i <= right; i++) {
            int temp = arr[i];
            int j = i - 1;
            while (j >= left) {
                comparaciones++;
                if (arr[j] > temp) {
                    arr[j + 1] = arr[j];
                    intercambios++;
                    j--;
                } else {
                    break;
                }
            }
            arr[j + 1] = temp;
        }
    }

    private static void merge(int[] arr, int l, int m, int r) {
        int len1 = m - l + 1, len2 = r - m;
        int[] left = new int[len1];
        int[] right = new int[len2];

        for (int x = 0; x < len1; x++) left[x] = arr[l + x];
        for (int x = 0; x < len2; x++) right[x] = arr[m + 1 + x];

        int i = 0, j = 0, k = l;

        while (i < len1 && j < len2) {
            comparaciones++;
            if (left[i] <= right[j]) {
                arr[k] = left[i];
                i++;
            } else {
                arr[k] = right[j];
                j++;
            }
            intercambios++;
            k++;
        }

        while (i < len1) {
            arr[k] = left[i];
            i++;
            intercambios++;
            k++;
        }

        while (j < len2) {
            arr[k] = right[j];
            j++;
            intercambios++;
            k++;
        }
    }

    private static void timSort(int[] arr, int n) {
        for (int i = 0; i < n; i += RUN) {
            insertionSort(arr, i, Math.min((i + RUN - 1), (n - 1)));
        }

        for (int size = RUN; size < n; size = 2 * size) {
            for (int left = 0; left < n; left += 2 * size) {
                int mid = left + size - 1;
                int right = Math.min((left + 2 * size - 1), (n - 1));

                if (mid < right) {
                    merge(arr, left, mid, right);
                }
            }
        }
    }
}