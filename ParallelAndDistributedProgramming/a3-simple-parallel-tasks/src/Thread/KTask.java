package Thread;

import Model.Matrix;

import java.util.AbstractMap;

public class KTask extends MatrixTask {
    public KTask(int startRow, int startColumn, int elementCount, int K, Matrix A, Matrix B, Matrix resultMatrix) {
        super(startRow, startColumn, elementCount, K, A, B, resultMatrix);
    }

    @Override
    protected void computeElements() {
        int i = startRow;
        int j = startColumn;
        int count = elementCount;

        while (count > 0 && i < resultMatrix.rows() && j < resultMatrix.columns()) {
            elements.add(new AbstractMap.SimpleEntry<>(i, j));
            count--;
            i += (j + K) / resultMatrix.columns();
            j = (j + K) % resultMatrix.columns();
        }
    }
}
