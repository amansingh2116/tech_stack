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

**Note:** Jumps/branches are expensive and hence should be avoided whenever possible. Note that, function calls require two jumps, in addition to stack memory manipulation.

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

### `__slots__` attribute

When you define a regular Python class, each instance of that class typically comes with its own hidden **`__dict__`** (dictionary). This `__dict__` is where all of the instance's attributes (instance variables) are stored. While flexible, this approach has certain implications:

* **Memory Overhead:** Each `__dict__` consumes a significant amount of memory, especially when you create thousands or millions of instances of a class.
* **Dynamic Nature:** Because attributes are stored in a dictionary, Python has to perform dictionary lookups every time you read or write an attribute (e.g., `my_object.attribute_name`). While highly optimized, these lookups are inherently slower than direct memory access.

To address these concerns, Python offers the `__slots__` mechanism:

* **Pre-allocated Fixed Space:** By defining `__slots__` in your class, you tell Python *not* to create a `__dict__` for each instance. Instead, you explicitly list the valid attribute names that instances of this class will have. Python then pre-allocates a fixed, compact amount of space for these attributes directly within the object's memory structure.

* **Reduced Memory Usage:**
  * **Eliminates `__dict__`:** The primary memory saving comes from getting rid of the individual `__dict__` for each object.
  * **Compact Storage:** Attributes are stored in a more memory-efficient array-like structure rather than hash tables.
  * **Significant Impact:** This can lead to substantial memory savings, especially when dealing with a large number of small objects (e.g., millions of data points, event objects).

* **Faster Attribute Access:**
  * **No Dictionary Lookups:** Accessing attributes defined in `__slots__` no longer requires a dictionary lookup. Python can directly access the pre-allocated memory slot, leading to faster read and write operations.

* **Loss of Dynamic Attribute Addition:**
  * **Fixed Attributes:** A key trade-off with `__slots__` is that you **cannot dynamically add new attributes** to an instance after it has been created, unless those attributes were explicitly listed in `__slots__`. Attempting to set an attribute not defined in `__slots__` will result in an `AttributeError`.
  * **`__dict__` Restoration (Optional):** If you *need* to allow dynamic attribute addition while still using `__slots__`, you can include `__dict__` in your `__slots__` list (e.g., `__slots__ = ('attr1', 'attr2', '__dict__')`). However, this negates much of the memory benefit.

* **Inheritance Behavior of `__slots__`:**
  * **Subclasses Must Redefine:** If a subclass of a slotted class also wants to reap the benefits of `__slots__`, it **must define its own `__slots__`** attribute. If it doesn't, instances of the subclass will default back to using `__dict__` for their attributes (including inherited ones), losing the memory advantage.
  * **Combined Slots:** When a subclass defines its `__slots__`, the effective slots for its instances will be a combination of its own `__slots__` and all `__slots__` inherited from its parent classes.

* **When to Use `__slots__`:**
  * **High Instance Count:** Ideal when you are creating a very large number of instances of a class, such as in data processing, simulations, or ORMs (Object-Relational Mappers).
  * **Memory Optimization is Critical:** When your application's performance is bottlenecked by memory consumption, especially for numerous small objects.
  * **Fixed Attribute Names:** When you know exactly what attributes your objects will have, and there's no need to add new ones dynamically at runtime.

By leveraging `__slots__`, you can fine-tune the memory footprint and attribute access speed of your Python classes, making them more efficient for specific performance-critical use cases.

```py
from pympler import asizeof

class RegularClass:
    def __init__(self, name, age):
        self.name = name
        self.age = age

regular = RegularClass('Alice', 30)
print(f"Memory usage of RegularClass instance: {asizeof.asizeof(regular)} bytes") # 520 bytes

class SlottedClass:
    __slots__ = ['name', 'age'] # This tells Python to use a fixed-size structure for these attributes
    def __init__(self, name, age):
        self.name = name
        self.age = age

slotted = SlottedClass('Bob', 25)
print(f"Memory usage of SlottedClass instance: {asizeof.asizeof(slotted)} bytes") # 128 bytes
```

### Iterators and Iterables

An **iterator** is an object that can be iterated upon, returning one element at a time. It represents a stream of data.

**Iterator Protocol:** A Python object is an iterator if it implements two special methods: `__iter__` (which returns the iterator object itself) and `__next__` (which returns the next item in the sequence).

**Iterables:** An object is "iterable" if you can obtain an iterator from it (e.g., by calling iter()). Common built-in types like lists, tuples, and strings are iterables.

