# Advanced Python Concepts

## `if` `__name__` `==` `"__main__"` in python

The `if` `__name__` `==` `"__main__"` idiom is a common pattern used in Python scripts to determine whether the script is being run directly or being imported as a module into another script.

In Python, the `__name__` variable is a built-in variable that is automatically set to the name of the current module. When a Python script is run directly, the `__name__` variable is set to the string `__main__` When the script is imported as a module into another script, the __name__ variable is set to the name of the module.

Here's an example of how the if `__name__ == __main__` idiom can be used:

```py
def main():
    # Code to be run when the script is run directly
    print("Running script directly")
if __name__ == "__main__":
    main()
```

In this example, the main function contains the code that should be run when the script is run directly. The if statement at the bottom checks whether the `__name__` variable is equal to `__main__`. If it is, the main function is called.

__Why is it useful?__

This idiom is useful because it allows you to reuse code from a script by importing it as a module into another script, without running the code in the original script. For example, consider the following script:

```py
def main():
    print("Running script directly")
if __name__ == "__main__":
    main()
```

If you run this script directly, it will output "Running script directly". However, if you import it as a module into another script and call the main function from the imported module, it will not output anything:

```py
import script
script.main()  # Output: "Running script directly"
```

This can be useful if you have code that you want to reuse in multiple scripts, but you only want it to run when the script is run directly and not when it's imported as a module.

__Is it a necessity?__

It's important to note that the if `__name__` == "`__main__`" idiom is not required to run a Python script. You can still run a script without it by simply calling the functions or running the code you want to execute directly. However, the if `__name__` == "`__main__`" idiom can be a useful tool for organizing and separating code that should be run directly from code that should be imported and used as a module.

In summary, the if `__name__` == "`__main__`" idiom is a common pattern used in Python scripts to determine whether the script is being run directly or being imported as a module into another script. It allows you to reuse code from a script by importing it as a module into another script, without running the code in the original script.

## Namespaces

A __namespace__ is a space that holds names(identifiers).Programmatically speaking, namespaces are dictionary of identifiers(keys) and their objects(values)

There are 4 types of namespaces:

- __Builtin Namespace (B)__ : Names pre-defined in Python (e.g., print, len, max). These are always available
- __Global Namespace (G)__ : Variables defined at the top-most level of a script or module. They are accessible throughout the entire script
- __Enclosing Namespace (E)__ : Variables defined in an enclosing (or outer) function. These are accessible in nested functions
- __Local Namespace (L)__ : Variables defined inside a function. They are accessible only within that function

### Scope and LEGB Rule

A __scope__ is a textual region of a Python program where a namespace is directly accessible.

The interpreter searches for a name from the inside out, looking in the local, enclosing, global, and finally the built-in scope. If the interpreter doesn’t find the name in any of these locations, then Python raises a NameError exception.

### Examples

__Local and Global Variables:__

```py
# global var
a = 2

def temp():
  # local var
  b = 3
  print(b) # Accessing local 'b'

temp() # Calls temp(), prints 3
print(a) # Accessing global 'a', prints 2
```

__Local and Global with Same Name (Shadowing):__

```py
a = 2 # Global 'a'

def temp():
  # local var
  a = 3 # Local 'a' (different from global 'a')
  print(b) # This line would cause a NameError because 'b' is not defined here
  print(a) # Accessing local 'a', prints 3

temp() # Calls temp(), prints 3
print(a) # Accessing global 'a', prints 2
```

__Local Does Not Have, but Global Has:__

```py
a = 2 # Global 'a'

def temp():
  # local var
  print(a) # Accessing global 'a'

temp() # Calls temp(), prints 2
print(a) # Accessing global 'a', prints 2
```

__Editing Global (Incorrect and Correct Approaches):__

```py
# Incorrect Way (Attempting to modify global without global keyword)
a = 2 # Global 'a'

def temp():
  # This tries to rebind 'a' locally, but also uses it before assignment
  a += 1 # This will cause an UnboundLocalError
  print(a)

# temp() # This call would raise UnboundLocalError
# print(a)


# Correct Way (Using global keyword):
a = 2 # Global 'a'

def temp():
  global a # Declares that 'a' refers to the global variable
  a += 1   # Modifies the global 'a'
  print(a)

temp() # Calls temp(), prints 3 (global 'a' becomes 3)
print(a) # Accessing modified global 'a', prints 3
```

__Global Created Inside Local:__

```py
# 'a' does not exist globally initially

def temp():
  global a # Declares that 'a' will be a global variable
  a = 1    # Creates the global variable 'a' and assigns 1 to it
  print(a) # Accessing the newly created global 'a', prints 1

temp() # Calls temp(), creates global 'a' and prints 1
print(a) # Accessing the global 'a', prints 1
```

__Function Parameter is Local:__

