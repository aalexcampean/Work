import java.util.*;

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

    public void addEdge(int fromVertex, int toVertex) {
        adjacencyList.get(fromVertex).add(toVertex);
        adjacencyList.get(toVertex).add(fromVertex);
    }

    public boolean isEdge(int fromVertex, int toVertex) {
        return adjacencyList.get(fromVertex).contains(toVertex);
    }

    public int nodesCount() {
        return cntNodes;
    }

    @Override
    public String toString() {
        var result = new StringBuilder();
        for (var i = 0; i < adjacencyList.size(); i++) {
            result.append(i).append(": ").append(adjacencyList.get(i).toString()).append("\n");
        }

        return result.toString();
    }
}