You can manually get an iterator from an iterable using iter() and then step through its elements using next(). Each next() call resumes from the previous state. When next() is called and there are no more items, a StopIteration exception is raised, signaling the end of the sequence.
Internally, Python's for loop automatically creates an iterator from the given iterable (by calling iter()), then repeatedly calls next() on it until StopIteration is caught, at which point the loop terminates.

```py
# What Python actually does:
iterable = [1, 2, 3]
iterator = iter(iterable)  # Calls __iter__()
while True:
    try:
        value = next(iterator)  # Calls __next__()
    except StopIteration:
        break
    print(value)
```

The primary benefit is lazy evaluation, meaning data is processed only when needed, not all at once. This significantly reduces memory footprint, allowing processing of datasets larger than available RAM.

Example: `map()` vs. `List Comprehension`

```py
# Memory-inefficient (creates a list)
squares = [x**2 for x in range(10_000)]  # O(n)

# Memory-efficient (iterator)
squares = map(lambda x: x**2, range(10_000))  # O(1)
```

### Generators

Iterator Implementation requires:

* Need `__iter__` & `__next__`
* Need to track internal state
* Need to raise StopIteration exception

Generators are a powerful feature in Python that allow you to create iterators in a memory-efficient way. They are defined using functions with the `yield` statement. `yield` pauses the function's execution, saves its entire local state, and "`yields`" a value. When `next()` is called again on the generator, the function resumes from where it left off, continuing execution until the next `yield` or the function ends (at which point `StopIteration` is implicitly raised).

Generators are particularly useful when dealing with large datasets or streams of data, as they allow you to iterate over items one at a time without loading the entire dataset into memory at once.

For example: `num = [x ** 2 for x in range(1000000)]` creates a list of squares, consuming a lot of memory. Instead, you can use a generator expression like `num = (x ** 2 for x in range(1000000))`, which generates each square on-the-fly as you iterate over it. Now you can access the squares without storing them all in memory at once by using `next(num)`.

Example: reading a large file line by line.

```py
def read_large_file(filename):
    """Generator to read a large file line by line."""
    with open(filename, 'r') as file:
        for line in file:
            yield line.strip()  # Yield each line without loading the entire file into memory
```

A more practical example of using a generator is calculating **rolling returns** for a stock price series:

```py
def periods(rets, roll_window=36):
    windows = ((start, start + roll_window) for start in range(rets.size - roll_window + 1))
    return (rets.iloc[win[0]:win[1]] for win in windows)

rolling_rets = [annualize_rets(period) for period in periods(rets)]
```

### `global` variable

Python manages variables differently based on their scope, which impacts how quickly they can be accessed:

**Local Variables:**

* Access Mechanism: Python's virtual machine accesses local variables using highly optimized "LOAD_FAST" and "STORE_FAST" bytecode instructions.
* Storage: They are stored in a fixed-size array that is allocated on the function's stack frame. This direct, array-based storage allows for very rapid access.
* Speed: Consequently, operations on local variables are generally the fastest.

**Global Variables:**

* Access Mechanism: Global variables are accessed using "LOAD_GLOBAL" and "STORE_GLOBAL" bytecode instructions, which are inherently slower.
* Storage: Unlike local variables, global variables are stored in a dictionary (specifically, the `globals()` dictionary of the module). Accessing values in a dictionary involves a hash lookup, which, while optimized, is slower than direct array indexing.
* Usage Guideline: Due to this overhead, it's a best practice to use global variables only when absolutely necessary for truly shared, module-level state, and to minimize frequent read/write operations on them within performance-critical loops.

```py
import timeit

# Global variable test
x = 10
def global_var():
    global x
    for i in range(1000):
        x = 5

print("Global variable time:", timeit.timeit(global_var, number=10000)) # 0.7568232

# Local variable test
def local_var():
    x = 10
    for i in range(1000):
        x = 5

print("Local variable time:", timeit.timeit(local_var, number=10000)) # 0.4231158
```

**Optimization Strategies for Variable Access:**

1. **Cache Global Variables as Locals:** For global variables that are accessed frequently within a loop or a performance-critical function, you can significantly improve speed by "caching" them in a local variable at the beginning of the function. This reduces repeated slow global lookups to a single lookup, followed by many fast local accesses.

    ```py
    def optimized():
        local_x = x  # Cache global as local
        for i in range(1000):
            local_x = 5
    ```

