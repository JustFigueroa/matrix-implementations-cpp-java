
//Simple RNG will generate two matrices and output to file
//Formatted
//array.rows array.cols
//row1col1Data row1col2Data ...
//.
//.
//.
#include <iostream>
#include <chrono>
#include <fstream>
#include <cstdlib>
using namespace std;
void fileGen(int arraySize);

int main(int argc, char const *argv[]){
int sizeOfArrays;
cout << "This program will generate two random sqare arrays and export them to a file to be processes by matrix operation programs" << endl;
cout << "Enter the square dimension of your arrays: ";
cin >> sizeOfArrays;
fileGen(sizeOfArrays);

return 0;
}  
void fileGen(int arraySize){
    int seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);
    ofstream arrayFile("arrays.dat");
    string arrayDat;
    float randomValue;
    for (int i = 0; i < 2; i++){
        arrayDat = to_string(arraySize) + " " + to_string(arraySize) + "\n";
        arrayFile << arrayDat;
        for (int j = 0; j < arraySize; j++){
            for (int k = 0; k < arraySize; k++){
                arrayDat = to_string((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 100.0);
                arrayFile << arrayDat;
                arrayDat = " ";
                arrayFile << arrayDat;
                }
                arrayDat = "\n";
                arrayFile << arrayDat;
            }
        }
    }