package Thread;

import Model.Matrix;

import java.util.AbstractMap;

public class RowTask extends MatrixTask {
    public RowTask(int startRow, int startColumn, int elementCount, Matrix A, Matrix B, Matrix resultMatrix) {
        super(startRow, startColumn, elementCount, A, B, resultMatrix);
    }

    @Override
    protected void computeElements() {
        int i = startRow;
        int j = startColumn;
        int count = elementCount;

        while (count > 0 && i < resultMatrix.rows() && j < resultMatrix.columns()) {
            elements.add(new AbstractMap.SimpleEntry<>(i, j));
            j++;
            count--;
            if (j == resultMatrix.columns()) {
                j = 0;
                i++;
            }
        }
    }
}
