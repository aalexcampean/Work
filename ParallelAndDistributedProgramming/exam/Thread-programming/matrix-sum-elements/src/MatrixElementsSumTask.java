import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Lock;

public class MatrixElementsSumTask extends Thread {
    protected final List<List<Integer>> matrix;
    protected final int startRow, startColumn, elementCount;
    private final Lock mutex;
    static AtomicInteger sum = new AtomicInteger(0);

    public MatrixElementsSumTask(List<List<Integer>> matrix, int startRow, int startColumn, int elementCount, Lock mutex) {
        this.matrix = matrix;
        this.startRow = startRow;
        this.startColumn = startColumn;
        this.elementCount = elementCount;
        this.mutex = mutex;
    }

    @Override
    public void run() {
        int i = startRow;
        int j = startColumn;
        int count = elementCount;

        while (count > 0 && i < matrix.size() && j < matrix.get(0).size()) {
            mutex.lock();
            sum.addAndGet(matrix.get(i).get(j));
            mutex.unlock();

            j++;
            count--;
            if (j == matrix.get(0).size()) {
                j = 0;
                i++;
            }
        }
    }
}
