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

## Exception Handling

### Errors and Exceptions

There are 2 stages where error may happen in a program

- During compilation -> __Syntax Error__
- During execution -> __Exceptions__

#### Syntax Error

- Something in the program is not written according to the program grammar.
- Error is raised by the interpreter/compiler
- You can solve it by rectifying the program

__Example:__

```py
# Examples of syntax error
print 'hello world'

#   File "<ipython-input-3-4655b84ba7b7>", line 2
#     print 'hello world'
#                       ^
# SyntaxError: Missing parentheses in call to 'print'. Did you mean print('hello world')?
```

__Other examples of syntax error:__

- Leaving symbols like colon, brackets (`SyntaxError`)
- Misspelling a keyword (`SyntaxError`)
- Incorrect indentation (`IndentationError`)
- empty if/else/loops/class/functions block (`IndentationError`)
- __IndexError__: Raised when trying to access an item at an invalid index.  
  Example: `L = [1, 2, 3]; L[100]`  
  Output: `IndexError: list index out of range`
- __ModuleNotFoundError__: Raised when a module could not be found.  
  Example: `import mathi; math.floor(5.3)`  
  Output: `ModuleNotFoundError: No module named 'mathi'`
- __KeyError__: Raised when a dictionary key is not found.  
  Example: `d = {'name': 'nitish'}; d['age']`  
  Output: `KeyError: 'age'`
- __TypeError__: Raised when an operation or function is applied to an object of inappropriate type.  
  Example: `1 + 'a'`  
  Output: `TypeError: unsupported operand type(s) for +: 'int' and 'str'`
- __ValueError__: Raised when a function receives an argument of inappropriate type.  
  Example: `int('a')`  
  Output: `ValueError: invalid literal for int() with base 10: 'a'`
- __NameError__: Raised when a local or global name is not found.  
  Example: `print(k)`  
  Output: `NameError: name 'k' is not defined`
- __AttributeError__: Raised when an invalid attribute reference or assignment is attempted.  
  Example: `L = [1, 2, 3]; L.upper()`  
  Output: `AttributeError: 'list' object has no attribute 'upper'`
- __ZeroDivisionError__: Raised when division or modulo by zero is attempted.  
  Example: `5 / 0`  
  Output: `ZeroDivisionError: division by zero`

#### Exceptions

If things go wrong during the execution of the program(runtime). It generally happens when something unforeseen has happened.

- Exceptions are raised by python runtime
- You have to takle it on the fly
- Examples:
  - Memory overflow
  - Divide by 0 -> logical error
  - Database error

#### Why handle exceptions?

When Python encounters an error, it raises an exception and provides a __stack trace__, which is useful for debugging. However, there are two reasons why you should handle exceptions:

1. __User Experience__: If an exception is raised and not handled, it can lead to a bad user experience. The user may see a confusing error message or the application may crash, which can be frustrating and make the user less likely to use the application again.
2. __Security__: If an exception is raised and not handled, it can also reveal sensitive information about the application, such as the code that caused the error, which can be used by malicious users to exploit the application. By handling exceptions, you can prevent this information from being exposed and keep your application secure.

### `try` and `except` block

When an error occurs, or exception as we call it, Python will normally stop and generate an error message.
These exceptions can be handled using the `try` statement. If the `try` block raises an error, the `except` block will be executed.

```py
# try catch demo
try:
  with open('sample1.txt','r') as f:
    print(f.read())
except:
  print('sorry file not found')

# sorry file not found
```

__Many Exceptions:__

But this way, we are not able to know what kind of error has occurred. We can handle specific exceptions using the `except` block. We can define as many exception blocks as you want, e.g. if we want to execute a special block of code for a special kind of error.

```py
try:
  m=5
  f = open('sample1.txt','r')
  print(f.read())
  print(m)
  print(5/2)
  L = [1,2,3]
  L[100]
except FileNotFoundError:
  print('file not found')
except NameError:
  print('variable not defined')
except ZeroDivisionError:
  print("can't divide by 0")

# A generic except for other unhandled exceptions, must be at the end
except Exception as e: # Catches all other exceptions
  print(e) # prints the error message

# [Errno 2] No such file or directory: 'sample1.txt'
```

__`else`__

If the `try` block does not raise any exceptions, the `else` block will be executed. For example, if you want to run a piece of code if a file is found, but do something else if the file is not found.

```py
try:
    # write what you think may wrong
  print("Hello")
except:
    # use it to handle what may go wrong in try block
  print("Something went wrong")
else:
    # write what should be done if there is no error raised by try block
  print("Nothing went wrong")
```

__finally:__

