import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Product {
    private String name;
    private float price;
    private Lock mutex = new ReentrantLock();

    public Product(String name, float price, Lock mutex) {
        this.name = name;
        this.price = price;
        this.mutex = mutex;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public float getPrice() {
        return price;
    }

    public void setPrice(float price) {
        this.price = price;
    }

    public Lock getMutex() {
        return mutex;
    }

    public void setMutex(Lock mutex) {
        this.mutex = mutex;
    }
}
