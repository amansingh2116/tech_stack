'''Write a program to multiply a pair of matrices given as user
input. Keep a check whether the input matrices are
multipliable or not.'''
def matrix(m,n):
    MAT = [[int(input()) for i in range(n)] for j in range(m)]
    return MAT
def genC(a,b):
    s=0
    for i in range(len(a)):
          s+=a[i]*b[i]
    return s              
m1=int(input("Enter no. of rows of matrix A :"))
n1=int(input("Enter no. of columns of matrix A :"))
l1 = matrix(m1,n1)
print('This is your entered matrix:')
for i in l1:
        print(i)
m2=int(input("Enter no. of rows of matrix B :"))
n2=int(input("Enter no. of columns of matrix B :"))
l2 = matrix(m2,n2)
print('This is your entered matrix:')
for i in l2:
        print(i)
l5=[]
for i in range(len(l2[0])):
    l4=[]
    for j in range(len(l2)):
        l4.append(l2[j][i])
    l5.append(l4)
if n1==m2 :
    print('here is your matrix A * B :')
    for i in range(m1):
        l3=[]
        for j in range(n2):
            l3.append(genC(l1[i],l5[j]))
        print(l3)
else :
    print("Matrix multiplication is not defined for the given matrices")