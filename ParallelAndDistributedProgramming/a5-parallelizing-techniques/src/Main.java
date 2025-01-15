import Algorithms.Parallel.ClassicParallel;
import Algorithms.Parallel.KaratsubaParallel;
import Algorithms.Sequential.ClassicSequential;
import Algorithms.Sequential.KaratsubaSequential;
import Model.Polynomial;
import Utilities.Choices;

import java.util.concurrent.ExecutionException;

import static Utilities.Choices.AlgorithmChoice.CLASSIC;
import static Utilities.Choices.AlgorithmChoice.KARATSUBA;
import static Utilities.Choices.MethodChoice.PARALLEL;
import static Utilities.Choices.MethodChoice.SEQUENTIAL;

public class Main {
    private static final Choices.MethodChoice METHOD = PARALLEL;
    private static final Choices.AlgorithmChoice ALGORITHM = KARATSUBA;

    public static void main(String[] args) throws ExecutionException, InterruptedException {
        Polynomial p1 = new Polynomial(100);
        System.out.println("p1 = " + p1);
        Polynomial p2 = new Polynomial(100);
        System.out.println("p2 = " + p2);
        long startTime = System.nanoTime();
        run(p1, p2);
        long stopTime = System.nanoTime();
        double totalTime = ((double) stopTime - (double) startTime) / 1_000_000_000.0;
        System.out.println("Elapsed running time: " + totalTime + "s");
    }

    private static void run(Polynomial polynomial1, Polynomial polynomial2) throws ExecutionException, InterruptedException {
        Polynomial result;
        if (METHOD.equals(SEQUENTIAL)) {
            if (ALGORITHM.equals(Choices.AlgorithmChoice.CLASSIC)) {
                result = ClassicSequential.multiply(polynomial1, polynomial2);
            } else {
                result = KaratsubaSequential.multiply(polynomial1, polynomial2);
            }
        } else {
            if (ALGORITHM.equals(Choices.AlgorithmChoice.CLASSIC)) {
                result = ClassicParallel.multiply(polynomial1, polynomial2);
            } else {
                result = KaratsubaParallel.multiply(polynomial1, polynomial2, 1);
            }
        }
        System.out.println("p1 * p2 = " + result.toString());
    }
}
