# Wildlife Conservation

## What Are Python Tracebacks?

In Python, a traceback is a detailed report generated when an error occurs in your code. A traceback, also called a stack trace, offers valuable information about what and where went wrong in the code by providing a step-by-step account of what lead up to the Python raising an exception. While tracebacks may appear daunting at first glance, they contain crucial details that can significantly aid in debugging your code.

By carefully examining a traceback, you can:

- Understand the nature of the exception
- See the sequence of code that led to the error
- Identify the exact line where the error occurred, sometimes even where in the line the error occurred

Learning to read and understand tracebacks is an essential skill for Python developers because it's one of the primary ways to debug errors in Python code.

Below is an example of code that has a bug in it. When the cell is executed, the code does not run because it raises an exception and generates a traceback.

```python
def greet(name):
    print("Hello,", name)


greet(user_name)
```

    ---------------------------------------------------------------------------

    NameError                                 Traceback (most recent call last)

    Cell In[1], line 5
          1 def greet(name):
          2     print("Hello,", name)
    ----> 5 greet(user_name)


    NameError: name 'user_name' is not defined

In the code above, we did not define the variable `user_name` before it was used. It's a common mistake to use a variable without defining it first.

Let's walk through the traceback. We read a traceback by **starting with the last line**. The first element is `NameError`, which is the type of exception that was raised. After the colon (`:`), there's a more detailed explanation: `name 'user_name' is not defined`. Looking at the next line up, we see an arrow (`---->`), which points to the line causing the error. Above that, there's also a brief snippet of code for context. The top line repeats some of the information: `NameError Traceback (most recent call last)`.

Let's fix the code so it runs.

```python
def greet(name):
    print("Hello,", name)


user_name = "Zarah"
greet(user_name)
```

    Hello, Zarah

The code now runs because the variable `user_name` is defined before it's called.

Now it's your turn. The code below is broken. Run the cell and use the traceback to locate the error.

**Task 1.2.1:** Fix a `NameError` using a traceback.

```python
def say_hello():
    print("Hello!")

say_hello()
```

    Hello!

A function needs to be defined before it's called. Thus, the order of the elements needed to be swapped.

Let's look at another example of broken code that generates a traceback.

```python
def calculate_average(numbers):
    return sum(numbers) / len(numbers)
```

```python
result = calculate_average([1, 2, 3, "4", 5])
```

    ---------------------------------------------------------------------------

    TypeError                                 Traceback (most recent call last)

    Cell In[6], line 1
    ----> 1 result = calculate_average([1, 2, 3, "4", 5])


    Cell In[5], line 2, in calculate_average(numbers)
          1 def calculate_average(numbers):
    ----> 2     return sum(numbers) / len(numbers)


    TypeError: unsupported operand type(s) for +: 'int' and 'str'

Let's walk through this traceback **starting with the last line**. The exception type is `TypeError`. There is an `unsupported operand type(s) for +`. An *operand* is the data on which an operation is performed. In this case, the function is attempting to add (`+`) an integer (`int`) and a string (`str`). The next line (`----> 2     return sum(numbers) / len(numbers)`) points to the line raising the exception in the function. The Python kernel also displays the cell in which this function is called. Above that, there is `----> 1 result = calculate_average([1, 2, 3, 'four', 5])`, which points to the line that called the function. These two code snippets provide the extended context which raises the exception.

Let's change the code to use a consistent datatype, integer makes the most sense in this example.

```python
result = calculate_average([1, 2, 3, 4, 5])
```

Now, the code runs without errors.

The following code is broken. Run the cell, read the traceback, understand the error, and then correct the code. Change only the code, do **not** modify the data.

Complete the `lower_case_dictionary_values` function. Inside the loop, check if each `value` is a string. If it is, add the key-value pair to `new_dict` with the value converted to lowercase. If not, add the original key-value pair to `new_dict`. Test the function with the `user_data` dictionary. Run the code and use any resulting traceback to identify and fix errors in your implementation.

**Task 1.2.2:** Fix the function `lower_case_dictionary_values` using traceback information.

```python
def lower_case_dictionary_values(dictionary):
    new_dict = {}
    for key, value in dictionary.items():
        if type(value) == str:
            new_dict[key] = value.lower()
        else:
            new_dict[key] = value
    return new_dict


user_data = {
    "username": "Maria Clara Santos",
    "email": "Maria.Clara.Aantos@example.com",
    "age": 30,
}

lower_case_dictionary_values(user_data)
```

    {'username': 'maria clara santos',
     'email': 'maria.clara.aantos@example.com',
     'age': 30}

The issue is that an `int` type can not be lowercased. One solution is to add a conditional that only lowercases `str` types.

Let's examine an example of a traceback coming from a common PyTorch error.

```python
import torch
```

```python
tensor_on_cpu = torch.tensor([1, 2, 3])
tensor_on_gpu = torch.tensor([4, 5, 6]).cuda()
result = tensor_on_cpu + tensor_on_gpu
```

    ---------------------------------------------------------------------------

    RuntimeError                              Traceback (most recent call last)

    Cell In[16], line 3
          1 tensor_on_cpu = torch.tensor([1, 2, 3])
          2 tensor_on_gpu = torch.tensor([4, 5, 6]).cuda()
    ----> 3 result = tensor_on_cpu + tensor_on_gpu


    RuntimeError: Expected all tensors to be on the same device, but found at least two devices, cuda:0 and cpu!

This `RuntimeError` is a result of trying to combine a CPU-based tensor with a GPU-based tensor. To fix this error, you need to ensure all tensors are on the same device before performing operations. One way to do that is to move the CPU-based tensor to the GPU, then the operation will be valid.

```python
tensor_moved_to_gpu = tensor_on_cpu.cuda()
result = tensor_moved_to_gpu + tensor_on_gpu
```

**Task 1.2.3:** Fix PyTorch `RuntimeError` using traceback information.

```python
# Important! Don't change this!
torch.manual_seed(42)
torch.cuda.manual_seed(42)

matrix_1 = torch.randn(3, 4).cuda()

matrix_2 = torch.randn(4, 2)

matrix_2 = matrix_2.cuda()
# your code goes here...

result = torch.mm(matrix_1, matrix_2)
```

In PyTorch, all tensors involved in a computation must be on the same device. One solution is to move tensors from the CPU to the GPU using the `.cuda()` method.

In closing, errors are a natural part of programming. When encountering an error, pause, read the traceback message slowly (always starting at the end), and think about what the traceback message is telling you about the cause of the error. Use that information to make a plan on how to fix the code.

---
This file &#169; 2024 by [WorldQuant University](https://www.wqu.edu/) is licensed under [CC BY-NC-ND 4.0](https://creativecommons.org/licenses/by-nc-nd/4.0/).
