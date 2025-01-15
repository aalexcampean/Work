import java.util.concurrent.locks.Lock;

public class Consumer extends Thread {
    private int sum;
    private Buffer buffer;

    public Consumer(Buffer buffer) {
        this.sum = 0;
        this.buffer = buffer;
    }

    @Override
    public void run() {
        while (true) {
            buffer.mutex.lock();
            try {
                while (buffer.buffer.isEmpty()) {
                    buffer.startConsumer.await();
                }

                sum += buffer.buffer.remove(buffer.buffer.size() - 1);
                buffer.startProducer.signalAll();
            } catch (InterruptedException e) {
                e.printStackTrace();
            } finally {
                buffer.mutex.unlock();
                System.out.println("Consumer computed the sum: "+ sum);
            }
        }
    }
}
