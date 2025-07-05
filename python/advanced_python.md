# Advanced Python Concepts

## Comprehensions

### List Comprehensions

List comprehensions provide a concise way to create lists. They consist of brackets containing an expression followed by a `for` clause, and can also include optional `if` clauses.

```python
L = [1, 2, 3, 4, 5, 6, 7]
L1 = [item*2 for item in L] # [2, 4, 6, 8, 10, 12, 14]

L2 = [i**2 for i in range(10) if i%2!=0] # [1, 9, 25, 49, 81]
```

### Dictionary Comprehensions

Dictionary comprehensions allow you to create dictionaries in a similar way to list comprehensions. They consist of curly braces containing key-value pairs followed by a `for` clause, and can also include optional `if` clauses.

```python
D = {i: i**2 for i in range(10) if i%2!=0} # {1: 1, 3: 9, 5: 25, 7: 49, 9: 81}

D1 = {"Name": "Nitish", "Gender": "Male", "Age": 30}
D1.items() # dict_items([('Name', 'Nitish'), ('Gender', 'Male'), ('Age', 30)])

D2 = {key:value for key,value in D1.items() if len(key) > 3} # {'Name': 'Nitish'. 'Gender': "Male"}
```

## Lambda Functions

Lambda functions are anonymous functions that can be defined and used without a name. They are often used to create short, one-line functions that are used as arguments to other functions.

```python
add = lambda x, y: x + y
result = add(2, 3) # result is 5
```

### Difference between `lambda` and `def`

- `lambda` is used for creating small, one-time functions. `def` is used for defining functions that may be reused multiple times.
- `lambda` has no return statement; it implicitly returns the result of the expression.
- `lambda` can only contain a single expression, also it does not have a name, while `def` can contain multiple statements and has a name.

### When to use `lambda`

- When you need a small function for a short period of time.
- When you want to pass a function as an argument to another function.
- along with `map`, `filter`, and `reduce` functions for functional programming tasks.
- along with other High Order Functions (fucntions that take other functions as arguments or return functions as results).

### Examples of using `lambda`

```python
x = lambda a, b: a + b # adds two numbers
print(x(5, 3))  # Output: 8

y = lambda x: "Even" if x % 2 == 0 else "Odd" # checks if a number is even or odd
print(y(4))  # Output: Even

# High Order Function Example
def return_sum(func, L):
    result = 0
    for i in L:
        if func(i):
            result = result + i
    return result
L = [11,14,21,23,56,78,45,29,28]
x = lambda x: x%2 == 0
y = lambda x: x%2!=0
z = lambda x: x%3 == 0
print(return_sum(x, L)) # Output: 176 (sum of even numbers)
print(return_sum(y, L)) # Output: 129 (sum of odd numbers)
print(return_sum(z, L)) # Output: 144 (sum of numbers divisible by 3)

# Using `lambda` with `map`
L = [1, 2, 3, 4, 5, 6, 7]
list(map(lambda x: x**2, L))  # Output: [1, 4, 9, 16, 25, 36, 49]
list(map(lambda x: x%2 ==0, L)) # Output: [False, True, False, True, False, True, False]

# Using `lambda` with `filter`
L = [1, 2, 3, 4, 5, 6, 7]
list(filter(lambda x: x>4, L)) # Output: [5, 6, 7]

fruits = ['Apple', 'Orange', 'Mango', 'Guava']
list(filter(lambda fruit: 'e' in fruit, fruits)) # Output: ['Apple', 'Orange']

# Using `lambda` with `reduce`
from functools import reduce
L = [1, 2, 3, 4, 5, 6, 7]
reduce(lambda x, y: x if x>y else y, L) # 7 (maximum element)
```

## Iterators

**What is an Iteration**
Iteration is a general term for taking each item of something, one after another. Any time you use a loop, explicit or implicit, to go over a group of items, that is iteration.

```py
# Example
num = [1,2,3]
for i in num:
    print(i)
# 1 2 3
```

**What is Iterator**
An Iterator is an object that allows the programmer to traverse through a sequence of data without having to store the entire data in the memory.