2. **Utilize Class Attributes as an Alternative to Globals:** Instead of using standalone global variables, consider encapsulating shared state within class attributes. This approach offers several advantages:
   1. Improved Access Speed: Accessing class attributes (using "LOAD_ATTR" bytecode) is generally faster than performing a "LOAD_GLOBAL" lookup.
   2. Logical Grouping: Class attributes allow you to logically group related variables, enhancing code organization and readability.
   3. Encapsulation Benefits: By putting shared state into a class, you can control access to it (e.g., through properties), modify behavior via inheritance, and manage its lifecycle more effectively.

    ```py
    class AppConfig:
        """A class to hold application-wide configuration or shared state."""
        current_counter = 0  # This is a class attribute

    def increment_counter():
        """Function that modifies a shared counter stored as a class attribute."""
        AppConfig.current_counter += 1

    # --- Demonstration ---
    print("\n--- Using Class Attributes for Shared State ---")
    print(f"Initial counter: {AppConfig.current_counter}")
    increment_counter()
    increment_counter()
    print(f"Counter after increments: {AppConfig.current_counter}")

    # You can also use a dedicated instance if state is more complex
    # app_state = AppConfig()
    # app_state.current_counter += 1
    ```

### Attribute Access: Caching with Local Variables

When working with object attributes that are accessed multiple times within a short code block or a calculation, it's a good practice to cache them in local variables. This approach, often considered a form of "avoiding repeated dot access," enhances both code readability and can offer minor performance benefits in performance-critical sections.

* **Improved Readability:** Assigning object.attribute to a concise, descriptive local variable (like rectangle_height instead of rectangle.height repeatedly) makes complex formulas or sequences of operations much cleaner and easier to read, especially when dealing with long object names or nested attribute access.
* **Potential Performance Gain:** While Python's attribute access (LOAD_ATTR bytecode) is highly optimized, retrieving a value from a local variable (LOAD_FAST bytecode`) is generally faster. In very tight loops or frequently executed functions, reducing repeated attribute lookups can lead to marginal, but sometimes measurable, performance improvements by replacing slower lookups with faster local variable accesses.

```py
class Rectangle:
    def __init__(self, h, w):
        self.height = h
        self.width = w
        
rectangle = Rectangle(10, 5)

# Cache the rectangle's attributes into local variables.
rectangle_height = rectangle.height
rectangle_width = rectangle.width

# Now, use these local variables for calculations.
surface = rectangle_height * rectangle_width
perimeter = 2 * rectangle_height + 2 * rectangle_width

print(f"Rectangle dimensions: {rectangle_height}x{rectangle_width}")
print(f"Calculated Surface Area: {surface}")
print(f"Calculated Perimeter: {perimeter}")
```

### Built-in Functions

When optimizing Python code, especially when dealing with data processing, leveraging built-in functions and specialized modules can lead to significant performance gains over manual Python loops. These optimized tools are often implemented in C, allowing them to execute much faster by avoiding the overhead of the Python interpreter for each individual operation.

1. **`map()`**

      * **Core Purpose (Optimization Context):** Efficiently applies a given function to every item in an iterable. It's highly optimized for transformations, outperforming explicit `for` loops where each iteration involves Python overhead.
      * **Why it's faster:** The core iteration logic of `map()` is implemented in C, which means it processes elements without the interpretive overhead of a Python `for` loop for each item. It also produces results lazily (as an iterator), saving memory.
      * **Example:** `numbers = [1, 2, 3, 4]; squared_numbers = list(map(lambda x: x**2, numbers)); # Efficiently squares all numbers`

2. **`filter()`**

      * **Core Purpose (Optimization Context):** Efficiently constructs an iterator from elements of an iterable for which a function returns true. It's the optimized way to select a subset of items based on a condition, replacing explicit loops with conditional checks.
      * **Why it's faster:** Similar to `map()`, `filter()`'s iteration and conditional checking logic operates at the C level, significantly reducing processing time compared to manual Python `for` loops with `if` statements. It also returns an iterator, supporting lazy evaluation.
      * **Example:** `numbers = [1, 5, 8, 12, 3]; evens = list(filter(lambda x: x % 2 == 0, numbers)); # Efficiently filters even numbers`

3. **`sum()`, `min()`, `max()` (Built-in Aggregates)**

      * **Core Purpose (Optimization Context):** These built-in functions efficiently calculate the sum, minimum, or maximum value of all elements in an iterable. They are the go-to for aggregation.
      * **Why it's faster:** These functions are highly optimized, implemented in C. They perform the aggregation directly on the iterable's elements without the overhead of a Python `for` loop and individual arithmetic operations for each item.
      * **Example:**

        ```python
        data = [10, 20, 5, 15]
        total = sum(data)    # Efficient sum: 50
        minimum = min(data)  # Efficient min: 5
        maximum = max(data)  # Efficient max: 20
        ```

