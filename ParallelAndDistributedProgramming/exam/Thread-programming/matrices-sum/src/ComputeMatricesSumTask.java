public class ComputeMatricesSumTask implements Runnable {
    protected final int[][] A, B, resultMatrix;
    protected final int startRow, startColumn, elementCount;

    public ComputeMatricesSumTask(int[][] A, int[][] B, int[][] resultMatrix, int startRow, int startColumn, int elementCount) {
        this.A = A;
        this.B = B;
        this.resultMatrix = resultMatrix;
        this.startRow = startRow;
        this.startColumn = startColumn;
        this.elementCount = elementCount;
    }

    @Override
    public void run() {
        int i = startRow;
        int j = startColumn;
        int count = elementCount;

        while (count > 0 && i < A.length && j < A[0].length) {
            resultMatrix[i][j] += A[i][j] + B[i][j];

            j++;
            count--;
            if (j == A[0].length) {
                j = 0;
                i++;
            }
        }
    }
}
