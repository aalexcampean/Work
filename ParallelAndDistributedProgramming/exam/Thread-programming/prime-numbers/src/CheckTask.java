import java.util.List;

public class CheckTask extends Thread {
    protected final List<Integer> primes;
    protected final int start, end;

    public CheckTask(List<Integer> primes, int start, int end) {
        this.primes = primes;
        this.start = start;
        this.end = end;
    }

    @Override
    public void run() {
        for (int i = start; i <= end; i++) {
            boolean isPrime = true;
            for (int prime : primes) {
                if (i % prime == 0) {
                    System.out.println(i + " is divisible with: " + prime);
                    isPrime = false;
                }
            }
            if (isPrime) System.out.println(i + " is prime");
        }
    }
}
