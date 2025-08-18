'''Write a program to print all the twin primes (the primes that
have a difference of 2) smaller than or equal to a specified
integer given as user input.'''
n = int(input('Enter number :'))
def checkprime(a):
    l=[]
    for i in range(2,a//2 + 1):
        if a%i==0:
            l.append(i)
    if len(l)==0:
        return True
    else:
        return False

for i in range(2,n+1):
    if checkprime(i)==True and checkprime(i+2)==True:
        print('pair of twin prime found :', i,',',i+2)
