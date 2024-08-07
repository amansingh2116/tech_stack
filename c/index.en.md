
# C cheat sheet / Notes

This is a C cheat sheet or notes, created while learning C through geekforgeeks blog on C programming.

## Sample C Code

```c
#include <stdio.h> 
// preprocessor command, tells compiler to include stdio.h from standard library in this program.

int main() {    
    // function from where compiler starts reading the program, since int main so the return value should be of int datatype

    int number1, number2, sum, value; // integer data type
    double a = 5;

    printf("Enter two integers: ");
    // print function

    scanf("%d %d", &number1, &number2); // The scanf will write the value input by the user into the integer variables number1 and number2.
    // scanf is a function that stands for Scan Formatted String. It is used to read data from stdin (standard input stream i.e. usually keyboard) and then writes the result into the given arguments.

    // calculation
    sum = number1 + number2;   
    value = sum * 5;

    printf("(%d + %d) * %a = %d\n", number1, number2, value);
    // \n is an escape character in C

    return 0;
    // return value of the main function
}
```

## Explanation of Topics

### Comments
- **Single line comment**:
  ```c
  // This is a single line comment
  ```
- **Multi-line comment**:
  ```c
  /* This is a
  Multiline comment */
  ```

### Compilation Commands
- To save an executable file:
  ```shell
  gcc file_name.c
  ```
  This command generates an executable file named `a.exe` which can be used to run the code.
- To create an executable file with a specific name:
  ```shell
  gcc file_name.c -o new_file_name
  ```
  This command creates the executable file `new_file_name.exe`.

### Preprocessor Directive
- The `#include <stdio.h>` line tells the compiler to include the standard input-output library `stdio.h` in the program. This library is necessary for using functions like `printf` and `scanf`.

### Main Function
- The `main` function is where the compiler starts reading the program. Since `main` is of type `int`, it should return a value of `int` datatype.

### Variables Declaration
- Declaring integer variables:
  ```c
  int number1, number2, sum, value;
  ```
- Declaring and initializing a double variable:
  ```c
  double a = 5;
  ```

### printf Function
- The `printf` function is used to output text to the console. It is part of the C standard library `<stdio.h>`.

#### Return Value
- `printf()` returns the number of characters printed after successful execution. If an error occurs, a negative value is returned.

#### Formatting in `printf`
- **Format Specifier Syntax**:
  ```c
  %[flags][width][.precision][length]specifier
  ```
- **Common Specifiers**:
  - `%d`: for printing integers
  - `%f`: for printing floating-point numbers
  - `%c`: for printing characters
  - `%s`: for printing strings
  - `%p`: for printing memory addresses
  - `%x`: for printing hexadecimal values

- **Width**:
  Specifies the minimum number of characters to be printed.
  ```c
  printf("%25s", some_string);
  printf("%*s", 25, some_string);
  ```

- **Precision**:
  Specifies the number of digits for various data types.
  ```c
  printf("%.10d", some_integer);
  printf("%.3f", some_float);
  printf("%.25s", some_string);
  ```

- **Length**:
  Specifies the length of the data type in memory.
  ```c
  printf("%lf", double_variable);
  ```

### scanf Function
- The `scanf` function reads formatted input from the standard input stream (usually the keyboard) and writes the result into the given arguments.
  ```c
  scanf("%d %d", &number1, &number2);
  ```

#### Format Specifiers
- `%d` to accept input of integers.
- `%ld` to accept input of long integers
- `%lld` to accept input of long long integers
- `%f` to accept input of real numbers.
- `%c` to accept input of character types.
- `%s` to accept input of a string.

#### Return Value
- **>0**: Number of values converted and assigned successfully.
- **0**: No value was assigned.
- **<0**: Read error encountered or end-of-file (EOF) reached before any assignment was made.

### Address-of Operator
- `&` is used to get the memory address of a variable.
  ```c
  // For example, &var is the address of var.
  ```

### Calculations
- Performing basic arithmetic operations:
  ```c
  sum = number1 + number2;   
  value = sum * 5;
  ```

### Escape Characters
- Escape characters in C:
  ```c
  printf("(%d + %d) * %a = %d\n", number1, number2, value);
  ```
  - `\n`: New Line
  - `\b`: Backspace
  - `\f`: Form Feed
  - `\r`: Carriage Return
  - `\t`: Horizontal Tab
  - `\v`: Vertical Tab
  - `\\`: Backslash
  - `\'`: Single Quote
  - `\"`: Double Quote
  - `\?`: Question Mark
  - `\ooo`: Octal Number
  - `\xhh`: Hexadecimal Number
  - `\0`: NULL

### Return Statement
- The `main` function should return an integer value. Returning `0` typically signifies that the program has executed successfully.
  ```c
  return 0;
  ```


## Variables in C

A variable in C is a memory location with some name that helps store some form of data and retrieves it when required. We can store different types of data in the variable and reuse the same variable for storing some other data any number of times.

### Variable Declaration
```c
data_type variable_name = value;    // defining single variable
data_type variable_name1, variable_name2;    // defining multiple variables
```

#### Example Code
```c
#include <stdio.h> 

int main() { 
    int harryName;   // This is variable declaration. 
                     // Most modern C compilers declare and define the variable in a single step.
    harryName = 76;  // This is variable initialization
    
    char five = '5'; // This is variable declaration and initialization/definition
    
    return 0;
}
```

### Rules for Naming Variables in C
1. A variable name must only contain alphabets, digits, and underscore.
2. A variable name must start with an alphabet or an underscore only. It cannot start with a digit.
3. No white space is allowed within the variable name.
4. A variable name must not be any reserved word or keyword.

### C Variable Types

#### Local Variables
A local variable is declared inside a function. A local variable is visible only inside their function; only statements inside a function can access that local variable. Local variables are declared when the function execution starts and get destroyed when the control exits from the function.

**Example:**
```c
#include <stdio.h>

void test();
void main() {
  int p = 22, q = 44;
  test();
  printf("Values in main() function p = %d and q = %d\n", p, q);
}

void test() {
  int p = 50, q = 80;
  printf("Values in test() function p = %d and q = %d\n", p, q);
}
```

**Output:**
```
Values in test() function p = 50 and q = 80
Values in main() function p = 22 and q = 44
```

