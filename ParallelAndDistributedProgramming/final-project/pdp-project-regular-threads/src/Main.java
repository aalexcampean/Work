public class Main {
    public static void main(String[] args) throws Exception {
        UndirectedGraph graph = new UndirectedGraph(5);
//        graph.addEdge(0, 1);
//        graph.addEdge(1, 2);
//        graph.addEdge(2, 3);
//        graph.addEdge(3, 4);
//        graph.addEdge(4, 0);
//        graph.addEdge(2, 0);
//        graph.addEdge(0, 4);
//        graph.addEdge(4, 3);
//        graph.addEdge(3, 1);
//        graph.addEdge(1, 4);

        Colors colors = new Colors(3);
        colors.setColorName(0, "red");
        colors.setColorName(1, "green");
        colors.setColorName(2, "blue");

        System.out.println(Solution.solve(graph, colors));
    }
}