The `finally` block, if specified, will be executed regardless if the try block raises an error or not. This is useful for closing files, database connections and other resources that should always be closed after use.

```py
try:
  f = open('sample1.txt','r')
except FileNotFoundError:
  print('file nai mili')
except Exception:
  print('kuch to lafda hai')
else:
  print(f.read())
finally:
  print('ye to print hoga hi')
```

### `raise` Exceptions

In Python programming, exceptions are raised when errors occur at runtime. We can also manually raise exceptions using the `raise` keyword. We can optionally pass values to the exception to clarify why that exception was raised.
Example: `raise ZeroDivisionError('aise hi try kar raha hu')` -> Output: `ZeroDivisionError: aise hi try kar raha hu`

```py
class Bank:

  def __init__(self,balance):
    self.balance = balance

  def withdraw(self,amount):
    if amount < 0:
      raise Exception('amount cannot be -ve')
    if self.balance < amount:
      raise Exception('paise nai hai tere paas')
    self.balance = self.balance - amount

obj = Bank(10000)
try:
  obj.withdraw(15000)
except Exception as e:
  print(e)
else:
  print(obj.balance)

# paise nhi hai tere paas
```

### Custom Exception

An exception class in Python is a blueprint for creating objects that represent errors or exceptional events that occur during program execution. When such an event happens, an "exception is raised," interrupting the normal flow of the program. If not handled, this can lead to the program crashing.

- All exceptions (like `ValueError`, `ModuleNotFoundError`, etc.) in Python are classes.
- Most inherit from a base class called `Exception`.
- Fundamental errors (e.g., `SystemExit`, `KeyboardInterrupt`) inherit from `BaseException`.

While Python offers many built-in exceptions (e.g., `ValueError`, `TypeError`, `KeyError`), there are cases where custom exceptions are necessary for handling unique error conditions specific to your application.

__Why Use Custom Exceptions?__

- __Clarity:__ Provide clear, specific error messages relevant to your application.
- __Granularity:__ Allow fine-grained error handling, making it easier to pinpoint issues.
- __Reusability:__ Can be reused across different parts of your application or projects.
- __Encapsulation:__ Can carry specific data (e.g., an AuthenticationError might include a user_id).
- __API Design:__ Essential for libraries/APIs, giving users a structured way to handle failures.
- __Separation of Concerns:__ Helps separate error-handling logic from business logic.

__Benefits:__

- Improves code readability and maintainability.
- Facilitates easier debugging by handling application-specific errors.

__Create a Custom Exception:__

To create a custom exception, you define a new class that inherits from the built-in `Exception` class. You can also add custom attributes or methods to provide additional context or functionality.

