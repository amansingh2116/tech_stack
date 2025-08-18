'''import time
start = time.time()
# INCLUDE YOUR CODE HERE
end = time.time()
print(end - start) # in seconds


comparative analysis (which is faster):

statistics.mean(ls) < statistics.fmean(ls)
ls[-1] > ls[len(ls)-1]
sum = sum + i < sum += i

Note that, x + (2’s complement of x) = 0
=⇒ x + ((1’s complement of x) + 1) = 0
=⇒ x + 1 = − (1’s complement of x) = -~x

x=x+1 > x=-~x


Try to avoid arithmetic multiplication as and when possible.

m * n will return the same result as that of (m << p) + m,
where n can be represented as 2^p + 1
m = 123
val = m * 65
It should be written using bitwise left shift as follows.
m = 123
val = (m << 6) + m

Never perform modular division with a power of 2.

m % n will return the same result as that of m & (n-1),
where n is a power of 2.
m = 97
val = m % 8
It should be written using bitwise AND as follows.
m = 97
val = m & 7


Never perform case insensitive alphabet checking as follows.

if ch == ’a’ or ch == ’A’:
vowel += 1
It can be made faster using bitwise OR as follows.
ch = ch | 0x20
if ch == ’a’:
    vowel += 1


Lazy evaluation
Typical usage:
while i < N and ls[i] >= 0:
...
If i >= N, ls[i] is not checked.
This is useful because checking ls[i] >= 0 when i >= N may lead to memory faults.
In such expressions, i >= N serves as a guard condition.

Loop jamming 
If a single loop contains a lot of operations (it might not fit
into the processor’s instruction cache), then two separate loops
may be faster than a single combined one.
Never use two loops where one will suffice.
for i in range(0, 10):
    <Statement 1>
for i in range(0,10):
    <Statement 2>
It should be written as follows:
for i in range(0,10):
    <Statement 1>
    <Statement 2>



Loop unrolling
The need for condition check adds some overhead to the program
The loop overhead can be reduced by decreasing the number of
iterations and replicating the body of the loop.
for i in range(0,100):
    <Statement>
The above code can be written as follows:
for i in range(0,100,2):
    <Statement>
    <Statement>


Loop inversion
We should always write count-down-to-zero loops and use simple
termination conditions for a better efficiency.
fact = 1
i = 1
while i <= n:
    fact *= i
    i += 1
The above code can be made efficient by writing as follows:
fact = 1
i = n
while i:
    fact *= i
    i -= 1


Loops versus list comprehensions
List comprehensions are faster than for loops only to create lists.
This is because we are creating a list by appending new elements
to it at each iteration.
However, if we want to perform some computations (or call an
independent function multiple times) and do not want to create a
list, then for loops are faster than list comprehensions.
    
print([l for l in ls if l == l[::-1]) < for l in ls:
                                            if l == l[::-1]:
                                            lsNew.append(l)




List comprehensions versus generator expressions
List comprehensions are usually faster than generator expressions
as generator expressions create another layer of overhead to store
references for the iterator. However, list comprehensions allocate
more memory than generator expressions.


Optimizing mathematical operations

1)The function sqrt() can often be avoided, especially in
comparisons where comparing the value squared gives the same
result.
2)In many equations, terms cancel out, either always or in some
special cases. Work on them before writing the program.
3)Avoid the use of pow() for computing small integer powers.
m = pow(2,4) < m = 2**4 < m = 2*2*2*2
4)Instead of repeatedly dividing by x, compute 1/x and multiply
accordingly. It is really beneficial if you do more than 3 divides.
n = 10
x = 0.5
result = 1.0
for i in range(1,n):
result /= x
This can be efficiently done in the following alternative way:
n = 10
x = 0.5
result = 1.0
x = result / x
for i in range(1,n):
result *= x



Type casting
Avoid type casting wherever possible. Integer and floating point
instructions often operate on different registers, so a casting
requires a copy
Shorter integer types (char and short) still require the use of a
full-sized register, and they need to be padded to 32/64-bits and
then converted back to the smaller size before storing back in
memory. However, this cost must be weighed against the
additional memory cost of a larger data type


Memory organization in lists
Two and higher dimensional arrays are still stored in one
dimensional memory. This means ls[i][j] and ls[i][j+1] are
adjacent to each other, whereas ls[i][j] and ls[i+1][j] may
be arbitrarily far apart.
When modern CPUs load data from main memory into processor
cache, they fetch more than a single value. Instead they fetch a
block of memory containing the requested data and adjacent data
(a cache line). This means after ls[i][j] is in the CPU cache,
ls[i][j+1] has a good chance of already being in cache, whereas
ls[i+1][j] is still likely to be in the main memory.


Memory organization in arrays
Accessing data in a more-or-less sequential fashion, as stored in
physical memory (in row major fashion), can dramatically speed up
the code.


Function calls
Move loops inside function calls. Replace the following code
Function():
...
for i in range(1,n):
    Function()
with this code
Function():
    for i in range(1,n):
...
Function()
Note: Jumps/branches are expensive and hence should be avoided
whenever possible. Note that, function calls require two jumps, in
addition to stack memory manipulation


Avoiding division
In standard processors, divisions are time-consuming because they
take a constant time plus a time for each bit to divide.
if (a / b) > c:
    print(’OK’)
It can be efficiently written as follows:
if a > (b * c):
    print(’OK’)
Here, the only assumptions are b is non-negative and b ∗ c fits into
an integer. The latter one is also safe if b = 0.

'''