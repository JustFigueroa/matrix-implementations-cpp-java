import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

public class Matrix{
private float [][] data;
private int rows;
private int cols;

public Matrix(int rows, int cols){
    if (rows < 1 || cols < 1){
        throw new IllegalArgumentException("Matrix dimensions should be between 1 and 100");
    }
    else if (rows > 100 || cols > 100){
        throw new IllegalArgumentException("Matrix dimensions should be between 1 and 100");
    };

this.rows = rows;
this.cols = cols;
this.data = new float[rows][cols];
}

public void setValue(int row, int col, float val){
    data[row][col] = val;
}

public Matrix add(Matrix matrixB){
    if (rows != matrixB.rows || cols != matrixB.cols){
        throw new IllegalArgumentException("Incompatable array sizes");
    }
    Matrix matrixC = new Matrix(rows, cols);
    for (int i =0; i < matrixB.rows; i++){
        for (int j = 0; j < matrixB.cols; j++){
            matrixC.data[i][j] = data[i][j] + matrixB.data[i][j];
        }
    }
    return matrixC;
}
public Matrix sub(Matrix matrixB){
    if (rows != matrixB.rows || cols != matrixB.cols){
        throw new IllegalArgumentException("Incompatable array sizes");
    }
    Matrix matrixC = new Matrix(rows, cols);
    for (int i =0; i < matrixB.rows; i++){
        for (int j = 0; j < matrixB.cols; j++){
            matrixC.data[i][j] = data[i][j] - matrixB.data[i][j];
        }
    }
    return matrixC;
}
public Matrix mult(Matrix matrixB){
    if (rows != matrixB.rows || cols != matrixB.cols){
        throw new IllegalArgumentException("Incompatable array sizes");
    }
    Matrix matrixC = new Matrix(rows, cols);
        for (int i = 0; i < rows; i++) {
        for (int j = 0; j < matrixB.cols; j++) {
            matrixC.data[i][j] = 0;
            for (int k = 0; k <cols; k++) {
                matrixC.data[i][j] += data[i][k] * matrixB.data[k][j];
                }
            }
        }
    return matrixC;
}

public void displayOperand(){
    for (int i =0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            System.out.print(data[i][j] + " ");
        }
        System.out.println();
    }
}

private static Matrix manualMatrixGenerator(Scanner userVal, string matrixName){


};


}