```py
class SecurityError(Exception):
    def __init__(self, message):
        print(message)
    
    def logout(self):
        print('logout')

class AuthenticationError(Exception):
    def __init__(self, message="Invalid credentials"):
        self.message = message
        super().__init__(self.message)
    
    def suggest_reset(self):
        print("Try password reset or contact support")

class Google:
    def __init__(self, name, email, password, device):
        self.name = name
        self.email = email
        self.password = password
        self.device = device

    def login(self, email, password, device):
        if device != self.device:
            raise SecurityError('bhai teri to lag gayi')
        if email == self.email and password == self.password:
            print('welcome')
        else:
            raise AuthenticationError('Invalid email or password')

obj = Google('nitish', 'nitish@gmail.com', '1234', 'android')

try:
    obj.login('nitish@gmail.com', 'wrongpass', 'android')
except SecurityError as e:
    e.logout()
except AuthenticationError as e:
    print(e)
    e.suggest_reset()
else:
    print(obj.name)
finally:
    print('database connection closed')
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

## Argument Parsing

Argument parsing is the process of handling command-line arguments passed to a Python script. This allows users to provide input parameters when running the script, enabling dynamic behavior based on user input.

### `*args` and `**kwargs`

In Python, `*args` and `**kwargs` are used to allow functions to accept an arbitrary number of arguments. These features provide great flexibility when designing functions that need to handle a varying number of inputs.

Passing arguments in Python:

- `*args` (Non-Keyword Arguments)
  - Used to pass a variable number of arguments to a function. It is used to pass a non-keyworded, variable-length argument list.
  - For example, we want to make a multiply function that takes any number of arguments and is able to multiply them all together. It can be done using *args.
  - Using `*` the variable that we associate with the `*` becomes iterable, meaning you can do things like iterate over it, run some higher-order functions such as map and filter, etc.
  - Example:

    ```py
    def fun(arg1, *argv):
        print("First argument :", arg1)
        for arg in argv:
            print("Argument *argv :", arg)


    fun('Hello', 'Welcome', 'to', 'GeeksforGeeks')
    # First argument : Hello
    # Argument *argv : Welcome
    # Argument *argv : to
    # Argument *argv : GeeksforGeeks
    ```

- `**kwargs` (Keyword Arguments)
  - Used to pass a variable length argument list. We use the name kwargs with the double star `**`.
  - A keyword argument is where you provide a name to the variable as you pass it into the function.
  - It collects all the additional keyword arguments passed to the function and stores them in a dictionary.
  - Example:

    ```py
    def fun(arg1, **kwargs):
        for k, val in kwargs.items():
            print("%s == %s" % (k, val))

    # Driver code
    fun("Hi", s1='Geeks', s2='for', s3='Geeks')
    # s1 == Geeks
    # s2 == for
    # s3 == Geeks
    ```

- Using both `*args` and `**kwargs`:

    ```py
    def print_stuff(main_item, *extra_items, **formatting_options):
        """
        Prints a main item, optional extra items, with customizable formatting.
        """
        separator = formatting_options.get('sep', ' ') # Get separator, default to space
        end_char = formatting_options.get('end', '\n') # Get end char, default to newline
        prefix = formatting_options.get('prefix', '') # Get prefix, default to empty

        output = [str(main_item)] + [str(item) for item in extra_items]
        final_string = prefix + separator.join(output) + end_char
        print(final_string, end='') # Use end='' because we already added end_char

    print_stuff("Hello", "World", "Python")
    # Output: Hello World Python

    print_stuff("Numbers:", 1, 2, 3, sep=" - ", prefix="Data: ")
    # Output: Data: Numbers: - 1 - 2 - 3

    print_stuff("Error!", level="CRITICAL", end="!!!\n") # 'level' is ignored unless handled
    # Output: Error!!!
    ```

### Command Line Argument Parsing in Python

Command-line arguments are inputs provided to a program directly in the operating system's shell when it's executed. Python offers built-in modules to efficiently handle these arguments, making your scripts more flexible and powerful. The two primary methods are `sys.argv` for simple positional arguments and `getopt` for more complex options and flags.

### Basic Arguments with `sys.argv`

The `sys` module provides access to command-line arguments through the `sys.argv` list.

- `sys.argv[0]` always holds the name of the script being executed.
- `sys.argv[1]`, `sys.argv[2]`, and so on, contain the arguments passed after the script name, treated as strings.

__Example Usage:__

```python
# myscript.py
import sys

# Get total number of arguments
num_args = len(sys.argv)
print("Total arguments passed:", num_args)

# Print script name
print("Script name:", sys.argv[0])

# Print all positional arguments
print("Arguments passed:", end=" ")
for i in range(1, num_args):
    print(sys.argv[i], end=" ")

# Example: Summing integer arguments
total_sum = 0
for i in range(1, num_args):
    try:
        total_sum += int(sys.argv[i])
    except ValueError:
        print(f"\nWarning: '{sys.argv[i]}' is not a valid number. Skipping.")
        continue
print("\nSum of numbers:", total_sum)
```

__Running the example in your terminal:__

```bash
geeks@GFGLTTCE0026:~/Desktop$ python3 myscript.py 2 3 5 6
Total arguments passed: 5
Script name: myscript.py
Arguments passed: 2 3 5 6
Sum of numbers: 16
```

__Limitation:__ `sys.argv` is straightforward for simple positional arguments. It lacks built-in support for parsing optional flags (e.g., `-o`, `--output`) or validating argument types without manual checks.

### Handling Options and Flags with `getopt`

The `getopt` module is designed for parsing command-line options that begin with hyphens (`-` for short options, `--` for long options). It helps define which options are expected and whether they require a value.

__Key Features:__

- Parses short options (e.g., `-f`, `-m`) and long options (e.g., `--filename`, `--message`).
- Allows specifying if an option expects an associated value (e.g., `-f value`).

__Example Usage:__

If you execute `python3 your_script.py -f results.txt --message "Hello World"`

```python
import getopt
import sys

# Set default values for optional arguments
file_name = "default.txt"
message = "Default message"
verbose = False # Example for a flag that doesn't take a value

try:
    # `sys.argv[1:]` excludes the script name itself
    # "f:m:v" -> 'f' and 'm' expect a value (indicated by ':'), 'v' is a boolean flag
    # ["filename=", "message=", "verbose"] -> Long options; '=' indicates value required
    opts, args = getopt.getopt(sys.argv[1:], "f:m:v", ["filename=", "message=", "verbose"])
except getopt.GetoptError:
    # Error handling for incorrect usage
    print("Usage: your_script.py [-f <filename>] [-m <message>] [-v]")
    sys.exit(2)

