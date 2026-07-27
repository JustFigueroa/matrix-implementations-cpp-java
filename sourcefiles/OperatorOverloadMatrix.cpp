#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
using namespace std;

class matrix {
private:
    float** data;
    int rows;
    int columns;
    void allocateMemory() {
        data = new float*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new float[columns];
        }
    }
    void deallocateMemory() {
        if (data != nullptr) {
            for (int row = 0; row < rows; ++row) {
                delete[] data[row];
            }

            delete[] data;
            data = nullptr;
        }
    }
    void initializeMatrix() {
        for (int row = 0; row < rows; ++row) {
            for (int column = 0; column < columns; ++column) {
                data[row][column] = 0.0;
            }
        }
    }
public:

    //constructor
    matrix(){
    rows = 0;
    columns = 0;
    data = nullptr;
    }
    //constructor overload
    matrix(int numOfRows, int numOfCols){
        rows = numOfRows;
        columns = numOfCols;
        data = nullptr;
        if (rows <= 0 || columns <= 0) {
            throw runtime_error("Matrix dimensions should be between 1 and 100");
        }
        allocateMemory();
        initializeMatrix();
    }
    matrix(const matrix& copy){
        rows = copy.rows;
        columns = copy.columns;
        data = nullptr;
        if (rows > 0 && columns > 0) {
            allocateMemory();
            copyFrom(copy);
        }
    }
    //copy values for = overload
    void copyFrom(const matrix& other) {
        for (int row = 0; row < rows; ++row) {
            for (int column = 0; column < columns; ++column) {
                data[row][column] = other.data[row][column];
            }
        }
    }
    //= overload
    matrix& operator=(matrix& copy) {
        if (this != &copy) {
            deallocateMemory();
            rows = copy.rows;
            columns = copy.columns;
            if (rows > 0 && columns > 0) {
                allocateMemory();
                copyFrom(copy);
            }
        }
        return *this;
    }

    //deconstructor
    ~matrix() {
        deallocateMemory();
    }
    //gettters setters
    int getRows() const {
        return rows;
    }
    int getColumns() const {
        return columns;
    }
    void input() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                cout << "Enter element [" << i
                          << "][" << j << "]: ";
                cin >> data[i][j];
            }
        }
    }
    void display(){
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                cout << data[i][j];
                cout << " ";
            }
            cout << endl;
        }
    }
    void setElement(int row, int column, double value) {
        if (row < 0 || row >= rows ||column < 0 || column >= columns) {
        throw runtime_error("Invalid Indecess");
        }
        data[row][column] = value;
    }

    // Overloaded addition operator.
    matrix operator+(matrix& matrixB){
        if (rows != matrixB.rows || columns != matrixB.columns) {
            throw runtime_error("Matrix Dimensions Invalid");
        }
        matrix matrixC(rows, columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                matrixC.data[i][j] = data[i][j] + matrixB.data[i][j];
            }
        }
        return matrixC;
    }
    matrix operator-(matrix& matrixB){
        if (rows != matrixB.rows ||
            columns != matrixB.columns) {
            throw runtime_error("Matrix Dimensions Invalid");
        }
        matrix matrixC(rows, columns);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                matrixC.data[i][j] = data[i][j] - matrixB.data[i][j];
            }
        }
        return matrixC;
    }
    matrix operator*(matrix& matrixB){
        if (columns != matrixB.rows){
            throw runtime_error("Matrix Dimensions Invalid");
        }
        matrix matrixC(rows, matrixB.columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < matrixB.columns; j++) {
                for (int k = 0; k < columns; k++) {
                    matrixC.data[i][j] += data[i][k] * matrixB.data[k][j];
                }
            }
        }
        return matrixC;
    }
};

void fileMatrixInitialization(matrix& matrixA, matrix& matrixB);
void manualMatrixInitialization(matrix& matrixA, matrix& matrixB);

