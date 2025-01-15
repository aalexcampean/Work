import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class UndirectedGraph {
    private final int cntNodes;
    private final List<Set<Integer>> adjacencyList;

    public UndirectedGraph(int cntNodes) {
        this.cntNodes = cntNodes;

        adjacencyList = new ArrayList<>();
        for (int node = 0; node < cntNodes; node++) {
            adjacencyList.add(new HashSet<>());
        }
    }

    public void addEdge(int x, int y) {
        adjacencyList.get(x).add(y);
        adjacencyList.get(y).add(x);
    }

    public boolean isEdge(int x, int y) {
        return adjacencyList.get(x).contains(y) || adjacencyList.get(y).contains(x);
    }

    public int getCntNodes() {
        return cntNodes;
    }
}