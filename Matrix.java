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
//Matrix multiplication class
public Matrix mult(Matrix matrixB){
    if (cols != matrixB.rows ){
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
//Mat
public void displayMatrices(){
    for (int i =0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            System.out.print(data[i][j] + " ");
        }
        System.out.println();
    }
}

private static Matrix manualMatrixGenerator(Scanner userVal, String matrixName){
    System.out.print (matrixName + " rows: ");
    int rows = userVal.nextInt();
    System.out.print (matrixName + " columns: ");
    int cols = userVal.nextInt();
    Matrix matrixM = new Matrix(rows, cols);
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            System.out.print(matrixName + "[" + i + "] [" + j + "]: ");
            matrixM.setValue(i, j, userVal.nextFloat());
        }
    }
    return matrixM;
}

private static Matrix[] fileMatrixInitialization(Scanner userFile) {
    System.out.print("Enter path to file: ");
    userFile.nextLine();
    String pathToFile = userFile.nextLine();
    try (Scanner fileInput = new Scanner(new File(pathToFile))) {
        Matrix matrixA = fileMatrixGenerator(fileInput);
        Matrix matrixB = fileMatrixGenerator(fileInput);
        return new Matrix[] {matrixA, matrixB};
    }
    catch (FileNotFoundException error) {
        throw new IllegalArgumentException("File could not be opened: " + pathToFile);
    }
}

private static Matrix fileMatrixGenerator(Scanner fileInput){
    int rows = fileInput.nextInt();
    int cols = fileInput.nextInt();
    Matrix matrixM = new Matrix(rows, cols);
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            matrixM.data[i][j] = fileInput.nextFloat();
        }
    }
    return matrixM;
}

private static int chooseOperation(Scanner userChoice){
    System.out.println("0. Select new matrices");
    System.out.println("1. Addition");
    System.out.println("2. Subtraction");
    System.out.println("3. Multiplication");
    System.out.print("Selection: ");
    return userChoice.nextInt();
}

public static void main(String[] args){
Scanner userInput = new Scanner(System.in);
boolean isRunning = true;
boolean matricesReady = false;
boolean selectNewMatrices = false;
 while (isRunning){
    Matrix matrixA = null;
    Matrix matrixB = null;
    Matrix matrixC = null;
    while (!matricesReady){
        System.out.println("---------------------");
        System.out.println("Choose an entry method");
        System.out.println("---------------------");
        System.out.println("0.Quit program");
        System.out.println("1.Manual Entry");
        System.out.println("2.Read from file");
        System.out.println("Selection: ");
        int selection = userInput.nextInt();
        try {switch (selection) {
            case 0:
                isRunning = false;
                break;
            case 1:
            matrixA = manualMatrixGenerator(userInput, "Matrix A");
            matrixB = manualMatrixGenerator(userInput, "Matrix B");
            matricesReady = true;
                break;
            case 2: 
            userInput.nextLine();
            Matrix[] matrices = fileMatrixInitialization(userInput);
            matrixA = matrices[0];
            matrixB = matrices[1];
            matricesReady = true;
                break;
            default:
            System.out.println("Invalid selection. Enter 1 or 2");
                break;
        }
        }
        catch (IllegalArgumentException error){
                }
                matricesReady = true;
            }
            System.out.println("Matrix A: ");
            matrixA.displayMatrices();
            System.out.println("Matrix B: ");
            matrixB.displayMatrices();
            while (isRunning && !selectNewMatrices){
                int operation = chooseOperation(userInput);
                try {switch (operation) {
                    case 0:
                        selectNewMatrices = true;
                        break;
                    case 1: 
                        matrixC = matrixA.add(matrixB);
                        System.out.println("Matrix C: ");
                        matrixC.displayMatrices();
                            break;
                    case 2:
                        matrixC = matrixA.sub(matrixB);
                        System.out.println("Matrix C: ");
                        matrixC.displayMatrices();
                            break;
                    case 3: 
                        matrixC = matrixA.mult(matrixB);
                        System.out.println("Matrix C: ");
                        matrixC.displayMatrices();
                            break;
                    default:
                        System.out.println("Invalid selection. Enter 0 thorugh 3");
                        break;
                    }
                }
                catch(IllegalArgumentException error){
                    
                }
            }
        } 
        userInput.close();
        System.out.println("Program Exiting");
    }
}


