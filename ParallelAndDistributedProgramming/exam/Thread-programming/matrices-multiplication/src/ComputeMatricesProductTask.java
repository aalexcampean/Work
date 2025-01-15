public class ComputeMatricesProductTask implements Runnable{
    protected final int[][] A, B, resultMatrix;
    protected final int startRow, startColumn, elementCount;

    public ComputeMatricesProductTask(int[][] A, int[][] B, int[][] resultMatrix, int startRow, int startColumn, int elementCount) {
        this.A = A;
        this.B = B;
        this.resultMatrix = resultMatrix;
        this.startRow = startRow;
        this.startColumn = startColumn;
        this.elementCount = elementCount;
    }

    @Override
    public void run() {
        int row = startRow;
        int column = startColumn;
        int count = elementCount;

        while (count > 0 && row < resultMatrix.length && column < resultMatrix[0].length) {

            int result = 0;
            int i = 0;
            while (i < A[0].length) {
                result += A[row][i] * B[i][column];
                i++;
            }

            resultMatrix[row][column] += result;

            column++;
            count--;
            if (column == resultMatrix[0].length) {
                column = 0;
                row++;
            }
        }
    }
}