# Process the parsed options
for opt, arg in opts:
    if opt in ("-f", "--filename"):
        file_name = arg
    elif opt in ("-m", "--message"):
        message = arg
    elif opt in ("-v", "--verbose"):
        verbose = True # Set flag to True if -v or --verbose is present

print(f"File Name: {file_name}")
print(f"Message: {message}")
print(f"Verbose mode: {verbose}")
print(f"Remaining positional arguments: {args}") # Any arguments not parsed as options
```

__Running the example in your terminal:__

```bash
geeks@GFGLTTCE0026:~/Desktop$ python3 your_script.py -f my_output.log -m "Custom content" -v
File Name: my_output.log
Message: Custom content
Verbose mode: True
Remaining positional arguments: []

geeks@GFGLTTCE0026:~/Desktop$ python3 your_script.py --filename report.csv some_extra_arg
File Name: report.csv
Message: Default message
Verbose mode: False
Remaining positional arguments: ['some_extra_arg']
```

#### Using `argparse` module

Using argparse module is a better option than the above two options as it provides a lot of options such as positional arguments, default value for arguments, help message, specifying data type of argument etc.

## Serialization and Deserialization

- __Serialization__ - process of converting python data types to `JSON` format
- __Deserialization__ - process of converting `JSON` to python data types

### JSON

We have learned a bit about `JSON` files in these links:

- [ml/ml_proj/ml_5.md](https://github.com/amansingh2116/tech_stack/blob/main/ml/ml_proj/ml_5.md)
- [ml/python/pandas.md](https://github.com/amansingh2116/tech_stack/blob/main/ml/python/pandas.md)

`JSON` (JavaScript Object Notation) is a lightweight data format for data exchange. `JSON` is easy to read and write for humans, and easy to parse and generate for machines. It is language-independent, meaning it can be used across different programming languages.
In Python you have the built-in `json` module for encoding and decoding JSON data. Simply import it and you are ready to work with `JSON` data: `import json`

__Some advantages of JSON:__
`JSON` exists as a "sequence of bytes" which is very useful in the case we need to transmit (stream) data over a network. - Compared to XML, `JSON` is much smaller, translating into faster data transfers, and better experiences. - `JSON` is extremely human-friendly since it is textual, and simultaneously machine-friendly.

```json
{
    "firstName": "Jane",
    "lastName": "Doe",
    "hobbies": ["running", "swimming", "singing"],
    "age": 28,
    "children": [
        {
            "firstName": "Alex",
            "age": 5
        },
        {
            "firstName": "Bob",
            "age": 7
        }
    ]
}
```

JSON supports primitive types __(strings, numbers, boolean)__, as well as __nested arrays__ and __objects__.
Simple Python objects are translated to JSON according to the following conversion:

| Python   | JSON     |
|----------|----------|
| dict     | object   |
| list, tuple | array   |
| str      | string   |
| int, long, float | number |
| True     | true     |
| False    | false    |
| None     | null     |

### Serialization

To convert Python objects to JSON format, you can use the `json.dumps()` method for strings.

```python
import json

person = {"name": "John", "age": 30, "city": "New York", "hasChildren": False, "titles": ["engineer", "programmer"]}

# convert into JSON:
person_json = json.dumps(person)
# use different formatting style
person_json2 = json.dumps(person, indent=4, separators=("; ", "= "), sort_keys=True)

# the result is a JSON string:
print(person_json) 
print(person_json2)

# {"name": "John", "age": 30, "city": "New York", "hasChildren": false, "titles":["engineer", "programmer"]}
# {
#     "age"= 30; 
#     "city"= "New York"; 
#     "hasChildren"= false; 
#     "name"= "John"; 
#     "titles"= [
#         "engineer"; 
#         "programmer"
#     ]
# }
```

Or convert Python objects into JSON objects and save them into a file with the `json.dump()` method.

```python
import json

person = {"name": "John", "age": 30, "city": "New York", "hasChildren": False, "titles": ["engineer", "programmer"]}

with open('person.json', 'w') as f:
    json.dump(person, f) # you can also specify indent etc...
```

### Deserialization

To convert JSON strings back into Python objects, you can use the `json.loads()` method for strings.

```python
import json
person_json = """
{
    "age": 30, 
    "city": "New York",
    "hasChildren": false, 
    "name": "John",
    "titles": [
        "engineer",
        "programmer"
    ]
}
"""
person = json.loads(person_json)
print(person)
# {'age': 30, 'city': 'New York', 'hasChildren': False, 'name': 'John', 'titles': ['engineer', 'programmer']}
```

Or read JSON objects from a file and convert them into Python objects with the `json.load()` method.

```python
import json