4. **`functools.reduce()`**

      * **Core Purpose (Optimization Context):** Applies a function of two arguments cumulatively to the items of an iterable, from left to right, to reduce the iterable to a single value. While it's powerful, its use cases for optimization are more specific than `sum`, `min`, `max`.
      * **Why it's faster:** Like other built-in tools, the core iteration and application of the function within `reduce()` are optimized in C, making it generally faster than writing a manual `for` loop with an accumulator variable, especially for complex reduction logic.
      * **Example:**

        ```python
        from functools import reduce
        numbers = [1, 2, 3, 4]
        # Calculate product: ((((1*2)*3)*4) = 24
        product = reduce(lambda x, y: x * y, numbers)
        ```

5. **`str.join()`**

      * **Core Purpose (Optimization Context):** Concatenates elements of an iterable (typically strings) into a single string, using the string on which `join()` is called as a separator. It's the highly optimized method for building strings from parts.
      * **Why it's faster:** Unlike repeated `+` or `+=` operations on strings (which create new string objects in memory with each concatenation due to string immutability), `str.join()` efficiently pre-calculates the final string size and constructs it in a single pass. This minimizes intermediate string creations and memory allocations.
      * **Example:** `words = ['Hello', 'World', 'Python']; sentence = ' '.join(words); # sentence will be 'Hello World Python'`

6. **`operator.itemgetter()` and `operator.attrgetter()`**

      * **Core Purpose (Optimization Context):** These functions from the `operator` module create callable objects that are highly optimized for retrieving items (from sequences or mappings) or attributes (from objects). They are particularly useful as the `key` argument in functions like `sorted()`, `list.sort()`, `min()`, or `max()`.
      * **Why it's faster:** `itemgetter` and `attrgetter` are implemented in C, making them significantly faster than equivalent `lambda` functions when used in performance-sensitive contexts like sorting large lists of complex objects, as they avoid Python function call overhead for each comparison.
      * **Example (`itemgetter`):**

        ```python
        from operator import itemgetter
        data = [('apple', 3), ('banana', 1), ('cherry', 2)]
        # Sort by the second element (index 1)
        sorted_by_count = sorted(data, key=itemgetter(1))
        # sorted_by_count will be [('banana', 1), ('cherry', 2), ('apple', 3)]
        ```

      * **Example (`attrgetter`):**

        ```python
        from operator import attrgetter
        class Person:
            def __init__(self, name, age):
                self.name = name
                self.age = age
        people = [Person('Alice', 30), Person('Bob', 25)]
        # Sort by the 'age' attribute
        sorted_by_age = sorted(people, key=attrgetter('age'))
        # sorted_by_age will be [Person(Bob, 25), Person(Alice, 30)]
        ```

7. **`zip()`**
    * **Purpose:** Aggregates elements from multiple iterables, creating an iterator of tuples where the i-th tuple contains the i-th element from each of the input iterables. It stops when the shortest iterable is exhausted.
    * **Syntax:** `zip(*iterables)`
    * **Key Behavior:** Returns a `zip` object (an iterator of tuples). If no iterables are passed, it returns an empty iterator.
    * **Example:** `names = ['Alice', 'Bob']; ages = [30, 24]; combined = list(zip(names, ages)); # combined will be [('Alice', 30), ('Bob', 24)]`

8. **`super()`**
    * **Purpose:** Returns a proxy object that allows you to refer to a parent or sibling class. Its primary use cases are avoiding explicitly naming the base class (especially in multiple inheritance) and ensuring proper method resolution order (MRO) when calling inherited methods (e.g., `__init__`).
    * **Syntax:** `super().method_name(*args)` (inside a child class method)
    * **Key Behavior:** Crucial for cooperative inheritance, ensuring parent class logic (like constructor initialization) is executed.
    * **Example:** `class Dog(Mammal): def __init__(self, name): super().__init__(name); print(f"{name} has four legs.")`

9. **`hash()`**
    * **Purpose:** Returns the hash value of an object, if it is hashable (immutable). Hash values are integers used internally for quick comparisons of dictionary keys and set members.
    * **Syntax:** `hash(object)`
    * **Key Behavior:** Only works for immutable objects (e.g., integers, floats, strings, tuples). Raises `TypeError` for mutable objects (e.g., lists, dictionaries). Internally calls `object.__hash__()`.
    * **Example:** `hash_int = hash(190); hash_str = hash("Python"); hash_tuple = hash((1, 2, 'a'))`

10. **`format()`**
    * **Purpose:** Returns a formatted representation of a given value controlled by a format specifier. It's similar to `str.format()` but works at a lower level on a single object.
    * **Syntax:** `format(value, format_specifier)`
    * **Key Behavior:** Allows precise control over how numbers (e.g., decimal places, binary), dates, etc., are represented as strings. Internally calls `value.__format__()`.
    * **Example:** `formatted_float = format(123.456, '.2f'); # formatted_float will be '123.46'`