Operating System calls the main() function at the time of execution. The local variables within the main() are created when the main() starts execution. When a call is made to the test() function, the control is transferred from main() to test(), and the local variables within the test() are created and available only within the test() function. After completion of execution of the test() function, the local variables are destroyed and the control is transferred back to the main() function.

#### Global Variables
Global variables are declared outside of any function. A global variable is visible to every function and can be used by any piece of code. Unlike local variables, global variables retain their values between function calls and throughout the program execution.

**Example:**
```c
#include <stdio.h>

int a = 20; // Global declaration

void test();
void main() {
  printf("In main() function a = %d\n", a); // Prints 20
  test();
  a = a + 15; // Uses global variable
  printf("In main() function a = %d\n", a); // Prints 55
}

void test() {
  a = a + 20; // Uses global variable
  printf("In test() function a = %d\n", a); // Prints 40
}
```

**Output:**
```
In main() function a = 20
In test() function a = 40
In main() function a = 55
```

In the above code, the global variable `a` is declared outside of all the functions. So, the variable `a` can be accessed in every function. The variable `a` has no local declaration in `main()` and `test()` functions, so they access the global variable `a`. The global variables are destroyed only after the completion of the execution of the entire program.

#### Static Variables
A static variable in C is a variable that is defined using the `static` keyword. It can be defined only once in a C program and its scope depends upon the region where it is declared (can be global or local). The default value of static variables is zero.

**Syntax:**
```c
static data_type variable_name = initial_value;
```

As its lifetime is till the end of the program, it can retain its value for multiple function calls.

**Example:**
```c
#include <stdio.h>

void function() {
    int x = 20;         // Local variable
    static int y = 30;  // Static variable
    x = x + 10;
    y = y + 10;
    printf("\tLocal: %d\n\tStatic: %d\n", x, y);
}

int main() {
    printf("First Call\n");
    function();
    printf("Second Call\n");
    function();
    printf("Third Call\n");
    function();
    return 0;
}
```

**Output:**
```
First Call
    Local: 30
    Static: 40
Second Call
    Local: 30
    Static: 50
Third Call
    Local: 30
    Static: 60
```

#### Automatic Variables
All the local variables are automatic variables by default. They are also known as auto variables. Their scope is local and their lifetime is till the end of the block. If needed, we can use the `auto` keyword to define the auto variables. The default value of the auto variables is a garbage value.

**Syntax:**
```c
auto data_type variable_name;
```

**Example:**
```c
#include <stdio.h>

void function() {
    int x = 10;       // Local variable (also automatic)
    auto int y = 20;  // Automatic variable
    printf("Auto Variable: %d", y);
}

int main() {
    function();
    return 0;
}
```

**Output:**
```
Auto Variable: 20
```

#### External Variables
External variables in C can be shared between multiple C files. We can declare an external variable using the `extern` keyword. Their scope is global and they exist between multiple C files.

**Syntax:**
```c
extern data_type variable_name;
```

**Example:**
```c
// myfile.h
extern int x = 10;  // External variable (also global)
```

```c
// program1.c
#include "myfile.h"
#include <stdio.h>

void printValue() {
    printf("Global variable: %d", x);
}
```

#### Register Variables
Register variables in C are stored in the CPU register instead of the conventional storage place like RAM. Their scope is local and exists till the end of the block or a function. These variables are declared using the `register` keyword. The default value of register variables is a garbage value.

**Syntax:**
```c
register data_type variable_name = initial_value;
```

**Example:**
```c
#include <stdio.h>

int main() {
    // Register variable
    register int var = 22;
    printf("Value of Register Variable: %d\n", var);
    return 0;
}
```

**Output:**
```
Value of Register Variable: 22
```

**Note:** We cannot get the address of the register variable using the address-of `&` operator because they are stored in the CPU register. The compiler will throw an error if we try to get the address of the register variable.

## Data Types in C

Data types in C are used to specify the type of data that a variable can hold. Each data type has a specific range and size, which determines the amount of memory required to store variables of that type.

### Integer Data Type
Integer data types are used to store whole numbers, both positive and negative, without any decimal part.

**Example:**
```c
int main() { 
    int var_name;
    return 0;
}
```

- **Range:** -2,147,483,648 to 2,147,483,647
- **Size:** 4 bytes
- **Format Specifier:** `%d`

**Variants:**
- `unsigned int`: Stores values from 0 to positive numbers, cannot store negative values.
- `short int`: Smaller than `int`, stores values from -32,768 to 32,767.
- `long int`: Larger than `int`, can store larger values.
- `unsigned short int`: Similar to `short int` but only stores positive values.

**Note:** The size of an integer data type is compiler-dependent. Use the `sizeof` operator to check the actual size.

### Floating-Point Data Type
Floating-point data types are used to store decimal and exponential values with single precision.

**Example:**
```c
int main() { 
    float var_name;
    return 0;
}
```

- **Range:** 1.2E-38 to 3.4E+38
- **Size:** 4 bytes
- **Format Specifier:** `%f`

### Character Data Type
Character data types are used to store single characters.

**Example:**
```c
int main() { 
    char var_name = 'x';
    return 0;
}
```

- **Range:** (-128 to 127) or (0 to 255)
- **Size:** 1 byte
- **Format Specifier:** `%c`

### Double Data Type
Double data types are used to store decimal numbers with double precision.

**Example:**
```c
int main() { 
    double var_name;
    return 0;
}
```

- **Range:** 1.7E-308 to 1.7E+308
- **Size:** 8 bytes
- **Format Specifier:** `%lf`

### Size of Data Types
The size of data types in C depends on the architecture of the system. To check the size of data types, use the `sizeof` operator.

**Example:**
```c
int main() {
    int size_of_int = sizeof(int);
    int size_of_char = sizeof(char);
    int size_of_float = sizeof(float);
    int size_of_double = sizeof(double);
 
    printf("The size of int data type: %d\n", size_of_int);
    printf("The size of char data type: %d\n", size_of_char);
    printf("The size of float data type: %d\n", size_of_float);
    printf("The size of double data type: %d\n", size_of_double);
 
    return 0;
}
```

**Output:**
```
The size of int data type: 4
The size of char data type: 1
The size of float data type: 4
The size of double data type: 8
```

### Typecasting in C