with open('person.json', 'r') as f:
    person = json.load(f)
    print(person)

# {'name': 'John', 'age': 30, 'city': 'New York', 'hasChildren': False, 'titles': ['engineer', 'programmer']}
```

### Working with Custom Objects

Encoding a custom object with the default `JSONEncoder` will raise a TypeError. We can specify a custom encoding function that will store the class name and all object variables in a dictionary. Use this function for the default argument in the `json.dump()` method.

```python
class Person:

  def __init__(self,fname,lname,age,gender):
    self.fname = fname
    self.lname = lname
    self.age = age
    self.gender = gender

# format to printed in
# -> Nitish Singh age -> 33 gender -> male

person = Person('Nitish','Singh',33,'male')

# As a string
import json

def show_object(person):
  if isinstance(person,Person):
    return "{} {} age -> {} gender -> {}".format(person.fname,person.lname,person.age,person.gender)

with open('demo.json','w') as f:
  json.dump(person,f,default=show_object)
# "Nitish Singh age -> 33 gender -> male"

# As a dict
import json

def show_object(person):
  if isinstance(person,Person):
    return {'name':person.fname + ' ' + person.lname,'age':person.age,'gender':person.gender}

with open('demo.json','w') as f:
  json.dump(person,f,default=show_object,indent=4) # indent is optional, it just makes the output more readable
# {
#     "name": "Nitish Singh",
#     "age": 33,
#     "gender": "male"
# }
```

### Template encode and decode functions

This works for all custom classes if all class variables are given in the `__init__` method.

```py
class User:
    # Custom class with all class variables given in the __init__()
    def __init__(self, name, age, active, balance, friends):
        self.name = name
        self.age = age
        self.active = active
        self.balance = balance
        self.friends = friends

class Player:
    # Other custom class
    def __init__(self, name, nickname, level):
        self.name = name
        self.nickname = nickname
        self.level = level


def encode_obj(obj):
    """
    Takes in a custom object and returns a dictionary representation of the object.
    This dict representation also includes the object's module and class names.
    """

    #  Populate the dictionary with object meta data 
    obj_dict = {
      "__class__": obj.__class__.__name__,
      "__module__": obj.__module__
    }

    #  Populate the dictionary with object properties
    obj_dict.update(obj.__dict__)

    return obj_dict


def decode_dct(dct):
    """
    Takes in a dict and returns a custom object associated with the dict.
    It makes use of the "__module__" and "__class__" metadata in the dictionary
    to know which object type to create.
    """
    if "__class__" in dct:
        # Pop ensures we remove metadata from the dict to leave only the instance arguments
        class_name = dct.pop("__class__")

        # Get the module name from the dict and import it
        module_name = dct.pop("__module__")

        # We use the built in __import__ function since the module name is not yet known at runtime
        module = __import__(module_name)

        # Get the class from the module
        class_ = getattr(module,class_name)

        # Use dictionary unpacking to initialize the object
        # Note: This only works if all __init__() arguments of the class are exactly the dict keys
        obj = class_(**dct)
    else:
        obj = dct
    return obj

# User class works with our encoding and decoding methods
user = User(name = "John",age = 28, friends = ["Jane", "Tom"], balance = 20.70, active = True)

userJSON = json.dumps(user,default=encode_obj,indent=4, sort_keys=True)
print(userJSON)

user_decoded = json.loads(userJSON, object_hook=decode_dct)
print(type(user_decoded))

# Player class also works with our custom encoding and decoding
player = Player('Max', 'max1234', 5)
playerJSON = json.dumps(player,default=encode_obj,indent=4, sort_keys=True)
print(playerJSON)

player_decoded = json.loads(playerJSON, object_hook=decode_dct)
print(type(player_decoded))

'''
{
    "__class__": "User",
    "__module__": "__main__",
    "active": true,
    "age": 28,
    "balance": 20.7,
    "friends": [
        "Jane",
        "Tom"
    ],
    "name": "John"
}
<class '__main__.User'>
{
    "__class__": "Player",
    "__module__": "__main__",
    "level": 5,
    "name": "Max",
    "nickname": "max1234"
}
<class '__main__.Player'>
'''
```

### Limitation of JSON

- JSON does not support all Python data types. For example, it cannot directly represent Python tuples, sets, or custom objects.
- JSON does not support comments, which can make it less readable for complex configurations.
- JSON is not a self-describing format, which means it is not easily readable by machines. For that we can use python's `pickle` module, which can serialize and deserialize Python objects, including complex data types like tuples, sets, and custom classes.
- __Pickling__ is the process whereby a Python object hierarchy is converted into a byte stream, and unpickling is the inverse operation, whereby a byte stream (from a binary file or bytes-like object) is converted back into an object hierarchy.
- Pickle lets the user to store data in binary format. JSON lets the user store data in a human-readable text format.

### jsonpickle module

- jsonpickle is a Python library that provides a way to serialize and deserialize Python objects to and from JSON.
- It supports serializing and deserializing arbitrary Python objects, including tuples, sets, and custom objects.
- While using json module, we need to define a custom encoding function for custom objects, but jsonpickle handles this automatically.

```python
import jsonpickle # Import the jsonpickle library for serialization/deserialization

