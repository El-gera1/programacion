import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;

public class Radix {
    private static long intercambios = 0;

    public static void main(String[] args) {
        int[] tamanos = {100, 500, 1000, 10000, 100000};
        
        System.out.println("--- RESULTADOS RADIX SORT (JAVA) ---");
        
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
            int n = arr.length;
            if (n == 0) continue;

            intercambios = 0;
            long comparaciones = 0;

            long inicio = System.nanoTime();

            // Manejo de negativos si los hay
            int minVal = arr[0];
            for (int i = 1; i < n; i++) {
                if (arr[i] < minVal) minVal = arr[i];
            }
            int offset = 0;
            if (minVal < 0) {
                offset = Math.abs(minVal);
                for (int i = 0; i < n; i++) arr[i] += offset;
            }

            int maxVal = arr[0];
            for (int i = 1; i < n; i++) {
                if (arr[i] > maxVal) maxVal = arr[i];
            }

            for (int exp = 1; maxVal / exp > 0; exp *= 10) {
                countingSortForRadix(arr, n, exp);
            }

            if (minVal < 0) {
                for (int i = 0; i < n; i++) arr[i] -= offset;
            }

            long fin = System.nanoTime();
            double tiempoMs = (fin - inicio) / 1_000_000.0;

            System.out.println("Tamaño: " + tamanoPrueba + " | Tiempo: " + tiempoMs + " ms | Intercambios: " + intercambios + " | Comparaciones: " + comparaciones);
        }
    }

    private static void countingSortForRadix(int[] arr, int n, int exp) {
        int[] output = new int[n];
        int[] count = new int[10];
        Arrays.fill(count, 0);

        for (int i = 0; i < n; i++) {
            count[(arr[i] / exp) % 10]++;
        }

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            int digit = (arr[i] / exp) % 10;
            output[count[digit] - 1] = arr[i];
            count[digit]--;
            intercambios++;
        }

        System.arraycopy(output, 0, arr, 0, n);
    }
}