11. **`enumerate()`**
    * **Purpose:** Adds a counter to an iterable and returns it as an enumerate object (an iterator of tuples), where each tuple contains `(index, element)`.
    * **Syntax:** `enumerate(iterable, start=0)`
    * **Key Behavior:** The `start` parameter is optional and sets the initial value of the counter. It's commonly used in `for` loops when you need both the item and its index.
    * **Example:** `groceries = ['bread', 'milk', 'butter']; for i, item in enumerate(groceries, start=1): print(f"{i}. {item}")`

12. **`memoryview()`**
    * **Purpose:** Returns a memory view object from a given argument, allowing direct access to the internal buffer of an object without copying it. This is useful for high-performance operations on large binary data.
    * **Syntax:** `memoryview(object)`
    * **Key Behavior:** The object must support the buffer protocol (e.g., `bytes`, `bytearray`). It provides a "view" into the underlying memory.
    * **Example:** `data = bytearray(b'ABC'); mv = memoryview(data); print(mv[0]); # Output: 65 (ASCII for 'A')`

13. **`pow()`**
    * **Purpose:** Returns the result of a base number raised to an exponent. Optionally, it can also compute the modulus of the result.
    * **Syntax:** `pow(base, exp, mod=None)`
    * **Key Behavior:** Equivalent to `base ** exp`. If `mod` is provided, it calculates `(base ** exp) % mod`, which is particularly useful in cryptography.
    * **Example:** `result1 = pow(2, 3); # result1 is 8 (2^3) ; result2 = pow(2, 3, 3); # result2 is 2 (8 % 3)`

14. **`repr()`**
    * **Purpose:** Returns a "printable representation" of an object that would ideally be a valid Python expression capable of recreating the object (or a similar one). It's typically used for debugging and development.
    * **Syntax:** `repr(object)`
    * **Key Behavior:** For strings, it includes quotes. For many built-in types, `repr()` returns a representation that could be passed to `eval()` to reconstruct the object.
    * **Example:** `my_var = 'foo'; repr_str = repr(my_var); # repr_str will be "'foo'" (including quotes)`

15. **`str.strip()`** (String Method)
    * **Purpose:** Returns a copy of the string with leading and trailing whitespace (or specified characters) removed.
    * **Syntax:** `string.strip([chars])`
    * **Key Behavior:** Does not modify the original string (strings are immutable). If `chars` is provided, it removes any combination of those characters from the ends.
    * **Example:** `text = "  Hello World  "; stripped_text = text.strip(); # stripped_text will be "Hello World"`

16. **`round()`**
    * **Purpose:** Rounds a floating-point number to a specified number of decimal digits or to the nearest integer.
    * **Syntax:** `round(number, ndigits=None)`
    * **Key Behavior:** If `ndigits` is omitted, it rounds to the nearest integer. It uses "round half to even" tie-breaking (e.g., `round(2.5)` is 2, `round(3.5)` is 4).
    * **Example:** `rounded1 = round(10.7); # rounded1 is 11 ; rounded2 = round(2.665, 2); # rounded2 is 2.67`

17. **`abs()`**
    * **Purpose:** Returns the absolute value of a given number. For complex numbers, it returns their magnitude.
    * **Syntax:** `abs(number)`
    * **Key Behavior:** Works for integers, floats, and complex numbers.
    * **Example:** `abs_int = abs(-20); # abs_int is 20 ; abs_float = abs(-30.33); # abs_float is 30.33`

18. **`dir()`**
    * **Purpose:** Attempts to return a list of valid attributes for the given object. If no argument is provided, it returns the names in the current scope.
    * **Syntax:** `dir([object])`
    * **Key Behavior:** Useful for exploring objects and understanding what methods and attributes they possess. Can be customized for user-defined classes by implementing `__dir__`.
    * **Example:** `my_list = [1, 2]; attributes = dir(my_list); # attributes will be a list of methods like 'append', 'pop', etc.`

19. **`list.clear()`** (List Method)
    * **Purpose:** Removes all elements from a list, making it empty.
    * **Syntax:** `list_object.clear()`
    * **Key Behavior:** Modifies the list in-place and does not return a value. This method is specific to list objects.
    * **Example:** `my_list = [1, 2, 3]; my_list.clear(); # my_list is now []`

20. **`sorted()`** (Standard Library Function)
    * **Purpose:** Returns a new sorted list from the elements in the iterable.
    * **Syntax:** `sorted(iterable, key=None, reverse=False)`
    * **Key Behavior:** Sorts the elements in the iterable and returns a new sorted list. If `key` is provided, it specifies a function to use for comparison.
    * **Example:** `numbers = [3, 1, 2]; sorted_numbers = sorted(numbers); # sorted_numbers will be [1, 2, 3]`

