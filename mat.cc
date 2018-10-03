#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <utility>
#include <vector>
#include <math.h>
#include <limits>
#include <cassert>
#include <typeinfo>
#include <ctime>

using namespace std;
const int INF = numeric_limits<int>::max();

//Compile g++ -o mat mat.cc
//Execute ./mat
//Sample function to print matrix
void printMat(vector<vector<int> >& A){

    for (int i = 0; i < A.size(); i++){
        for (int j = 0; j < A[0].size(); j++){
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

//Graph diameter
int Diameter(vector<vector<int> >& A){
    int max = 0;

    for (int i = 0; i < A.size(); i++){
        for (int j = 0; j < A[0].size(); j++){
            if (A[i][j] != INF & A[i][j] > max){
                max = A[i][j];
            }
        }
    }
    return max;
}

//Graph reader
void readGraph(vector<vector<int> >& A){
    ifstream data("data/test.txt");
    string line;
    int s1, s2, w;

    if (data.is_open()){
        data >> line >> s1 >> s2 >> w;
        for (int i = 0; i < s2; i++){
            vector<int>aux(s2, INF);
            A.push_back(aux);
        }

        while (data.good()){
            data >> line >> s1 >> s2 >> w;
            A[s1-1][s2-1] = w;
        }
        data.close();
    }
    else{
        cout << "File not exists";
    }
    for (int i = 0; i < A.size(); i++){
        A[i][i] = 0;
    } 
}

//Function to make *matrix multiplication*
void matmult(const vector<vector<int> >& A, const vector<vector<int> >& B, vector<vector<int> >& G){

    if (A[0].size() != B.size())
        cout << "Cannot multiply the two matrices. Incorrect dimensions." << endl;

    for (int i = 0; i < A.size(); i++){
        for (int j = 0; j < B[0].size(); j++){
            for (int k = 0; k < A[0].size(); k++){
                if (A[i][k] + B[k][j] >= 0){
                    //C[i][j] = min(C[i][j], A[i][k] * B[k][j]); This is a normal multiplication
                    G[i][j] = min(G[i][j], A[i][k] + B[k][j]); //THis is a *matrix multiplication
                }
            }
        }
    }
}

//Normal case 2^n mat multiplication
void mult(const vector<vector<int> >& A, vector<vector<int> >& G){
    int cont = 0;
    
    for(int i = 0; i < A.size(); i++){
        for(int j = 0; j < A[0].size(); j++){
            G[i][j] = A[i][j];
        }
    }
    for (int i = 0; i < A.size(); i++){
        matmult(A, G, G);
        cont++;
    }
    cout<<"\nMultiplications with normal case: "<<cont<<endl;
}

//Logarithm on base (n) multiplications  l2(n)
void Exponential(const vector<vector<int> >& A, vector<vector<int> >& G){
    int nodes = A.size();
    int cont = 0;

    for(int i = 0; i < A.size(); i++){
        for(int j = 0; j < A[0].size(); j++){
            G[i][j] = A[i][j];
        }
    }

    if (nodes == 0 || nodes == 1){
        cout<<"Incorrect operation. Matriz must to have a data"<<endl;
    }

    if (nodes % 2 == 0){
        for (int i = 0; i < (nodes/2); i++){
            matmult(A, G, G);
            cont++;
        }
    }

    if (nodes % 2 != 0){
        nodes = nodes - 1;
        for (int j = 0; j < (nodes/2); j++){
            matmult(A, G, G);
            cont++;
        }
        matmult(A, G, G);
    }

    cout<<"\nMultiplications with logarithm function: "<<cont<<endl;
}

int main(){
    
    vector<vector<int> > A;
    readGraph(A);
    printMat(A);
    
    /*/isomorphic operation to matrix multiplication.
    A = {{0, 1, 3, INF, INF, INF, INF, INF},
         {5, 0, 1, 8, INF, INF, INF, INF},
         {INF, 9, 0, INF, 8, INF, INF, INF},
         {INF, INF, INF, 0, INF, INF, INF, INF},
         {INF, INF, 7, INF, 0, INF, 2, 7},
         {INF, 1, INF, 4, INF, 0, 7, INF},
         {INF, INF, 7, INF, INF, INF, 0, INF},
         {INF, INF, INF, INF, INF, 1, INF, 0}};*/

    vector<vector<int> > C(A.size(), vector<int>(A.size(), INF));

    unsigned t0, t1;

    /*t0 = clock();
    mult(A, C);
    t1 = clock();
    double time1 = (double(t1-t0)/CLOCKS_PER_SEC);
    printMat(C);
    cout << "Elapsed Time: " << time1 << endl;
    cout<<"\n";*/

    t0 = clock();
    Exponential(A, C);
    t1 = clock();
    double time2 = (double(t1-t0)/CLOCKS_PER_SEC);
    printMat(C);
    cout << "Elapsed Time: " << time2 << endl;
    
    int max = Diameter(C);
    cout << "\nMatriz Diameter " << max << endl;

    return 0;
}