import mpi.MPI;

import java.util.ArrayList;
import java.util.List;

public class Main {
    public static boolean check(List<Integer> permutation) {
        return permutation.get(0) % 2 == 0;
    }

    public static void permutationBack(List<Integer> sol, int N, List<List<Integer>> sols) {
        if (sol.size() == N) {
            if (check(sol)) {
                System.out.println(sol);
                sols.add(new ArrayList<>(sol));
            }
            return;
        }

        for (int i = 1; i <= N; i++) {
            if (sol.contains(i)) continue;
            sol.add(i);
            permutationBack(sol, N, sols);
            sol.remove(sol.size() - 1);
        }
    }

    private static void master(int N, int nrProcesses) {
        int step = N / (nrProcesses - 1);
        List<List<Integer>> result = new ArrayList<>();

        int start;
        int end = 1;
        for (int i = 1; i < nrProcesses; i++) {
            start = end;
            end = start + step;

            if (i == nrProcesses - 1) {
                end = N;
            }

            int[] metadata = new int[]{start, end, N};
            MPI.COMM_WORLD.Send(metadata, 0, 3, MPI.INT, i, 0);
        }

        for (int i = 1; i < nrProcesses; i++) {
            Object[] permutations = new Object[1];
            MPI.COMM_WORLD.Recv(permutations, 0, 1, MPI.OBJECT, i, 0);
            result.addAll((List<List<Integer>>) permutations[0]);
        }
        System.out.println(result);
    }

    private static void worker() {
        int[] metadata = new int[3];
        MPI.COMM_WORLD.Recv(metadata, 0, 3, MPI.INT, 0, 0);
        int start = metadata[0];
        int end = metadata[1];
        int N = metadata[2];

        List<List<Integer>> permutations = new ArrayList<>(N);
        for (int i = start; i <= end; i++) {
            List<Integer> sol = new ArrayList<>();
            sol.add(i);
            permutationBack(sol, N, permutations);
        }
        MPI.COMM_WORLD.Send(new Object[]{permutations}, 0, 1, MPI.OBJECT, 0, 0);
    }

    public static void main(String[] args) {
        MPI.Init(args);
        int me = MPI.COMM_WORLD.Rank();
        int nrProcesses = MPI.COMM_WORLD.Size();
        int N = 4;

        if (me == 0) {
            master(N, nrProcesses);
        } else {
            worker();
        }
        MPI.Finalize();
    }
}