# Define the Employee class
class Employee:
    # Constructor method (__init__) to initialize Employee objects
    # It takes employee number (eno), name (ename), salary (esal),
    # address (eaddr), and marital status (isMarried) as arguments.
    def __init__(self, eno, ename, esal, eaddr, isMarried):
        self.eno = eno
        self.ename = ename
        self.esal = esal
        self.eaddr = eaddr
        self.isMarried = isMarried

    # Method to display employee details
    def display(self):
        print(f'ENO: {self.eno}, ENAME: {self.ename}, ESAL: {self.esal}, '
              f'EADDR: {self.eaddr}, Is Married: {self.isMarried}')

# Create an instance of the Employee class
e = Employee(100, 'Durga', 1000.0, 'Hyderabad', True)

print("--- Original Employee Object ---")
e.display()
print("\n")

# --- Serialization to JSON string ---
# jsonpickle.encode() converts a Python object (e) into a JSON string.
# It automatically handles custom classes by adding a "py/object" key
# to store the class path, allowing for proper deserialization later.
json_string = jsonpickle.encode(e)
print("--- Serialized JSON String ---")
print(json_string)
print("\n")

# --- Serialization to JSON file ---
# Open a file named 'emp.json' in write mode ('w').
# The 'with' statement ensures the file is properly closed after writing.
with open('emp.json', 'w') as f:
    # Write the generated JSON string to the file.
    f.write(json_string)
print("--- Object serialized to 'emp.json' ---")
print("\n")

# --- Deserialization from JSON string ---
# jsonpickle.decode() converts a JSON string back into a Python object.
# It uses the "py/object" information to reconstruct the original class instance.
e2 = jsonpickle.decode(json_string)
print("--- Deserialized Object from JSON String ---")
# Verify the type of the deserialized object
print(f"Type of deserialized object (e2): {type(e2)}")
# Call the display method on the deserialized object to show its contents
e2.display()
print("\n")

# --- Deserialization from JSON file ---
# Open the 'emp.json' file in read mode ('r').
with open('emp.json', 'r') as f:
    # Read the entire JSON string from the file.
    file_json_string = f.readline() # Use readline() as it's a single line JSON string

# Decode the JSON string read from the file back into a Python object.
e3 = jsonpickle.decode(file_json_string)
print("--- Deserialized Object from JSON File ---")
# Call the display method on the deserialized object
e3.display()
```

## Type Hints and Annotations

__Note__ that type hints and annotations are not enforced at runtime, they are just hints to the developer and static type checkers. They help with code readability and can be checked by static type checkers like `mypy`. They __do not speed__ up your program.

### Annotations

__Annotations__ can be added to variables, functions, and classes using the `: type` syntax. They are a way to provide hints about the expected types of variables and function parameters, but they do not enforce type checking at runtime. Annotations are primarily used for documentation purposes and can be checked by static type checkers like `mypy` (`mypy python_script.py`).

__Variable annotations__ are used to specify the expected type of a variable, making the code more readable and helping with static type checking.
Example: `x: int = 10`, `name: str = "Alice"`, `data: List[int] = [1, 2, 3]`, etc.

__Function Annotations__ are used to specify the expected types of function arguments and return values. This helps with code readability and allows for static type checking.
Example:

```python
def greet(name: str, age: int) -> str:
    """Return a greeting message for a user based on their name and age.

    Args:
        name (str): The name of the user.
        age (int): The age of the user.

    Returns:
        str: A greeting message for the user.
    """
    return f"Hello {name}, you are {age} years old."

print(greet("John", 30))  # Hello John, you are 30 years old.

def add(a: int, b: int) -> None: # It is not necessary to specify return type as None if the function does not return anything. But it increases readability.
    """Add two numbers without returning the result.

    Args:
        a (int): The first number.
        b (int): The second number.
    """
    print(a + b)