```py
def temp(z): # 'z' is a local parameter
  # local var
  print(z) # Accessing local 'z'

a = 5 # Global 'a'
temp(5) # Calls temp(), 'z' becomes 5 (local to temp)
print(a) # Accessing global 'a', prints 5
print(z) # This would cause a NameError because 'z' is local to temp()
```

__Built-in-Scope:__

- `builtins` is a module that contains all the pre-defined names in Python (functions like print, len, type, exceptions like NameError, etc.).
- `dir(builtins)` lists all the names available in the built-in scope. These names are accessible from anywhere in your code without explicit import, unless shadowed by a variable in a narrower scope.

```py
import builtins
print(dir(builtins))
```

__Renaming Built-ins (Shadowing Built-ins):__

```py
L = [1,2,3]
print(max(L)) # Uses the built-in max function, prints 3

def max(): # Creates a new function named 'max' in the global scope
  print('hello')

print(max(L)) # This would now cause a TypeError because the global 'max'
              # is now your function, not the built-in one, and your function
              # doesn't accept arguments.
```

__Enclosing Space:__

```py
a = 10 # Global 'a' (let's define it for clarity in this example)

def outer():
  # 'a' here refers to the global 'a' because there's no local 'a' in outer
  def inner():
    print(a) # Accessing 'a' from the enclosing (global) scope
  inner() # Calls inner(), prints 10
  print('outer function') # Prints 'outer function'

outer() # Calls outer()
print('main program') # Prints 'main program'
```

__`nonlocal` Keyword:__

The `nonlocal` keyword is used to declare that a variable is a nonlocal variable in a nested scope.

```py
def outer():
  a = 1 # 'a' in the enclosing scope of inner()
  def inner():
    nonlocal a # Declares that 'a' refers to 'a' in the nearest enclosing scope
    a += 1    # Modifies 'a' in the enclosing scope
    print('inner', a) # Prints 'inner 2'
  inner()
  print('outer', a) # Prints 'outer 2'

outer() # Calls outer()
print('main program') # Prints 'main program'
```

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

__What is an Iteration__
Iteration is a general term for taking each item of something, one after another. Any time you use a loop, explicit or implicit, to go over a group of items, that is iteration.

```py
# Example
num = [1,2,3]
for i in num:
    print(i)
# 1 2 3
```

__What is Iterator__
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

__What is Iterable__
Iterable is an object, which one can iterate over.
It generates an Iterator when passed to iter() method.

```py
# Example

L = [1,2,3]
type(L) # L is an iterable

type(iter(L)) # list_iterator

```

__Point to remember:__

- Every Iterator is also an Iterable
- Not all Iterables are Iterators like lists, tuples, sets, dictionaries, etc. (We can iterate over an iterable using `for` or `while` loops)
- Every Iterable has an __iter function__ (use `dir()` to check)
- Every Iterator has both __iter function__ as well as a __next function__
- `iter(iter(iterable))` returns the iterator itself (that is same address, use `id()` to check)

__How for loop actually works:__

```py
def mera_khudka_for_loop(iterable):
    
    iterator = iter(iterable)
    
    while True:
        
        try:
            print(next(iterator))
        except StopIteration:
            break 
```

__create our own range() function:__

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

- __First iteration:__ The gen_demo() function starts executing. It runs until it hits the first yield "first statement". At this point, it pauses execution, returns "first statement" to the loop (which is then printed), and remembers its exact state (where it stopped, the values of local variables, etc.).
- __Second iteration:__ The loop requests the next value from gen. The gen_demo() function resumes execution from where it left off (after the first yield). It then proceeds to the yield "second statement", pauses again, returns "second statement", and remembers its new state.
- __Third iteration:__ Similarly, the function resumes, executes yield "third statement", pauses, returns the string, and remembers its state.
- __Subsequent iterations:__ After the last yield, if the loop tries to get another value, the generator function simply finishes execution and implicitly raises a StopIteration error, signaling that there are no more items. The loop handles this gracefully, and the program continues.

__`yield` vs `return`:__

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

__create our own `range()` function using generators:__

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

__Generator Expression:__
Generator expressions are similar to list comprehensions but use parentheses instead of square brackets. They create a generator object that can be iterated over, yielding one item at a time.

```py
gen = (i**2 for i in range(1,101))

for i in gen:
    print(i)
```

__Uses:__

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

__Benefits of using generators:__

1. __Ease of Implementation__

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

2. __Memory Efficient__

    ```py
    L = [x for x in range(100000)]
    gen = (x for x in range(100000))

    import sys

    print('Size of L in memory',sys.getsizeof(L)) # Size of L in memory 824456
    print('Size of gen in memory',sys.getsizeof(gen)) # Size of gen in memory 112
    ```

3. __Representing Infinite Streams__

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

4. __Chaining Generators__

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

## Closures

