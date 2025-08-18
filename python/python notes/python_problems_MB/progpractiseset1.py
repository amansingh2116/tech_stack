'''Write a program to count the number of unique characters (including special characters
too) in a string.'''
a = input('Enter string: ')
print('no of unique characters in the given string : ', len(set(a)))

'''Given a list of strings, write a program to return the palindromes within it.'''
l1 = ['abracadabra', 'matata', 'jahaj', 'pooioop']
l2=[]
for i in l1:
    if i==i[::-1]:
        l2.append(i)
print('here are your palindromes :',l2)

'''Given a list of strings, write a program to count the number of strings where the
string length is no less than 3 and the first and last characters are the same.'''
l = ['cdidbi', 'wbhbdbw','ceb', 'f', 'dy', 'jgvdj', 'hojanabhai']
c = 0
for i in l:
    if len(i)>=3 and i[0]==i[len(i)-1]:
        c+=1
print('no of such strings :',c)

'''Write a program to crop out the alphanumeric characters from a string.'''
s =  "Hello! This is 123 an example text, #2023."
s1 = ''
for i in s :
    if i.isalnum() :
        s1+=i
print('here is cut out alphanumeric characters :', s1)

'''Write a program to check whether a given number is a power of 4 or not.Accordingly,
print POWER OF 4 or NOT POWER OF 4.'''
n = int(input('Enter number : '))
def pow4(n):
    if n <= 0:
        return False

    while n > 1:
        if n % 4 != 0:
            return False
        n //= 4

    return True
if pow4(n):
    print('POWER OF 4')
else:
    print('NOT POWER OF 4')

'''Write a program to take three numbers as input and verify whether all of them are
same or not. Accordingly, print SAME or DIFFERENT. '''
n = (input('Enter 3 numbers with spaces:')).split()
if n[0]==n[1]==n[2]:
    print('SAME')
else:
    print('DIFFERENT')

'''Let us define a number as CONJOINED TWIN if it can be represented as the sum
of two distinct numbers that are reverse of each other (e.g., 12 and 21 are reverse of each
other). Note that, for being reverse to each other they must have same number of significant
digits. Hence, 100 is not reverse of 1 (considering 1 as 001). Write a program to show all the
CONJOINED TWIN numbers that are no more than n in increasing order.'''
n1 = int(input('enter number :'))
print('here is a list of increasing CONJOINED TWIN  numbers till', n1)
for i in range(11,n1+1): # since single digit numbers reverse is same and 10 reverse 01 which has 0 as insignifact
    j = str(i)
    k = j[::-1]
    if len(int(j))==len(int(k)) :
        print(int(j)+int(k))

