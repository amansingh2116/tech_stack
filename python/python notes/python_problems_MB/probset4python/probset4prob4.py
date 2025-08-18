'''Write an optimized C program that takes an integer n from
stdin and prints the first n elements (separated by comma) of
Fibonacci series on stdout. Recall that Fibonacci series
appears as:
0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, . . .
Measure and print the time taken by the program.
'''
import time
start = time.time()
k = int(input('enter number of elements : '))

def fibo(n):
    if n==1:
        return 0
    elif n==2:
        return 1
    else:
        return fibo(n-1)+fibo(n-2)
for i in range(k):
    print(fibo(i+1),end=',')
end = time.time()
print('time taken to complete the program : ',end-start)