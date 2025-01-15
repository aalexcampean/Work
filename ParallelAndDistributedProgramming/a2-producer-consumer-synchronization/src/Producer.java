import java.util.ArrayList;

public class Producer extends Thread {
    private ArrayList<Integer> vector1;
    private ArrayList<Integer> vector2;
    private int vectorSize;
    private int vectorIndex;
    private Buffer buffer;

    public Producer(Buffer buffer) {
        this.buffer = buffer;
        this.vector1 = new ArrayList<>();
        this.vector2 = new ArrayList<>();
        this.vectorSize = 100;
        this.vectorIndex = 0;
        for (int i = 0; i < vectorSize; i++) {
            vector1.add(i + 1);
            vector2.add(i + 1);
        }
        System.out.print("vector1( ");
        for (int i = 0; i < vectorSize; i++) {
            System.out.print(vector1.get(i));
            System.out.print(", ");
        }
        System.out.println(")");
        System.out.print("vector2( ");
        for (int i = 0; i < vectorSize; i++) {
            System.out.print(vector2.get(i));
            System.out.print(", ");
        }
        System.out.println(")");
    }

    private int vectorsProduct() {
        return vector1.get(vectorIndex) * vector2.get(vectorIndex);
    }

    @Override
    public void run() {
        while (vectorIndex < vectorSize) {
            buffer.mutex.lock();
            try {
                while (buffer.buffer.size() > 2) {
                    try {
                        buffer.startProducer.await();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                buffer.buffer.add(vectorsProduct());
                buffer.startConsumer.signalAll();
                vectorIndex += 1;
            } finally {
                buffer.mutex.unlock();
            }
        }
    }
}
