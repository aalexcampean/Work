package ubb.pdp.Model;

import ubb.pdp.Thread.ColumnTask;
import ubb.pdp.Thread.KTask;
import ubb.pdp.Thread.MatrixTask;
import ubb.pdp.Thread.RowTask;

public class Utils {
    public static MatrixTask initRowTask(int index, Matrix A, Matrix B, Matrix C, int nrThreads) {
        int sizeC = C.rows() * C.columns();
        int count = sizeC / nrThreads;

        int startRow = count * index / C.columns();
        int startCol = count * index % C.columns();

        if (index == nrThreads - 1)
            count += sizeC % nrThreads;

        return new RowTask(startRow, startCol, count, A, B, C);
    }

    public static MatrixTask initColumnTask(int index, Matrix A, Matrix B, Matrix C, int nrThreads) {
        int sizeC = C.rows() * C.columns();
        int count = sizeC / nrThreads;

        int startRow = count * index % C.columns();
        int startCol = count * index / C.columns();

        if (index == nrThreads - 1)
            count += sizeC % nrThreads;

        return new ColumnTask(startRow, startCol, count, A, B, C);
    }

    public static MatrixTask initKTask(int index, Matrix A, Matrix B, Matrix C, int nrThreads) {
        int sizeC = C.rows() * C.columns();
        int count = sizeC / nrThreads;

        if (index < sizeC % nrThreads)
            count++;

        int startRow = index / C.columns();
        int startCol = index % C.rows();

        return new KTask(startRow, startCol, count, nrThreads, A, B, C);
    }

    public static int computeMatrixElement(Matrix A, Matrix B, int row, int column) {
        if (row >= A.rows() || column >= B.columns()) {
            throw new IllegalArgumentException("Row/Column index out of range");
        }

        int result = 0;
        int i = 0;
        while (i < A.columns()) {
            result += A.get(row, i) * B.get(i, column);
            i++;
        }
        return result;
    }

    public enum GenerationApproach {
        ROWS,
        COLUMNS,
        KTH
    }

    public enum ThreadApproach {
        CLASSIC,
        THREAD_POOL
    }
}
