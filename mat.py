import sys

g = sys.maxsize #Max integer in python

def matrixmult (A, B):
    rows_A = len(A) 	#Len for Mat A
    cols_A = len(A[0])	#Len for Mat A[0]
    rows_B = len(B)		#Len for Mat B
    cols_B = len(B[0])	#Len for Mat B[0]

    if cols_A != rows_B:
      print("Cannot multiply the two matrices. Incorrect dimensions.")
      return

    C = [[g for row in range(cols_B)] for col in range(rows_A)]
    
    for i in range(rows_A):
        for j in range(cols_B):
            for k in range(cols_A):
                C[i][j] = min(C[i][j], A[i][k] + B[k][j]) #This is not a normal multiplication
    return C

def matmult(G):
    nodes = len(G)
    A = G
    for i in range(nodes):
        A = matrixmult(G,A)
    return A

#isomorphic operation to matrix multiplication.
A = [[0, 1, 3, g, g, g, g, g],
     [5, 0, 1, 8, g, g, g, g],
     [g, 9, 0, g, 8, g, g, g],
     [g, g, g, 0, g, g, g, g],
     [g, g, 7, g, 0, g, 2, 7],
     [g, 1, g, 4, g, 0, 7, g],
     [g, g, 7, g, g, g, 0, g],
     [g, g, g, g, g, 1, g, 0]]

X = matmult(A)
print(X)
