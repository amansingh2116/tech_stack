'''Write a program to multiply a pair of matrices given as user
input employing the standard approach. Keep a check
whether the input matrices are multipliable or not. Further try
implementing the Strassen’s matrix multiplication algorithm.
'''
# approach one (divide and conquer)
def matrix(m,n):
    MAT = [[int(input()) for i in range(n)] for j in range(m)]
    return MAT

def matrix_multiply(matrix_A, matrix_B):
    if len(matrix_A[0]) != len(matrix_B):
        raise ValueError("Matrix dimensions are not compatible for multiplication")
    
    result = []
    for i in range(len(matrix_A)):
        row = []
        for j in range(len(matrix_B[0])):
            dot_product = 0
            for k in range(len(matrix_B)):
                dot_product += matrix_A[i][k] * matrix_B[k][j]
            row.append(dot_product)
        result.append(row)
    return result

def pow2(n):
     while n:
          if n%2!=0 :
               return False
          else:
               return True

def matrix_combine(c1, c2, c3, c4):
    n = len(c1)
    mid = n // 2
    result = [[0] * n for _ in range(n)]
    for i in range(mid):
        result[i] = c1[i] + c2[i]
        result[i + mid] = c3[i] + c4[i]
    return result
def matrix_add(matrix_A, matrix_B):
    return [[matrix_A[i][j] + matrix_B[i][j] for j in range(len(matrix_A[0]))] for i in range(len(matrix_A))]
def subM(M):
    a1,a2,a3,a4 = [],[],[],[]
    n = len(M[0])
    mid = n//2
    for i in range(mid):
        a1.append(M[i][0:mid])
        a2.append(M[i][mid:n])
        a3.append(M[i+mid][0:mid])
        a4.append(M[i+mid][mid:n])
    return [a1,a2,a3,a4]
def strauss(M,N,n):
    if n<=2 :
        if n <= 2:
            result = [[0] * n for _ in range(n)]
            for i in range(n):
                for j in range(n):
                    for k in range(n):
                        result[i][j] += matrix_A[i][k] * matrix_B[k][j]
            return result
    else:
        a = subM(M)
        b = subM(N)
        c1 = matrix_add(strauss(a[0], b[0], n // 2), strauss(a[1], b[2], n // 2))
        c2 = matrix_add(strauss(a[0], b[1], n // 2), strauss(a[1], b[3], n // 2))
        c3 = matrix_add(strauss(a[2], b[0], n // 2), strauss(a[3], b[2], n // 2))
        c4 = matrix_add(strauss(a[2], b[1], n // 2), strauss(a[3], b[3], n // 2))
        return matrix_combine(c1, c2, c3, c4)
t = int(input('Enter n :'))
print('Enter elements for matrix A :')
matrix_A = matrix(t,t)
print('Enter elements for matrix B :')
matrix_B = matrix(t,t)
print('Here is your matrix A :')
for i in matrix_A:
    print(i)
print('Here is your matrix B :')
for i in matrix_B:
    print(i)
print('Here is your A * B : ')
result = strauss(matrix_A,matrix_B,t)
for i in result:
    print(i)

#matrix_A = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]
#matrix_B = [[9, 8, 7, 6], [5, 4, 3, 2], [1, 1, 2, 3], [4, 5, 6, 7]]

#approach 2 (strassen)
def matrix_add(matrix_A, matrix_B):
    n = len(matrix_A)
    result = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            result[i][j] = matrix_A[i][j] + matrix_B[i][j]
    return result

def matrix_subtract(matrix_A, matrix_B):
    n = len(matrix_A)
    result = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            result[i][j] = matrix_A[i][j] - matrix_B[i][j]
    return result

def strassen_matrix_multiply(matrix_A, matrix_B):
    n = len(matrix_A)

    if n <= 2:
        result = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(n):
                for k in range(n):
                    result[i][j] += matrix_A[i][k] * matrix_B[k][j]
        return result

    mid = n // 2

    A11 = [row[:mid] for row in matrix_A[:mid]]
    A12 = [row[mid:] for row in matrix_A[:mid]]
    A21 = [row[:mid] for row in matrix_A[mid:]]
    A22 = [row[mid:] for row in matrix_A[mid:]]

    B11 = [row[:mid] for row in matrix_B[:mid]]
    B12 = [row[mid:] for row in matrix_B[:mid]]
    B21 = [row[:mid] for row in matrix_B[mid:]]
    B22 = [row[mid:] for row in matrix_B[mid:]]

    P1 = strassen_matrix_multiply(matrix_add(A11, A22), matrix_add(B11, B22))
    P2 = strassen_matrix_multiply(matrix_add(A21, A22), B11)
    P3 = strassen_matrix_multiply(A11, matrix_subtract(B12, B22))
    P4 = strassen_matrix_multiply(A22, matrix_subtract(B21, B11))
    P5 = strassen_matrix_multiply(matrix_add(A11, A12), B22)
    P6 = strassen_matrix_multiply(matrix_subtract(A21, A11), matrix_add(B11, B12))
    P7 = strassen_matrix_multiply(matrix_subtract(A12, A22), matrix_add(B21, B22))

    C11 = matrix_add(matrix_subtract(matrix_add(P1, P4), P5), P7)
    C12 = matrix_add(P3, P5)
    C21 = matrix_add(P2, P4)
    C22 = matrix_add(matrix_add(matrix_subtract(P1, P2), P3), P6)

    result_matrix = [[0] * n for _ in range(n)]
    for i in range(mid):
        result_matrix[i] = C11[i] + C12[i]
        result_matrix[i + mid] = C21[i] + C22[i]

    return result_matrix

def matrix(m,n):
    MAT = [[int(input()) for i in range(n)] for j in range(m)]
    return MAT
t = int(input('Enter n :'))
print('Enter elements for matrix A :')
matrix_A = matrix(t,t)
print('Enter elements for matrix B :')
matrix_B = matrix(t,t)
# Perform matrix multiplication using Strassen algorithm
result_matrix = strassen_matrix_multiply(matrix_A, matrix_B)

print("Matrix A:")
for row in matrix_A:
    print(row)
print("Matrix B:")
for row in matrix_B:
    print(row)
print("Result of matrix multiplication (A*B) using Strassen algorithm:")
for row in result_matrix:
    print(row)
