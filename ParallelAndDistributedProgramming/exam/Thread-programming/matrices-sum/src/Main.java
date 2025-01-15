import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Main {
    static final int nrThreads = 3;
    static final ExecutorService executorService = Executors.newFixedThreadPool(nrThreads);
    static final int[][] A = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
    static final int[][] B = {{3, 2, 1}, {3, 2, 1}, {3, 2, 1}};
    static final int[][] C = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

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

    public static ComputeMatricesSumTask initMatrixElementSumTask(int index, int[][] A, int[][] B, int[][] C) {
        int matrixSize = A.length * A[0].length;
        int count = matrixSize / nrThreads;

        int startRow = count * index / A[0].length;
        int startCol = count * index % A[0].length;

        if (index == nrThreads - 1)
            count += matrixSize % nrThreads;

        return new ComputeMatricesSumTask(A, B, C, startRow, startCol, count);
    }
}