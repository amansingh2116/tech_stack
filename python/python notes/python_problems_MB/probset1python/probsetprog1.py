'''An n-digit number is SPECIAL if the addition of its sum of the
digits and the product of its digits equals to the original
number. E.g., 19 is a SPECIAL 2-digit number. Write a
program to verify whether a given number is SPECIAL or not.
Extend this program to verify whether there exists any
SPECIAL number for a given value of number of digits n.'''
def spc(n):
    j=n
    s=0
    p=1
    while n:
        s+=n%10
        p*=n%10
        n=n//10
    if (p+s == j):
        return True

n=int(input("Enter number of digits to check :"))
k=0
for i in range(10**(n-1),10**(n)):
    if spc(i)==True :
        print(i,"is a special number")
        k+=1
print("there are total",k,"special numbers for chosen number of digits")
# for part (a) of the question, we can just call the function spc to check whether a number is special or not