Typecasting in C is the process of converting one data type to another data type by the programmer using the casting operator during program design. There are two types of typecasting:

1. **Implicit Typecasting:** Automatically performed by the compiler when a lower data type is converted to a higher data type. No data value is altered during this conversion.
2. **Explicit Typecasting:** Used when the programmer explicitly converts one data type to another. It is necessary when the default typecasting would result in incorrect output.

**Syntax for Explicit Typecasting:**
```c
int x;
float y;
y = (float)x;
```

**Example:**
```c
#include <stdio.h> 
  
// Driver Code 
int main() 
{ 
    // Given a & b 
    int a = 15, b = 2; 
    float div; 
  
    // Division of a and b 
    div = a / b; 
  
    printf("The result is %f\n", div); 
  
    return 0; 
}
```
**Output:**
```
The result is 7.000000
```
**Required Output:**
```
7.500000
```

**Corrected Example with Explicit Typecasting:**
```c
#include <stdio.h> 
  
// Driver Code 
int main() 
{ 
    // Given a & b 
    int a = 15, b = 2; 
    char x = 'a'; 
    double div; 
  
    // Explicit Typecasting to double 
    div = (double)a / b; 
  
    // Implicitly converting x to a+3 i.e., 'd' 
    x = x + 3; 
  
    printf("The result of Implicit typecasting is %c\n", x); 
    printf("The result of Explicit typecasting is %f", div); 
  
    return 0; 
}
```
**Output:**
```
The result of Implicit typecasting is d
The result of Explicit typecasting is 7.500000
```

#### Conversion Functions in C

C provides several functions to convert data types:

- `atof()`: Converts a string to a float.
- `atol()`: Converts a string to a long.
- `itoa()`: Converts an int to a string.
- `itob()`: Converts an int to a binary string.
- `atoi()`: Converts a string to an int.

These functions are useful for handling data conversions in various scenarios, ensuring the correct data type is used for computations and storage.

### Constants in C

Constants in C are read-only variables whose values cannot be modified once they are declared. They can be of various types, such as integer constants, floating point constants, string constants, or character constants. The `const` keyword is used to define constants in C.

**Example:**
```c
int main() {
    const int var_name = 10;
    return 0;
}
```

**Properties of Constants in C:**
1. **Initialization with Declaration:**
   - Constants must be initialized at the time of declaration.
   - If not initialized, they will store garbage values.

2. **Immutability:**
   - Constants cannot be modified after initialization.
   - They can only be assigned a value once.

### Constants vs. Literals

- **Constants:**
  - Variables that cannot be modified once declared.
  - Defined using the `const` keyword.
  - Store literal values.
  - Address can be determined.
  - They are lvalues (can appear on the left side of assignment).

- **Literals:**
  - Fixed values that define themselves.
  - Cannot be modified.
  - Address cannot be determined (except string literals).
  - They are rvalues (can appear on the right side of assignment).

**Example of Constant:**
```c
const int c = 20;
```

**Example of Literals:**
```c
24, 15.5, 'a', "Geeks"
```

### Defining Constants Using `#define`

The `#define` directive is used to define constants. Unlike `const`, it does not create a variable but replaces all occurrences of the defined name with the value.

**Example:**
```c
#include <stdio.h>
#define pi 3.14
 
int main() {
    printf("The value of pi: %.2f", pi);
    return 0;
}
```

## Operators in C

Operators in C are symbols that perform operations on variables and values. The various types of operators in C include:

1. **Arithmetic Operators**
2. **Relational Operators**
3. **Logical Operators**
4. **Bitwise Operators**
5. **Assignment Operators**
6. **Misc Operators**

### **Arithmetic Operators:**
```c
int main() {
    int a = 60, b = 7;
    printf("The sum of a and b is %d\n", a + b);
    printf("The difference of a and b is %d\n", a - b);
    printf("The multiplication result of a and b is %d\n", a * b);
    printf("The division result of a and b is %d\n", a / b);
    printf("The modulo result of a and b is %d\n", a % b);
    printf("The increment result of a is %d\n", ++a);
    printf("The decrement result of b is %d\n", --b);
    return 0;
}
```

### **Relational Operators:**
```c
int main() {
    int harry = 9, rohan = 45;
    printf("%d\n", harry == rohan);
    printf("%d\n", harry != rohan);
    printf("%d\n", harry > rohan);
    printf("%d\n", harry < rohan);
    return 0;
}
```

### **Logical Operators:**
```c
int main() {
    int h = 0, j = 1;
    printf("The logical operator returned %d\n", h && j);
    printf("The logical operator returned %d\n", h || j);
    printf("The logical operator returned %d\n", !j);
    printf("The logical operator returned %d\n", !h);
    return 0;
}
```

### **Bitwise Operators:**
```c
int main() {
    int A = 60, B = 14;
    printf("Bitwise and operator returned %d\n", A & B);
    printf("Bitwise or operator returned %d\n", A | B);
    printf("Bitwise xor operator returned %d\n", A ^ B);
    printf("Bitwise ones complement operator returned %d\n", ~B);
    printf("Bitwise left shift operator returned %d\n", A << B);
    printf("Bitwise right shift operator returned %d\n", A >> B);
    return 0;
}
```

### **Assignment Operators:**
```c
int main() {
    int ha = 9;
    ha += 9;
    printf("ha is %d\n", ha);
    return 0;
}
```

### **Misc Operators:**
- Address-of (`&`)
- Pointer (`*`)
- Conditional (`?:`)

**Example of Taking Input from User:**
```c
#include <stdio.h>

int main() {
    int harryInput;
    printf("\n Please enter the value of harryInput: ");
    scanf("%d", &harryInput);
    printf("\n You Entered %f as harryInput", (float) harryInput);
    return 0;
}
```

## Conditional Statements in C

Conditional statements are used to perform different actions based on different conditions. They include `if-else`, `switch`, conditional operators, and jump statements.

### 1. `if-else-if-else`

The `if-else-if-else` statement allows you to test multiple conditions sequentially.

**Syntax:**
```c
if (condition) {
    // Executes this block if condition is true
} else if (condition) {
    // Executes this block if the previous condition is false and this condition is true
} else {
    // Executes this block if all previous conditions are false
}
```

