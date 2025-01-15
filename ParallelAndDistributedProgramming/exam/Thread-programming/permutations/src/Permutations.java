import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.AtomicInteger;

public class Permutations {
    public AtomicInteger cnt;
    public ExecutorService executorService = Executors.newFixedThreadPool(10);

    public Permutations() {
        cnt = new AtomicInteger(0);
    }

    public boolean check(List<Integer> permutation) {
        return permutation.get(0) % 2 == 0;
    }

    public List<Integer> back(List<Integer> sol, int T, int n) throws Exception {
        if (sol.size() == n) {
            if (check(sol)) {
                System.out.println(sol);
                cnt.getAndIncrement();

                return sol;
            }
            return Collections.emptyList();
        }
        if (T == 1) {
            for (int i = 1; i <= n; i++) {
                if (sol.contains(i)) continue;
                sol.add(i);
                back(sol, T, n);
                sol.remove(sol.size() - 1);
            }
        } else {
            List<Integer> solution = new ArrayList<>(sol);
            for (int i = 1; i <= n; i ++) {
                if (solution.contains(i)) continue;
                solution.add(i);

                var future = executorService.submit(() -> back(solution, T -1, n));
                var result = future.get();

                if (!result.isEmpty()) return result;
                solution.remove(solution.size() - 1);
            }
        }
        return Collections.emptyList();
    }
}
