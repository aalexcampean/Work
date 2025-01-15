import mpi.MPI;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class BigNumbersProduct {
    public static void master(List<Integer> a, List<Integer> b, int nrProcesses) {
        Collections.reverse(a);
        Collections.reverse(b);

        int n = a.size();
        int newCapacity = 2 * n;

        List<Integer> result = new ArrayList<>(newCapacity);
        for (int i = 0; i < newCapacity; i++) {
            result.add(0);
        }

        int step = n / (nrProcesses - 1);
        int start;
        int end = 0;

        for (int i = 1; i <= nrProcesses - 1; i++) {
            start = end;
            end = start + step;

            if (i == nrProcesses - 1) {
                end = n;
            }

            int countB = end - start;
            List<Integer> bCopy = new ArrayList<>();
            for (int j = start; j < end; j++) {
                bCopy.add(b.get(j));
            }

            // 1 2 3 4
            // 5 6 7 8

            int[] metadata = new int[]{n, countB, start};
            MPI.COMM_WORLD.Send(metadata, 0, 3, MPI.INT, i, 0);
            MPI.COMM_WORLD.Send(new Object[]{a}, 0, 1, MPI.OBJECT, i, 0);
            MPI.COMM_WORLD.Send(new Object[]{bCopy}, 0, 1, MPI.OBJECT, i, 0);
        }

        int carry = 0;
        for (int i = 1; i <= nrProcesses - 1; i++) {
            Object[] received = new Object[1];

            MPI.COMM_WORLD.Recv(received, 0, 1, MPI.OBJECT, i, 0);

            List<Integer> receivedList = (List<Integer>) received[0];
            carry = 0;

            for (int p = 0; p < newCapacity; p++) {
                result.set(p, result.get(p) + receivedList.get(p) + carry);
                carry = result.get(p) / 10;
                result.set(p, result.get(p) % 10);
            }
        }

        if (carry == 1) {
            result.set(newCapacity, 1);
        }

        Collections.reverse(result);
        System.out.println(result);
    }

    public static void worker() {
        int[] metadata = new int[3];
        Object[] objs = new Object[2];

        MPI.COMM_WORLD.Recv(metadata, 0, 3, MPI.INT, 0, 0);
        MPI.COMM_WORLD.Recv(objs, 0, 1, MPI.OBJECT, 0, 0);
        MPI.COMM_WORLD.Recv(objs, 1, 1, MPI.OBJECT, 0, 0);

        int n = metadata[0];
        int bSize = metadata[1];
        int start = metadata[2];

        List<Integer> a = (List<Integer>) objs[0];
        List<Integer> bCopy = (List<Integer>) objs[1];

        List<Integer> result = new ArrayList(2 * n);
        for (int i = 0; i < 2 * n; i++) {
            result.add(0);
        }

        for (int i = 0; i < bSize; i++) {
            for (int j = 0; j < n; j++) {
                int prod = a.get(j) * bCopy.get(i);
                result.set(start + i + j, result.get(start + i + j) + prod);
            }
        }

        MPI.COMM_WORLD.Send(new Object[]{result}, 0, 1, MPI.OBJECT, 0, 0);
    }


    public static void main(String[] args) {
        MPI.Init(args);
        int me = MPI.COMM_WORLD.Rank();
        int nrProcesses = MPI.COMM_WORLD.Size();

        List<Integer> a = Arrays.asList(1, 2, 3);
        List<Integer> b = Arrays.asList(1, 2, 9);

        if (me == 0) {
            master(a, b, nrProcesses);
        } else {
            worker();
        }
        MPI.Finalize();
    }
}