A closure is a function that captures the local variables from its enclosing scope, allowing it to access those variables even when the function is called outside that scope. Closures are often used to create functions with persistent state.

```py
def fun1(x):
    # This is the outer function that takes an argument 'x'
    def fun2(y):
      
        # This is the inner function that takes an argument 'y'
        return x + y  # 'x' is captured from the outer function
    
    return fun2  # Returning the inner function as a closure

# Create a closure by calling outer_function
closure = fun1(10)

# Now, we can use the closure, which "remembers" the value of 'x' as 10
print(closure(5))
```

__How Closures Work Internally?__
When a closure is created, Python internally stores a reference to the environment (variables in the enclosing scope) where the closure was defined. This allows the inner function to access those variables even after the outer function has completed.
In simple terms, a closure "captures" the values from its surrounding scope and retains them for later use. This is what allows closures to remember values from their environment.

__Use of Closures:__

- __Encapsulation:__ Closures help encapsulate functionality. The inner function can access variables from the outer function, but those variables remain hidden from the outside world.
- __State Retention:__ Closures can retain state across multiple function calls. This is especially useful in situations like counters, accumulators, or when you want to create a function factory that generates functions with different behaviors.
- __Functional Programming:__ Closures are a core feature of functional programming. They allow you to create more flexible and modular code by generating new behavior dynamically.

## Decorators

A decorator in python is a function that receives another function as input and adds some functionality(decoration) to and it and returns it. Decorators are essentially syntactic sugar for wrapping one function with another. They are heavily reliant on closures.

This can happen only because python functions are 1st class citizens. They can be assigned to variables, passed as arguments to other functions, returned from functions, etc.

There are 2 types of decorators available in python

- Built in decorators like `@staticmethod`, `@classmethod`, `@abstractmethod` and `@property` etc
- User defined decorators that we programmers can create according to our needs

```py
def my_decorator(func):
  def wrapper():
    print('***********************')
    func()
    print('***********************')
  return wrapper

def hello():
  print('hello')

a = my_decorator(hello)
a()

# ***********************
# hello
# ***********************
```

__OR:__

```py
# Better syntax

def my_decorator(func):
  def wrapper():
    print('***********************')
    func()
    print('***********************')
  return wrapper

@my_decorator
def hello():
  print('hello')

hello()
```

---

### Decorators vs. Closures

At their core, __decorators are built upon closures__. A decorator is simply a function that returns a closure, where the inner function of that closure "closes over" the original function it's decorating.

__Similarities:__

- Both utilize __nested functions__.
- Both rely on the inner function retaining access to variables from its __enclosing scope__.
- Both are powerful tools in Python's __functional programming__ paradigm.

__Differences:__

| Feature   | Closure                                       | Decorator                                            |
| :-------- | :-------------------------------------------- | :--------------------------------------------------- |
| __Purpose__ | To retain state or configuration across calls | To add functionality to a function without modifying its source |
| __Input__ | Often takes data or configuration             | Always takes a function                              |
| __Output__ | Returns a function remembering its environment | Returns a new, wrapped version of the input function |
| __Usage__ | General-purpose pattern for data encapsulation | Specific design pattern for modifying function behavior |
| __Syntax__ | Explicit function call (`my_closure = outer(data)`) | Often uses the `@` syntactic sugar                 |

__When to Use Which?__

- __Use Closures:__
  - To create "factories" for customized functions (e.g., a length validator).
  - To encapsulate state that changes over time, especially when a full class isn't needed.

- __Use Decorators:__
  - To add __cross-cutting concerns__ like logging, timing, or authentication to multiple functions.
  - To enhance or modify function behavior without altering their original definition.
  - To improve code readability by separating core logic from auxiliary features.

---

### Examples of Decorators

```py
import time

def timer(func):
  def wrapper(*args): # *args allows passing any number of arguments to the function
    start = time.time()
    func(*args)
    print('time taken by',func.__name__,time.time()-start,'secs')
  return wrapper

@timer
def hello():
  print('hello world')
  time.sleep(2)

@timer
def square(num):
  time.sleep(1)
  print(num**2)

@timer
def power(a,b):
  print(a**b)

hello() # hello world   time taken by hello 2.003671884536743 secs
square(2) # 4   time taken by square 1.0009939670562744 secs
power(2,3) # 8  time taken by power 2.1696090698242188e-05 secs
```

Decorators with input arguments:

```py
def sanity_check(data_type):
  def outer_wrapper(func):
    def inner_wrapper(*args):
      if type(*args) == data_type:
        func(*args)
      else:
        raise TypeError('Ye datatype nai chalega')
    return inner_wrapper
  return outer_wrapper

@sanity_check(int)
def square(num):
  print(num**2)

@sanity_check(str)
def greet(name):
  print('hello',name)

square(2) # 4
```
