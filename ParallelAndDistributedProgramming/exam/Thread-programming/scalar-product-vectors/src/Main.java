import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class Main {
    static final int nrThreads = 3;
    static final ExecutorService executorService = Executors.newFixedThreadPool(nrThreads);
    static final int[] A = {5, 6, 7, 10, 4, 5, 1, 0};
    static final int[] B = {1, 2, 3, 6, 1, 11, 5, 7};

    public static void main(String[] args) throws Exception {
        for (int i = 0; i < nrThreads; ++i) {
            executorService.submit(initMatrixElementSumTask(i, A, B));
        }
        executorService.shutdown();

        try {
            if (!executorService.awaitTermination(300, TimeUnit.SECONDS)) {
                executorService.shutdownNow();
            }
            System.out.println("Scalar Product: " + ComputeMatricesSumTask.scalarProduct);
        } catch (InterruptedException ex) {
            executorService.shutdownNow();
            Thread.currentThread().interrupt();
        }
    }

    public static ComputeMatricesSumTask initMatrixElementSumTask(int index, int[] A, int[] B) {
        int vectorSize = A.length;
        int count = vectorSize / nrThreads;

        int startPos = count * index;

        if (index == nrThreads - 1)
            count += vectorSize % nrThreads;

        return new ComputeMatricesSumTask(A, B, startPos, count);
    }
}