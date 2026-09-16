public class ordena14 {
    public static void selection(int[] a) {
        int n = a.length;
        for (int i = 0; i < n; i++) {
            int small = i;
            for (int j = i + 1; j < n; j++) {
                if (a[small] > a[j]) {
                    small = j;
                }
            }
            int temp = a[i];
            a[i] = a[small];
            a[small] = temp;
        }
    }
    public static void printArr(int[] a) {
        for (int i = 0; i < a.length; i++) {
            System.out.print(a[i] + " ");
        }
        System.out.println();
    }

    public static void main(String[] args) {
        int[] a = {65, 26, 13, 23, 12};

        System.out.println("arreglo antes de ser ordenado: ");
        printArr(a);

        selection(a);

        System.out.println("\narreglo despues de ser ordenado: ");
        printArr(a);
    }
    
}
