# Optimizing Python Code

When we talk about making Python code faster, it's a topic that often sparks debate. While Python is known for its ease of use and rapid development, not its raw speed, that doesn't mean we should ignore performance entirely.

First, it's crucial to understand the philosophy behind optimization: the common wisdom "premature optimization is the root of all evil" holds true. This means that if you spend too much time fine-tuning small details early in development, you might slow down your progress or even prevent your application from ever being completed. Your initial focus should always be on getting your code to work correctly. Once you have a functional application, *then* you can identify and address any performance bottlenecks. If a section of code is working but not perfectly optimized, it's a good idea to make a note and revisit it later if performance becomes a problem.

However, completely dismissing optimization in Python isn't a good approach either. Some believe that if speed is a concern, you should simply use a lower-level language like C++ or Java. This perspective often overlooks Python's capabilities for making meaningful performance improvements.

Here are some key considerations for Python code optimization:

* **Aim for "Acceptably Fast," Not "Fastest Ever":** Don't try to achieve the absolute maximum speed in Python; other languages are fundamentally designed for that. Instead, focus on making your code run at a speed that is satisfactory for your application's needs.
* **Prioritize Readability:** Python's core strengths are its simplicity and clarity. Any optimization effort should never make your code difficult to read or understand. If an optimization significantly sacrifices readability, you might be better off considering a different language that offers greater performance without such a trade-off.
* **Significant Gains, Not Micro-Optimizations:** Focus on optimizing larger sections of code where you can save noticeable amounts of time per execution (e.g., seconds), rather than obsessing over "micro-optimizations" that yield negligible gains. Simple techniques, like using list comprehensions instead of traditional `for` loops, can often provide substantial improvements.
* **Small Savings Accumulate:** Even minor time savings per execution can add up dramatically. If a process that saves half a second is run many times a day, those small gains quickly translate into significant time savings over weeks or months. The value of optimization directly relates to how frequently your code runs.
* **Optimizations Are Context-Dependent and Can Change:**
  * **Beware of Bias:** Benchmarks and optimization advice can sometimes be biased or based on very specific scenarios that don't apply universally.
  * **Environmental Factors:** The performance of your code can be influenced by your computer's resources, background processes, and overall system load during testing.
  * **Version Evolution:** Python itself, along with its libraries, is constantly evolving. An optimization that was effective in an older version (for instance, before Python 3.11's performance enhancements) might become redundant or even counterproductive in a newer version.
* **Always Test in Your Own Environment:** It is paramount that you **always test any proposed optimization within your specific codebase and execution environment.** Never blindly apply optimization tips; what works well for someone else's code might not translate to gains (or could even lead to performance degradation) in your unique setup.
* **Unbiased Testing is Difficult:** Performing truly unbiased and comprehensive performance tests is a complex task. Many factors can influence results, and it's easy to overlook details that skew benchmarks.

## Python Optimization Techniques

### statistics.mean(ls) vs statistics.fmean(ls)

The `statistics.mean(ls)` function calculates the arithmetic mean of a list of numbers, while `statistics.fmean(ls)` is designed to compute the mean more efficiently for large datasets, especially when dealing with floating-point numbers.

* Uses C-based floating-point arithmetic
* Optimized for performance
* Doesn't handle edge cases like Decimal/Fraction objects

```python
import statistics
ls = [float(i) for i in range(1_000_000)]

# Test 1: statistics.mean()
%timeit statistics.mean(ls)
# Result: ~120 ms ± 5 ms per loop

# Test 2: statistics.fmean()
%timeit statistics.fmean(ls)
# Result: ~15 ms ± 0.5 ms per loop
```

### ls[-1] vs ls[len(ls)-1]

Accessing the last element of a list using `ls[-1]` is more efficient than using `ls[len(ls)-1]`. The former directly accesses the last item, while the latter calculates the length of the list first, which adds unnecessary overhead.

* Direct pointer arithmetic in CPython
* No intermediate len() calculation
* Fundamental Python optimization

```python
ls = list(range(1_000_000))

# Test 1: Negative indexing
%timeit ls[-1]
# Result: ~30 ns ± 1 ns

# Test 2: len() calculation
%timeit ls[len(ls)-1]
# Result: ~120 ns ± 5 ns
```

### sum = sum + i vs sum += i

Using `sum += i` is more efficient than `sum = sum + i`. The former modifies the existing variable in place, while the latter creates a new object and assigns it back to the variable, which incurs additional overhead.

* In-place operation (no new object creation)
* Special bytecode optimization (INPLACE_ADD)
* Avoids temporary variable creation

```py
sum_val = 0

# Test 1: sum = sum + i
%timeit for i in range(1000): sum_val = sum_val + i
# Result: ~150 µs ± 5 µs

# Test 2: sum += i
%timeit for i in range(1000): sum_val += i
# Result: ~120 µs ± 3 µs
```

### x = x + 1 vs x = -~x

Using `x = -~x` is a clever trick to increment a number by 1 without using the addition operator. This method takes advantage of bitwise operations, which can be faster in some cases.

* More readable to interpreter
* Bitwise operations have overhead in Python
* No real optimization benefit for integers

Note that, x + (2’s complement of x) = 0
⇒ x + ((1’s complement of x) + 1) = 0
⇒ x + 1 = − (1’s complement of x) = -~x

```py
x = 0

# Test 1: x = x + 1
%timeit for _ in range(1000): x = x + 1
# Result: ~80 µs ± 2 µs

# Test 2: x = -~x
%timeit for _ in range(1000): x = -~x
# Result: ~90 µs ± 3 µs
```

### Multiplication vs. Shift-Add

**Original:** `m * 65`
**Optimized:** `(m << 6) + m`

**Analysis:**

* Modern CPUs can perform integer multiplication in 1-3 cycles, and compilers/interpreters are already smart enough to replace constant multiplications with shift-add operations when beneficial.
* The shift-add version requires 2 operations (shift + add), which might be faster on very old processors but likely makes no difference or could even be slower on modern CPUs due to instruction-level parallelism.
* The optimized version is less readable and offers minimal to no performance benefit on modern hardware.

### Modulo vs. Bitwise AND

**Original:** m % 8
**Optimized:** m & 7

**Analysis:**

* This is a classic and effective optimization when the divisor is a power of 2.
* The % operation is much slower than a bitwise AND (typically 10-20 cycles vs. 1 cycle).
* Compilers already perform this optimization automatically when possible.
* The optimized version is significantly faster and should be used when performance is critical (though good compilers will do it for you).

### Case Checking vs. Bitwise OR

**Original:**

```python
if ch == 'a' or ch == 'A':
    vowel += 1
```

**Optimized:**

```python
ch = ch | 0x20
if ch == 'a':
    vowel += 1
```

**Analysis:**

* The original does two comparisons (with potential branch prediction overhead).
* The optimized version does one bitwise OR (very fast, 1 cycle) and one comparison.
* Bitwise OR with 0x20 converts uppercase ASCII letters to lowercase (works for A-Z/a-z).
* The optimized version avoids a branch and is likely faster, but:
  * Only works for ASCII (not Unicode).
  * Less readable unless well-documented.
  * Modern branch predictors might minimize the difference.

### Lazy Evaluation

**Typical usage:**
`while i < N and ls[i] >= 0:`
    `...`

* If `i >= N`, `ls[i]` is not checked.
* This is useful because checking `ls[i] >= 0` when `i >= N` may lead to memory faults.
* In such expressions, `i >= N` serves as a guard condition.

### Loop Jamming

Loop jamming is a technique where multiple loops that iterate over the same data are combined into a single loop. This can reduce overhead and improve cache locality.

* If a single loop contains a lot of operations (it might not fit into the processor’s instruction cache), then two separate loops may be faster than a single combined one.
* Never use two loops where one will suffice.

```py
for i in range(0, 10):
    <Statement 1>
for i in range(0,10):
    <Statement 2>
```

It should be written as follows:

```py
for i in range(0,10):
    <Statement 1>
    <Statement 2>
```

### Loop unrolling

Loop unrolling is a technique that reduces the overhead of loop control by executing multiple iterations of the loop body in a single iteration. This can lead to performance improvements, especially in tight loops.

* The need for condition check adds some overhead to the program
* The loop overhead can be reduced by decreasing the number of
iterations and replicating the body of the loop.

```py
for i in range(0,100):
    <Statement>
```

The above code can be written as follows:

```py
for i in range(0,100,2):
    <Statement>
    <Statement>
```

### Loop inversion

Loop inversion is a technique that can improve the efficiency of loops by changing the way the loop condition is checked. Instead of checking the condition at the beginning of each iteration, it checks it at the end, which can reduce the number of condition checks.

* We should always write count-down-to-zero loops and use simple termination conditions for a better efficiency.

```py
fact = 1
i = 1
while i <= n:
    fact *= i
    i += 1
```

The above code can be made efficient by writing as follows:

```py
fact = 1
i = n
while i:
    fact *= i
    i -= 1
```

### List Comprehension vs. `for` Loop

List comprehensions are often more efficient than using a `for` loop to create lists. They are optimized for performance and can lead to cleaner, more readable code.
This is because we are creating a list by appending new elements to it at each iteration.
However, if we want to perform some computations (or call an independent function multiple times) and do not want to create a list, then for loops are faster than list comprehensions.

`print([l for l in ls if l == l[::-1]])  # Creates a list of palindromes`

* Python optimizes list comprehensions internally.
* Avoids the overhead of repeated .append() calls.
* Drawback: Unnecessary if you don’t need the list (wastes memory).

```py
for l in ls:
    if l == l[::-1]:
        print(l)  # Just prints, no list stored
```

* No memory allocation for a new list.
* Better for large datasets where memory matters.
* Drawback: Slower than list comprehension if you eventually need the list.

### List comprehensions versus generator expressions

List comprehensions are usually faster than generator expressions as generator expressions create another layer of overhead to store references for the iterator. However, list comprehensions allocate more memory than generator expressions.

**List Comprehension** (`[x for x in iter]`)

* **Speed:** **Faster** for immediate iteration (no generator overhead).  
* **Memory:** **Stores the entire list in memory** → higher memory usage.  
* **Use Case:** When you need **random access** or **multiple iterations** over the result.
* Prefer List Comprehension When you **need the full list** (e.g., indexing, slicing, multiple passes).

**Generator Expression** (`(x for x in iter)`)

* **Speed:** **Slightly slower** due to iterator protocol overhead.  
* **Memory:** **Lazy evaluation** → only computes values on demand (memory-efficient).  
* **Use Case:** When processing **large datasets** or **pipelining operations** (e.g., `sum(x for x in range(10))`).
* Prefer Generator Expression When:**
* You **only iterate once** (e.g., `sum()`, `max()`, `any()`).The dataset is **large** (avoids memory issues).  

### Type casting

Avoid type casting wherever possible. Integer and floating point instructions often operate on different registers, so a casting requires a copy.
Shorter integer types (char and short) still require the use of a full-sized register, and they need to be padded to 32/64-bits and then converted back to the smaller size before storing back in memory. However, this cost must be weighed against the additional memory cost of a larger data type.

### Memory organization in lists

Two and higher dimensional arrays are still stored in one dimensional memory. This means `ls[i][j]` and `ls[i][j+1]` are adjacent to each other, whereas `ls[i][j]` and `ls[i+1][j]` may be arbitrarily far apart. When modern CPUs load data from main memory into processor cache, they fetch more than a single value. Instead they fetch a block of memory containing the requested data and adjacent data (a cache line). This means after `ls[i][j]` is in the CPU cache, `ls[i][j+1]` has a good chance of already being in cache, whereas `ls[i+1][j]` is still likely to be in the main memory.

When modern CPUs load data from main memory into processor cache, they fetch more than a single value. Instead they fetch a block of memory containing the requested data and adjacent data (a cache line). This means after `ls[i][j]` is in the CPU cache, `ls[i][j+1]` has a good chance of already being in cache, whereas `ls[i+1][j]` is still likely to be in the main memory.

**Memory organization in arrays**
Accessing data in a more-or-less sequential fashion, as stored in physical memory (in row major fashion), can dramatically speed up the code.

### Function calls

Move loops inside function calls. Replace the following code

```python
Function():
    ...
for i in range(1,n):
    Function()
```

Better:

```py
Function():
    for i in range(1,n):
    ...
Function()
```

**Note:** Jumps/branches are expensive and hence should be avoided
whenever possible. Note that, function calls require two jumps, in
addition to stack memory manipulation.

### Avoiding division

In standard processors, divisions are time-consuming because they take a constant time plus a time for each bit to divide.

```py
if (a / b) > c:
    print(’OK’)
```

It can be efficiently written as follows:

```py
if a > (b * c):
    print(’OK’)
```

Here, the only assumptions are `b` is non-negative and `b ∗ c` fits into an integer. The latter one is also safe if `b = 0`.

### Optimizing mathematical operations

1) The function `sqrt()` can often be avoided, especially in comparisons where comparing the value squared gives the same result.
2) In many equations, terms cancel out, either always or in some special cases. Work on them before writing the program.
3) Avoid the use of `pow()` for computing small integer powers. `m = pow(2,4)` < `m = 2**4` < `m = 2*2*2*2`. The latter is the fastest.
4) Instead of repeatedly dividing by x, compute 1/x and multiply accordingly. It is really beneficial if you do more than 3 divides.

```py
n = 10
x = 0.5
result = 1.0
for i in range(1,n):
    result /= x
```

This can be efficiently done in the following alternative way:

```py
n = 10
x = 0.5
result = 1.0
x = result / x
for i in range(1,n):
    result *= x
```
