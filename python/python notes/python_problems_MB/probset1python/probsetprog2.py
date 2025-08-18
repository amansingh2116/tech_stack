'''Consider an n-digit number. Square it and add the right n
digits to the left n or n − 1 digits. If the resultant sum is same
as the original number, then it is called a Kaprekar number.
E.g., 45 is a Kaprekar number. Write a program to verify
whether a given number is Kaprekar or not.'''
n=int(input("Enter number to check :"))
r=str(n)
j=len(r)
k=str(n*n)
l=len(k)
m=k[::-1]
h=m[0:j]
g=m[j:]
print(n,r,j,k,l,m,h,g,sep='\n')
if (int(h[::-1]) + int(g[::-1]))==n:
    print(n,"is a Kaprekar number")