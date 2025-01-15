package Thread;

import Model.Matrix;

import java.util.AbstractMap;

public class ColumnTask extends MatrixTask {
    public ColumnTask(int startRow, int startColumn, int elementCount, Matrix A, Matrix B, Matrix resultMatrix) {
        super(startRow, startColumn, elementCount, A, B, resultMatrix);
    }

    @Override
    protected void computeElements() {
        int i = startRow;
        int j = startColumn;
        int count = elementCount;

        while (count > 0 && i < resultMatrix.rows() && j < resultMatrix.columns()) {
            elements.add(new AbstractMap.SimpleEntry<>(i, j));
            i++;
            count--;
            if (i == resultMatrix.rows()) {
                i = 0;
                j++;
            }
        }
    }
}
