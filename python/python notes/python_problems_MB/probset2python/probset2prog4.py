'''Write a program to apply the Pollard’s rho algorithm on a
semi-prime number, say n = pq, to find its non-trivial prime
factors p and q.'''
import random
import math
n=int(input("Enter a semi-prime number :"))
def ranc():
    m = random.randint(1,10)
    return m
c=ranc()
def initialfunc(k):
    return k*k + c
def pollard(n):
    x=random.randint(1,20)
    y=x
    x=initialfunc(x)
    y=initialfunc(y)
    y=initialfunc(y)
    d=math.gcd(abs(y-x),n)
    if d==1:
        return pollard(n)
    elif d==n:
        c = ranc()
        return pollard(n)
    else:
        return d
result = pollard(n)
print('factor found', result)