int main(){ 
    // Declarations
    int operation = 0;
    int val = 0;
    bool newOperation = false;
    bool newArray = true;
    matrix matrixA;
    matrix matrixB;
    matrix matrixC;
    // End declarations
    try{
        while (newArray){
            cout << "-----------------" << endl;
            cout << "1. Manual Entry" << endl;
            cout << "2. File Entry" << endl;
            cout << "Selection: ";
            cin >> val;
            if (val == 1){
                manualMatrixInitialization(matrixA, matrixB);
                cout << "Matrix A: " << endl;
                matrixA.display();
                cout << endl;
                cout << "Matrix B: " << endl;
                matrixB.display(); 
                cout << endl; 
                newOperation = true;

            }
            else if (val == 2){
                fileMatrixInitialization(matrixA, matrixB);
                  cout << "Matrix A: " << endl;
                matrixA.display();
                cout << endl;
                cout << "Matrix B: " << endl;
                matrixB.display(); 
                cout << endl; 
                newOperation = true;

            }
            else{
                cout << "Invalid selection" << endl;
                newOperation = false;
            }

            while (newOperation){
                cout << "Choose an Operation: " << endl << "0.New Matrix" << endl << "1.Addition" << endl << "2.Subtraction" << endl << "3.Multiplication" << endl;
                cin >> operation;
                switch (operation){
                    case 0:{
                        newOperation = false;
                        break;
                    }
                    case 1:{
                        matrix temp = matrixA + matrixB;
                        matrixC = temp;
                        matrixC.display();
                        break;
                    }
                    case 2:{
                        matrix temp = matrixA - matrixB;
                        matrixC = temp;
                        matrixC.display();
                        break;
                    }
                    case 3:{
                        auto start = chrono::high_resolution_clock::now();
                        matrix temp = matrixA * matrixB;
                        auto end = chrono:: high_resolution_clock::now();
                        auto elapsedTime =chrono::duration<double, milli>(end - start).count();   
                         cout << "*******" << endl;
                         cout << elapsedTime;
                         cout << "ms" << endl;
                         cout << "*******" << endl;
                        matrixC = temp;
                        matrixC.display();
                        break;
                    }
                    default:
                        cout << "Invalid operation." << endl;
                        break;
                }

                if (operation != 0){
                    newOperation = true;
                }
            }
            newArray = false;
        }
    }
    catch (exception error)
    {
        return -1;
    }
    return 0;
}
//modified matrix initializaiton funcitons reused from other programs
//modified to use class setters
void fileMatrixInitialization(matrix& matrixA, matrix& matrixB){
    string pathToFile;
    string line;
    int rows;
    int cols;
    float val;

    cout <<"---------------------------" << endl;
    cout << "File selection parameters: " << endl;
    cout << "File should be a text file" << endl;
    cout << "Filepath should be formatted: /Path/To/File.extension" << endl;
    cout << "Data should be formatted: " << endl;
    cout << "numberOfRowsMatrixA numberOfColumnsMatrixA" << endl;
    cout << "row1value1 row1value2 ... row1valueN" << endl;
    cout << "row2value1 row2value2 ..." << endl;
    cout << "numberOfRowsMatrixB numberOfColumnsMatrixB" << endl;
    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;
    cout << "------------------- " << endl;
    cout << "Enter path to file: " << endl;
    cout << "------------------- " << endl;
    cin >> pathToFile;
    ifstream data(pathToFile);
    if (!data.is_open()){
        throw runtime_error ("File could not be opened");
        return;
    }
    cout << "------------------- " << endl;
    getline(data, line);
    stringstream dimensionsA(line);
    dimensionsA >> rows >> cols;
    matrix tempMatrixA(rows, cols);
    matrixA= tempMatrixA;
        for (int i = 0; i < rows; i++) {
        getline(data, line);
        stringstream rowStream(line);
        for (int j = 0; j < cols; j++) {
            rowStream >> val;
                    matrixA.setElement(i,j,val);

        }   
    }
    getline(data, line);
    stringstream dimensionsB(line);
    dimensionsB >> rows >> cols;
    matrix tempMatrixB(rows, cols);
    matrixB = tempMatrixB;
    for (int i = 0; i < rows; i++) {
        getline(data, line);
        stringstream rowStream(line);
            for (int j = 0; j < cols; j++) {
                rowStream >> val;
                    matrixB.setElement(i,j,val);
            }
        }
    }

void manualMatrixInitialization(matrix& matrixA, matrix& matrixB){
int rowsA;
int colsA;
int rowsB;
int colsB;
float val;
bool isValidSize = false;
while (!isValidSize){
cout << "------------------------------------------" << endl;
cout << "Enter the dimensions of your first matrix " << endl;
cout << "------------------------------------------" << endl;
cout << "matrix A rows: ";
cin >> rowsA;
cout << "matrix A columns: ";
cin >> colsA;
cout << "------------------------------------------" << endl;
cout << "Enter the dimensions of your second matrix " << endl;
cout << "------------------------------------------" << endl;
cout << "matrix B rows: ";
cin >> rowsB;
cout << "matrix B columns: ";
cin >> colsB;
cout << "------------------------------------------" << endl;
isValidSize = true;
}
matrix tempMatrixA(rowsA, colsA);
matrix tempMatrixB(rowsB, colsB);
matrixA = tempMatrixA;
matrixB = tempMatrixB;
cout << "Enter values for Matrix A: " << endl;
    for (int i = 0; i < rowsA; i++){
        for (int j = 0; j < colsA; j++){
        cout << "Matrix A [" << i << "][" << j << "]: ";
             cin >> val;
             matrixA.setElement(i,j,val);
            }
        }
cout << "Enter values for Matrix B: " << endl;
    for (int i = 0; i < rowsB; i++){
        for (int j = 0; j < colsB; j++){
        cout << "Matrix B [" << i << "][" << j << "]: ";
            cin >> val;
                matrixB.setElement(i,j,val);
            }
        }
}