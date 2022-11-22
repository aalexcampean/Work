package ubb.pdp.Model;

public class Matrix {
    private final int rows;
    private final int cols;
    private int[][] matrix;

    public Matrix(int rows, int cols) {
        this.rows = rows;
        this.cols = cols;
        this.matrix = new int[rows][cols];

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = 1;
            }
        }
    }

    public int rows() {
        return rows;
    }

    public int columns() {
        return cols;
    }

    public int get(int row, int col) {
        return matrix[row][col];
    }

    public void set(int row, int col, int val) {
        matrix[row][col] = val;
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                builder.append(matrix[i][j]).append(" ");
            }
            builder.append("\n");
        }
        return builder.toString();
    }
}
