import java.util.Map;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Transaction extends Inventory implements Runnable {
    private int id;
    private double totalSum = 0;
    private Boolean inventoryChanged;
    private Inventory inventory;
    private Map<Product, Lock> mutexes;

    public Transaction(Inventory inventory, int id, Map<Product, Lock> mutexes) {
        this.id = id;
        this.inventory = inventory;
        this.mutexes = mutexes;
    }

    public int getId() {
        return this.id;
    }

    public double getTotalSum() {
        return this.totalSum;
    }

    @Override
    public void add(Product product, Integer quantity) {
        super.add(product, quantity);
        inventoryChanged = true;
    }

    @Override
    public void run() {
        this.getProducts().forEach(product -> {
            mutexes.get(product).lock();

            try {
                inventory.remove(product, this.getProductQuantity(product));
                // Update the total sum of the transaction
                this.totalSum += this.getProductQuantity(product) * product.getPrice();
                System.out.println("| Transaction " + this.id + " | Sold " + this.getProductQuantity(product) +  " Units of: " + product.getName());
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }

            mutexes.get(product).unlock();
        });
    }
}