add(4, 5)  # 9
```

__Class annotations__ are used to specify the expected types of class attributes. This helps with code readability and allows for static type checking.

```py
class Person:
    """A simple class example."""

    name: str
    age: int

    def __init__(self, name: str, age: int) -> None:
        """Initialize a new Person object.

        Args:
            name (str): The name of the person.
            age (int): The age of the person.
        """
        self.name = name
        self.age = age

    def __str__(self) -> str:
        """Return a string representation of the Person object.

        Returns:
            str: A string representation of the Person object.
        """
        return f"Person(name={self.name}, age={self.age})"

p: Person = Person("John", 30) # Not necessary to specify type of p as Person, but it increases readability.
print(p)  # Person(name=John, age=30)
```

### Type Hints

__Type hints__ are used to specify the expected type of a variable, function, or class. They help with code readability and static type checking. Type hints are more powerful than annotations because they can be used to specify more complex types such as `list[list[int]]`, which is not possible with annotations. Furthermore, type hints can be used to specify the type of a variable even if it is not explicitly assigned a value. This can be useful when the type of a variable is not immediately obvious from the code, such as when a variable is assigned a value from a function call.
We need to import the `typing` module to use type hints for complex types like lists, dictionaries, and tuples.

__Variable annotations:__

```python
from typing import List, Dict, Set

x: List[List[int]] = [[1, 2], [3, 431, 4]]
y: Dict[str, float] = {"pi": 3.14, "e": 2.718}
z: Set[bool] = {True, False}
```

__Function annotations:__

```python
from typing import List, Dict, Set

def process_data(data: List[int]) -> Dict[str, float]:
    """Process a list of integers and return a dictionary with statistics."""
    total = sum(data)
    count = len(data)
    average = total / count if count > 0 else 0.0
    return {"total": total, "average": average}

print(process_data([1, 2, 3, 4, 5])) # {'total': 15, 'average': 3.0}
```

```py
from typing import List, Dict, Set, Union

# --- Type Aliases for Readability ---

# A 'Record' is a dictionary with string keys and values that can be a string or an integer.
Record = Dict[str, Union[str, int]]

# A 'Dataset' is a list of Records.
Dataset = List[Record]

# A 'UniqueIDs' is a set of integers.
UniqueIDs = Set[int]

# --- Function with Type Hints ---

def process_data(data: Dataset) -> UniqueIDs:
    """
    Takes a list of records and returns a set of unique integer IDs found within them.
    Assumes each record has an 'id' key.
    """
    found_ids: UniqueIDs = set() # Initialize an empty set with type hint
    for record in data:
        record_id = record.get('id') # Safely get the 'id' key
        if isinstance(record_id, int): # Ensure the ID is an integer
            found_ids.add(record_id)
    return found_ids

# --- Example Usage ---

# Sample data conforming to the 'Dataset' type
my_dataset: Dataset = [
    {'id': 101, 'name': 'Alpha'},
    {'id': 102, 'name': 'Beta', 'status': 'active'},
    {'id': 101, 'name': 'Gamma'}, # Duplicate ID
    {'id': 103, 'name': 'Delta', 'value': 42},
    {'id': 'not_an_int_id', 'name': 'Invalid'} # This ID will be ignored
]

# Process the data and get unique IDs
unique_ids_result = process_data(my_dataset)

print(f"Original Data: {my_dataset}")
print(f"Unique IDs found: {unique_ids_result}")
# Expected Output: Unique IDs found: {101, 102, 103}
```

### More functions of Type Hints

#### Optional

The `Optional` type hint is used to indicate that a variable or function parameter can either be of a specific type or `None`. It is a shorthand for `Union[type, None]`.

```python
from typing import Optional

def greet(name: str, age: Optional[int] = None) -> str:
    """
    Greets a person. Age is optional.
    """
    if age is not None: # Check if age was provided
        return f"Hello, {name}! You are {age} years old."
    else:
        return f"Hello, {name}!"

# --- Example Usage ---
print(greet("Alice"))          # Output: Hello, Alice!
print(greet("Bob", age=30))    # Output: Hello, Bob! You are 30 years old.
```

#### Any

The `Any` type hint is used when you want to allow a variable or function parameter to accept any type of value. It is useful when you don't know the specific type in advance or when the type can vary widely.

```python
from typing import Any

def process_flexible_data(input_data: Any) -> Any:
    """
    Takes any type of input and returns a modified version (could be any type).
    """
    if isinstance(input_data, str):
        return input_data.upper() + "!"
    elif isinstance(input_data, (int, float)):
        return input_data * 2
    else:
        return "Unsupported data type."

