import mpi.MPI;

import java.util.*;


public class Solution {
    public static Map<Integer, String> handleMainProcess(int mpiSize, UndirectedGraph graph, Colors colors) {
        int cntColors = colors.getCntColors();
        int[] codes = graphColoringRec(0, graph, cntColors, new int[graph.nodesCount()], 0, mpiSize, 0);

        if (codes[0] == -1)
            throw new RuntimeException("No solution found!");

        return colors.getNodesToColors(codes);
    }

    private static int[] graphColoringRec(int node, UndirectedGraph graph, int cntColors, int[] codes, int mpiId, int mpiSize, int power) {
        int nodesNo = graph.nodesCount();

        if (!isCodeValid(node, codes, graph))
            return getArrayOf(nodesNo);

        if (node + 1 == graph.nodesCount()) {
            return codes;
        }

        int coefficient = (int) Math.pow(cntColors, power);
        int code = 0;
        int destination = mpiId + coefficient * (code + 1); // 1

        while (code < cntColors - 1 && destination < mpiSize) {
            code++; // 2, 3
            destination = mpiId + coefficient * (code + 1); // 2, 3, 4
        }

        // code = 3, dest = 4
        int nextNode = node + 1; // 1
        int nextPower = power + 1; // 1

        for (int currentCode = 1; currentCode < code; currentCode++) {
            destination = mpiId + coefficient * currentCode; // 1

            int[] data = new int[]{mpiId, nextNode, nextPower};
            MPI.COMM_WORLD.Send(data, 0, data.length, MPI.INT, destination, 0);

            int[] nextCodes = Arrays.copyOf(codes, codes.length);
            nextCodes[nextNode] = currentCode;

            MPI.COMM_WORLD.Send(nextCodes, 0, nodesNo, MPI.INT, destination, 0);
        }

        int[] nextCodes = Arrays.copyOf(codes, codes.length);
        nextCodes[nextNode] = 0;

        int[] result = graphColoringRec(nextNode, graph, cntColors, nextCodes, mpiId, mpiSize, nextPower);
        if (result[0] != -1) {
            return result;
        }

        for (int currentCode = 1; currentCode < code; currentCode++) {
            destination = mpiId + coefficient * currentCode;

            result = new int[nodesNo];
            MPI.COMM_WORLD.Recv(result, 0, nodesNo, MPI.INT, destination, MPI.ANY_TAG);

            if (result[0] != -1) {
                return result;
            }
        }

        for (int currentCode = code; currentCode < cntColors; currentCode++) {
            nextCodes = Arrays.copyOf(codes, codes.length);
            nextCodes[nextNode] = currentCode;

            result = graphColoringRec(nextNode, graph, cntColors, nextCodes, mpiId, mpiSize, nextPower);
            if (result[0] != -1) {
                return result;
            }
        }

        return result;
    }

    public static void handleWorkerProcess(int mpiMe, int mpiSize, UndirectedGraph graph, int codesNo) {
        int nodesNo = graph.nodesCount();

        int[] data = new int[3];
        MPI.COMM_WORLD.Recv(data, 0, data.length, MPI.INT, MPI.ANY_SOURCE, MPI.ANY_TAG);

        int parent = data[0];
        int node = data[1];
        int power = data[2];

        int[] codes = new int[nodesNo];
        MPI.COMM_WORLD.Recv(codes, 0, nodesNo, MPI.INT, MPI.ANY_SOURCE, MPI.ANY_TAG);

        int[] newCodes = graphColoringRec(node, graph, codesNo, codes, mpiMe, mpiSize, power);

        MPI.COMM_WORLD.Send(newCodes, 0, nodesNo, MPI.INT, parent, 0);
    }

    private static boolean isCodeValid(int node, int[] codes, UndirectedGraph graph) {
        for (int currentNode = 0; currentNode < node; currentNode++)
            if ((graph.isEdge(node, currentNode) || graph.isEdge(currentNode, node)) && codes[node] == codes[currentNode])
                return false;

        return true;
    }

    private static int[] getArrayOf(int length) {
        int[] array = new int[length];
        Arrays.fill(array, -1);

        return array;
    }
}