 class Main {
    public static void main(String[] args) {
        int r = 3;
        int c = 3;
        int[] arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        int[][] TwoDArr = new int[r][c];
        for (int x = 0; x < r; x++) {
            for (int y = 0; y < c; y++) {
                int k = x * r + y;
                TwoDArr[x][y] = arr[k]; 
            }
        }
        System.out.println("Matriz 2D reconstruida:");
        for (int x = 0; x < r; x++) {
            for (int y = 0; y < c; y++) {
                System.out.print(TwoDArr[x][y] + " ");
            }
            System.out.println();
        }
    }
}