```py
# Example
L = [x for x in range(1,10000)]

#for i in L:
    #print(i*2)
    
import sys

print(sys.getsizeof(L)/64) # 1369.0

x = range(1,10000000000)

#for i in x:
    #print(i*2)
    
print(sys.getsizeof(x)/64) # 0.75

```

**What is Iterable**
Iterable is an object, which one can iterate over.
It generates an Iterator when passed to iter() method.

```py
# Example

L = [1,2,3]
type(L) # L is an iterable

type(iter(L)) # list_iterator

```

**Point to remember:**

- Every Iterator is also an Iterable
- Not all Iterables are Iterators like lists, tuples, sets, dictionaries, etc. (We can iterate over an iterable using `for` or `while` loops)
- Every Iterable has an **iter function** (use `dir()` to check)
- Every Iterator has both **iter function** as well as a **next function**
- `iter(iter(iterable))` returns the iterator itself (that is same address, use `id()` to check)

**How for loop actually works:**

```py
def mera_khudka_for_loop(iterable):
    
    iterator = iter(iterable)
    
    while True:
        
        try:
            print(next(iterator))
        except StopIteration:
            break 
```

**create our own range() function:**

```py
# iterable
class mera_range:

    def __init__(self,start,end):
        self.start = start
        self.end = end
        
    def __iter__(self):
        return mera_range_iterator(self)

# iterator
class mera_range_iterator:
    
    def __init__(self,iterable_obj):
        self.iterable = iterable_obj
    
    def __iter__(self):
        return self
    
    def __next__(self):
        
        if self.iterable.start >= self.iterable.end:
            raise StopIteration
            
        current = self.iterable.start
        self.iterable.start+=1
        return current

x = mera_range(1,11)
type(x) # __main__.mera_range
iter(x) # <__main__.mera_range_iterator at 0x2130fd362b0>
```

## Generators

Generators are a special type of iterator that allow you to create iterators in a more concise and readable way. They are defined using functions with the `yield` statement, which allows the function to return a value and pause its execution, resuming later from where it left off.

```python
# When the Python interpreter encounters a function with a yield keyword, it recognizes it as a generator function.
def gen_demo():
    
    yield "first statement"
    yield "second statement"
    yield "third statement"
gen = gen_demo() # calling this function doesn't immediately execute its code. Instead, it creates a generator object

# function's code isn't run until you start iterating over this generator object
for i in gen:
    print(i)
# first statement
# second statement
# third statement
```

- **First iteration:** The gen_demo() function starts executing. It runs until it hits the first yield "first statement". At this point, it pauses execution, returns "first statement" to the loop (which is then printed), and remembers its exact state (where it stopped, the values of local variables, etc.).
- **Second iteration:** The loop requests the next value from gen. The gen_demo() function resumes execution from where it left off (after the first yield). It then proceeds to the yield "second statement", pauses again, returns "second statement", and remembers its new state.
- **Third iteration:** Similarly, the function resumes, executes yield "third statement", pauses, returns the string, and remembers its state.
- **Subsequent iterations:** After the last yield, if the loop tries to get another value, the generator function simply finishes execution and implicitly raises a StopIteration error, signaling that there are no more items. The loop handles this gracefully, and the program continues.

**yield vs return:**

- A normal function (using `return`) executes completely once called, returns a single value, and then its local variables and state are cleared from memory.
- A generator function (using `yield`), on the other hand, can pause its execution multiple times using yield, return a value, and then retain its state (including local variable values) so that it can resume from that exact point when called again. This makes them highly efficient for processing large data streams as they don't need to load all data into memory at once.

```py
def square(num):
    for i in range(1,num+1):
        yield i**2
gen = square(10)

print(next(gen))
print(next(gen))
print(next(gen))

for i in gen:
    print(i)
# 1
# 4
# 9
# 16
# 25
# 36
# 49
# 64
# 81
# 100
```

**create our own range() function using generators:**

```py
def mera_range(start,end):
    
    for i in range(start,end):
        yield i
for i in mera_range(15,26):
    print(i)
# 15
# 16
# 17
# 18
# 19
# 20
# 21
# 22
# 23
# 24
# 25
```

**Generator Expression:**
Generator expressions are similar to list comprehensions but use parentheses instead of square brackets. They create a generator object that can be iterated over, yielding one item at a time.

