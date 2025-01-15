import java.util.Arrays;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;


public class Solution {
    public static Map<Integer, String> solve(UndirectedGraph graph, Colors colors) throws Exception {
        var executor = Executors.newFixedThreadPool(4);
        var cntColors = colors.getCntColors();
        var codes = graphColoringRecAsync(0, graph, cntColors, new int[graph.getCntNodes()], 0, executor);
        executor.shutdown();
        executor.awaitTermination(60, TimeUnit.DAYS);

        if (codes[0] == -1)
            throw new RuntimeException("No solution found!");

        return colors.getNodesToColors(codes);
    }

    public static int[] graphColoringRecAsync(int node, UndirectedGraph graph, int colorsCount, int[] codes, int depth, ExecutorService executor) throws Exception {
        if (depth >= 2) {
            return graphColoringRec(node, graph, colorsCount, codes);
        }

        if (node == graph.getCntNodes()) {
            if (isCodeValid(codes, graph)) {
                return codes;
            }

            return getArrayOf(graph.getCntNodes());
        }

        for (int code = 0; code < colorsCount; code++) {
            codes[node] = code;

            var future = executor.submit(() ->
                    graphColoringRecAsync(node  + 1, graph, colorsCount, codes, depth + 1, executor));

            var result = future.get();
            // If valid
            if (result[0] != -1) {
                return result;
            }

            codes[node] = 0;
        }

        return getArrayOf(graph.getCntNodes());
    }

    public static int[] graphColoringRec(int node, UndirectedGraph graph, int colorsCount, int[] codes) {
        if (node == graph.getCntNodes()) {
            if (isCodeValid(codes, graph)) {
                return codes;
            }

            return getArrayOf(graph.getCntNodes());
        }

        for (int code = 0; code < colorsCount; code++) {
            codes[node] = code;

            var result = graphColoringRec(node + 1, graph, colorsCount, codes);
            if (result[0] != -1) {
                return codes;
            }

            codes[node] = 0;
        }

        return getArrayOf(graph.getCntNodes());
    }

    private static boolean isCodeValid(int[] codes, UndirectedGraph graph) {
        for (var x = 0; x < graph.getCntNodes() - 1; x++) {
            for (var y = x + 1; y < graph.getCntNodes(); y++) {
                if (graph.isEdge(x, y) && codes[x] == codes[y]) {
                    return false;
                }
            }
        }
        return true;
    }

    private static int[] getArrayOf(int length) {
        int[] array = new int[length];
        Arrays.fill(array, -1);

        return array;
    }
}