### Using data structures wisely

The choice of data structure is fundamental to writing efficient Python code, as different structures offer varying performance characteristics for common operations like membership testing, insertion, and deletion.

1. **Efficient Key Checking in Dictionaries:**
    When you need to check if a key exists in a dictionary, there's a specific way that's significantly more efficient than others.

      * **Optimal Approach (Direct `in` operator):**
        To check for a key's presence, directly use the `in` operator on the dictionary itself. This method leverages the dictionary's underlying hash table implementation, providing very fast, average **O(1) (constant time)** lookup performance.

        ```python
        my_dict = {'apple': 1, 'banana': 2, 'cherry': 3}
        if 'banana' in my_dict: # This is the highly optimized way
            print("Banana is in the dictionary.")
        ```

      * **Less Optimal Approach (`.keys()` method):**
        Avoid checking for a key's presence by first calling `.keys()` and then using `in` on the resulting "keys view" object (or converting it to a list). While `dict.keys()` returns a view that provides efficient membership testing in Python 3, explicitly calling it adds a minor overhead. In older Python 2 versions, `dict.keys()` returned a *list* of keys, which would then lead to an **O(n) (linear time)** search, making it dramatically slower for large dictionaries. Even in Python 3, directly using `in dict` is the canonical and most straightforward approach.

        ```python
        # Avoid this pattern, even if it works in Python 3
        # In Python 2, this was an O(n) operation due to list creation
        if 'banana' in my_dict.keys():
            print("Banana is in the dictionary (less optimal way).")
        ```

2. **Sets for Fast Membership Testing and Unique Collections:**
    Sets are an incredibly powerful data structure for scenarios requiring rapid membership checks and for maintaining collections of unique items.

      * **Hash Table Implementation:** Sets, like dictionaries (which they are built upon), are implemented using **hash tables**. This fundamental design choice is what gives them their exceptional performance.
      * **Optimal Performance for Key Operations:**
          * **Membership Checking (`in` operator):** Checking if an element is in a set has an average **O(1) (constant time)** complexity. This means that whether your set contains 10 elements or 10 million, the time taken to check for an element's presence remains virtually the same.
          * **Insertion and Deletion:** Adding or removing elements from a set also performs, on average, in **O(1) (constant time)**.
      * **Contrast with Lists:** In stark contrast, checking for an element in a `list` (or searching for an item to delete) requires iterating through the list, resulting in **O(n) (linear time)** complexity. This means the time taken scales directly with the size of the list, becoming very slow for large collections.
      * **Uniqueness and Order:** Sets inherently store only **unique elements** and do **not preserve insertion order**. This characteristic, while sometimes a limitation, contributes to their efficiency by simplifying their internal management and search space.
      * **Creation Overhead:** While operations on sets are fast, the initial creation of a set (especially from a list with many duplicates) can be slightly slower than creating a list, as it involves hashing and checking for uniqueness for each element. However, for scenarios involving frequent lookups, insertions, or deletions, this one-time creation cost is quickly recouped by the subsequent performance gains.

    **In summary, choose sets when:**

      * You frequently need to check for the presence of an item.
      * You need to store a collection of unique items.
      * The order of elements does not matter.

    **Example:**

    ```python
    import timeit

    # Create a large list and set for comparison
    large_list = list(range(1_000_000))
    large_set = set(large_list)

    # Test membership checking speed
    print("Time for list membership check:")
    # This will be much slower
    print(timeit.timeit("999999 in large_list", globals={'large_list': large_list}, number=100))

    print("\nTime for set membership check:")
    # This will be significantly faster
    print(timeit.timeit("999999 in large_set", globals={'large_set': large_set}, number=100))
    ```

### Numpy

Numpy is a popular library for numerical computing in Python. It provides a powerful and efficient way to work with arrays and matrices, and is often used in scientific and data analysis applications. It provides with a lot of optimized functions for mathematical operations, which can significantly speed up your code compared to using Python's built-in lists and loops.

#### Numpy array vs Python Lists

Numpy arrays offer significant performance and memory usage advantages over Python lists. By specifying the data type of each element, Numpy arrays can store data in a more compact form, reducing memory usage. Additionally, Numpy arrays are highly optimized for numerical computations, making them a great choice for scientific and data analysis applications.

```py
import numpy as np
import time

# Benchmark Python list
start_list = time.time()
numbers = list(range(1000)) 
squared = [x ** 2 for x in numbers]
print("First 10 squares (list):", squared[:10])
print(f"Python list time: {time.time() - start_list:.5f}s") # 0.04157s

# Benchmark NumPy array
start_np = time.time()
numbers_np = np.arange(1000) 
squared_np = numbers_np ** 2
print("First 10 squares (NumPy):", squared_np[:10]) 
print(f"NumPy time: {time.time() - start_np:.5f}s") # 0.00267s
```

