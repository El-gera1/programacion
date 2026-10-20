import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Seleccion {
    public static void main(String[] args) {
        int[] tamanos = {100, 500, 1000, 10000, 100000};
        
        System.out.println("--- RESULTADOS SELECCIÓN (JAVA) ---");
        
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
            long comparaciones = 0;
            long intercambios = 0;

            long inicio = System.nanoTime();

            for (int i = 0; i < n - 1; i++) {
                int minIdx = i;
                for (int j = i + 1; j < n; j++) {
                    comparaciones++;
                    if (arr[j] < arr[minIdx]) {
                        minIdx = j;
                    }
                }
                if (minIdx != i) {
                    int temp = arr[i];
                    arr[i] = arr[minIdx];
                    arr[minIdx] = temp;
                    intercambios++;
                }
            }

            long fin = System.nanoTime();
            double tiempoMs = (fin - inicio) / 1_000_000.0;

            System.out.println("Tamaño: " + tamanoPrueba + " | Tiempo: " + tiempoMs + " ms | Intercambios: " + intercambios + " | Comparaciones: " + comparaciones);
        }
    }
}