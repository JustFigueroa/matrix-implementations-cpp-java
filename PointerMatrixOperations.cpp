#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
using namespace std;
//Structures
struct matrix{
    float** data = nullptr;
    int rows = 0;
    int cols = 0;
};
//End Structures

//Function Protypes
matrix matrixAddition(matrix& matrixA, matrix& matrixB);
matrix matrixSubtraction(matrix& matrixA, matrix& matrixB);
matrix matrixMultiplication(matrix& matrixA, matrix& matrixB);
void fileMatrixInitialization(matrix& matrixA, matrix& matrixB);
void manualMatrixInitialization(matrix& matrixA, matrix& matrixB);
void displayOperands(matrix& matrixA, matrix& matrixB);
void displayResults(matrix& matrixC);
int  chooseOperation();
bool getEntryMethod();
bool tryNewArray();
bool tryNewOperation();
bool sizeCheck(matrix& matrixA, matrix& matrixB);
//Memory Allocation Functions
void allocateMemory(matrix& matrixM, int rows, int cols);
void deallocateMemory(matrix& matrixM);
//End Function Protoypes


int main(int argc, char* argv[]) {
//Declerations
int operation = 0;
bool isManualEntry = false;
bool newOperation = true;
bool newArray = true;
matrix matrixA;
matrix matrixB;
matrix matrixC;
//End Declerations
//While Loop to Permit New Arrays
while (newArray){
isManualEntry = getEntryMethod();
if (isManualEntry){
manualMatrixInitialization(matrixA, matrixB);
}
else if (!isManualEntry){
fileMatrixInitialization(matrixA, matrixB);
}
//While Loop to Permit New Operations
    while (newOperation){
    operation = chooseOperation();
    //Switch to Determine Operation to be Performed
        switch (operation){
            case 0: 
                break;
            case 1: 
                matrixC = matrixAddition(matrixA, matrixB);
                displayResults (matrixC);
                deallocateMemory(matrixC);
                break;
            case 2:
                matrixC = matrixSubtraction(matrixA, matrixB);
                displayResults (matrixC);
                deallocateMemory(matrixC);
                break;
            case 3:
                matrixC = matrixMultiplication(matrixA, matrixB);
                displayResults (matrixC);
                deallocateMemory(matrixC);
                break;
            default:
                return -1;
                }
        newOperation = tryNewOperation();
        }
    newArray = tryNewArray();
    newOperation = true;
    deallocateMemory(matrixA);
    deallocateMemory(matrixB);
    }
return 0;
}

//Operation Functions as Required by Assignment
//Reused From Stack Dynamic But Altered to Manually Allocate and Deallocate Memory / Return a Matrix
matrix matrixAddition(matrix& matrixA, matrix& matrixB){
    if (matrixA.cols != matrixB.cols || matrixA.rows != matrixB.rows){
        throw runtime_error("Incompatible array sizes");
    }
    else {
    matrix matrixC;
    matrixC.rows = matrixA.rows;
    matrixC.cols = matrixA.cols;
    allocateMemory(matrixC, matrixC.rows, matrixC.cols);    for (int i = 0; i < matrixA.rows; i++) {
        for (int j = 0; j < matrixA.cols; j++) {
            matrixC.data[i][j] = matrixA.data[i][j] + matrixB.data[i][j];
            }
        }
    return matrixC;
    }
throw runtime_error("Unexpected Error: -1");
}
matrix matrixSubtraction(matrix& matrixA, matrix& matrixB){
    if (matrixA.cols != matrixB.cols || matrixA.rows != matrixB.rows){
        throw runtime_error("Incompatible array sizes");
    }
    else{
    matrix matrixC;
    matrixC.rows = matrixA.rows;
    matrixC.cols = matrixA.cols;
    allocateMemory(matrixC, matrixC.rows, matrixC.cols);
    for (int i = 0; i < matrixA.rows; i++) {
        for (int j = 0; j < matrixA.cols; j++) {
            matrixC.data[i][j] = matrixA.data[i][j] - matrixB.data[i][j];
            }
        }
    return matrixC;
    }
throw runtime_error("Unexpected Error: -1");
}
matrix matrixMultiplication(matrix& matrixA, matrix& matrixB){
    if (matrixA.cols != matrixB.rows){
        cout << "Incompatible array sizes" << endl;
        throw runtime_error("Incompatible array sizes");
    }
    else if (matrixA.cols == matrixB.rows){
        matrix matrixC;
        matrixC.data = nullptr;
        matrixC.rows = matrixA.rows;
        matrixC.cols = matrixB.cols;
        allocateMemory(matrixC, matrixC.rows, matrixC.cols);
    for (int i = 0; i < matrixA.rows; i++) {
        for (int j = 0; j < matrixB.cols; j++) {
            matrixC.data[i][j] = 0;
            for (int k = 0; k < matrixA.cols; k++) {
                matrixC.data[i][j] += matrixA.data[i][k] * matrixB.data[k][j];
                }
            }
        }
    return matrixC;
    }
    throw runtime_error("Unexpected Error: -1");
}