**Example:**
```c
#include <stdio.h>

int main() {
    int number = 10;

    if (number > 0) {
        printf("The number is positive.\n");
    } else if (number < 0) {
        printf("The number is negative.\n");
    } else {
        printf("The number is zero.\n");
    }

    return 0;
}
```

### 2. Nested `if-else`

Nested `if-else` statements are `if-else` statements within another `if` or `else`.

**Syntax:**
```c
if (condition1) {
    if (condition2) {
        // Executes when condition1 and condition2 are true
    } else {
        // Executes when condition1 is true and condition2 is false
    }
} else {
    if (condition3) {
        // Executes when condition1 is false and condition3 is true
    } else {
        // Executes when condition1 and condition3 are false
    }
}
```

**Example:**
```c
#include <stdio.h>

int main() {
    int number = 15;

    if (number > 0) {
        if (number % 2 == 0) {
            printf("The number is positive and even.\n");
        } else {
            printf("The number is positive and odd.\n");
        }
    } else {
        if (number < 0) {
            printf("The number is negative.\n");
        } else {
            printf("The number is zero.\n");
        }
    }

    return 0;
}
```

### 3. `switch` Statement

The `switch` statement is used as an alternative to multiple `if-else` statements, typically when checking the value of a variable against a series of constants.

**Syntax:**
```c
switch (expression) {
    case value1:
        // Executes when expression matches value1
        break;
    case value2:
        // Executes when expression matches value2
        break;
    // Additional cases
    default:
        // Executes when none of the above cases match
}
```

**Example:**
```c
#include <stdio.h>

int main() {
    int day = 3;

    switch (day) {
        case 1:
            printf("Monday\n");
            break;
        case 2:
            printf("Tuesday\n");
            break;
        case 3:
            printf("Wednesday\n");
            break;
        default:
            printf("Invalid day\n");
            break;
    }

    return 0;
}
```

### 4. Conditional Operator (`? :`)

The conditional operator is a shorthand for `if-else` statements, used to return a value based on a condition.

**Syntax:**
```c
condition ? true_statements : false_statements;
```

**Example:**
```c
#include <stdio.h>

int main() {
    int age = 20;
    int i4 = age > 3 ? 100 : 200;

    printf("The value of i4 is %d\n", i4);

    return 0;
}
```

### 5. Jump Statements

Jump statements are used to alter the flow of control in a program.

- **`break`**: Terminates the nearest enclosing loop or `switch` statement.

**Example:**
```c
#include <stdio.h>

int main() {
    for (int i = 0; i < 10; i++) {
        if (i == 5) {
            break; // Exit the loop when i equals 5
        }
        printf("%d ", i);
    }

    return 0;
}
```

- **`continue`**: Skips the current iteration of the nearest enclosing loop and proceeds with the next iteration.

**Example:**
```c
#include <stdio.h>

int main() {
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            continue; // Skip even numbers
        }
        printf("%d ", i);
    }

    return 0;
}
```

- **`goto`**: Jumps to a labeled statement within the same function. It is generally discouraged as it can make code harder to read and maintain.

**Example:**
```c
#include <stdio.h>

void printNumbers() {
    int n = 1;
label:
    printf("%d ", n);
    n++;
    if (n <= 10)
        goto label;
}

int main() {
    printNumbers();
    return 0;
}
```

## Loops in C

Loops in C are used to execute a block of code repeatedly based on a condition. There are mainly two types of loops: entry-controlled loops and exit-controlled loops.

### 1. **For Loop** (Entry Controlled)

The `for` loop is used when the number of iterations is known beforehand. It initializes a variable, checks a condition, and updates the variable after each iteration.

**Syntax:**
```c
for (initialization_expression; test_expression; update_expression) {
    // body of the for loop
}
```

**Example:**
```c
#include <stdio.h>

int main() {
    int i;

    for (i = 1; i <= 10; i++) {
        printf("Hello World\n");
    }

    return 0;
}
```

### 2. **While Loop** (Entry Controlled)

The `while` loop is used when the number of iterations is not known beforehand and depends on the condition. The condition is checked before entering the loop body.

**Syntax:**
```c
initialization_expression;
while (test_expression) {
    // body of the while loop
    update_expression;
}
```

**Example:**
```c
#include <stdio.h>

int main() {
    int i = 2;

    while (i < 10) {
        printf("Hello World\n");
        i++;
    }

    return 0;
}
```

### 3. **Do-While Loop** (Exit Controlled)

The `do-while` loop is similar to the `while` loop, but the condition is checked after the loop body has executed. Therefore, the loop body is executed at least once.

**Syntax:**
```c
initialization_expression;
do {
    // body of the do-while loop
    update_expression;
} while (test_expression);
```

**Example:**
```c
#include <stdio.h>

int main() {
    int i = 2;

    do {
        printf("Hello World\n");
        i++;
    } while (i < 1); // Loop condition is false, but loop body will execute at least once

    return 0;
}
```

## Functions in C

A function in C is a set of statements that perform a specific task when called. Functions provide modularity and code reusability.

**Note:** A function must be declared globally before it is called.

### Syntax of Functions in C

The syntax of a function can be divided into three aspects:

1. **Function Declaration:** Declares the function with its return type and parameters.
2. **Function Definition:** Contains the actual statements to be executed when the function is called.
3. **Function Call:** Executes the function and returns the result.

### Function Declaration

Function declaration tells the compiler that there is a function with the given name defined elsewhere.

**Syntax:**
```c
return_type function_name(parameter_1_type, parameter_2_type);
```

**Example:**
```c
int sum(int a, int b);  // Function declaration with parameter names
int sum(int, int);      // Function declaration without parameter names
```

### Function Definition

The function definition includes the actual code to be executed.

**Syntax:**
```c
return_type function_name(parameter_1_type parameter_1_name, parameter_2_type parameter_2_name) {
    // body of the function
}
```

**Example:**
```c
#include <stdio.h>

int sum(int a, int b) {
    return a + b;
}

int main() {
    int add = sum(10, 30); // Calling sum function
    printf("Sum is: %d", add);
    return 0;
}
```

### Function Return Type

The return type specifies the type of value returned by the function. Use `void` if no value is returned.

**Example:**
```c
int func(parameter_1, parameter_2); // Returns an integer
void func(); // Does not return a value
```

