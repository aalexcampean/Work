import Algorithm.HamiltonianCycleFinder;
import Model.Graph;

import java.util.AbstractMap;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {

        //Hamiltonian cycle: 0->1->2->4->3->0
        Graph graphWithHamiltonianCycle = new Graph(new ArrayList<>(List.of(0, 1, 2, 3, 4)),
                new ArrayList<>(List.of(
                        new AbstractMap.SimpleEntry<>(0, List.of(1)),
                        new AbstractMap.SimpleEntry<>(1, List.of(2, 3)),
                        new AbstractMap.SimpleEntry<>(2, List.of(4)),
                        new AbstractMap.SimpleEntry<>(3, List.of(0)),
                        new AbstractMap.SimpleEntry<>(4, List.of(1, 3, 4)))));

        //No Hamiltonian cycles (removed edge 4->3)
        Graph graphWithoutHamiltonianCycle = new Graph(new ArrayList<>(List.of(0, 1, 2, 3, 4)),
                new ArrayList<>(List.of(
                        new AbstractMap.SimpleEntry<>(0, List.of(1)),
                        new AbstractMap.SimpleEntry<>(1, List.of(2, 3)),
                        new AbstractMap.SimpleEntry<>(2, List.of(4)),
                        new AbstractMap.SimpleEntry<>(3, List.of(0)),
                        new AbstractMap.SimpleEntry<>(4, List.of(1, 4)))));

        //Random graph
        Graph randomGraph = new Graph(10);

        System.out.println(graphWithHamiltonianCycle);
        System.out.println(graphWithoutHamiltonianCycle);
        System.out.println(randomGraph);

        long startTime = System.nanoTime();

        HamiltonianCycleFinder finder = new HamiltonianCycleFinder(graphWithHamiltonianCycle);
        finder.startSearch();

        long stopTime = System.nanoTime();

        double totalTime = ((double) stopTime - (double) startTime) / 1_000_000_000.0;
        System.out.println("Elapsed running time: " + totalTime + "s");
    }
}