//Helper Functions To Enhance readability of Main
void fileMatrixInitialization(matrix& matrixA, matrix& matrixB){
    string pathToFile;
    string line;
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
    dimensionsA >> matrixA.rows >> matrixA.cols;
    allocateMemory(matrixA, matrixA.rows, matrixA.cols);
    for (int i = 0; i < matrixA.rows; i++) {
        getline(data, line);
        stringstream rowStream(line);
        for (int j = 0; j < matrixA.cols; j++) {
            rowStream >> matrixA.data[i][j];
        }   
    }
    
    getline(data, line);
    stringstream dimensionsB(line);
    dimensionsB >> matrixB.rows >> matrixB.cols;
    allocateMemory(matrixB, matrixB.rows, matrixB.cols);
    for (int i = 0; i < matrixB.rows; i++) {
        getline(data, line);
        stringstream rowStream(line);

            for (int j = 0; j < matrixB.cols; j++) {
                rowStream >> matrixB.data[i][j];
        }
    }
    displayOperands(matrixA, matrixB);
}
void manualMatrixInitialization(matrix& matrixA, matrix& matrixB){
bool isValidSize = false;
while (!isValidSize){
cout << "------------------------------------------" << endl;
cout << "Enter the dimensions of your first matrix " << endl;
cout << "------------------------------------------" << endl;
cout << "matrix A rows: ";
cin >> matrixA.rows;
cout << "matrix A columns: ";
cin >> matrixA.cols;
cout << "------------------------------------------" << endl;
cout << "Enter the dimensions of your second matrix " << endl;
cout << "------------------------------------------" << endl;
cout << "matrix B rows: ";
cin >> matrixB.rows;
cout << "matrix B columns: ";
cin >> matrixB.cols;
cout << "------------------------------------------" << endl;
isValidSize = sizeCheck(matrixA, matrixB);
if (!isValidSize){
    cout << "------------------------------------------" << endl;
    cout << "Please choose dimensions between 1 and 100" << endl;
    cout << "------------------------------------------" << endl;
    }
}
allocateMemory(matrixA, matrixA.rows, matrixA.cols);
allocateMemory(matrixB, matrixB.rows, matrixB.cols);
cout << "Enter values for Matrix A: " << endl;
    for (int i = 0; i < matrixA.rows; i++){
        for (int j = 0; j < matrixA.cols; j++){
        cout << "Matrix A [" << i << "][" << j << "]: ";
        cin >> matrixA.data[i][j]; 
            }
        }

cout << "Enter values for Matrix B: " << endl;
    for (int i = 0; i < matrixB.rows; i++){
        for (int j = 0; j < matrixB.cols; j++){
        cout << "Matrix B [" << i << "][" << j << "]: ";
        cin >> matrixB.data[i][j]; 
            }
        }
displayOperands(matrixA, matrixB);
}
//Helpers Exclusive To Pointer Matrix Operations
//Used to Allocate and Deallocate
void allocateMemory(matrix& matrixM, int rows, int cols){
    matrixM.rows = rows; 
    matrixM.cols = cols;
    matrixM.data = new float*[rows];
    for (int i = 0; i < rows; i++){
        matrixM.data[i] = new float[cols];
    }
}
void deallocateMemory(matrix& matrixM){
    if (matrixM.data == nullptr) {
        return;
    }

    for (int i = 0; i < matrixM.rows; i++) {
        delete[] matrixM.data[i];
    }

    delete[] matrixM.data;

    matrixM.data = nullptr;
    matrixM.rows = 0;
    matrixM.cols = 0;
}
//These Helpers Are Reused From Stack Dynamic Program
void displayOperands(matrix& matrixA, matrix& matrixB){
        cout << "Matrix A:" << endl;
    for (int i = 0; i < matrixA.rows; i++) {
        for (int j = 0; j < matrixA.cols; j++) {
            cout << matrixA.data[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Matrix B:" << endl;
    for (int i = 0; i < matrixB.rows; i++) {
        for (int j = 0; j < matrixB.cols; j++) {
            cout << matrixB.data[i][j] << " ";
        }
        cout << endl;
    }
        cout << "------------------------------" << endl;
}
void displayResults(matrix& matrixC){
    if (matrixC.data == nullptr){
        return;
    }
    cout << "Matrix C: " << endl;
    for (int i = 0; i < matrixC.rows; i++){
        for (int j = 0; j < matrixC.cols; j++){
        cout << matrixC.data[i][j] << " ";  
        }
    cout << endl;
    }
}
bool getEntryMethod(){
bool isManual = false;
int selection = 0;
cout << "Select entry method: " << endl;
cout << "0.File entry" << endl;
cout << "1.Manual entry" << endl;
cin >> selection;
while (selection != 0 && selection != 1){
    cout << "Invalid Selection" << endl;
    cout << "-----------------" << endl;
    cout << "Select entry method: " << endl;
    cout << "0.File entry" << endl;
    cout << "1.Manual entry" << endl;
    cin >> selection;
}
    isManual = selection;
    return isManual;
}
bool tryNewArray(){
    int tryAgain;
        cout << "--------------" << endl;
        cout << "Try new array?" << endl;
        cout << "--------------" << endl;
        cout << "0. No" << endl;
        cout << "1.Yes" << endl;
        cin >> tryAgain;
        while (tryAgain != 0 && tryAgain != 1){
        cout << "Invalid Selection" << endl;
        cout << "-----------------" << endl;
        cout << "Try new array?" << endl;
        cout << "--------------" << endl;
        cout << "0. No" << endl;
        cout << "1.Yes" << endl;
        cin >> tryAgain;
        }
        return tryAgain;
}
bool tryNewOperation(){
    int tryAgain;
        cout << "--------------------------" << endl;
        cout << "Try a different operation?" << endl;
        cout << "--------------------------" << endl;
        cout << "0. No" << endl;
        cout << "1.Yes" << endl;
        cin >> tryAgain;
        while (tryAgain != 0 && tryAgain != 1){
        cout << "Invalid Selection" << endl;
        cout << "--------------------------" << endl;
        cout << "Try a different operation?" << endl;
        cout << "--------------------------" << endl;

        cout << "0. No" << endl;
        cout << "1.Yes" << endl;
        cin >> tryAgain;
        }
        return tryAgain;
}
bool sizeCheck(matrix& matrixA, matrix& matrixB){
    if (matrixA.rows > 100 || matrixA.rows < 1){
        return 0;
    }
    else if (matrixA.cols > 100 || matrixA.cols < 1){
        return 0;
    }
    else if (matrixB.rows > 100 || matrixB.rows < 1){
        return 0;
    }  
    else if (matrixB.cols > 100 || matrixB.cols < 1){
        return 0;
    }
    else
    return 1;
}
int  chooseOperation(){
    int operationChoice;
    cout << "Choose an operation to Perform" << endl;
    cout << "------------------------------" << endl;
    cout << "0. Quit" << endl;
    cout << "1. Addition" << endl;
    cout << "2. Subtraction" << endl;
    cout << "3. Multiplication" << endl;
    cin >> operationChoice;
    while (operationChoice < 0 || operationChoice >= 4){
        cout << "Invalid selection" << endl;
        cout << "Choose an operation to Perform" << endl;
        cout << "------------------------------" << endl;
        cout << "1. Addition" << endl;
        cout << "2. Subtraction" << endl;
        cout << "3. Multiplication" << endl;
        cin >> operationChoice;
    }
    return operationChoice;
}