#### Numpy mathematical functions

Python loops are notoriously slow for numerical operations on large datasets because they involve interpreting Python bytecode for each element and frequent context switching between Python objects. NumPy, on the other hand, is a library written largely in C and Fortran, allowing it to perform array operations at speeds comparable to compiled languages. This is where its optimization power lies.

**Using Standard Python Loops (Inefficient):**

```py
import time
import numpy as np

random_scores = np.random.randint(1, 100, size=10000000) # Create 10 million random scores

start = time.time() # Start timer

count_failed = 0
sum_failed = 0
for score in random_scores: # Explicit Python for loop
    if score < 70:          # Conditional check in Python
        sum_failed += score # Individual Python arithmetic operations
        count_failed += 1

print(sum_failed / count_failed) # Calculate mean
print("Total Time =", time.time() - start, "seconds")
# Output (from image): Total Time = 4.304428339004517 seconds
```

**Leveraging NumPy Built-in Functions (Optimized):**

```py
import time
import numpy as np

random_scores = np.random.randint(1, 100, size=10000000) # Create 10 million random scores

start = time.time() # Start timer

# Vectorized operation: Filter and calculate mean in one go
# 1. random_scores < 70: Creates a boolean array (True/False for each score)
# 2. random_scores[boolean_array]: Uses the boolean array to select only the scores where the condition is True
# 3. .mean(): Calculates the mean of the selected scores efficiently
mean_failed = (random_scores[random_scores < 70]).mean()
print(mean_failed)
print("Total Time =", time.time() - start, "seconds")
# Output (from image): Total Time = 0.906869649887085 seconds (approximately 4.7 times faster)
```

Just like that Numpy offers a lot of optimized Mathematical Operation functions such as:

* `np.sum()`: Calculate the sum of elements in an array.
* `np.mean()`: Calculate the mean of elements in an array.
* `np.median()`: Calculate the median of elements in an array.
* `np.std()`: Calculate the standard deviation of elements in an array.
* `np.dot()`: Calculate the dot product of two arrays.
* `np.linalg.inv()`: Calculate the inverse of a matrix.
* `np.linalg.solve()`: Solve a linear matrix equation.
* `np.linalg.eig()`: Calculate the eigenvalues and eigenvectors of a matrix.
* `np.linalg.svd()`: Calculate the singular value decomposition of a matrix.
* `np.corrcoef()`: Calculate the correlation coefficients of an array.
* `np.cov()`: Calculate the covariance matrix of an array.
* `np.sqrt()`: Calculate the square root of each element in an array.
* `np.squared_norm()`: Calculate the squared norm of an array.

### Pandas

**Tips for Optimizing Pandas Performance:**

1. **Specify Columns with `usecols`:**
    When loading data from a CSV file, you often only need a subset of its columns. Instead of loading the entire dataset into memory and then selecting columns, you can tell Pandas to load *only* the specific columns you need right from the start. This significantly reduces memory footprint and speeds up the initial data loading process, as less data needs to be read and parsed.
    * **Example:** `df_usecols = pd.read_csv('SalesRecords.csv', usecols=['Item Type', 'Order Priority', 'Units Sold'])`

2. **Define Data Types with `dtypes`:**
    By default, Pandas infers data types by reading through your entire dataset, which can be time-consuming and often leads to inefficient memory allocation. For instance, a column might be inferred as a generic `object` (Python string) type when `category` or a smaller integer type (like `int8`, `int16`, `int32`) would suffice. Explicitly specifying the `dtype` for each column during CSV import reduces memory usage (e.g., `int64` vs. `int32` for numbers, `object` vs. `category` for strings) and speeds up loading by skipping the inference step.
    * **Example:** `df_dtypes = pd.read_csv('SalesRecords.csv', dtype={'Item Type': 'category', 'Order Priority': 'category', 'Units Sold': 'int32'})`

3. **Utilize Sparse Data Types with `Sparse[dtype]`:**
    For columns that contain a high proportion of missing values (NaNs), using standard data types can waste considerable memory by storing these empty entries. Pandas' `Sparse[dtype]` data types offer a memory-efficient solution by only storing the non-missing values and their locations. This is particularly effective for columns that are "sparse" or "dense with NaNs."
    * **Example:** When reading: `df_sparse = pd.read_csv('SalesRecords.csv', dtype={'Customer Rating': 'Sparse[int8]', 'Notes': 'Sparse[str]'})`.
    * **Alternatively, after loading:** You can convert an existing Series to a sparse type using `series.astype('Sparse[float64]')` for numeric columns or `series.astype('Sparse[str]')` for object columns.

