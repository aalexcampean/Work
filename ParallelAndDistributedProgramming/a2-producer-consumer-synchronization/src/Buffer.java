import java.util.ArrayList;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Buffer {
    protected ArrayList<Integer> buffer = new ArrayList<>();
    public Lock mutex = new ReentrantLock(true);
    public Condition startProducer = mutex.newCondition();
    public Condition startConsumer = mutex.newCondition();
}
