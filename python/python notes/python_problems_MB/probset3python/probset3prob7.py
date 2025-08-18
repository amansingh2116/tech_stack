'''Write a recursive function to compute the binomial coefficient
using the following definition :
C(n,r) = C(n-1,r) + C(n-1,r-1)'''
def binocoeff(n, r):
    if n < 0 or r < 0:
        return 0
    elif r == 0 or r == n:
        return 1
    else:
        return binocoeff(n - 1, r) + binocoeff(n - 1, r - 1)

n = int(input('Enter the value of n: '))
r = int(input('Enter the value of r: '))
print(f'The binomial coefficient C({n}, {r}) is', binocoeff(n, r))