```py
gen = (i**2 for i in range(1,101))

for i in gen:
    print(i)
```

**Uses:**

Using a generator to create an iterator allows for efficient processing of large datasets by only holding one item in memory at a time. This is particularly useful in machine learning and data science when working with massive datasets that exceed system RAM capacity.

```py
# Practical Example
import os
import cv2

def image_data_reader(folder_path):

    for file in os.listdir(folder_path):
        f_array = cv2.imread(os.path.join(folder_path,file))
        yield f_array
    
gen = image_data_reader('C:/Users/91842/emotion-detector/train/Sad')

next(gen) # This will read the first image and yield its NumPy array representation
# You can call next(gen) multiple times to read subsequent images one by one
next(gen)
```

Frameworks like `Keras` use similar "image data generators" which are essentially iterators, leveraging this exact principle.

**Benefits of using generators:**

1. **Ease of Implementation**

    ```py
    class mera_range:
        
        def __init__(self,start,end):
            self.start = start
            self.end = end
            
        def __iter__(self):
            return mera_iterator(self)
    # iterator
    class mera_iterator:
        
        def __init__(self,iterable_obj):
            self.iterable = iterable_obj
        
        def __iter__(self):
            return self
        
        def __next__(self):
            
            if self.iterable.start >= self.iterable.end:
                raise StopIteration
            
            current = self.iterable.start
            self.iterable.start+=1
            return current
    def mera_range(start,end):
        
        for i in range(start,end):
            yield i
    ```

2. **Memory Efficient**

    ```py
    L = [x for x in range(100000)]
    gen = (x for x in range(100000))

    import sys

    print('Size of L in memory',sys.getsizeof(L)) # Size of L in memory 824456
    print('Size of gen in memory',sys.getsizeof(gen)) # Size of gen in memory 112
    ```

3. **Representing Infinite Streams**

    ```py
    def all_even():
        n = 0
        while True:
            yield n
            n += 2
    even_num_gen = all_even()
    next(even_num_gen)
    next(even_num_gen) # 2
    ```

4. **Chaining Generators**

    ```py
    def fibonacci_numbers(nums):
        x, y = 0, 1
        for _ in range(nums):
            x, y = y, x+y
            yield x

    def square(nums):
        for num in nums:
            yield num**2

    print(sum(square(fibonacci_numbers(10)))) # 4895
    ```

## Magic or Dunder Methods

Magic methods, also known as dunder (double underscore) methods, are special methods in Python that allow you to define the behavior of your objects for built-in operations. They are prefixed and suffixed with double underscores (e.g., `__init__`, `__str__`, `__add__`, etc.).

```py
class Person:
    def __init__(self,name,age): # constructor
        self.name = name
        self.age = age

    def __del__(self): # destructor, e.g., del(p1)
        print(f"{self.name} is deleted")
        
    def __repr__(self): # for unambiguous representation, e.g., for developers, repr() or print()
        return f"Person({self.name}, {self.age})"

    def __str__(self): # for user-friendly display, e.g., str() or print()
        return f"{self.name} is {self.age} years old"
    
    def __add__(self,other): # +
        return self.age + other.age 

    # __sub__ (-), __mul__ (*), __truediv__ (/), etc.
    
    def __lt__(self,other): # >
        return self.age < other.age
    
    def __gt__(self,other): # <
        return self.age > other.age
    
    def __eq__(self,other): # ==
        return self.age == other.age

    # __ne__ (!=), __le__ (<=), __ge__ (>=)

    def __call__(self): # Allows the object to be called like a function like `p1()`
        return f"{self.name} is {self.age} years old"

    def __len__(self): # len()
        return self.age

    # __getitem__ (for [] access), __setitem__ (for [] assignment), __contains__ (for in operator)

    def __enter__(self): # for with statement
        print(f"Entering context for {self.name}")
        return self

    def __exit__(self, exc_type, exc_value, traceback): # for with statement
        print(f"Exiting context for {self.name}")
        if exc_type:
            print(f"An exception occurred: {exc_value}")
    
p1 = Person("Alice", 30)
p2 = Person("Bob", 25)

print(p1) # Alice is 30 years old
print(p1 + p2) # 55
```
