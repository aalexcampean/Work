package Algorithm;

import Model.Graph;

import java.util.ArrayList;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

public class HamiltonianCycleFinder {
    public Graph graph;

    public HamiltonianCycleFinder(Graph graph) {
        this.graph = graph;
    }

    public void startSearch() {
        ArrayList<Integer> path = new ArrayList<>();

        try {
            int randomNode = graph.getRandomNode();
            path.add(randomNode);
            search(randomNode, randomNode, path, 0);
        } catch (final Exception e) {
            e.printStackTrace();
        }
    }

    public void search(int currentNode, int initialNode, ArrayList<Integer> path, int depth) throws Exception {
        //base case when we found a solution
        //we can reach the first node from the current node and the pathCount is equal to the number of nodes
        if (graph.getNeighbours(currentNode).contains(initialNode) && path.size() == graph.size()) {
            System.out.println("Hamiltonian cycle found: " + path);
            return;
        }
        //if we visited all nodes we just return
        if (path.size() == graph.size()) {
            return;
        }

        //we start checking all possible vertices
        graph.getNeighbours(currentNode).forEach((node) -> {
            //if there is an edge to the node and we haven't already visited it
            // we add it to the path and mark it as visited(temporarily remove the edge)
            if (!path.contains(node)) {
                path.add(node);

                final int newNode = node;

                if (depth < 4) {
                    //call the search function for this node recursively on a new thread
                    ThreadPoolExecutor executor = (ThreadPoolExecutor) Executors.newFixedThreadPool(4);

                    final Runnable task = () -> {
                        try {
                            search(newNode, initialNode, path, depth + 1);
                        } catch (Exception e) {
                            throw new RuntimeException(e.getMessage());
                        }
                    };
                    executor.execute(task);

                    executor.shutdown();
                    try {
                        executor.awaitTermination(50, TimeUnit.SECONDS);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                } else {
                    try {
                        search(newNode, initialNode, path, depth + 1);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }

                //delete the path after it was checked
                path.remove(path.size() - 1);

            }
        });
    }
}
