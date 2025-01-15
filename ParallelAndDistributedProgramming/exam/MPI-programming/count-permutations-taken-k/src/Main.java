import mpi.MPI;

import java.util.ArrayList;
import java.util.List;

public class Main {
    public static int cnt;

    public static boolean check(List<Integer> permutation){
        return permutation.get(0) % 2 == 0;
    }

    public static void permutationBack(List<Integer> sol, int N, int K){
        if (sol.size() == K) {
            if (check(sol)) {
                cnt += 1;
            }
            return;
        }

        for (int i = 1; i <= N ; i++) {
            if(sol.contains(i)) continue;
            sol.add(i);
            permutationBack(sol, N, K);
            sol.remove(sol.size() - 1);
        }
    }

    private static void master(int N, int K, int nrProcesses) {
        int step = N / (nrProcesses - 1);

        int start;
        int end = 1;
        for (int i = 1; i < nrProcesses; i++) {
            start = end;
            end = start + step;

            if (i == nrProcesses - 1) {
                end = N;
            }

            int[] metadata = new int[]{start, end, N, K};
            MPI.COMM_WORLD.Send(metadata, 0, 4, MPI.INT, i, 0);
        }

        int[] count = new int[1];
        for (int i = 1; i < nrProcesses; i++) {
            MPI.COMM_WORLD.Recv(count, 0, 1, MPI.INT, i, 0);
        }
        System.out.println(count[0]);
    }

    private static void worker() {
        int[] metadata = new int[4];
        MPI.COMM_WORLD.Recv(metadata, 0, 4, MPI.INT, 0, 0);
        int start = metadata[0];
        int end = metadata[1];
        int N = metadata[2];
        int K = metadata[3];

        for (int i = start; i < end; i++) {
            List<Integer> sol = new ArrayList<>();
            sol.add(i);
            permutationBack(sol, N, K);
        }
        MPI.COMM_WORLD.Send(new int[]{cnt}, 0,1, MPI.INT, 0,0);
    }

    public static void main(String[] args) {
        MPI.Init(args);
        int me = MPI.COMM_WORLD.Rank();
        int nrProcesses = MPI.COMM_WORLD.Size();
        int N = 5;
        int K = 3;

        if (me == 0) {
            master(N, K, nrProcesses);
        } else {
            worker();
        }
        MPI.Finalize();
    }
}
