package Model;

import java.util.*;

public class Graph {
    private Map<Integer, List<Integer>> graph = new HashMap<>();

    public Graph(int nodes) {
        for (var i = 0; i < nodes; ++i)
            graph.put(i, new ArrayList<>());
        generateEdges();
    }

    public Graph(List<Integer> nodes, List<Map.Entry<Integer, List<Integer>>> edges) {
        nodes.forEach((node) -> {
            graph.put(node, new ArrayList<>());
        });

        edges.forEach((entry) -> {
            graph.put(entry.getKey(), entry.getValue());
        });
    }

    public void generateEdges() {
        Random random = new Random();
        var size = Math.pow(size(), 2);

        for (int i = 0; i < size / 2; i++) {
            int nodeA = random.nextInt(size());
            int nodeB = random.nextInt(size());

            addEdge(nodeA, nodeB);
        }
    }

    public void addEdge(int node1, int node2) {
        if (!graph.get(node1).contains(node2))
            graph.get(node1).add(node2);
    }

    public Set<Integer> getNodes() {
        return graph.keySet();
    }

    public List<Map.Entry<Integer, List<Integer>>> getEdges() {
        List<Map.Entry<Integer, List<Integer>>> result = new ArrayList<>();
        graph.entrySet().forEach((entry) -> {
            result.add(new AbstractMap.SimpleEntry<>(entry.getKey(), entry.getValue()));
        });
        return result;
    }

    public Integer getRandomNode() {
        return getNodes().stream().skip(new Random().nextInt(size())).findFirst().orElse(null);
    }

    public List<Integer> getNeighbours(int node) {
        return graph.get(node);
    }

    public int size() {
        return graph.size();
    }

    @Override
    public String toString() {
        StringBuilder resultString = new StringBuilder();

        graph.entrySet().forEach((entry) -> {
            resultString.append("node ").append(entry.getKey()).append(":\n");
            entry.getValue().forEach((neighbour) -> {
                resultString.append("(").append(entry.getKey()).append(" -> ").append(neighbour).append(")\n");
            });
        });

        return resultString.toString();
    }
}