4. **Process Large Files in Chunks with `chunksize`:**
    When dealing with exceptionally large CSV files that might exceed your system's available RAM, attempting to load the entire file at once will lead to a `MemoryError`. The `chunksize` parameter in `pd.read_csv()` allows you to read the file in smaller, manageable portions (chunks). You can then process each chunk iteratively, perform aggregations, or save intermediate results, thus avoiding memory overflow.
    * **Example:** `for chunk in pd.read_csv('large_data.csv', chunksize=50000): process_and_aggregate(chunk)`

5. **Efficiently Cast Boolean Columns:**
    Boolean columns (containing `True`/`False` values) are very memory-efficient when stored with the `bool` dtype. If your boolean-like columns are loaded as `object` (strings like 'Yes'/'No', 'True'/'False') or `int` (0/1), converting them to the explicit `bool` data type can save memory. You can achieve this directly with `astype()` or by mapping string values to actual boolean `True`/`False`.
    * **Example (using `astype`):** `df['Is Active'] = df['Is Active'].astype('bool')`
    * **Example (using `map` for string conversions):** `df['Status'] = df['Status'].map({'Active': True, 'Inactive': False})`

6. **Convert Categorical Columns to `category` Dtype:**
    String columns that contain a limited number of unique values (e.g., 'Gender', 'Product Type', 'Region') are ideal candidates for conversion to the `category` data type. Pandas stores categorical data more efficiently by mapping unique string values to integer codes in the background, significantly reducing memory usage and often speeding up operations like grouping and sorting.
    * **Example:** `df['Product Category'] = df['Product Category'].astype('category')`

7. When performing row-wise calculations or conditional logic on Pandas DataFrames, the choice of method significantly impacts performance.
    1. **apply:** apply a function to each row of the DataFrame, which is slower than vectorized operations.
    2. **vectorized operations:** use boolean indexing, masking, or logical operators to apply conditional logic directly to the DataFrame, which is faster than using a custom function per row.

```py
def reward_calc(row):
    """
    Calculates a reward based on age, time in bed, and sleeping percentage.
    This function operates on a single row (which is typically a Pandas Series).
    """
    if row['age'] >= 90:
        return row['favorite_food']
    if (row['time_in_bed'] > 5) and (row['pct_sleeping'] > 0.5):
        return row['favorite_food']
    return row['hate_food']

# Dummy data for demonstration
import pandas as pd
import numpy as np

def get_data(num_rows=10000):
    """Generates a dummy DataFrame for testing."""
    np.random.seed(42) # for reproducibility
    data = {
        'age': np.random.randint(20, 100, num_rows),
        'time_in_bed': np.random.uniform(2, 10, num_rows),
        'pct_sleeping': np.random.uniform(0.1, 0.9, num_rows),
        'favorite_food': np.random.choice(['pizza', 'pasta', 'sushi', 'burger'], num_rows),
        'hate_food': np.random.choice(['broccoli', 'spinach', 'anchovies'], num_rows)
    }
    return pd.DataFrame(data)

# Level 1 - Loop (Inefficient)
# You iterate over each row of the DataFrame, accessing data and assigning results one by one. df.iterrows() yields (index, Series) pairs, allowing you to access row data via dictionary-like indexing (row['column_name']).

df = get_data() # Reset df for each timing run
for index, row in df.iterrows():
    df.loc[index, 'reward'] = reward_calc(row)

# Level 2 - Apply (Better, but not optimal)
# df.apply(function, axis=1) takes your custom function (like reward_calc) and applies it to each row of the DataFrame. Pandas handles the iteration internally, which is more optimized than a Python for loop. It effectively batches some operations before passing the row (as a Series) to your function.

df = get_data() # Reset df for each timing run
df['reward'] = df.apply(reward_calc, axis=1)

# Level 3 - Vectorized (Optimal)
# Instead of applying a custom function per row, you translate your conditional logic directly into Pandas' boolean indexing (df.loc[]) and logical operators (&, |, ~). Pandas and NumPy handle these operations in highly optimized, compiled C code, processing entire arrays simultaneously.

df = get_data() # Reset df for each timing run

# Initialize 'reward' column with the default 'hate_food' value
df['reward'] = df['hate_food']

# Apply favorite_food where conditions are met, overwriting the default
df.loc[
    ((df['pct_sleeping'] > 0.5) & (df['time_in_bed'] > 5)) | # Condition 1: Sleeping well
    (df['age'] > 90),                                        # Condition 2: Very old
    'reward'                                                # Target column to update
] = df['favorite_food']
```
