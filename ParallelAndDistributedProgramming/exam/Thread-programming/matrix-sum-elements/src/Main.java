import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Main {
    static final int nrThreads = 3;
    static final List<List<Integer>> matrix = Arrays.asList(Arrays.asList(1, 2, 3), Arrays.asList(4, 5, 6), Arrays.asList(7, 8, 9));
    public static Lock mutex = new ReentrantLock(true);

    public static void main(String[] args) throws Exception {
        List<Thread> threads = new ArrayList<>();
        for (int i = 0; i < nrThreads; ++i) {
            threads.add(initMatrixElementSumTask(i));
        }

        for (Thread thread : threads) {
            thread.start();
        }

        for (Thread thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        System.out.println("Sum of matrix elements:" + MatrixElementsSumTask.sum);
    }

    public static MatrixElementsSumTask initMatrixElementSumTask(int index) {
        int matrixSize = matrix.size() * matrix.get(0).size();
        int count = matrixSize / nrThreads;

        int startRow = count * index / matrix.get(0).size();
        int startCol = count * index % matrix.get(0).size();

        if (index == nrThreads - 1)
            count += matrixSize % nrThreads;

        return new MatrixElementsSumTask(matrix, startRow, startCol, count, mutex);
    }
}