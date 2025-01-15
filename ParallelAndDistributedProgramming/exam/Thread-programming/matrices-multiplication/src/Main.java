import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class Main {
    static final int nrThreads = 3;
    static final ExecutorService executorService = Executors.newFixedThreadPool(nrThreads);
    static final int[][] A = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
    static final int[][] B = {{3, 2, 1}, {3, 2, 1}, {3, 2, 1}};
    static final int[][] C = new int[A.length][B[0].length];

    public static void main(String[] args) throws Exception {
        for (int i = 0; i < nrThreads; ++i) {
            executorService.submit(initMatrixElementSumTask(i, A, B, C));
        }
        executorService.shutdown();

        try {
            if (!executorService.awaitTermination(300, TimeUnit.SECONDS)) {
                executorService.shutdownNow();
            }
            for (int[] ints : C) {
                for (int elem : ints) {
                    System.out.print(elem + " ");
                }
                System.out.println();
            }
        } catch (InterruptedException ex) {
            executorService.shutdownNow();
            Thread.currentThread().interrupt();
        }
    }

    public static ComputeMatricesProductTask initMatrixElementSumTask(int index, int[][] A, int[][] B, int[][] C) {
        int matrixSize = C.length * C[0].length;
        int count = matrixSize / nrThreads;

        int startRow = count * index / C[0].length;
        int startCol = count * index % C[0].length;

        if (index == nrThreads - 1)
            count += matrixSize % nrThreads;

        return new ComputeMatricesProductTask(A, B, C, startRow, startCol, count);
    }
}