**Note:** Only one value can be returned. To return multiple values, use pointers or structures.

### Function Arguments

Arguments (or parameters) are the data passed to a function.

**Example:**
```c
int function_name(int var1, int var2);
```

### Passing Parameters to Functions

Arguments can be passed in two ways:

1. **Pass by Value:** Copies the value into the function’s parameters. Changes inside the function do not affect the caller’s variables.

    **Example:**
    ```c
    #include <stdio.h>

    void swap(int var1, int var2) {
        int temp = var1;
        var1 = var2;
        var2 = temp;
    }

    int main() {
        int var1 = 3, var2 = 2;
        printf("Before swap: %d, %d\n", var1, var2);
        swap(var1, var2);
        printf("After swap: %d, %d\n", var1, var2);
        return 0;
    }
    ```
    **Output:**
    ```
    Before swap: 3, 2
    After swap: 3, 2
    ```

2. **Pass by Reference:** Uses pointers to refer to the actual parameters, so changes affect the caller’s variables.

    **Example:**
    ```c
    #include <stdio.h>

    void swap(int *var1, int *var2) {
        int temp = *var1;
        *var1 = *var2;
        *var2 = temp;
    }

    int main() {
        int var1 = 3, var2 = 2;
        printf("Before swap: %d, %d\n", var1, var2);
        swap(&var1, &var2);
        printf("After swap: %d, %d\n", var1, var2);
        return 0;
    }
    ```
    **Output:**
    ```
    Before swap: 3, 2
    After swap: 2, 3
    ```

### Types of Functions

1. **Library Functions:** Built-in functions provided by the compiler package.

2. **User-Defined Functions:** Functions created by the programmer.

---

### Recursion in C

Recursion is a process where a function calls itself to solve a problem. A recursive function has two main components:

1. **Recursion Case:** Defines how the problem is divided into smaller subproblems.
2. **Base Condition:** Specifies when the recursion should terminate.

**Note:** Define the base condition to prevent infinite recursion.

#### Syntax of Recursive Functions

**Syntax:**
```c
type function_name(args) {
    // function statements
    // base condition
    // recursion case (recursive call)
}
```

**Example:**
```c
#include <stdio.h>

int nSum(int n) {
    if (n == 0) {
        return 0;
    }
    return n + nSum(n - 1);
}

int main() {
    int n = 5;
    int sum = nSum(n);
    printf("Sum of First %d Natural Numbers: %d", n, sum);
    return 0;
}
```

#### How Recursion Works

1. **nSum(5):** Calls `nSum(4)`
2. **nSum(4):** Calls `nSum(3)`
3. **nSum(3):** Calls `nSum(2)`
4. **nSum(2):** Calls `nSum(1)`
5. **nSum(1):** Calls `nSum(0)`
6. **nSum(0):** Returns 0

The final calculation:
```
nSum(5) = 5 + 4 + 3 + 2 + 1 + 0 = 15
```

#### Memory Allocation for Recursive Functions

1. A new stack frame is created for each recursive call.
2. The function’s local variables and state are stored in the stack frame.
3. Each stack frame is removed after the function returns a value.

**Steps:**
1. **Create Stack Frame:** For `nSum(5)`
2. **Recursive Calls:** New stack frames created for each call.
3. **Return Values:** Stack frames are removed as values are returned.

#### Stack Overflow

Occurs when the recursion depth exceeds the stack memory limit, causing program termination.

**Definition:** Stack overflow is an error when the call stack cannot store more data due to excessive recursion.

---

Here's a Markdown version of the notes on arrays in C:


## Arrays in C

An array in C is a fixed-size collection of similar data items stored in contiguous memory locations. It can store primitive data types like `int`, `char`, `float`, etc., as well as derived and user-defined types like pointers and structures. Arrays in C are static, meaning memory is allocated at compile time.

### Characteristics of Arrays

1. **Fixed Size**: The size of the array must be known at compile time and cannot be changed once declared.
2. **Homogeneous Collection**: An array can store only one type of element. All elements must be of the same type.
3. **Indexing**: Array indices start at 0. The index of the first element is 0, and the last element is `N - 1` for an array of size `N`.
4. **Dimensions**: The number of dimensions refers to the number of indexes required to access an element.
5. **Contiguous Storage**: Elements are stored continuously in memory, allowing for random access.
6. **Random Access**: Elements can be accessed directly using their index in constant time.
7. **No Index Out of Bounds Checking**: C does not check for index out-of-bounds errors.

### Array Declaration

To declare an array, specify its name, type, and size.

**Syntax**:
```c
data_type array_name[size];
```

For multidimensional arrays:
```c
data_type array_name[size1][size2]...[sizeN];
```

### Array Initialization

Arrays can be initialized in several ways:

1. **With Declaration**:
   ```c
   data_type array_name[size] = {value1, value2, ..., valueN};
   ```

2. **With Declaration (Size Deduction)**:
   ```c
   data_type array_name[] = {1, 2, 3, 4, 5}; // Size is automatically deduced
   ```

3. **After Declaration (Using Loops)**:
   ```c
   for (int i = 0; i < N; i++) {
       array_name[i] = valuei;
   }
   ```

### Accessing and Updating Array Elements

**Access an element**:
```c
array_name[index];
```

**Update an element**:
```c
array_name[index] = new_value;
```

### Array Traversal

Traversal involves visiting each element of the array. This is commonly done using loops.

**Example using a `for` loop**:
```c
for (int i = 0; i < N; i++) {
    // Process array_name[i]
}
```

### Relationship Between Arrays and Pointers

Arrays and pointers are closely related. The array name is a constant pointer to the first element. Arrays decay to pointers when passed to functions.

**Example**:
```c
#include <stdio.h>

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int* ptr = &arr[0];

    // Print addresses
    printf("Address Stored in Array name: %p\nAddress of 1st Array Element: %p\n", arr, &arr[0]);

    // Print array elements using pointers
    printf("Array elements using pointer: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", *ptr++);
    }
    return 0;
}
```

### Passing Arrays to Functions

Arrays are passed to functions as pointers. The array decays to a pointer to its first element.

