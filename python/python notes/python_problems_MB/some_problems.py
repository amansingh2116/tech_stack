# print all non decreasing sequences of natural numbers whose sum equals a given natural number

X = int(input("Enter a number: "))
def listh(k):
    if k <= 0:
        return [[]]
    if k == 1:
        return [[1]]
    l = []
    for i in range(1, k + 1):
        h = listh(k - i)
        for s in h:
            if len(s) == 0 or i >= s[-1]:
                print(i,s)
                l.append([i] + s)
    return l
l = listh(X)
l = [sorted(q) for q in l]
m = []
for f in l:
    if f not in m:
        m.append(f)
print(m)


# Consider the number $45656$. <br>
# It can be seen that each pair of consecutive digits of $45656$ has a difference of one.<br>
# A number for which every pair of consecutive digits has a difference of one is called a step number.<br>
# A pandigital number  contains every decimal digit from $0$ to $9$ at least once.<br>
# How many pandigital step numbers less than $10^{40}$ are there?

def step(n):
    f=list(n)
    for i in range(len(f)-1):
        if abs(int(f[i])-int(f[i+1]))!=1:
            return False
    return True
def pandigital(k):
    if sorted(list(set(k))) == ['0','1','2','3','4','5','6','7','8','9']:
        return True
    return False
c=0
for i in range(10**9,10**40):
    g = str(i)
    if step(g) and pandigital(g):
        print(i)
        c+=1
print(c)

# print max (sum of (digital sum of (each factor (of each factorisation of a (given number)))))

def digitalsum(f):
    if f < 10:
        return f
    else:
        total = 0
        while f > 0:
            total += f % 10
            f //= 10
        return digitalsum(total)

def factors(k):
    factors_list = []
    for i in range(2, k + 1):
        if k % i == 0:
            factors_list.append(i)
    return factors_list

def tiger(h):
    factors_list = factors(h)
    max_digital_sum = -1
    
    for factor in factors_list:
        ds = digitalsum(factor)
        if ds > max_digital_sum:
            max_digital_sum = ds
    
    return max_digital_sum

x = int(input('Enter number: '))
print(tiger(x))


# Write a program to take a filename as user input and insert the character comma (i.e., ‘,’)
# after every i th character within it such that i = 1, 2, . . . as applicable

#method1
from math import sqrt
file = input("please enter the file name:")
file1 = open(file,'r+')
s = file1.read()
n = len(s)
for i in range(n):
    file1.seek(i,1)
    file1.write(',')
file1.close()

#method2
from math import sqrt

file = input("please enter the file name:")
# opening file
file1 = open(file,'r+')
#reading file
s = file1.read()
n = len(s)
# inserting ',' after each i for i=1,2,3..
for i in range(1,int((1+sqrt(1+8*n))/2)):
    k = int(i*(i+1)/2)
    s = s[:k+i-1]+','+s[k+i-1:]
# rewrite it to file
file1.seek(0)
file1.write(s)


# Let us define the folding of a k-digit natural number, say N =Pk−1i=0 ni ∗ 10i(nk−1 = 0 ̸ ), as
# adding each pair of its digits at a time starting from the two ends going up to the middle.
# Hence, the folding of N will result into the following number:⌊Xk/2⌋i=0(n⌊(k−1)/2⌋−i + n⌊k/2⌋+i) ∗ 10i
# A number is foldable if none of the digits formed through the aforementioned folding
# process, i.e. (n⌊(k−1)/2⌋−i + n⌊k/2⌋+i) for all applicable i surpasses 9, after the folding is
# attempted. Write a program to take an input number and print all the foldable numbers,
# including the given one, that can be obtained after repeatedly folding it

N=input("Enter your number")
def foldable(n):
    if n[0]==0 or int(n)<=0:
        return "invalid number"
    l=list(n)                                                      
    l1=[]
    l2=[]
    for i in range(((len(l)-1)//2)+1):
        l1.append(int(l[i])+int(l[len(l)-i-1]))
    for i in l1:
        if i>=10:
            return  "not foldable number"
    for j in range(len(l1)):
        l2.append(str(l1[j]))
        
    b="".join(l2)
    print(int(b))
    if len(n)==1 & int(n)<=4:
        return n*2
    if len(n)==1 & int(n)>=5:
        return n
    return foldable(b)
foldable(N)