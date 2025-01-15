import java.util.ArrayList;

public class Main {
    public static void main(String[] args) throws Exception {
        Permutations p = new Permutations();
        p.back(new ArrayList<>(), 2, 4);
        p.executorService.shutdown();

        if (p.cnt.get() == 0) System.out.println("No permutations found");
    }
}
