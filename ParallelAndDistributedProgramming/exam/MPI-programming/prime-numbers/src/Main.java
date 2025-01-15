import mpi.MPI;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Main {
    public static boolean isPrime(int n) {
        if (n <= 1) {
            return false;
        }
        for (int i = 2; i <= Math.sqrt(n); i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }

    public static List<Integer> getPrimesUpToSqrt(int N) {
        List<Integer> primes = new ArrayList<Integer>();
        for (int i = 2; i <= Math.sqrt(N); i++) {
            if (isPrime(i)) {
                primes.add(i);
            }
        }
        return primes;
    }

    public static List<Integer> primesInInterval(int me, int nrProcesses, int N, List<Integer> primesToSqrt) {
        List<Integer> result = new ArrayList<>();
        int begin;
        int end;

        begin = me == 0 ? (int) Math.sqrt(N) : me * (N - primesToSqrt.get(primesToSqrt.size() - 1) + 1) / nrProcesses;
        end = me == (nrProcesses - 1) ? N : (me + 1) * (N - primesToSqrt.get(primesToSqrt.size() - 1) + 1) / nrProcesses;

        System.out.println("Start: " + begin + "\n");
        System.out.println("End: " + end + "\n");
        for (int i = begin; i < end; i++) {
            if (isPrime(i)) {
                result.add(i);
            }
        }
        return result;
    }

    private static void master(int N, int nrProcesses) {
        List<Integer> primesToSqrt = getPrimesUpToSqrt(N);

        int[] metadata = new int[1];
        metadata[0] = N;
        for (int i = 1; i < nrProcesses; i++) {
            MPI.COMM_WORLD.Send(metadata, 0, 1, MPI.INT, i, 0);
            MPI.COMM_WORLD.Send(new Object[]{primesToSqrt}, 0, 1, MPI.OBJECT, i, 0);
        }

        List<Integer> result = primesToSqrt;
        result.addAll(primesInInterval(0, nrProcesses, N, primesToSqrt));
        for (int i = 1; i < nrProcesses; i++) {
            Object[] obj = new Object[1];
            MPI.COMM_WORLD.Recv(obj, 0, 1, MPI.OBJECT, i, 0);
            result.addAll((List<Integer>) obj[0]);
        }
        System.out.println(result);
    }

    private static void worker(int me, int nrProcesses) {
        int[] metadata = new int[1];
        Object[] primesToSqrt = new Object[1];

        MPI.COMM_WORLD.Recv(metadata, 0, 2, MPI.INT, 0, 0);
        MPI.COMM_WORLD.Recv(primesToSqrt, 0, 1, MPI.OBJECT, 0, 0);

        int N = metadata[0];
        List<Integer> primes = (List<Integer>) primesToSqrt[0];

        List<Integer> result = primesInInterval(me, nrProcesses, N, primes);
        MPI.COMM_WORLD.Send(new Object[]{result}, 0, 1, MPI.OBJECT, 0, 0);
    }

    public static void main(String[] args) {
        MPI.Init(args);
        int me = MPI.COMM_WORLD.Rank();
        int nrProcesses = MPI.COMM_WORLD.Size();
        int N = 100;

        if (me == 0) {
            master(N, nrProcesses);
        } else {
            worker(me, nrProcesses);
        }
        MPI.Finalize();
    }
}