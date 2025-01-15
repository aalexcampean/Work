import java.util.concurrent.atomic.AtomicInteger;

public class ComputeMatricesSumTask implements Runnable{
    protected final int[] V1, V2;
    protected final int startingPos, elementCount;
    static AtomicInteger scalarProduct = new AtomicInteger(0);

    public ComputeMatricesSumTask(int[] V1, int[] V2, int startingPos, int elementCount) {
        this.V1 = V1;
        this.V2 = V2;
        this.startingPos = startingPos;
        this.elementCount = elementCount;
    }

    @Override
    public void run() {
        for (int i = startingPos; i < startingPos + elementCount; i++) {
            scalarProduct.addAndGet(V1[i] * V2[i]);
        }
    }
}