'''Recall that a semi-prime number can be represented as n = p ∗ q, the multiplication
of two prime factors. Write a program to verify whether a number is semi-prime or not.
Accordingly, print SEMI-PRIME or NOT SEMI-PRIME.'''
n2 = int(input('enter a number :'))
list = []
for i in range(2,(n//2)+1):
    if n2%i==0:
        list.append(i)
if len(list)==2 and list[1]%list[0]!=0:
    print('SEMI-PRIME')
else:
    print('NOT SEMI-PRIME')

'''Write a program to print the following pattern given the line number as user input.
$       $
  $   $
   $ $
    $
   $ $
  $   $
$       $'''
line_number = int(input("enter number of lines : "))
for mi in range(line_number):
    for mj in range(line_number):
        if mi==mj:
            print('$',end="")
        elif mi == line_number-mj-1:
            print('$', end = '')
        else:
            print(" ",end='')
    print('\n')

'''Let us define a string, comprising English alphabets, as NICE if each vowel within
it are equidistant from its successor and predecessor vowel, if applicable. E.g., “rhythm”,
“cool”, “malayalam” are NICE strings. Write a program to verify whether a given string is
NICE or not. You are required to take the string as a direct input without asking for its
length.'''
string = input('enter string:')
vow = []
for i in range(len(string)):
    if string[i] in ['a','e','i','o','u','A','E','I','O','O','U'] :
        vow.append(i)
if len(vow)>2:
    d = vow[1]-vow[0]
    for i in range(len(vow)) :
        if vow[i+1]-vow[i]!=d:
            print('NOT NICE')
            break
    print('NICE')

'''Two elements A[i] and A[j] of a list A are said to form an inversion pair if
A[i] > A[j] but i < j. Write a program to count the number of inversion pairs in a list A
containing distinct integers'''
list1 = [4,7,9,3,68,34,84,5,2,91,1,26,13]
count = 0
for i in range(len(list1)):
    for j in range(len(list1)):
        if list1[i]>list1[j] and i<j:
            count+=1
print('no of inversion pair in given list:', count)


'''Write a program to verify whether an input matrix is square or not. If it is not a
square matrix, print NOT SQUARE. Otherwise, further check whether it is singular (determinant is 0) or unimodular (determinant is 1). Accordingly, print SQUARE - SINGULAR or
SQUARE - UNIMODULAR, otherwise print SQUARE - OTHER'''
import copy
col = int(input('enter number of columns : '))
row = int(input('enter number of row : '))
MATRIX = [[int(input('enter element : '))for j in range(row)]for i in range(col)]
if col!=row :
    print('NOT SQUARE')
def subM(M,a,b):
    P = copy.deepcopy(M)
    P.pop(a)
    for i in range(len(P)):
        P[i].pop(b)
    return P
def determinant(M):
    if len(M) == 1:
        return M[0][0] 

    if len(M) != len(M[0]):
        raise ValueError("Matrix is not square")

    if len(M) == 2:
        return M[0][0] * M[1][1] - M[0][1] * M[1][0]

    det = 0
    for i in range(len(M)):
        minor = subM(M, 0, i)
        det += ((-1) ** i) * M[0][i] * determinant(minor)

    return det


print(MATRIX)
deter = determinant(MATRIX)


if deter==0 :
    print('SINGULAR')
elif deter==1:
    print('SQUARE - UNIMODULAR')

'''Given two binary strings representing two integers, find the product of the two
integers using Karatsuba's algorithm.
'''
def karatsuba(x, y):
    if x < 10 or y < 10:
        return x * y
    else:
        n = max(len(str(x)), len(str(y)))
        half = n // 2
        a = x // (10 ** half)  # left part of x
        b = x % (10 ** half)   # right part of x
        c = y // (10 ** half)  # left part of y
        d = y % (10 ** half)   # right part of y

        ac = karatsuba(a, c)
        bd = karatsuba(b, d)
        ad_plus_bc = karatsuba(a + b, c + d) - ac - bd

        return ac * (10 ** (2 * half)) + ad_plus_bc * (10 ** half) + bd

u = input('Enter binary 1: ')
v = input('Enter binary 2: ')

# Convert binary strings to integers
u_int = int(u, 2)
v_int = int(v, 2)

result = karatsuba(u_int, v_int)

print(f'The product of {u_int} and {v_int} is {result}')


'''A group of n friends F1, F2, . . . , Fn decide to try their luck at a lottery. Each person
Fi buys a number Xi of lottery tickets. Each lottery ticket has a digit (0-9) printed on it.
The rule for winning the jackpot is as follows. Each person is asked to announce the largest
multiple of 3 that can be formed by selecting and arranging the digits on his lottery tickets.
The person who has the highest such multiple wins the jackpot. Note that a person's tickets
may not have distinct digits on them.'''

#METHOD 1
#for this we just should find an algorithm to find the highest multiple of 3 that can be formed given a list of some integer digits (0-9), 
#then we just do this for all n friends and find who has the maximum such number

l1 = [4, 5, 4, 0, 6, 4, 6, 7, 4]
l3 = []

def pseudo(m):
    if sum(m) % 3 == 0:
        return True
    return False

l3 = []
list1 = []

def checkpseudo(lst, k=0):
    if k == len(lst):
        if pseudo(l3):
            copy = list(l3)
            list1.append(copy)
        return

    l3.append(lst[k])
    checkpseudo(lst, k + 1)

    l3.remove(lst[k])
    checkpseudo(lst, k + 1)

checkpseudo(l1)

# Filter out empty strings and convert to integers
integers = [int(''.join(map(str, l))) for l in list1 if ''.join(map(str, l))]

# Sort integers in descending order
integers.sort(reverse=True)

# Find the largest multiple of 3
largest_multiple_of_3 = None
for num in integers:
    if num % 3 == 0:
        largest_multiple_of_3 = num
        break

print("The largest multiple of 3 is:", largest_multiple_of_3)

#METHOD 2
n=int(input("enter no of digits to enter :"))
l=[]
for i in range(n):
    l.append(int(input("enter a digit (0-9) :")))
l.sort()
l_0=[]
l_1=[]
l_2=[]
for i in l:
    if i%3==0:
        l_0.append(i)
    elif i%3==1:
        l_1.append(i)
    else:
        l_2.append(i)
l_1.sort()
l_2.sort()
print(l,l_1,l_2,l_0)
if sum(l)%3==0:
    print(l[::-1])
elif sum(l)%3==1:
    if len(l_1)!=0: 
        l.remove(l_1[0])
        print(l[::-1])
    if len(l_1)==0:
        l.remove(l_2[0]) 
        l.remove(l_2[1])
        print(l[::-1])
elif sum(l)%3==2: 
    if len(l_2)!=0:
        l.remove(l_2[0])
        print(l[::-1])
    elif len(l_2)==0 :
        l.remove(l_1[0])
        l.remove(l_1[1])
        print(l[::-1])
    

''') Suppose we define the angle between a pair of hands (denoting hour, minute, and
second) of a clock as the lowest of the two possible angles. Let the hands are said to be
in EQUIANGULAR position if the angles between them are the same. Further assume
that the hands of a clock are said to be in SEMI-EQUIANGULAR position if the angles
between any two pairs of hands are the same. Write a program that takes the time as
user input (in the 24-hour format) and returns whether the clock is in EQUIANGULAR,
SEMI-EQUIANGULAR, or NONE of the above positions. Consider that there is a tolerance
level to ensure whether a pair of angles are same or not. Given the two angles α and β, they
are said to be same for a tolerance level δ if | α - β| ≤ δ'''


def calculate_angle(hour, minute):
    # Calculate the angle of a clock hand from the 12 o'clock position
    return abs((30 * hour - (11/2) * minute) % 360)

def clock_position(time_str, tolerance):
    # Parse the input time in 24-hour format
    try:
        hours, minutes, seconds = map(int, time_str.split(':'))
        if not (0 <= hours < 24) or not (0 <= minutes < 60) or not (0 <= seconds < 60):
            return "INVALID INPUT"
    except ValueError:
        return "INVALID INPUT"

    # Calculate angles between clock hands
    hour_angle = calculate_angle(hours % 12, minutes)
    minute_angle = calculate_angle(minutes, seconds)
    second_angle = calculate_angle(seconds, seconds)

    # Check for EQUIANGULAR and SEMI-EQUIANGULAR positions
    if abs(hour_angle - minute_angle) <= tolerance and abs(minute_angle - second_angle) <= tolerance:
        return "SEMI-EQUIANGULAR"
    elif abs(hour_angle - minute_angle) <= tolerance and abs(minute_angle - second_angle) <= tolerance and abs(hour_angle - second_angle) <= tolerance:
        return "EQUIANGULAR"
    else:
        return "NONE"

def main():
    time_str = input("Enter the time in 24-hour format (HH:MM:SS): ")
    tolerance = float(input("Enter the tolerance level for angle matching: "))
    
    result = clock_position(time_str, tolerance)
    print(f"The clock is in {result} position.")

if __name__ == "__main__":
    main()
