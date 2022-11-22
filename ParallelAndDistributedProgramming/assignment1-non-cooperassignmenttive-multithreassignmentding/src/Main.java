import java.io.File;
import java.io.FileNotFoundException;
import java.text.DecimalFormat;
import java.util.*;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Main {
    private static final int NUMBER_OF_THREADS = 5;
    private static double initialSum = 0.0f;

    private static Inventory inventory = new Inventory();
    private static List<Product> products = new ArrayList<>();
    private static List<Transaction> transactionRecord = new ArrayList<>();
    private static Map<Product, Lock> mutexes = new HashMap<>();

    public static void main(String[] args) {
        ReadFromFile();
        initialSum = inventory.computeTotalSum();

        float start = System.nanoTime() / 1000000;
        for (int i = 1; i <= NUMBER_OF_THREADS; i++) {
            // Create a transaction with the inventory at the moment before it is executed
            Transaction transaction = new Transaction(inventory, i, mutexes);

            // Selecting a random number of products for a transaction
            int numberOfProducts = new Random().nextInt(10);

            for (int j = 0; j < numberOfProducts; j++) {
                // Selecting a random quantity for a product to be sold
                int quantity = new Random().nextInt(10);
                while (quantity == 0) {
                    quantity = new Random().nextInt(10);
                }

                // Selecting a random product
                int productIndex = new Random().nextInt(products.size());

                Product randomProduct = products.get(productIndex);
                transaction.add(randomProduct, quantity);
            }
            transactionRecord.add(transaction);
        }


        List<Thread> threads = new ArrayList<>();

        transactionRecord.forEach(t -> threads.add(new Thread(t)));
        threads.forEach(Thread::start);
        threads.forEach(thread -> {
            try {
                thread.join();
            } catch (InterruptedException e) {
                System.out.println(e.getMessage());
            }
        });

        verifyInvoice();

        float end = System.nanoTime() / 1000000;
        System.out.println("\n End work: " + (end - start) / 1000 + " seconds");
    }

    private static void ReadFromFile() {
        File file = new File("/Users/alexcampean/Documents/university/sem_5/PDP/labs/a1-non-cooperative-multithreading/src/Inventory");
        try {
            Scanner scanner = new Scanner(file);
            while (scanner.hasNext()) {
                Lock mutex = new ReentrantLock();
                Product product = new Product(scanner.next(), scanner.nextFloat(), mutex);

                products.add(product);
                inventory.add(product, scanner.nextInt());
                mutexes.put(product, mutex);
            }
        } catch (FileNotFoundException e) {
            System.out.println(e.getMessage());
        }
    }

    static void verifyInvoice() {
        System.err.println("Verifying the stock...");

        double currentSum = inventory.computeTotalSum();

        double expectedSum = initialSum - currentSum;
        double actualSum = transactionRecord.stream().mapToDouble(Transaction::getTotalSum)
                .sum();

        DecimalFormat df = new DecimalFormat("#.#");
        if(Objects.equals(df.format(expectedSum), df.format(actualSum))) {
            System.err.println("Verification Successful!");
        } else {
            System.err.println("Stock verification failed!");
        }
    }
}