# --- Example Usage ---
print(process_flexible_data("hello"))  # Output: HELLO!
print(process_flexible_data(10))       # Output: 20
print(process_flexible_data([1, 2]))   # Output: Unsupported data type.
```

#### Sequence

The `Sequence` type hint is used to indicate that a variable or function parameter is expected to be a sequence type, such as a str, list or tuple, but you don't care about the specific type of sequence, only that it can be iterated and indexed.

```python
from typing import Sequence, Union

def calculate_total(numbers: Sequence[Union[int, float]]) -> float:
    """
    Calculates the sum of numbers from any sequence (list, tuple, etc.).
    """
    total = 0.0
    for num in numbers:
        total += num
    return total

# --- Example Usage ---
my_list = [10, 20, 30.5]
my_tuple = (5, 15)
my_range = range(1, 4) # 1, 2, 3

print(f"Total from list: {calculate_total(my_list)}")     # Output: Total from list: 60.5
print(f"Total from tuple: {calculate_total(my_tuple)}")   # Output: Total from tuple: 20.0
print(f"Total from range: {calculate_total(my_range)}")   # Output: Total from range: 6.0
```

#### Callable

The `Callable` type hint is used to indicate that a variable or function parameter is expected to be a callable object, such as a function or a method. You can specify the types of the arguments and the return type of the callable.

__Syntax:__ `Callable[[ArgType1, ArgType2, ...], ReturnType]`

```python
from typing import Callable, List

# This function expects a 'processor' function that takes one string and returns a string.
def apply_string_processor(
    texts: List[str],
    processor: Callable[[str], str] # The 'processor' must take a str, and return a str
) -> List[str]:
    """
    Applies a given string processing function to each text in a list.
    """
    return [processor(text) for text in texts]

# --- Example Usage ---

# Define some functions that match the Callable signature: (str) -> str
def to_uppercase(s: str) -> str:
    return s.upper()

def add_exclamation(s: str) -> str:
    return s + "!"

# Use a lambda function, which also matches the Callable signature
remove_spaces = lambda s: s.replace(" ", "")

my_texts = ["hello world", "python is fun", "type hints"]

# Apply different processors using the same `apply_string_processor` function
uppercased_texts = apply_string_processor(my_texts, to_uppercase)
print(f"Uppercased: {uppercased_texts}")

exclaimed_texts = apply_string_processor(my_texts, add_exclamation)
print(f"Exclaimed: {exclaimed_texts}")

no_space_texts = apply_string_processor(my_texts, remove_spaces)
print(f"No Spaces: {no_space_texts}")

# If you tried to pass a function with a mismatching signature,
# a type checker would warn you (e.g., a function expecting an int, or returning an int).
# def bad_processor(x: int) -> str: return str(x)
# apply_string_processor(my_texts, bad_processor) # MyPy error
```

#### tuple

A tuple in Python can be used in two main ways regarding type hinting:

- __Variable-length Tuple (Homogeneous Elements)__
    The syntax is `Tuple[ElementType, ...]` (using an ellipsis `...`).
    This represents a tuple of any length, where all elements are of the same specified type. This is similar to `List[ElementType]`, but for tuples.
    For example, `Tuple[int, ...]` means `(1, 2, 3)` or `(5,)` or `()`, where all elements are integers.

- __Fixed-length Tuple (Heterogeneous or Homogeneous Elements)__
    The syntax is `Tuple[ElementType1, ElementType2, ..., ElementTypeN]`.
    This represents a tuple with an exact, fixed length, where each position has its own specific data type.
    __Why specify each element?__ Because tuples of fixed length are often used to return or represent a specific "record" or "set of distinct values" where the meaning and type of each item depend on its position. Static type checkers (like MyPy) can verify that you're assigning or accessing the correct type at each specific index of the tuple. If you try to get a str from an index that's supposed to hold an int, it will warn you.

    ```py
    from typing import Tuple

    # This function returns a fixed-length tuple: (string, integer, boolean)
    def get_user_status(user_id: int) -> Tuple[str, int, bool]:
        """
        Returns a user's (name, age, is_active) based on their ID.
        Each element in the returned tuple has a fixed type and meaning.
        """
        if user_id == 1:
            return "Alice", 30, True
        else:
            return "Guest", 0, False

    # --- Example Usage ---
    # We can unpack the tuple directly into variables with clear types
    name, age, is_active = get_user_status(1)
    print(f"User Name: {name}, Age: {age}, Active: {is_active}")

    # Another example call
    name2, age2, is_active2 = get_user_status(99)
    print(f"User Name: {name2}, Age: {age2}, Active: {is_active2}")

    # If we tried to assign to a tuple of different types, MyPy would warn us:
    # wrong_types: Tuple[int, str, bool] = get_user_status(1) # MyPy error
    ```