**Example**:
```c
#include <stdio.h>

void printArray(int arr[]) {
    printf("Size of Array in Functions: %d\n", sizeof(arr));
    printf("Array Elements: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
}

int main() {
    int arr[5] = {10, 20, 30, 40, 50};

    printf("Size of Array in main(): %d\n", sizeof(arr));
    printArray(arr);
    return 0;
}
```

### Returning Arrays from Functions

C functions can only return a single value. To return an array, use a pointer. 

**Example**:
```c
#include <stdio.h>

int* func() {
    static int arr[5] = {1, 2, 3, 4, 5};
    return arr;
}

int main() {
    int* ptr = func();
    printf("Array Elements: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", *ptr++);
    }
    return 0;
}
```

> *Note*: The array is declared `static` to ensure it persists after the function returns.

## Strings in C

A string in C is a sequence of characters terminated by a null character (`\0`). In C, strings are stored as arrays of characters. Unlike a character array, a C string is explicitly terminated by a null character. Note that C does not provide an inbuilt data type for strings but uses the format specifier `%s` to print and read strings.

### String Declaration

Declaring a string is similar to declaring a one-dimensional array.

**Syntax**:
```c
char string_name[size];
```

### String Initialization

1. **Assigning a String Literal without Size**:
   ```c
   char str[] = "GeeksforGeeks";
   ```

2. **Assigning a String Literal with a Predefined Size**:
   Ensure to account for the null character.
   ```c
   char str[50] = "GeeksforGeeks";
   ```

3. **Assigning Character by Character with Size**:
   Manually set the null character.
   ```c
   char str[14] = { 'G','e','e','k','s','f','o','r','G','e','e','k','s','\0' };
   ```

4. **Assigning Character by Character without Size**:
   The size is determined by the compiler.
   ```c
   char str[] = { 'G','e','e','k','s','f','o','r','G','e','e','k','s','\0' };
   ```

> *Note*: When a string is enclosed in double quotation marks, a null character is automatically appended.

The length of the string is the number of characters excluding the null character. It can be determined using the `strlen()` function from the string.h library.

**Example**:
```c
#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Geeks";
    printf("%s\n", str);
    int length = strlen(str);
    printf("Length of string str is %d", length);
    return 0;
}
```

**Output**:
```
Geeks
Length of string str is 5
```

### Reading a String Input from the User

**Example**:
```c
#include <stdio.h>

int main() {
    char str[50];
    scanf("%s", str);
    printf("%s", str);
    return 0;
}
```

**Input**:
```
GeeksforGeeks
```

**Output**:
```
GeeksforGeeks
```

Note: `scanf()` reads a string until the first whitespace. To handle strings with spaces, consider using `fgets()` or `scanf("%[^\n]s", str)`.

### Reading Strings with Whitespaces

1. **Using `fgets()`**:
   ```c
   #include <stdio.h>
   #define MAX 50

   int main() {
       char str[MAX];
       fgets(str, MAX, stdin);
       printf("String is: \n");
       puts(str);
       return 0;
   }
   ```

2. **Using Scanset in `scanf()`**:
   ```c
   #include <stdio.h>

   int main() {
       char str[20];
       scanf("%[^\n]s", str);
       printf("%s", str);
       return 0;
   }
   ```

### Passing Strings to Functions

**Example**:
```c
#include <stdio.h>

void printStr(char str[]) {
    printf("String is : %s", str);
}

int main() {
    char str[] = "GeeksforGeeks";
    printStr(str);
    return 0;
}
```

**Output**:
```
String is : GeeksforGeeks
```

### Strings and Pointers

Strings and pointers are closely related. A character pointer can point to the start of a string.

**Example**:
```c
#include <stdio.h>

int main() {
    char str[20] = "GeeksforGeeks";
    char* ptr = str;

    while (*ptr != '\0') {
        printf("%c", *ptr);
        ptr++;
    }
    return 0;
}
```

**Output**:
```
GeeksforGeeks
```

### Standard C Library – `string.h` Functions

| Function Name | Description |
|---------------|-------------|
| `strlen(string_name)` | Returns the length of `string_name`. |
| `strcpy(s1, s2)` | Copies the contents of `s2` to `s1`. |
| `strcmp(str1, str2)` | Compares `str1` with `str2`. Returns 0 if equal. |
| `strcat(s1, s2)` | Concatenates `s2` to `s1`. |
| `strlwr()` | Converts string to lowercase. |
| `strupr()` | Converts string to uppercase. |
| `strstr(s1, s2)` | Finds the first occurrence of `s2` in `s1`. |


## Pointers in C

A pointer is a derived data type that stores the address of another variable or a memory location. Using pointers, you can access and manipulate data stored in that memory location. The size of pointers in C is independent of the type of data they point to and depends on the system architecture.

## Syntax of C Pointers

The syntax for declaring a pointer is similar to variable declaration but includes the dereferencing operator `*`:

```c
datatype *ptr;
```

### 1. Pointer Declaration

To declare a pointer, use the `*` operator before its name:

```c
int *ptr;
```

### 2. Pointer Initialization

Initialize a pointer by assigning it the address of a variable using the `&` (address-of) operator:

```c
int var = 10;
int *ptr;
ptr = &var;

// or declare and initialize in one step
int *ptr = &var;
```

**Note:** Pointers should be initialized before use to avoid errors.

### 3. Pointer Dereferencing

Dereferencing a pointer accesses the value stored at the address it points to:

```c
int var = 10;
int *ptr = &var;
printf("Value at *ptr = %d\n", *ptr);
```

### Types of Pointers

#### 1. Integer Pointers

Pointers to integer values:

```c
int *ptr;
```

#### 2. Array Pointers

Pointers to arrays:

```c
char *ptr = &array_name;
```

#### 3. Structure Pointers

Pointers to structures:

```c
struct struct_name *ptr;
```

#### 4. Function Pointers

Pointers to functions:

```c
int (*ptr)(int, char);
```

#### 5. Double Pointers

Pointers to pointers:

```c
datatype **pointer_name;
```

#### 6. NULL Pointers

Pointers that point to no memory location, initialized as NULL:

```c
data_type *pointer_name = NULL;
```

#### 7. Void Pointers

Pointers with no associated data type:

```c
void *pointer_name;
```

**Note:** Void pointers cannot be dereferenced directly.

#### 8. Wild Pointers

Uninitialized pointers that can cause crashes or data corruption.

