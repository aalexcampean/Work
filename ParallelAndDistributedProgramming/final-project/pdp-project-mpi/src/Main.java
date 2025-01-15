import mpi.*;

public class Main {

    public static void main(String[] args) {
        MPI.Init(args);

        int id = MPI.COMM_WORLD.Rank();
        int size = MPI.COMM_WORLD.Size();

        UndirectedGraph graph = new UndirectedGraph(4);
        graph.addEdge(0, 1);
        graph.addEdge(1, 2);
        graph.addEdge(2, 3);
        graph.addEdge(2, 0);
        graph.addEdge(3, 1);
        graph.addEdge(0, 3);

        Colors colors = new Colors(4);
        colors.setColorName(0, "yellow");
        colors.setColorName(1, "red");
        colors.setColorName(2, "blue");
        colors.setColorName(3, "purple");

        if (id == 0) {
            System.out.println("Rank 0 is alive and running on " + MPI.Get_processor_name());
            System.out.println("Graph: \n" + graph);

            try {
                System.out.println(Solution.handleMainProcess(size, graph, colors));
            } catch (Exception gce) {
                System.out.println(gce.getMessage());
            }
        }
        else {
            System.out.println("Process " + id);

            int codesNo = colors.getCntColors();
            Solution.handleWorkerProcess(id, size, graph, codesNo);
        }

        MPI.Finalize();
    }
}