#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <utility>
#include <string>
#include <vector>
#include <tuple>
#include <math.h>
#include <limits>
//Compile g++ -o mat mat.cc
//Execute ./mat
using namespace std;
//const int INF = numeric_limits<int>::max();
const int INF = 1000000;

//Sample function to return min(a,b)
int min(int a, int b){
    if (a < b)
        return a;
    else
        return b;
}

//Sample function to print matrix
void printMat(vector<vector<int>>& A){
    int rows_A = A.size();
    int cols_A = A[0].size();
    int i,j;

    for (i = 0; i < rows_A; i++){
        for (j = 0; j < cols_A; j++){
            if(A[i][j] == INF){
                cout << "INF" << "\t";
                }
            else{
                cout << A[i][j] << "\t";
                }
        }
        cout << "\n";
    }
}

//Function to make *matrix multiplication*
vector<vector<int>> matmult(vector<vector<int>>& A, vector<vector<int>>& B){
    int rows_A = A.size();
    int cols_A = A[0].size();
    int rows_B = B.size();
    int cols_B = B[0].size();
    int i,j,k;

    vector<vector<int>> C; //Matriz to return A*B

    if (cols_A != rows_B)
        cout << "Cannot multiply the two matrices. Incorrect dimensions." << endl;

    for (i = 0; i < rows_A; i++){
        vector<int> aux(cols_B, INF);
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

//Normal case 2^n mat multiplication
vector<vector<int>> mult(vector<vector<int>>& G){
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

//Logarithm on base (n) multiplications  l2(n)
vector<vector<int>> Exponential(vector<vector<int>>& G){
    bool flag = false;
    int nodes = G.size();
    int cont = 0, i, j;
    vector<vector<int>> A;
    vector<vector<int>> B;

    //Identity Matriz
    if (nodes == 0){
        for(i = 0; i < G.size(); i++){
            for(j = 0; j < G[0].size(); j++){
                if (i = j){
                    G[i][j] = 1;
                }
                else{
                    G[i][j] = 0;
                }
            }
        }
    }

    //N = 1 Return G
    if (nodes == 1){
        return G;
    }

    //odd N 
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
    vector<vector<int>> Mat;

//isomorphic operation to matrix multiplication.
    A = {{0, 1, 3, INF, INF, INF, INF, INF},
         {5, 0, 1, 8, INF, INF, INF, INF},
         {INF, 9, 0, INF, 8, INF, INF, INF},
         {INF, INF, INF, 0, INF, INF, INF, INF},
         {INF, INF, 7, INF, 0, INF, 2, 7},
         {INF, 1, INF, 4, INF, 0, 7, INF},
         {INF, INF, 7, INF, INF, INF, 0, INF},
         {INF, INF, INF, INF, INF, 1, INF, 0}};

    Mat = mult(A);
    printMat(Mat);

    cout<<"\n";

    Mat = Exponential(A);
    printMat(Mat);
    return 0;
}