#### 9. Constant Pointers

Pointers with a constant memory address:

```c
data_type * const pointer_name;
```

#### 10. Pointer to Constant

Pointers to constant values:

```c
const data_type *pointer_name;
```

### Size of Pointers

The size of pointers is determined by the operating system and CPU architecture:

- 8 bytes for a 64-bit system
- 4 bytes for a 32-bit system

**Example:**

```c
#include <stdio.h>

int main() {
    int *ptr_int;
    char *ptr_char;
    struct str *ptr_str;
    void (*ptr_func)(int, int);
    void *ptr_vn;

    printf("Size of Integer Pointer  \t: %lu bytes\n", sizeof(ptr_int));
    printf("Size of Character Pointer \t: %lu bytes\n", sizeof(ptr_char));
    printf("Size of Structure Pointer \t: %lu bytes\n", sizeof(ptr_str));
    printf("Size of Function Pointer \t: %lu bytes\n", sizeof(ptr_func));
    printf("Size of NULL Void Pointer \t: %lu bytes\n", sizeof(ptr_vn));

    return 0;
}
```

### C Pointer Arithmetic

#### Increment and Decrement

Pointers can be incremented or decremented, which changes the address by the size of the data type:

```c
int *ptr;
ptr = ptr + 1;  // Moves to next integer
ptr = ptr - 1;  // Moves to previous integer
```

#### Addition and Subtraction

Adding or subtracting integers from pointers:

```c
int N = 4;
int *ptr1 = &N;
ptr1 = ptr1 + 3; // Moves 3 integers ahead
ptr1 = ptr1 - 3; // Moves 3 integers back
```

#### Subtracting Two Pointers

Find the number of elements between two pointers:

```c
int x = 6, N = 4;
int *ptr1 = &N, *ptr2 = &x;
int diff = ptr1 - ptr2;  // Difference in terms of number of elements
```

#### Pointer Comparison

Compare pointers to check if they are equal or not:

```c
int arr[5];
int *ptr1 = arr;
int *ptr2 = &arr[0];

if (ptr1 == ptr2) {
    printf("Pointers are equal.\n");
} else {
    printf("Pointers are not equal.\n");
}
```

### Pointer Arithmetic on Arrays

Arrays and pointers are closely related. The array name acts as a pointer to its first element. You can use pointer arithmetic to traverse arrays:

```c
int arr[] = {1, 2, 3, 4, 5};
int *ptr = arr;

for (int i = 0; i < 5; i++) {
    printf("%d ", *(ptr + i));  // Access elements using pointer
}
```

#### Example: Traversing a 2D Array

```c
#include <stdio.h>

void traverseArr(int* arr, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", *((arr + i * M) + j));
        }
        printf("\n");
    }
}

int main() {
    int arr[][2] = {{1, 2}, {3, 4}, {5, 6}};
    traverseArr((int*)arr, 3, 2);
    return 0;
}
```

## Structures in C

The structure in C is a user-defined data type that can be used to group items of possibly different types into a single type. The `struct` keyword is used to define the structure in the C programming language. The items in the structure are called its members and they can be of any valid data type. Additionally, the values of a structure are stored in contiguous memory locations.

### C Structure Declaration

**Syntax:**

```c
struct structure_name {
    data_type member_name1;
    data_type member_name2;
    // ...
};
```

### C Structure Definition

1. **Structure Variable Declaration with Structure Template:**

```c
struct structure_name {
    data_type member_name1;
    data_type member_name2;
    // ...
} variable1, variable2, ...;
```

2. **Structure Variable Declaration after Structure Template:**

```c
// structure declared beforehand
struct structure_name variable1, variable2, .......;
```

### Access Structure Members

We can access structure members by using the ( `.` ) dot operator.

**Syntax:**

```c
structure_name.member1;
structure_name.member2;
```

In the case where we have a pointer to the structure, we can also use the arrow operator to access the members.

### Initialize Structure Members

Structure members cannot be initialized with the declaration.

```c
struct Point {
   int x = 0;  // COMPILER ERROR:  cannot initialize members here
   int y = 0;  // COMPILER ERROR:  cannot initialize members here
};
```

The reason for the above error is simple. When a datatype is declared, no memory is allocated for it. Memory is allocated only when variables are created.

**Default Initialization**

By default, structure members are not automatically initialized to 0 or NULL. Uninitialized structure members will contain garbage values. However, when a structure variable is declared with an initializer, all members not explicitly initialized are zero-initialized.

```c
struct Point {    
     int x;    
     int y;
};

struct Point p = {0}; // Both x and y are initialized to 0
```

We can initialize structure members in 3 ways which are as follows:

1. **Using Assignment Operator:**

```c
struct structure_name str;
str.member1 = value1;
str.member2 = value2;
str.member3 = value3;
// ...
```

2. **Using Initializer List:**

```c
struct structure_name str = { value1, value2, value3 };
```

In this type of initialization, the values are assigned in sequential order as they are declared in the structure template.

3. **Using Designated Initializer List:**

Designated Initialization allows structure members to be initialized in any order. This feature has been added in the C99 standard.

```c
struct structure_name str = { .member1 = value1, .member2 = value2, .member3 = value3 };
```

### C Program to Illustrate the Use of Structures

```c
#include <stdio.h>

// Declaring structure with name str1
struct str1 {
    int i;
    char c;
    float f;
    char s[30];
};

// Declaring structure with name str2
struct str2 {
    int ii;
    char cc;
    float ff;
} var; // Variable declaration with structure template

// Driver code
int main()
{
    // Variable declaration after structure template
    // Initialization with initializer list and designated initializer list
    struct str1 var1 = { 1, 'A', 1.00, "GeeksforGeeks" },
                var2;
    struct str2 var3 = { .ff = 5.00, .ii = 5, .cc = 'a' };

    // Copying structure using assignment operator
    var2 = var1;

    printf("Struct 1:\n\ti = %d, c = %c, f = %f, s = %s\n",
           var1.i, var1.c, var1.f, var1.s);
    printf("Struct 2:\n\ti = %d, c = %c, f = %f, s = %s\n",
           var2.i, var2.c, var2.f, var2.s);
    printf("Struct 3\n\ti = %d, c = %c, f = %f\n", var3.ii,
           var3.cc, var3.ff);

    return 0;
}
```

