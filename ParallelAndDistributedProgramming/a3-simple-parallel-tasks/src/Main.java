import Model.Matrix;
import Model.Utils;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

public class Main {
    private static final int rowsA = 2000;
    private static final int colsA = 2000;

    private static final int rowsB = 2000;
    private static final int colsB = 2000;

    private static final int nrThreads = 3;
    private static final Utils.ThreadApproach THREAD_APPROACH = Utils.ThreadApproach.THREAD_POOL;
    private static final Utils.GenerationApproach GENERATION_APPROACH = Utils.GenerationApproach.COLUMNS;

    public static void main(String[] args) {
        Matrix A = new Matrix(rowsA, colsA);
        Matrix B = new Matrix(rowsB, colsB);

        if (colsA != rowsB) {
            System.out.println("The nr of columns in A should be equal to the nr of rows in B " +
                    "in order to be able to multiply");
        } else {
            Matrix resultMatrix = new Matrix(rowsA, colsB);

            System.out.println("---------------- Starting computing matrix");
            double startTime = System.nanoTime();

            switch (THREAD_APPROACH) {
                case CLASSIC -> classicThreadApproach(A, B, resultMatrix);
                case THREAD_POOL -> threadPoolApproach(A, B, resultMatrix);
                default -> System.out.println("Invalid thread approach");
            }

            double endTime = System.nanoTime();
            System.out.println("----------------  Stopping computing matrix");

            double totalTime = (endTime - startTime) / 1_000_000_000.0;
            System.out.println("Elapsed running time: " + totalTime + "s");
        }
    }

    private static void classicThreadApproach(Matrix A, Matrix B, Matrix C) {
        List<Thread> threads = new ArrayList<>();

        switch (GENERATION_APPROACH) {
            case ROWS:
                for (int i = 0; i < nrThreads; ++i) {
                    threads.add(Utils.initRowTask(i, A, B, C, nrThreads));
                }
                break;
            case COLUMNS:
                for (int i = 0; i < nrThreads; ++i) {
                    threads.add(Utils.initColumnTask(i, A, B, C, nrThreads));
                }
                break;
            case KTH:
                for (int i = 0; i < nrThreads; ++i) {
                    threads.add(Utils.initKTask(i, A, B, C, nrThreads));
                }
                break;
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

        System.out.println("Matrix C:");
        System.out.println(C.toString());
    }

    private static void threadPoolApproach(Matrix A, Matrix B, Matrix C) {
        ExecutorService executorService = new ThreadPoolExecutor(
                nrThreads,
                nrThreads,
                0L,
                TimeUnit.MILLISECONDS,
                new ArrayBlockingQueue<>(nrThreads, true)
        );

        switch (GENERATION_APPROACH) {
            case ROWS:
                for (int i = 0; i < nrThreads; ++i) {
                    executorService.submit(Utils.initRowTask(i, A, B, C, nrThreads));
                }
                break;
            case COLUMNS:
                for (int i = 0; i < nrThreads; ++i) {
                    executorService.submit(Utils.initColumnTask(i, A, B, C, nrThreads));
                }
                break;
            case KTH:
                for (int i = 0; i < nrThreads; ++i) {
                    executorService.submit(Utils.initKTask(i, A, B, C, nrThreads));
                }
                break;
        }
        executorService.shutdown();
        try {
            if (!executorService.awaitTermination(300, TimeUnit.SECONDS)) {
                executorService.shutdownNow();
            }
//            System.out.println("Matrix C:");
//            System.out.println(C.toString());
        } catch (InterruptedException ex) {
            executorService.shutdownNow();
            Thread.currentThread().interrupt();
        }
    }
}
