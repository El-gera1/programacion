import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Insercion {
    public static void main(String[] args) {
        int[] tamanos = {100, 500, 1000, 10000, 100000};
        
        System.out.println("--- RESULTADOS INSERCIÓN (JAVA) ---");
        
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

            for (int i = 1; i < n; i++) {
                int key = arr[i];
                int j = i - 1;

                while (j >= 0) {
                    comparaciones++;
                    if (arr[j] > key) {
                        arr[j + 1] = arr[j];
                        intercambios++;
                        j--;
                    } else {
                        break;
                    }
                }
                arr[j + 1] = key;
            }

            long fin = System.nanoTime();
            double tiempoMs = (fin - inicio) / 1_000_000.0;

            System.out.println("Tamaño: " + tamanoPrueba + " | Tiempo: " + tiempoMs + " ms | Intercambios: " + intercambios + " | Comparaciones: " + comparaciones);
        }
    }
}