**Output:**

```
Struct 1:
    i = 1, c = A, f = 1.000000, s = GeeksforGeeks
Struct 2:
    i = 1, c = A, f = 1.000000, s = GeeksforGeeks
Struct 3
    i = 5, c = a, f = 5.000000
```

### Typedef for Structures

The `typedef` keyword is used to define an alias for the already existing datatype. In structures, we have to use the `struct` keyword along with the structure name to define the variables. Sometimes, this increases the length and complexity of the code. We can use `typedef` to define some new shorter name for the structure.

**Example:**

```c
#include <stdio.h>

// Defining structure
typedef struct {
    int a;
} str1;

// Another way of using typedef with structures
typedef struct {
    int x;
} str2;

int main()
{
    // Creating structure variables using new names
    str1 var1 = { 20 };
    str2 var2 = { 314 };

    printf("var1.a = %d\n", var1.a);
    printf("var2.x = %d\n", var2.x);

    return 0;
}
```

**Output:**

```
var1.a = 20
var2.x = 314
```

### Nested Structures

C language allows us to insert one structure into another as a member. This process is called nesting and such structures are called nested structures. There are two ways in which we can nest one structure into another:

1. **Embedded Structure Nesting**

In this method, the structure being nested is also declared inside the parent structure.

```c
struct parent {
    int member1;
    struct member_str {
        int member_str1;
        char member_str2;
        // ...
    } member2;
    // ...
};
```

2. **Separate Structure Nesting**

In this method, two structures are declared separately and then the member structure is nested inside the parent structure.

```c
struct member_str {
    int member_str1;
    char member_str2;
    // ...
};

struct parent {
    int member1;
    struct member_str member2;
    // ...
};
```

One thing to note here is that the declaration of the structure should always be present before its definition as a structure member. For example, the declaration below is invalid as the struct `mem` is not defined when it is declared inside the parent structure.

```c
struct parent {
    struct mem a;
};

struct mem {
    int var;
};
```

### Accessing Nested Members

We can access nested Members by using the same ( `.` ) dot operator two times as shown:

```c
str_parent.str_child.member;
```

**Example of Structure Nesting**

```c
#include <stdio.h>

// Child structure declaration
struct child {
    int x;
    char c;
};

// Parent structure declaration
struct parent {
    int a;
    struct child b;
};

// Driver code
int main()
{
    struct parent var1 = { 25, 195, 'A' };

    // Accessing and printing nested members
    printf("var1.a = %d\n", var1.a);
    printf("var1.b.x = %d\n", var1.b.x);
    printf("var1.b.c = %c", var1.b.c);

    return 0;
}
```

**Output:**

```
var1.a = 25
var1.b.x = 195
var1.b.c = A
```

### Structure Pointer in C

We can define a pointer that points to the structure like any other variable. Such pointers are generally called Structure Pointers. We can access the members of the structure pointed by the structure pointer using the ( `->` ) arrow operator.

**Example of Structure Pointer**

```c
#include <stdio.h>

// Structure declaration
struct Point {
    int x, y;
};

int main()
{
    struct Point str = { 1, 2 };

    // p2 is a pointer to structure p1
    struct Point* ptr = &str;

    // Accessing structure members using structure pointer
    printf("%d %d", ptr->x, ptr->y);

    return 0;
}
```

**Output:**

```
1 2
```

### Self-Referential Structures

The self-referential structures in C are those structures that contain references to the same type as themselves i.e., they contain a member of the type pointer pointing to the same structure type.

**Example of Self-Referential Structures**

```c
#include <stdio.h>

// Structure template
typedef struct str {
    int mem1;
    int mem2;
    struct str* next;
} str;

// Driver code
int main()
{
    str var1 = { 1, 2, NULL };
    str var2 = { 10, 20, NULL };

    // Assigning the address of var2 to var1.next
    var1.next = &var2;

    // Pointer to var1
    str *ptr1 = &var1;

    // Access

ing var2 members using var1
    printf("var2.mem1: %d\nvar2.mem2: %d", ptr1->next->mem1,
           ptr1->next->mem2);

    return 0;
}
```

**Output:**

```
var2.mem1: 10
var2.mem2: 20
```

Such kinds of structures are used in different data structures such as to define the nodes of linked lists, trees, etc.

### C Structure Padding and Packing

Technically, the size of the structure in C should be the sum of the sizes of its members. But it may not be true for most cases. The reason for this is Structure Padding.

**Structure Padding** is the concept of adding multiple empty bytes in the structure to naturally align the data members in the memory. It is done to minimize the CPU read cycles to retrieve different data members in the structure.

There are some situations where we need to pack the structure tightly by removing the empty bytes. In such cases, we use **Structure Packing**. C language provides two ways for structure packing:

- Using `#pragma pack(1)`
- Using `__attribute((packed))`

**Example of Structure Padding and Packing**

```c
#include <stdio.h>

// Structure with padding
struct str1 {
    char c;
    int i;
};

struct str2 {
    char c;
    int i;
} __attribute((packed)); // Using structure packing

// Driver code
int main()
{
    printf("Size of str1: %d\n", sizeof(struct str1));
    printf("Size of str2: %d\n", sizeof(struct str2));
    return 0;
}
```

**Output:**

```
Size of str1: 8
Size of str2: 5
```

As we can see, the size of the structure is varied when structure packing is performed.

To know more about structure padding and packing, refer to this article – Structure Member Alignment, Padding, and Data Packing.

### Bit Fields

Bit Fields are used to specify the length of the structure members in bits. When we know the maximum length of the member, we can use bit fields to specify the size and reduce memory consumption.

**Syntax of Bit Fields**

```c
struct structure_name {
    data_type member_name: width_of_bit-field;
};
```

**Example of Bit Fields**

```c
#include <stdio.h>

// Declaring structure for reference
struct str1 {
    int a;
    char c;
};

// Structure with bit fields
struct str2 {
    int a : 24; // Size of 'a' is 3 bytes = 24 bits
    char c;
};

// Driver code
int main()
{
    printf("Size of Str1: %d\nSize of Str2: %d",
           sizeof(struct str1), sizeof(struct str2));
    return 0;
}
```

**Output:**

```
Size of Str1: 8
Size of Str2: 4
```
