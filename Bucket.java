import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Bucket {
    private static long comparaciones = 0;
    private static long intercambios = 0;

    public static void main(String[] args) {
        int[] tamanos = {100, 500, 1000, 10000, 100000};
        
        System.out.println("--- RESULTADOS BUCKET SORT (JAVA) ---");
        
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
            if (n <= 1) continue;

            comparaciones = 0;
            intercambios = 0;

            long inicio = System.nanoTime();

            int minVal = arr[0];
            int maxVal = arr[0];
            for (int i = 1; i < n; i++) {
                if (arr[i] < minVal) minVal = arr[i];
                if (arr[i] > maxVal) maxVal = arr[i];
            }

            int rango = maxVal - minVal + 1;
            int numBuckets = Math.max(1, Math.min(n, 100));
            
            @SuppressWarnings("unchecked")
            ArrayList<Integer>[] buckets = new ArrayList[numBuckets];
            for (int i = 0; i < numBuckets; i++) {
                buckets[i] = new ArrayList<>();
            }

            for (int num : arr) {
                int index;
                if (rango == 1) {
                    index = 0;
                } else {
                    index = (int)((long)(num - minVal) * (numBuckets - 1) / (maxVal - minVal));
                }
                buckets[index].add(num);
                intercambios++;
            }

            int k = 0;
            for (ArrayList<Integer> bucket : buckets) {
                // Insertion sort local
                for (int i = 1; i < bucket.size(); i++) {
                    int key = bucket.get(i);
                    int j = i - 1;
                    while (j >= 0) {
                        comparaciones++;
                        if (bucket.get(j) > key) {
                            bucket.set(j + 1, bucket.get(j));
                            intercambios++;
                            j--;
                        } else {
                            break;
                        }
                    }
                    bucket.set(j + 1, key);
                }

                for (int num : bucket) {
                    arr[k++] = num;
                }
            }

            long fin = System.nanoTime();
            double tiempoMs = (fin - inicio) / 1_000_000.0;

            System.out.println("Tamaño: " + tamanoPrueba + " | Tiempo: " + tiempoMs + " ms | Intercambios: " + intercambios + " | Comparaciones: " + comparaciones);
        }
    }
}