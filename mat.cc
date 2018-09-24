#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <utility>
#include <string.h>
#include <vector>
#include <tuple>
#include <math.h>
#include <limits.h>
#define g 10000

//Compile g++ -std=c++11 -o mat mat.cc
//Execute /.mat.cc


using namespace std;

int min(int a, int b){
    if (a < b)
        return a;
    else
        return b;
}

//Sample function to print matrix
void printMat(vector<vector<int>> A){
    int rows_A = A.size();
    int cols_A = A[0].size();

    for (int i = 0; i < rows_A; i++){
        for (int j = 0; j < cols_A; j++){
            cout << A[i][j] << "\t";
        }
        cout << "\n";
    }
}

//Function to make *matrix multiplication* 
vector<vector<int>> matmult(vector<vector<int>> A, vector<vector<int>> B){
    int rows_A = A.size();
    int cols_A = A[0].size();
    int rows_B = B.size();
    int cols_B = B[0].size();
    int i,j,k;

    vector<vector<int>> C;

    if (cols_A != rows_B)
        cout << "Cannot multiply the two matrices. Incorrect dimensions." << endl;

    for (i = 0; i < rows_A; i++){
        vector<int> aux(cols_B, g);
        C.push_back(aux);
    }

    for (i = 0; i < rows_A; i++){
        for (j = 0; j < cols_B; j++){
            for (k = 0; k < cols_A; k++){
            	//C[i][j] = min(C[i][j], A[i][k] * B[k][j]); This is a normal multiplication
                C[i][j] = min(C[i][j], A[i][k] + B[k][j]); //THis is a *matrix multiplication
            }
        }
    }

    return C;
}

vector<vector<int>> mult(vector<vector<int>> G){
    int nodes = G.size();
    int cont = 0, i;
    vector<vector<int>> A = G;

    for (i = 0; i < nodes; i++){
        A = matmult(G, A);
        cont++;
    }
    cout<<"Multiplications with normal case: "<<cont<<endl;
    return A;
}

vector<vector<int>> Exponential(vector<vector<int>> G){
    bool flag = false;
    int nodes = G.size();
    int cont = 0;
    vector<vector<int>> A;
    vector<vector<int>> B;

    if (nodes % 2 != 0){
        flag = true;
        nodes = nodes - 1;
        B = G;
    }

    while (nodes != 1){
        A = matmult(G, G);
        G = A;
        nodes = nodes / 2;
        cont++;
    }

    if (flag == true){
        A = matmult(B, G);
        cont++;
    }
    cout<<"Multiplications with logarithm on base(nodes): "<<cont<<endl;
    return A;
}

int main(){
    vector<vector<int>> A;
    vector<vector<int>> X;

//isomorphic operation to matrix multiplication.
    A = {{0, 1, 3, g, g, g, g, g},
         {5, 0, 1, 8, g, g, g, g},
         {g, 9, 0, g, 8, g, g, g},
         {g, g, g, 0, g, g, g, g},
         {g, g, 7, g, 0, g, 2, 7},
         {g, 1, g, 4, g, 0, 7, g},
         {g, g, 7, g, g, g, 0, g},
         {g, g, g, g, g, 1, g, 0}};

    X = mult(A);
    printMat(X);
    cout<<"\n";
    X = Exponential(A);
    printMat(X);
    return 0;
}