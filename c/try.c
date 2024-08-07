// This is a single line comment
/* This is a
Multiline comment */
// gcc file_name.c -> save a /a.exe executable file which can be used to run code
// gcc file_name.c -o new_file_name.c -> create the executable file with /new_file_name.exe

#include <stdio.h> 
// preprocessor comman, tells compiler to include studio.h from standard library in this program.
int main() {    
// function from where compiler starts reading program, since int main so the return value should be of int datatype

    int number1, number2, sum, value; //integer data type
    double a=5;

    printf("Enter two integers: ");
    // print function
    /* The printf function is a part of the C standard library <stdio.h> and it can allow formatting the output in numerous ways.

    // Return Value
    printf() returns the number of characters printed after successful execution.
    If an error occurs, a negative value is returned.

    // Formatting in C printf
    In C, a value can be a character type, integer type, float type, and so on. To display and format these values using printf, we have format specifiers that are used in the formatted string. These format specifiers start with the percentage symbol ‘%’.

    *Syntax of Format Specifier: 
        %[flags][width][.precision][length]specifier

    Specifier: It is the character that denotes the type of data.
    %d: for printing integers
    %f: for printing floating-point numbers
    %c: for printing characters
    %s: for printing strings
    %p: for printing memory addresses
    %x: for printing hexadecimal values
    Width:
        It is the sub-specifier that denotes the minimum number of characters that will be printed.
        If the number of characters is less than the specified width, the white space will be used to fill the remaining characters’ places. But if the number of characters is greater than the specified width, all the characters will be still printed without cutting off any.
        Example
        printf("%25s", some_string);
        printf("%*s", 25, some_string);
    Precision subspecifier:  meaning differs for different format specifiers it is being used with.
        For Integral data(d, i, u, o, x, X): Specifies the minimum number of digits to be printed. But unlike the width sub-specifier, instead of white spaces, this sub-specifier adds leading zeroes to the number. If the number has more digits than the precision, the number is printed as it is.
        For Float or Double Data(f, e, a, A): Specifies the number of digits to be printed after the decimal point.
        For String (s): Specifies the length of the string to be printed.
        Example
        printf("%.10d", some_integer);
        printf("%.3f", some_float);
        printf("%.25s", some_string);
     Length: Specifies the length of the data type in the memory. It is used in correspondence with data type modifiers.
    There are 3 length sub-specifiers:
        h: With short int and unsigned short int
        l: With long int and unsigned long int.
        L: With long double
        Example
        printf("%lf", double_variable);
    */

    scanf("%d %d", &number1, &number2); //The scanf will write the value input by the user into the integer variables number1 and number 2.
    // scanf is a function that stands for Scan Formatted String. It is used to read data from stdin (standard input stream i.e. usually keyboard) and then writes the result into the given arguments.
    //It accepts character, string, and numeric data from the user using standard input. scanf also uses format specifiers like printf.
    /*
    %d to accept input of integers.
    %ld to  accept input of long integers
    %lld to accept input of long long integers
    %f to accept input of real number.
    %c to accept input of character types.
    %s to accept input of a string.
    
    Return Value of scanf
    The scanf in C returns three types of values:

    >0: The number of values converted and assigned successfully.
    0: No value was assigned.
    <0: Read error encountered or end-of-file(EOF) reached before any assignment was made.
    
    While scanning the input, scanf needs to store that input data somewhere. To store this input data, scanf needs to known the memory location of a variable. And here comes the ampersand to rescue.
    - & is also called as address of the operator.
    - For example, &var is the address of var.
    
    */



    // calculation
    sum = number1 + number2;   
    value = sum * 5;
    
    printf("(%d + %d) * %a = %d", number1, number2, value, "\n");
    // \n is an escape character in c
    /*
    Escape Sequence	Name	Description
    \b	Backspace	It is used to move the cursor one place backward.
    \f	Form Feed	It is used to move the cursor to the start of the next logical page.
    \n	New Line	It moves the cursor to the start of the next line.
    \r	Carriage Return	It moves the cursor to the start of the current line.
    \t	Horizontal Tab	It inserts some whitespace to the left of the cursor and moves the cursor accordingly.
    \v	Vertical Tab	It is used to insert vertical space.
    \\	Backlash	Use to insert backslash character.
    \’	Single Quote	It is used to display a single quotation mark.
    \”	Double Quote	It is used to display double quotation marks.
    \?	Question Mark	It is used to display a question mark.
    \ooo	Octal Number	It is used to represent an octal number.
    \xhh	Hexadecimal Number	It represents the hexadecimal number.
    \0	NULL	It represents the NULL character.
    */
    return 0;
    // return value of the main function
}




// VARIABLES IN C
/*
A variable in C is a memory location with some name that helps store some form of data and retrieves it when required. We can store different types of data in the variable and reuse the same variable for storing some other data any number of times.

data_type variable_name = value;    // defining single variable
            or
data_type variable_name1, variable_name2;    // defining multiple variable */
#include <stdio.h> 
    int main() { 
    int harryName;   // This is variable declaration. Most of the modern C compilers declare and define the variable in single step. 
    harryName = 76;  // This is variable initialization
    char five = '5'; // This is variable declaration and initialization/definition
    return 0;
}
/*
Rules for Naming Variables in C
You can assign any name to the variable as long as it follows the following rules:

1. A variable name must only contain alphabets, digits, and underscore.
2. A variable name must start with an alphabet or an underscore only. It cannot start with a digit.
3. No white space is allowed within the variable name.
4. A variable name must not be any reserved word or keyword.


C Variable Types

# C Local variables:
A local variable is declared inside a function. A local variable is visible only inside their function, only statements inside a function can access that local variable.
Local variables are declared when the function execution started and local variables get destroyed when the control exits from the function.

example:

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
Output:
Values in test() function p = 50 and q = 80
Values in main() function p = 22 and q = 44

Operating System calls the main() function at the time of execution. the local variables within the main() are created when the main() starts execution. When a call is made to test() function, first the control is transferred from main() to test(), next to the local variables within the test() is created and they are available only within the test() function.
After completion of execution of test() function, the local variables are destroyed and the control is transferred back to the main() function.


# C Global variables:
Global variables are declared outside of any function. A global variable is visible to every function and can be used by any piece of code. Unlike local variables, global variables retain their values between function calls and throughout the program execution.
Global variables are accessible in the entire program. If a local and global variable has the same name, then the local variable has the highest precedence to access within the function.

example:

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

Output:
In main() function a = 20
In test() function a = 40
In main() function a = 55

In the above code, the global variable a is declared outside of all the functions. So, the variable a can be accessed in every function. Operating System calls the main() function at the time of execution. the variable a has no local declaration, so it accesses the global variable a.
In test() function also there is no local declaration of variable a, the variable a gets access from the global. The global variables are destroyed only after the completion of the execution of the entire program.


# Static Variables in C
A static variable in C is a variable that is defined using the static keyword. It can be defined only once in a C program and its scope depends upon the region where it is declared (can be global or local).
The default value of static variables is zero.

Syntax of Static Variable in C
static data_type variable_name = initial_value;
As its lifetime is till the end of the program, it can retain its value for multiple function calls as shown in the example.

Example

// C program to demonstrate use of static variable
#include <stdio.h>

void function()
{
    int x = 20; // local variable
    static int y = 30; // static variable
    x = x + 10;
    y = y + 10;
    printf("\tLocal: %d\n\tStatic: %d\n", x, y);
}

int main()
{
    printf("First Call\n");
    function();
    printf("Second Call\n");
    function();
    printf("Third Call\n");
    function();
    return 0;
}

Output
First Call
    Local: 30
    Static: 40
Second Call
    Local: 30
    Static: 50
Third Call
    Local: 30
    Static: 60


# Automatic Variable in C
All the local variables are automatic variables by default. They are also known as auto variables.
Their scope is local and their lifetime is till the end of the block. If we need, we can use the auto keyword to define the auto variables.
The default value of the auto variables is a garbage value.

Syntax of Auto Variable in C
auto data_type variable_name;
        or
data_type variable_name;    (in local scope)

Example

// C program to demonstrate use of automatic variable
#include <stdio.h>

void function()
{
    int x = 10; // local variable (also automatic)
    auto int y = 20; // automatic variable
    printf("Auto Variable: %d", y);
}
int main()
{

    function();
    return 0;
}

Output
Auto Variable: 20

# External Variables in C
External variables in C can be shared between multiple C files. We can declare an external variable using the extern keyword.
Their scope is global and they exist between multiple C files.

Syntax of Extern Variables in C
extern data_type variable_name;

Example 
  ----------myfile.h------------
  extern int x=10;  //external variable (also global)
   
  ----------program1.c----------
  #include "myfile.h"
  #include <stdio.h>
  void printValue(){
  printf("Global variable: %d", x);
  }

# Register Variables in C
Register variables in C are those variables that are stored in the CPU register instead of the conventional storage place like RAM. Their scope is local and exists till the end of the block or a function.
These variables are declared using the register keyword.
The default value of register variables is a garbage value.

Syntax of Register Variables in C
register data_type variable_name = initial_value;
Example of Register Variables in C

// C program to demonstrate the definition of register
// variable
#include <stdio.h>

int main()
{
    //    register variable
    register int var = 22;

    printf("Value of Register Variable: %d\n", var);
    return 0;
}

Output
Value of Register Variable: 22

NOTE: We cannot get the address of the register variable using addressof (&) operator because they are stored in the CPU register. The compiler will throw an error if we try to get the address of register variable.

# Constact variable in C
constant variable in C is a read-only variable whose value cannot be modified once it is defined. We can declare a constant variable using the const keyword.

Syntax of Const Variable in C
const data_type variable_name = value;
Note: We have to always initialize the const variable at the definition as we cannot modify its value after defining.

*/



//DATA TYPE IN C

int main() { 
int var_name;
return 0;
}
/* 
used to store the integer numbers(any number including positive, negative and zero without decimal part)
Range:  -2,147,483,648 to 2,147,483,647
Size: 4 bytes
Format Specifier: %d
unsigned int: Unsigned int data type in C is used to store the data values from zero to positive numbers but it can’t store negative values like signed int.
short int: It is lesser in size than the int by 2 bytes so can only store values from -32,768 to 32,767.
long int: Larger version of the int datatype so can store values greater than int.
unsigned short int: Similar in relationship with short int as unsigned int with int.
Note: The size of an integer data type is compiler-dependent. We can use sizeof operator to check the actual size of any data type. */

int main() { 
float var_name;
return 0;
}
/*
used to store floating-point values. Float in C is used to store decimal and exponential values. It is used to store decimal numbers (numbers with floating point values) with single precision. 6 decimal precision
Range: 1.2E-38 to 3.4E+38
Size: 4 bytes
Format Specifier: %f */

int main() { 
char var_name = 'x';
return 0;
}
/*
allows its variable to store only a single character, in single comma as double comma is for string
Range: (-128 to 127) or (0 to 255)
Size: 1 byte
Format Specifier: %c */

int main() { 
double var_name;
return 0;
}
/* used to store decimal numbers (numbers with floating point values) with double precision. 15 decimal precision
Range: 1.7E-308 to 1.7E+308
Size: 8 bytes
Format Specifier: %lf */

//size of()
/* he size of the data types in C is dependent on the size of the architecture, so we cannot define the universal size of the data types. For that, the C language provides the sizeof() operator to check the size of the data types.
example: */

int main()
{
    int size_of_int = sizeof(int);
    int size_of_char = sizeof(char);
    int size_of_float = sizeof(float);
    int size_of_double = sizeof(double);
 
    printf("The size of int data type : %d\n", size_of_int);
    printf("The size of char data type : %d\n",
           size_of_char);
    printf("The size of float data type : %d\n",
           size_of_float);
    printf("The size of double data type : %d",
           size_of_double);
 
    return 0;
}


/*
Typecasting in C is the process of converting one data type to another data type by the programmer using the casting operator during program design.
Types:  Implicit type casting : Implicit type casting in C is used to convert the data type of any variable without using the actual value that the variable holds. It performs the conversions without altering any of the values which are stored in the data variable. Conversion of lower data type to higher data type will occur automatically.
        Explicit type casting : There are some cases where if the datatype remains unchanged, it can give incorrect output. In such cases, typecasting can help to get the correct output and reduce the time of compilation.
Syntax:

int x;
float y;
y = (float) x;

E.G., printf("\n You Entered %f as harryInput", (float) harryInput);

Example:
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

OUTPUT = 7.000000, REQUIRED OUTPUT = 7.500000

#include <stdio.h> 
  
// Driver Code 
int main() 
{ 
    // Given a & b 
    int a = 15, b = 2; 
    char x = 'a'; 
  
    double div; 
  
    // Explicit Typecasting in double 
    div = (double)a / b; 
  
    // converting x implicitly to a+3 i.e, a+3 = d 
    x = x + 3; 
  
    printf("The result of Implicit typecasting is %c\n", x); 
  
    printf("The result of Explicit typecasting is %f", div); 
  
    return 0; 
}
Output =
The result of Implicit typecasting is d
The result of Explicit typecasting is 7.500000


atof(): This function is used for converting the string data type into a float data type.
atbol(): This function is used for converting the string data type into a long data type.
Itoa(): This function is used to convert the long data type into the string data type.
itoba(): This function is used to convert an int data type into a string data type.
atoi(): This data type is used to convert the string data type into an int data type. 

*/



// CONSTANTS IN C

int main(){
const int /*data_type*/ var_name = 10 /*value*/;
return 0; }
/*
The constants in C are the read-only variables whose values cannot be modified once they are declared in the C program. The type of constant can be an integer constant, a floating pointer constant, a string constant, or a character constant. In C language, the const keyword is used to define the constants.
One thing to note here is that we have to initialize the constant variables at declaration. Otherwise, the variable will store some garbage value and we won’t be able to change it.

Properties of Constant in C
The important properties of constant variables in C defined using the const keyword are as follows:

1. Initialization with Declaration
We can only initialize the constant variable in C at the time of its declaration. Otherwise, it will store the garbage value.
2. Immutability
The constant variables in c are immutable after its definition, i.e., they can be initialized only once in the whole program. After that, we cannot modify the value stored inside that variable.

                             Constant                          ||                         Literals

Constants are variables that cannot be modified once declared. ||	Literals are the fixed values that define themselves.
Constants are defined by using the const keyword in C. 
They store literal values in themselves.	                   || They themselves are the values that are assigned to the variables or constants.
We can determine the address of constants.	                   || We cannot determine the address of a literal except string literal.
They are lvalues.	                                           || They are rvalues.
Example: const int c = 20.	                                   || Example: 24,15.5, ‘a’, “Geeks”, etc.


// #define const_name value
example:
// C Program to define a constant using #define */
#include <stdio.h>
#define pi 3.14
 
int main()
{
 
    printf("The value of pi: %.2f", pi);
    return 0;
}



//OPERATORS IN C
int main()
{
/*
Arithmetic Operators
Relational Operators
Logical Operators
Bitwise Operators
Assignment Operators
Misc Operators
*/
// Arithmetic Operators
int a = 60, b = 7, c = 8;
printf("The sum of a and b is %d\n", a + b);
printf("The difference of a and b is %d\n", a - b);
printf("The multiplication result of a and b is %d\n", a * b);
printf("The division result of a and b is %d\n", a / b);
printf("The modulo result of a and b is %d\n", a % b);
printf("The increment result of a is %d\n", ++a); //a = 7
printf("The decrement result of a is %d\n", --b); //b = 6
printf("The increment result of a is %d\n", a++); //6, a = 7
printf("The decrement result of a is %d\n", b--); //7, b = 6

// Relational Operators
int harry = 9, rohan = 45;
printf("%d\n", harry == rohan);
printf("%d\n", harry != rohan);
printf("%d\n", harry > rohan);
printf("%d\n", harry < rohan);

// Logical Operators
int h = 0, j = 1;
printf("The logical operator returned %d\n", h && j);
printf("The logical operaTor returned %d\n", h || j);
printf("The logical operator returned %d\n", !j);
printf("The logical operator returned %d\n", !h);

// Bitwise Operators
// A = 60 B=13
// A = 00111100
// B = 00001101
// R = 00001100 (&)
int A = 60, B = 14;
printf("Bitwise and operator returned %d\n", A & B);
printf("Bitwise or operator returned %d\n", A | B);
printf("Bitwise xor operator returned %d\n", A ^ B);
printf("Bitwise ones complement operator returned %d\n", ~B);
printf("Bitwise left shift operator operator returned %d\n", A << B);
printf("Bitwise right shift operator operator returned %d\n", A >> B);

// Assignment Operators
// =, +=, -=, *=, %=, etc
int ha = 9;
ha += 9;
printf("ha is %d\n", ha);

// Misc Operators - &, *, ?:

printf("\n\n*******Taking input from user in C*********");
int harryInput;
printf("\n Please enter the value of harryInput");
// scanf("%d", &harryInput);
// printf("\n You Entered %f as harryInput", (float) harryInput);
return 0;
}


// CONDITIONAL STATEMENT IN C
/*
IF-ELSE-IF-ELSE
if (condition)
{
    // Executes this block if
    // condition is true
}
else if (condition)
    statement;
.
.
else
{
    // Executes this block if
    // condition is false
}

NESTED IF-ELSE

if (condition1) 
{
   // Executes when condition1 is true
   if (condition_2) 
   {
      // statement 1
   }
   else
   {
         // Statement 2
    }
}
else {
     if (condition_3) 
   {
      // statement 3
   }
   else
   {
         // Statement 4
    }
}

SWITCH STATEMENTS : The switch case statement is an alternative to the if else if ladder that can be used to execute the conditional code based on the value of the variable specified in the switch statement.
Note: The switch expression should evaluate to either integer or character. It cannot evaluate any other data type.

switch (expression) {
    case value1:
        IF TRUE, ELSE NEXT CASE
        statements;
        BREAK
    case value2:
        IF TRUE, ELSE NEXT CASE
        statements;
        BREAK
    ....
    ....
    ....
    default:
        statements;
}

CONDITIONAL OPERATOR
(condition) ? [true_statements] : [false_statements];
e.g., int i4 = age > 3 ? 100 : 200; //if age>3, i4 = 100, else 200

JUMP STATEMENTS
1. break; This loop control statement is used to terminate the loop. As soon as the break statement is encountered from within a loop, the loop iterations stop there, and control returns from the loop immediately to the first statement after the loop.
2. continue; The continue statement forces the loop to continue or execute the next iteration. When the continue statement is executed in the loop, the code inside the loop following the continue statement will be skipped and the next iteration of the loop will begin
3. goto; The goto statement in C also referred to as the unconditional jump statement can be used to jump from one point to another within a function. 
    e.g., 

// C program to print numbers
// from 1 to 10 using goto
// statement
#include <stdio.h>

// function to print numbers from 1 to 10
void printNumbers()
{
    int n = 1;
label:
    printf("%d ", n);
    n++;
    if (n <= 10)
        goto label;
}
// Driver program to test above function
int main()
{
    printNumbers();
    return 0;
}

*/


// LOOPS IN C
/*
There are mainly two types of loops in C Programming:

Entry Controlled loops: In Entry controlled loops the test condition is checked before entering the main body of the loop. For Loop and While Loop is Entry-controlled loops.
Exit Controlled loops: In Exit controlled loops the test condition is evaluated at the end of the loop body. The loop body will execute at least once, irrespective of whether the condition is true or false. do-while Loop is Exit Controlled loop.


In For loop firstly we initialize the loop variable with some value, then check its test condition. If the statement is true then control will move to the body and the body of for loop will be executed. Steps will be repeated till the exit condition becomes true. If the test condition will be false then it will stop.

for (initialize expression; test expression; update expression)
{
    //
    // body of for loop
    //
}

example:
#include <stdio.h>
  
// Driver code
int main()
{
  int i = 0;
   
  for (i = 1; i <= 10; i++)
  {
    printf( "Hello World\n");   
  }
  return 0;
}

While loop does not depend upon the number of iterations. In for loop the number of iterations was previously known to us but in the While loop, the execution is terminated on the basis of the test condition. If the test condition will become false then it will break from the while loop else body will be executed.

initialization_expression;
while (test_expression)
{
    // body of the while loop
    
    update_expression;
}
example:
#include <stdio.h>
int main()
{
  // Initialization expression
  int i = 2; 
  
  // Test expression
  while(i < 10)
  {
    // loop body
    printf( "Hello World\n");   
     
    // update expression
    i++;
  } 
  return 0;
}

The do-while loop is similar to a while loop but the only difference is that in the do-while loop, the loop body will execute at least once irrespective of the test condition.

initialization_expression;
do
{
    // body of do-while loop
    
    
    update_expression;

} while (test_expression);
example:
#include <stdio.h>
  
// Driver code
int main()
{
  // Initialization expression
  int i = 2; 
   
  do
  {
    // loop body
    printf( "Hello World\n");   
  
    // Update expression
    i++;
     
    // Test expression
  }  while (i < 1);   
   
  return 0;
}
*/



// FUNCTION IN C
/*
A function in C is a set of statements that when called perform some specific task. It is the basic building block of a C program that provides modularity and code reusability.
Note: A function in C must always be declared globally before calling it.

Syntax of Functions in C
The syntax of function can be divided into 3 aspects:

How Does C Function Work?
Working of the C function can be broken into the following steps as mentioned below:
-->
Declaring a function: Declaring a function is a step where we declare a function. Here we define the return types and parameters of the function.
Defining a function: 
Calling the function: Calling the function is a step where we call the function by passing the arguments in the function.
Executing the function: Executing the function is a step where we can run all the statements inside the function to get the final result.
Returning a value: Returning a value is the step where the calculated value after the execution of the function is returned. Exiting the function is the final step where all the allocated memory to the variables, functions, etc is destroyed before giving full control to the main function.


Function Declaration
In a function declaration, we must provide the function name, its return type, and the number and type of its parameters. A function declaration tells the compiler that there is a function with the given name defined somewhere else in the program.
Syntax
return_type name_of_the_function (parameter_1, parameter_2);
Example
int sum(int a, int b);  // Function declaration with parameter names
int sum(int , int);      // Function declaration without parameter names

Function Definition
The function definition consists of actual statements which are executed when the function is called (i.e. when the program control comes to the function).
A C function is generally defined and declared in a single step because the function definition always starts with the function declaration so we do not need to declare it explicitly.
return_type function_name (para1_type para1_name, para2_type para2_name)
{
    // body of the function
}

Function Call
A function call is a statement that instructs the compiler to execute the function. We use the function name and parameters in the function call.
Note: Function call is neccessary to bring the program control to the function definition. If not called, the function statements will not be executed.
In the below example, the first sum function is called and 10,30 are passed to the sum function. After the function call sum of a and b is returned and control is also returned back to the main function of the program.
// C program to show function
// call and definition
#include <stdio.h>
// Function that takes two parameters 
// a and b as inputs and returns 
// their sum
int sum(int a, int b) 
{ 
  return a + b; 
}
// Driver code
int main()
{
  // Calling sum function and 
  // storing its value in add variable
  int add = sum(10, 30);
  
  printf("Sum is: %d", add);
  return 0;
}

Function Return Type
Function return type tells what type of value is returned after all function is executed. When we don’t want to return a value, we can use the void data type.
Example:
int func(parameter_1,parameter_2);
The above function will return an integer value after running statements inside the function.
Note: Only one value can be returned from a C function. To return multiple values, we have to use pointers or structures.

Function Arguments
Function Arguments (also known as Function Parameters) are the data that is passed to a function.
Example:
int function_name(int var1, int var2);

Passing Parameters to Functions
The data passed when the function is being invoked is known as the Actual parameters. In the above program, 10 and 30 are known as actual parameters. Formal Parameters are the variable and the data type as mentioned in the function declaration. In the below program, a and b are known as formal parameters.
We can pass arguments to the C function in two ways:
-->
Pass by Value
Pass by Reference

1. Pass by Value
Parameter passing in this method copies values from actual parameters into formal function parameters. As a result, any changes made inside the functions do not reflect in the caller’s parameters. 
Example:
// C program to show use 
// of call by value
#include <stdio.h>
void swap(int var1, int var2)
{
  int temp = var1;
  var1 = var2;
  var2 = temp;
}
// Driver code
int main()
{
  int var1 = 3, var2 = 2;
  printf("Before swap Value of var1 and var2 is: %d, %d\n",
          var1, var2);
  swap(var1, var2);
  printf("After swap Value of var1 and var2 is: %d, %d",
          var1, var2);
  return 0;
}
Output
Before swap Value of var1 and var2 is: 3, 2
After swap Value of var1 and var2 is: 3, 2

2. Pass by Reference
The caller’s actual parameters and the function’s actual parameters refer to the same locations, so any changes made inside the function are reflected in the caller’s actual parameters. 
Example:
// C program to show use of 
// call by Reference
#include <stdio.h>
void swap(int *var1, int *var2)
{
  int temp = *var1;
  *var1 = *var2;
  *var2 = temp;
}
// Driver code
int main()
{
  int var1 = 3, var2 = 2;
  printf("Before swap Value of var1 and var2 is: %d, %d\n",
          var1, var2);
  swap(&var1, &var2);
  printf("After swap Value of var1 and var2 is: %d, %d",
          var1, var2);
  return 0;
}
Output
Before swap Value of var1 and var2 is: 3, 2
After swap Value of var1 and var2 is: 2, 3

Types of Functions
There are two types of functions in C:

Library Functions : A library function is also referred to as a “built-in function”. A compiler package already exists that contains these functions, each of which has a specific meaning and is included in the package. Built-in functions have the advantage of being directly usable without being defined, whereas user-defined functions must be declared and defined before being used. 
User Defined Functions : Functions that the programmer creates are known as User-Defined functions or “tailor-made functions”. User-defined functions can be improved and modified according to the need of the programme

*/

// Recursion in C
/*
Recursion is the process of a function calling itself repeatedly till the given condition is satisfied. A function that calls itself directly or indirectly is called a recursive function and such kind of function calls are called recursive calls.
The fundamental of recursion consists of two objects which are essential for any recursive function. These are:
- Recursion Case : The recursion case refers to the recursive call present in the recursive function. It decides what type of recursion will occur and how the problem will be divided into smaller subproblems. 
- Base Condition : The base condition specifies when the recursion is going to terminate. It is the condition that determines the exit point of the recursion.

Note: It is important to define the base condition before the recursive case otherwise, the base condition may never encountered and recursion might continue till infinity.
The basic syntax structure of the recursive functions is:

type function_name (args) {
    // function statements
    // base condition
    // recursion case (recursive call)
}

// C Program to calculate the sum of first N natural numbers
// using recursion
#include <stdio.h>

int nSum(int n)
{
    // base condition to terminate the recursion when N = 0
    if (n == 0) {
        return 0;
    }

    // recursive case / recursive call
    int res = n + nSum(n - 1);

    return res;
}

int main()
{
    int n = 5;

    // calling the function
    int sum = nSum(n);

    printf("Sum of First %d Natural Numbers: %d", n, sum);
    return 0;
}

How Recursion works in C?
Recursion is considered difficult to understand by many people but once you understand the working of recursion, it becomes a powerful weapon in your arsenal to battle complex problems.
To understand how C recursion works, we will again refer to the example above and trace the flow of the program. In the nSum() function, Recursive Case is

int res = n + nSum(n - 1);

In the example, n = 5, so as nSum(5)’s recursive case, we get

int res = 5 + nSum(4);

In nSum(4), the recursion case and everything else will be the same, but n = 4. Let’s evaluate the recursive case for n = 4,

int res = 4 + nSum(3);

Similarly, for nSum(3), nSum(2) and nSum(1)

int res = 3 + nSum(2);    // nSum(3)
int res = 2 + nSum(1);    // nSum(2)
int res = 1 + nSum(0);    // nSum(1)

Let’s not evaluate nSum(0) and further for now.
Now recall that the return value of the nSum() function in this same integer named res. So, instead of the function, we can put the value returned by these functions. As such, for nSum(5), we get

int res = 5 + 4 + nSum(3);

Similarly, putting return values of nSum() for every n, we get

int res = 5 + 4 + 3 + 2 + 1 + nSum(0);

In nSum() function, the base condition is

if (n == 0) {
    return 0;
}

which means that when nSum(0) will return 0. Putting this value in nSum(5)’s recursive case, we get

int res = 5 + 4 + 3 + 2 + 1 + 0 = 15

At this point, we can see that there are no function calls left. So the recursion will stop here and the final value returned by the function will be 15 which is the sum of the first 5 natural numbers.


Memory Allocation for C Recursive Function
To further improve our understanding of recursion in C, we will look into how the recursion is internally handled by the C compiler and how the memory is managed for recursive functions.

- As you may know, all the function’s local variables and other stuff are stored inside the stack frame in stack memory and once the function returns some value, its stack frame is removed from the memory. The recursion follows a similar concept but with a little twist. In Recursion,
- A stack frame is created on top of the existing stack frames each time a recursive call is encountered and the data of each recursive copy of the function will be stored in their respective stack.
- Once, some value is returned by the function, its stack frame will be destroyed.
- The compiler maintains an instruction pointer to store the address of the point where the control should return in the function after its progressive copy returns some value. This return point is the statement just after the recursive call.
- After all the recursive copy returned some value, we come back to the base function and the finally return the control to the caller function.

Let’s use the first example again and see how the memory is managed for the nSum() function.

Step 1:
When nSum() is called from the main() function with 5 as an argument, a stack frame for nSum(5) is created.

Step 2:
While executing nSum(5), a recursive call is encountered as nSum(4). The compiler will now create a new stack frame on top of the nSum(5)’s stack frame and maintain an instruction pointer at the statement where nSum(4) was encountered.

Step 3:
In the execution of nSum(4), we encounter another recursive call as nSum(3). The compiler will again follow the same steps and maintain another instruction pointer and stack frame for nSum(3).

Step 4:
The same thing will happen with nSum(3), nSum(2), and nSum(1)’s execution.

Step 5:
But when the control comes to nSum(0), the condition (n == 0) becomes true and the statement return 0 is executed.

Step 6:
As the value is returned by the nSum(0), the stack frame for the nSum(0) will be destroyed. Using the instruction pointer, the program control will return to the nSum(1) function and the nSum(0) call will be replaced by value 0.

Step 7:
Now, in nSum(1), the expression int res = 1 + 0 will be evaluated and the statement return res will be executed. The program control will move to the nSum(2).

Step 8:
In nSum(2), nSum(1) call will be replaced by the value it returned, which is 1. So, after evaluating int res = 2 + 1, 3 will be returned to nSum(3). The same thing will keep happening till the control comes to the nSum(5) again.

Step 9:
When the control reaches the nSum(5), the expression int res = 5 + nSum(4) will look like int res = 5 + 10. Finally, this value will be returned to the main() function and the execution of nSum() function will be completed.


Stack Overflow
The program’s call stack has limited memory assigned to it by the operating system and is generally enough for program execution. But if we have a recursive function that goes on for infinite times, sooner or later, the memory will be exhausted and no more data can be stored. This is called stack overflow. In other words,

Stack overflow is the error that occurs occurs when the call stack of the program cannot store more data resulting in program termination.

It is one of the most common errors that is associated with the recursion.

*/


// ARRAYS IN C
/*
An array in C is a fixed-size collection of similar data items stored in contiguous memory locations. It can be used to store the collection of primitive data types such as int, char, float, etc., and also derived and user-defined data types such as pointers, structures, etc.
The C arrays are static in nature, i.e., they are allocated memory at the compile time.


1. Fixed Size
The array in C is a fixed-size collection of elements. The size of the array must be known at the compile time and it cannot be changed once it is declared.

2. Homogeneous Collection
We can only store one type of element in an array. There is no restriction on the number of elements but the type of all of these elements must be the same.

3. Indexing in Array
The array index always starts with 0 in C language. It means that the index of the first element of the array will be 0 and the last element will be N – 1.

4. Dimensions of an Array
A dimension of an array is the number of indexes required to refer to an element in the array. It is the number of directions in which you can grow the array size.

5. Contiguous Storage
All the elements in the array are stored continuously one after another in the memory. It is one of the defining properties of the array in C which is also the reason why random access is possible in the array.

6. Random Access
The array in C provides random access to its element i.e we can get to a random element at any index of the array in constant time complexity just by using its index number.

7. No Index Out of Bounds Checking
There is no index out-of-bounds checking in C/C++, for example, the following program compiles fine but may produce unexpected output when run.  



C Array Declaration
In C, we have to declare the array like any other variable before using it. We can declare an array by specifying its name, the type of its elements, and the size of its dimensions. When we declare an array in C, the compiler allocates the memory block of the specified size to the array name.

Syntax of Array Declaration
data_type array_name [size];
         or
data_type array_name [size1] [size2]...[sizeN]; //Multidimentional array
where N is the number of dimensions.

C Array Initialization
Initialization in C is the process to assign some initial value to the variable. When the array is declared or allocated memory, the elements of the array contain some garbage value. So, we need to initialize the array to some meaningful value. There are multiple ways in which we can initialize an array in C.

1. Array Initialization with Declaration
In this method, we initialize the array along with its declaration. We use an initializer list to initialize multiple elements of the array. An initializer list is the list of values enclosed within braces { } separated b a comma.

data_type array_name [size] = {value1, value2, ... valueN};

2. Array Initialization with Declaration without Size
If we initialize an array using an initializer list, we can skip declaring the size of the array as the compiler can automatically deduce the size of the array in these cases. The size of the array in these cases is equal to the number of elements present in the initializer list as the compiler can automatically deduce the size of the array.

data_type array_name[] = {1,2,3,4,5};
The size of the above arrays is 5 which is automatically deduced by the compiler.

3. Array Initialization after Declaration (Using Loops)
We initialize the array after the declaration by assigning the initial value to each element individually. We can use for loop, while loop, or do-while loop to assign the value to each element of the array.

for (int i = 0; i < N; i++) {
    array_name[i] = valuei;
}

Access Array Elements
We can access any element of an array in C using the array subscript operator [ ]  and the index value i of the element.

array_name [index];
One thing to note is that the indexing in the array always starts with 0, i.e., the first element is at index 0 and the last element is at N – 1 where N is the number of elements in the array.

Update Array Element
We can update the value of an element at the given index i in a similar way to accessing an element by using the array subscript operator [ ] and assignment operator =.

array_name[i] = new_value;
C Array Traversal
Traversal is the process in which we visit every element of the data structure. For C array traversal, we use loops to iterate through each element of the array.

Array Traversal using for Loop
for (int i = 0; i < N; i++) {
    array_name[i];
}

Relationship between Arrays and Pointers
Arrays and Pointers are closely related to each other such that we can use pointers to perform all the possible operations of the array. The array name is a constant pointer to the first element of the array and the array decays to the pointers when passed to the function.
// C Program to demonstrate the relation between arrays and
// pointers
#include <stdio.h>

int main()
{

    int arr[5] = { 10, 20, 30, 40, 50 };
    int* ptr = &arr[0];

    // comparing address of first element and address stored
    // inside array name
    printf("Address Stored in Array name: %p\nAddress of "
           "1st Array Element: %p\n",
           arr, &arr[0]);

    // printing array elements using pointers
    printf("Array elements using pointer: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", *ptr++);
    }
    return 0;
}
Output
Address Stored in Array name: 0x7ffcab67d8e0
Address of 1st Array Element: 0x7ffcab67d8e0
Array elements using pointer: 10 20 30 40 50 

Passing an Array to a Function in C
An array is always passed as pointers to a function in C. Whenever we try to pass an array to a function, it decays to the pointer and then passed as a pointer to the first element of an array.
// C Program to pass an array to a function
#include <stdio.h>

void printArray(int arr[])
{
    printf("Size of Array in Functions: %d\n", sizeof(arr));
    printf("Array Elements: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ",arr[i]);
    }
}

// driver code
int main()
{

    int arr[5] = { 10, 20, 30, 40, 50 };

    printf("Size of Array in main(): %d\n", sizeof(arr));
    printArray(arr);
    return 0;
}
Output
Size of Array in main(): 20
Size of Array in Functions: 8
Array Elements: 10 20 30 40 50 

Return an Array from a Function in C
In C, we can only return a single value from a function. To return multiple values or elements, we have to use pointers. We can return an array from a function using a pointer to the first element of that array.
// C Program to return array from a function
#include <stdio.h>

// function
int* func()
{
    static int arr[5] = { 1, 2, 3, 4, 5 };

    return arr;
}

// driver code
int main()
{

    int* ptr = func();

    printf("Array Elements: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", *ptr++);
    }
    return 0;
}
Output
Array Elements: 1 2 3 4 5 
Note: You may have noticed that we declared static array using static keyword. This is due to the fact that when a function returns a value, all the local variables and other entities declared inside that function are deleted. So, if we create a local array instead of static, we will get segmentation fault while trying to access the array in the main function.

*/


// Strings in C
/*
A String in C programming is a sequence of characters terminated with a null character ‘\0’. The C String is stored as an array of characters. The difference between a character array and a C string is that the string in C is terminated with a unique character ‘\0’.
Note: The C language does not provide an inbuilt data type for strings but it has an access specifier “%s” which can be used to print and read strings directly. 

C String Declaration Syntax
Declaring a string in C is as simple as declaring a one-dimensional array. Below is the basic syntax for declaring a string.

char string_name[size];

C String Initialization
1. Assigning a String Literal without Size
String literals can be assigned without size. Here, the name of the string str acts as a pointer because it is an array.

char str[] = "GeeksforGeeks";
2. Assigning a String Literal with a Predefined Size
String literals can be assigned with a predefined size. But we should always account for one extra space which will be assigned to the null character. If we want to store a string of size n then we should always declare a string with a size equal to or greater than n+1.

char str[50] = "GeeksforGeeks";
3. Assigning Character by Character with Size
We can also assign a string character by character. But we should remember to set the end character as ‘\0’ which is a null character.

char str[14] = { 'G','e','e','k','s','f','o','r','G','e','e','k','s','\0'};
4. Assigning Character by Character without Size
We can assign character by character without size with the NULL character at the end. The size of the string is determined by the compiler automatically.

char str[] = { 'G','e','e','k','s','f','o','r','G','e','e','k','s','\0'};
Note: When a Sequence of characters enclosed in the double quotation marks is encountered by the compiler, a null character ‘\0’ is appended at the end of the string by default.

The length of the string is the number of characters present in the string except for the NULL character. We can easily find the length of the string using the loop to count the characters from the start till the NULL character is found.

// C program to illustrate strings
 
#include <stdio.h>
#include <string.h>
 
int main()
{
    // declare and initialize string
    char str[] = "Geeks";
 
    // print string
    printf("%s\n", str);
 
    int length = 0;
    length = strlen(str);
 
    // displaying the length of string
    printf("Length of string str is %d", length);
 
    return 0;
}
Output
Geeks
Length of string str is 5

We can see in the above program that strings can be printed using normal printf statements just like we print any other variable. Unlike arrays, we do not need to print a string, character by character.

Note: The C language does not provide an inbuilt data type for strings but it has an access specifier “%s” which can be used to print and read strings directly. 


Read a String Input From the User
// C program to read string from user
#include<stdio.h>
   
int main()
{   
    // declaring string
    char str[50];
       
    // reading string
    scanf("%s",str);
       
    // print string
    printf("%s",str);
   
    return 0;
}
Input
GeeksforGeeks

Output
GeeksforGeeks

You can see in the above program that the string can also be read using a single scanf statement. Also, you might be thinking that why we have not used the ‘&’ sign with the string name ‘str’ in scanf statement! To understand this you will have to recall your knowledge of scanf. 
We know that the ‘&’ sign is used to provide the address of the variable to the scanf() function to store the value read in memory. As str[] is a character array so using str without braces ‘[‘ and ‘]’ will give the base address of this string. That’s why we have not used ‘&’ in this case as we are already providing the base address of the string to scanf.

// C Program to take input string which is separated by
// whitespaces
#include <stdio.h>
 
// driver code
int main()
{
 
    char str[20];
    // taking input string
    scanf("%s", str);
 
    // printing the read string
    printf("%s", str);
   
    return 0;
}
Input
Geeks for Geeks

Output
Geeks

Here, the string is read only till the whitespace is encountered.
Note: After declaration, if we want to assign some other text to the string, we have to assign it one by one or use the built-in strcpy() function because the direct assignment of the string literal to character array is only possible in declaration.


How to Read a String Separated by Whitespaces in C?
We can use multiple methods to read a string separated by spaces in C. The two of the common ones are:

1. We can use the fgets() function to read a line of string and gets() to read characters from the standard input  (stdin) and store them as a C string until a newline character or the End-of-file (EOF) is reached.
// C program to illustrate
// fgets()
#include <stdio.h>
#define MAX 50
int main()
{
    char str[MAX];
 
    // MAX Size if 50 defined
    fgets(str, MAX, stdin);
 
    printf("String is: \n");
 
    // Displaying Strings using Puts
    puts(str);
 
    return 0;
}

2. We can also scanset characters inside the scanf() function
// C Program to take string separated by whitespace using
// scanset characters
#include <stdio.h>
 
// driver code
int main()
{
 
    char str[20];
 
    // using scanset in scanf
    scanf("%[^\n]s", str);
 
    // printing read string
    printf("%s", str);
 
    return 0;
}

Passing Strings to Function
// C program to illustrate how to
// pass string to functions
#include <stdio.h>
 
void printStr(char str[]) { printf("String is : %s", str); }
 
int main()
{
    // declare and initialize string
    char str[] = "GeeksforGeeks";
 
    // print string by passing string
    // to a different function
    printStr(str);
 
    return 0;
}
Output:

String is : GeeksforGeeks
Note: We can’t read a string value with spaces, we can use either gets() or fgets() in the C programming language.

Strings and Pointers in C
In Arrays, the variable name points to the address of the first element.
Similar to arrays, In C, we can create a character pointer to a string that points to the starting address of the string which is the first character of the string. The string can be accessed with the help of pointers as shown in the below example. 
// C program to print string using Pointers
#include <stdio.h>
 
int main()
{
 
    char str[20] = "GeeksforGeeks";
 
    // Pointer variable which stores
    // the starting address of
    // the character array str
    char* ptr = str;
 
    // While loop will run till 
    // the character value is not
    // equal to null character
    while (*ptr != '\0') {
        printf("%c", *ptr);
       
        // moving pointer to the next character.
        ptr++;
    }
 
    return 0;
}
Output
GeeksforGeeks


Standard C Library – String.h  Functions
TABLE:

Function Name	Description
strlen(string_name)	Returns the length of string name.
strcpy(s1, s2)	Copies the contents of string s2 to string s1.
strcmp(str1, str2)	Compares the first string with the second string. If strings are the same it returns 0.
strcat(s1, s2)	Concat s1 string with s2 string and the result is stored in the first string.
strlwr()	Converts string to lowercase.
strupr()	Converts string to uppercase.
strstr(s1, s2)	Find the first occurrence of s2 in s1.

*/



// POINTERS IN C
/*
A pointer is defined as a derived data type that can store the address of other C variables or a memory location. We can access and manipulate the data stored in that memory location using pointers.
As the pointers in C store the memory addresses, their size is independent of the type of data they are pointing to. This size of pointers in C only depends on the system architecture.

Syntax of C Pointers
The syntax of pointers is similar to the variable declaration in C, but we use the ( * ) dereferencing operator in the pointer declaration.

datatype * ptr;

1. Pointer Declaration
In pointer declaration, we only declare the pointer but do not initialize it. To declare a pointer, we use the ( * ) dereference operator before its name.

Example
int *ptr;

2. Pointer Initialization
Pointer initialization is the process where we assign some initial value to the pointer variable. We generally use the ( &: ampersand ) addressof operator to get the memory address of a variable and then store it in the pointer variable.

Example
int var = 10;
int * ptr;
ptr = &var;

We can also declare and initialize the pointer in a single step. This method is called pointer definition as the pointer is declared and initialized at the same time.

Example
int *ptr = &var;
Note: It is recommended that the pointers should always be initialized to some value before starting using it. Otherwise, it may lead to number of errors.

3. Pointer Dereferencing
Dereferencing a pointer is the process of accessing the value stored in the memory address specified in the pointer. We use the same ( * ) dereferencing operator that we used in the pointer declaration.

// C program to illustrate Pointers
#include <stdio.h>

void geeks()
{
    int var = 10;

    // declare pointer variable
    int* ptr;

    // note that data type of ptr and var must be same
    ptr = &var;

    // assign the address of a variable to a pointer
    printf("Value at ptr = %p \n", ptr);
    printf("Value at var = %d \n", var);
    printf("Value at *ptr = %d \n", *ptr);
}

// Driver program
int main()
{
    geeks();
    return 0;
}
Output
Value at ptr = 0x7ffca84068dc 
Value at var = 10 
Value at *ptr = 10 


Types of Pointers in C
1. Integer Pointers
As the name suggests, these are the pointers that point to the integer values.

Syntax

int *ptr;

These pointers are pronounced as Pointer to Integer.

Similarly, a pointer can point to any primitive data type. It can point also point to derived data types such as arrays and user-defined data types such as structures.

2. Array Pointer
Pointers and Array are closely related to each other. Even the array name is the pointer to its first element. They are also known as Pointer to Arrays. We can create a pointer to an array using the given syntax.

Syntax

char *ptr = &array_name;

Pointer to Arrays exhibits some interesting properties which we discussed later in this article.

3. Structure Pointer
The pointer pointing to the structure type is called Structure Pointer or Pointer to Structure. It can be declared in the same way as we declare the other primitive data types.

Syntax

struct struct_name *ptr;

In C, structure pointers are used in data structures such as linked lists, trees, etc.

4. Function Pointers
Function pointers point to the functions. They are different from the rest of the pointers in the sense that instead of pointing to the data, they point to the code. Let’s consider a function prototype – int func (int, char), the function pointer for this function will be

Syntax

int (*ptr)(int, char);

Note: The syntax of the function pointers changes according to the function prototype.

5. Double Pointers
In C language, we can define a pointer that stores the memory address of another pointer. Such pointers are called double-pointers or pointers-to-pointer. Instead of pointing to a data value, they point to another pointer.

Syntax

datatype ** pointer_name;

Dereferencing Double Pointer

*pointer_name; // get the address stored in the inner level pointer
**pointer_name; // get the value pointed by inner level pointer

Note: In C, we can create multi-level pointers with any number of levels such as – ***ptr3, ****ptr4, ******ptr5 and so on.

6. NULL Pointer
The Null Pointers are those pointers that do not point to any memory location. They can be created by assigning a NULL value to the pointer. A pointer of any type can be assigned the NULL value.

Syntax

data_type *pointer_name = NULL;
        or
pointer_name = NULL

It is said to be good practice to assign NULL to the pointers currently not in use.

7. Void Pointer
The Void pointers in C are the pointers of type void. It means that they do not have any associated data type. They are also called generic pointers as they can point to any type and can be typecasted to any type.

Syntax

void * pointer_name;

One of the main properties of void pointers is that they cannot be dereferenced.

8. Wild Pointers
The Wild Pointers are pointers that have not been initialized with something yet. These types of C-pointers can cause problems in our programs and can eventually cause them to crash. If values is updated using wild pointers, they could cause data abort or data corruption.

Example

int *ptr;
char *str;

9. Constant Pointers
In constant pointers, the memory address stored inside the pointer is constant and cannot be modified once it is defined. It will always point to the same memory address.

Syntax

data_type * const pointer_name;

10. Pointer to Constant
The pointers pointing to a constant value that cannot be modified are called pointers to a constant. Here we can only access the data pointed by the pointer, but cannot modify it. Although, we can change the address stored in the pointer to constant.

Syntax

const data_type * pointer_name;

Other Types of Pointers in C:
There are also the following types of pointers available to use in C apart from those specified above:

Far pointer: A far pointer is typically 32-bit that can access memory outside the current segment.
Dangling pointer: A pointer pointing to a memory location that has been deleted (or freed) is called a dangling pointer.
Huge pointer: A huge pointer is 32-bit long containing segment address and offset address.
Complex pointer: Pointers with multiple levels of indirection.
Near pointer: Near pointer is used to store 16-bit addresses means within the current segment on a 16-bit machine.
Normalized pointer: It is a 32-bit pointer, which has as much of its value in the segment register as possible.
File Pointer: The pointer to a FILE data type is called a stream pointer or a file pointer.
Size of Pointers in C
The size of the pointers in C is equal for every pointer type. The size of the pointer does not depend on the type it is pointing to. It only depends on the operating system and CPU architecture. The size of pointers in C is 

8 bytes for a 64-bit System
4 bytes for a 32-bit System
The reason for the same size is that the pointers store the memory addresses, no matter what type they are. As the space required to store the addresses of the different memory locations is the same, the memory required by one pointer type will be equal to the memory required by other pointer types.

How to find the size of pointers in C?
We can find the size of pointers using the sizeof operator as shown in the following program:
// C Program to find the size of different pointers types
#include <stdio.h>

// dummy structure
struct str {
};

// dummy function
void func(int a, int b){};

int main()
{
    // dummy variables definitions
    int a = 10;
    char c = 'G';
    struct str x;

    // pointer definitions of different types
    int* ptr_int = &a;
    char* ptr_char = &c;
    struct str* ptr_str = &x;
    void (*ptr_func)(int, int) = &func;
    void* ptr_vn = NULL;

    // printing sizes
    printf("Size of Integer Pointer  \t:\t%d bytes\n",
           sizeof(ptr_int));
    printf("Size of Character Pointer\t:\t%d bytes\n",
           sizeof(ptr_char));
    printf("Size of Structure Pointer\t:\t%d bytes\n",
           sizeof(ptr_str));
    printf("Size of Function Pointer\t:\t%d bytes\n",
           sizeof(ptr_func));
    printf("Size of NULL Void Pointer\t:\t%d bytes",
           sizeof(ptr_vn));

    return 0;
}
Output
Size of Integer Pointer      :    8 bytes
Size of Character Pointer    :    8 bytes
Size of Structure Pointer    :    8 bytes
Size of Function Pointer    :    8 bytes
Size of NULL Void Pointer    :    8 bytes
As we can see, no matter what the type of pointer it is, the size of each and every pointer is the same.

Now, one may wonder that if the size of all the pointers is the same, then why do we need to declare the pointer type in the declaration? The type declaration is needed in the pointer for dereferencing and pointer arithmetic purposes.


C Pointer Arithmetic
The Pointer Arithmetic refers to the legal or valid arithmetic operations that can be performed on a pointer. It is slightly different from the ones that we generally use for mathematical calculations as only a limited set of operations can be performed on pointers. These operations include:

Increment in a Pointer: It is a condition that also comes under addition. When a pointer is incremented, it actually increments by the number equal to the size of the data type for which it is a pointer. 
For Example:
If an integer pointer that stores address 1000 is incremented, then it will increment by 4(size of an int), and the new address will point to 1004. While if a float type pointer is incremented then it will increment by 4(size of a float) and the new address will be 1004.

Decrement in a Pointer: It is a condition that also comes under subtraction. When a pointer is decremented, it actually decrements by the number equal to the size of the data type for which it is a pointer. 
For Example:
If an integer pointer that stores address 1000 is decremented, then it will decrement by 4(size of an int), and the new address will point to 996. While if a float type pointer is decremented then it will decrement by 4(size of a float) and the new address will be 996.

Addition of integer to a pointer
// C program to illustrate pointer Addition
#include <stdio.h>
 
// Driver Code
int main()
{
    // Integer variable
    int N = 4;
 
    // Pointer to an integer
    int *ptr1, *ptr2;
 
    // Pointer stores the address of N
    ptr1 = &N;
    ptr2 = &N;
 
    printf("Pointer ptr2 before Addition: ");
    printf("%p \n", ptr2);
 
    // Addition of 3 to ptr2
    ptr2 = ptr2 + 3;
    printf("Pointer ptr2 after Addition: ");
    printf("%p \n", ptr2);
 
    return 0;
}
Output
Pointer ptr2 before Addition: 0x7ffca373da9c 
Pointer ptr2 after Addition: 0x7ffca373daa8 

Subtraction of integer to a pointer
// C program to illustrate pointer Subtraction
#include <stdio.h>
 
// Driver Code
int main()
{
    // Integer variable
    int N = 4;
 
    // Pointer to an integer
    int *ptr1, *ptr2;
 
    // Pointer stores the address of N
    ptr1 = &N;
    ptr2 = &N;
 
    printf("Pointer ptr2 before Subtraction: ");
    printf("%p \n", ptr2);
 
    // Subtraction of 3 to ptr2
    ptr2 = ptr2 - 3;
    printf("Pointer ptr2 after Subtraction: ");
    printf("%p \n", ptr2);
 
    return 0;
}
Output
Pointer ptr2 before Subtraction: 0x7ffd718ffebc 
Pointer ptr2 after Subtraction: 0x7ffd718ffeb0 

Subtracting two pointers of the same type
// C program to illustrate Subtraction
// of two pointers
#include <stdio.h>
 
// Driver Code
int main()
{
    int x = 6; // Integer variable declaration
    int N = 4;
 
    // Pointer declaration
    int *ptr1, *ptr2;
 
    ptr1 = &N; // stores address of N
    ptr2 = &x; // stores address of x
 
    printf(" ptr1 = %u, ptr2 = %u\n", ptr1, ptr2);
    // %p gives an hexa-decimal value,
    // We convert it into an unsigned int value by using %u
 
    // Subtraction of ptr2 and ptr1
    x = ptr1 - ptr2;
 
    // Print x to get the Increment
    // between ptr1 and ptr2
    printf("Subtraction of ptr1 "
           "& ptr2 is %d\n",
           x);
 
    return 0;
}
Output
 ptr1 = 2715594428, ptr2 = 2715594424
Subtraction of ptr1 & ptr2 is 1

Comparison of pointers of the same type.
// C Program to illustrare pointer comparision
#include <stdio.h>
 
int main()
{
    // declaring array
    int arr[5];
 
    // declaring pointer to array name
    int* ptr1 = &arr;
    // declaring pointer to first element
    int* ptr2 = &arr[0];
 
    if (ptr1 == ptr2) {
        printf("Pointer to Array Name and First Element "
               "are Equal.");
    }
    else {
        printf("Pointer to Array Name and First Element "
               "are not Equal.");
    }
 
    return 0;
}
Output
Pointer to Array Name and First Element are Equal.

Comparison to NULL
A pointer can be compared or assigned a NULL value irrespective of what is the pointer type. Such pointers are called NULL pointers and are used in various pointer-related error-handling methods.
// C Program to demonstrate the pointer comparison with NULL
// value
#include <stdio.h>
 
int main()
{
 
    int* ptr = NULL;
 
    if (ptr == NULL) {
        printf("The pointer is NULL");
    }
    else {
        printf("The pointer is not NULL");
    }
    return 0;
}
Output
The pointer is NULL

Pointer Comparison in Array
C
// Pointer Comparision in Array
#include <stdio.h>
 
int main()
{
    int n = 10; // length of an array
 
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int* ptr; // Declaration of pointer variable
 
    ptr = arr; // Pointer points the first (0th index)
               // element in an array
    int count_even = 0;
    int count_odd = 0;
 
    for (int i = 0; i < n; i++) {
 
        if (*ptr % 2 == 0) {
            count_even++;
        }
        if (*ptr % 2 != 0) {
            count_odd++;
        }
        ptr++; // Pointing to the next element in an array
    }
    printf("No of even elements in an array is : %d",
           count_even);
    printf("\nNo of odd elements in an array is : %d",
           count_odd);
}
Output
No of even elements in an array is : 5
No of odd elements in an array is : 5

Pointer Arithmetic on Arrays
Pointers contain addresses. Adding two addresses makes no sense because there is no idea what it would point to. Subtracting two addresses lets you compute the offset between the two addresses. An array name acts like a pointer constant. The value of this pointer constant is the address of the first element.

For Example: if an array is named arr then arr and &arr[0] can be used to reference the array as a pointer.

// C program to illustrate the array
// traversal using pointers in 2D array
#include <stdio.h>
 
// Function to traverse 2D array
// using pointers
void traverseArr(int* arr, int N, int M)
{
 
    int i, j;
 
    // Traverse rows of 2D matrix
    for (i = 0; i < N; i++) {
 
        // Traverse columns of 2D matrix
        for (j = 0; j < M; j++) {
 
            // Print the element
            printf("%d ", *((arr + i * M) + j));
        }
        printf("\n");
    }
}
 
// Driver Code
int main()
{
 
    int N = 3, M = 2;
 
    // A 2D array
    int arr[][2] = { { 1, 2 }, { 3, 4 }, { 5, 6 } };
 
    // Function Call
    traverseArr((int*)arr, N, M);
    return 0;
}
Output
1 2 
3 4 
5 6 
*/




//STRUCTURES IN C
/*
The structure in C is a user-defined data type that can be used to group items of possibly different types into a single type. The struct keyword is used to define the structure in the C programming language. The items in the structure are called its member and they can be of any valid data type. Additionally, the values of a structure are stored in contiguous memory locations.

C Structure Declaration
Syntax
struct structure_name {
    data_type member_name1;
    data_type member_name1;
    ....
    ....
};

C Structure Definition
1. Structure Variable Declaration with Structure Template
struct structure_name {
    data_type member_name1;
    data_type member_name1;
    ....
    ....
}variable1, varaible2, ...;
2. Structure Variable Declaration after Structure Template
// structure declared beforehand
struct structure_name variable1, variable2, .......;

Access Structure Members
We can access structure members by using the ( . ) dot operator.
Syntax
structure_name.member1;
strcuture_name.member2;
In the case where we have a pointer to the structure, we can also use the arrow operator to access the members.


Initialize Structure Members
Structure members cannot be initialized with the declaration.

struct Point
{
   int x = 0;  // COMPILER ERROR:  cannot initialize members here
   int y = 0;  // COMPILER ERROR:  cannot initialize members here
};
The reason for the above error is simple. When a datatype is declared, no memory is allocated for it. Memory is allocated only when variables are created.

Default Initialization
By default, structure members are not automatically initialized to 0 or NULL. Uninitialized structure members will contain garbage values. However, when a structure variable is declared with an initializer, all members not explicitly initialized are zero-initialized.

struct Point
{    
     int x;    
     int y;
};

struct Point p = {0}; // Both x and y are initialized to 0
We can initialize structure members in 3 ways which are as follows:

Using Assignment Operator.
Using Initializer List.
Using Designated Initializer List.
1. Initialization using Assignment Operator
struct structure_name str;
str.member1 = value1;
str.member2 = value2;
str.member3 = value3;
.
.
.
2. Initialization using Initializer List
struct structure_name str = { value1, value2, value3 };
In this type of initialization, the values are assigned in sequential order as they are declared in the structure template.

3. Initialization using Designated Initializer List
Designated Initialization allows structure members to be initialized in any order. This feature has been added in the C99 standard.

struct structure_name str = { .member1 = value1, .member2 = value2, .member3 = value3 };


// C program to illustrate the use of structures
#include <stdio.h>

// declaring structure with name str1
struct str1 {
    int i;
    char c;
    float f;
    char s[30];
};

// declaring structure with name str2
struct str2 {
    int ii;
    char cc;
    float ff;
} var; // variable declaration with structure template

// Driver code
int main()
{
    // variable declaration after structure template
    // initialization with initializer list and designated
    //    initializer list
    struct str1 var1 = { 1, 'A', 1.00, "GeeksforGeeks" },
                var2;
    struct str2 var3 = { .ff = 5.00, .ii = 5, .cc = 'a' };

    // copying structure using assignment operator
    var2 = var1;

    printf("Struct 1:\n\ti = %d, c = %c, f = %f, s = %s\n",
           var1.i, var1.c, var1.f, var1.s);
    printf("Struct 2:\n\ti = %d, c = %c, f = %f, s = %s\n",
           var2.i, var2.c, var2.f, var2.s);
    printf("Struct 3\n\ti = %d, c = %c, f = %f\n", var3.ii,
           var3.cc, var3.ff);

    return 0;
}

Output
Struct 1:
    i = 1, c = A, f = 1.000000, s = GeeksforGeeks
Struct 2:
    i = 1, c = A, f = 1.000000, s = GeeksforGeeks
Struct 3
    i = 5, c = a, f = 5.000000
typedef for Structures
The typedef keyword is used to define an alias for the already existing datatype. In structures, we have to use the struct keyword along with the structure name to define the variables. Sometimes, this increases the length and complexity of the code. We can use the typedef to define some new shorter name for the structure.

Example

// C Program to illustrate the use of typedef with
// structures
#include <stdio.h>

// defining structure
typedef struct {
    int a;
} str1;

// another way of using typedef with structures
typedef struct {
    int x;
} str2;

int main()
{
    // creating structure variables using new names
    str1 var1 = { 20 };
    str2 var2 = { 314 };

    printf("var1.a = %d\n", var1.a);
    printf("var2.x = %d\n", var2.x);

    return 0;
}

Output
var1.a = 20
var2.x = 314


Nested Structures
C language allows us to insert one structure into another as a member. This process is called nesting and such structures are called nested structures. There are two ways in which we can nest one structure into another:

1. Embedded Structure Nesting
In this method, the structure being nested is also declared inside the parent structure.

Example

struct parent {
    int member1;
    struct member_str member2 {
        int member_str1;
        char member_str2;
        ...
    }
    ...
}
2. Separate Structure Nesting
In this method, two structures are declared separately and then the member structure is nested inside the parent structure.

Example

struct member_str {
    int member_str1;
    char member_str2;
    ...
}

struct parent {
    int member1;
    struct member_str member2;
    ...
}
One thing to note here is that the declaration of the structure should always be present before its definition as a structure member. For example, the declaration below is invalid as the struct mem is not defined when it is declared inside the parent structure.

struct parent {
    struct mem a;
};

struct mem {
    int var;
};
Accessing Nested Members
We can access nested Members by using the same ( . ) dot operator two times as shown:

str_parent.str_child.member;
Example of Structure Nesting

// C Program to illustrate structure nesting along with
// forward declaration
#include <stdio.h>

// child structure declaration
struct child {
    int x;
    char c;
};

// parent structure declaration
struct parent {
    int a;
    struct child b;
};

// driver code
int main()
{
    struct parent var1 = { 25, 195, 'A' };

    // accessing and printing nested members
    printf("var1.a = %d\n", var1.a);
    printf("var1.b.x = %d\n", var1.b.x);
    printf("var1.b.c = %c", var1.b.c);

    return 0;
}

Output
var1.a = 25
var1.b.x = 195
var1.b.c = A
Structure Pointer in C
We can define a pointer that points to the structure like any other variable. Such pointers are generally called Structure Pointers. We can access the members of the structure pointed by the structure pointer using the ( -> ) arrow operator.

Example of Structure Pointer

// C program to illustrate the structure pointer
#include <stdio.h>

// structure declaration
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

Output
1 2
Self-Referential Structures
The self-referential structures in C are those structures that contain references to the same type as themselves i.e. they contain a member of the type pointer pointing to the same structure type.

Example of Self-Referential Structures
struct structure_name {
    data_type member1;
    data_type member2;
    struct structure_name* str;
}

// C program to illustrate the self referential structures
#include <stdio.h>

// structure template
typedef struct str {
    int mem1;
    int mem2;
    struct str* next;
}str;

// driver code
int main()
{
    str var1 = { 1, 2, NULL };
    str var2 = { 10, 20, NULL };

    // assigning the address of var2 to var1.next
    var1.next = &var2;

    // pointer to var1
    str *ptr1 = &var1;

    // accessing var2 members using var1
    printf("var2.mem1: %d\nvar2.mem2: %d", ptr1->next->mem1,
           ptr1->next->mem2);

    return 0;
}

Output
var2.mem1: 10
var2.mem2: 20
Such kinds of structures are used in different data structures such as to define the nodes of linked lists, trees, etc.

C Structure Padding and Packing
Technically, the size of the structure in C should be the sum of the sizes of its members. But it may not be true for most cases. The reason for this is Structure Padding.

Structure padding is the concept of adding multiple empty bytes in the structure to naturally align the data members in the memory. It is done to minimize the CPU read cycles to retrieve different data members in the structure.

There are some situations where we need to pack the structure tightly by removing the empty bytes. In such cases, we use Structure Packing. C language provides two ways for structure packing:

Using #pragma pack(1)
Using __attribute((packed))__
Example of Structure Padding and Packing

// C program to illustrate structure padding and packing
#include <stdio.h>

// structure with padding
struct str1 {
    char c;
    int i;
};

struct str2 {
    char c;
    int i;
} __attribute((packed)) __; // using structure packing

// driver code
int main()
{

    printf("Size of str1: %d\n", sizeof(struct str1));
    printf("Size of str2: %d\n", sizeof(struct str2));
    return 0;
}

Output
Size of str1: 8
Size of str2: 5
As we can see, the size of the structure is varied when structure packing is performed.

To know more about structure padding and packing, refer to this article – Structure Member Alignment, Padding and Data Packing.

Bit Fields
Bit Fields are used to specify the length of the structure members in bits. When we know the maximum length of the member, we can use bit fields to specify the size and reduce memory consumption.

Syntax of Bit Fields
struct structure_name {
    data_type member_name: width_of_bit-field;
};
 Example of Bit Fields

// C Program to illustrate bit fields in structures
#include <stdio.h>

// declaring structure for reference
struct str1 {
    int a;
    char c;
};

// structure with bit fields
struct str2 {
    int a : 24; // size of 'a' is 3 bytes = 24 bits
    char c;
};

// driver code
int main()
{
    printf("Size of Str1: %d\nSize of Str2: %d",
           sizeof(struct str1), sizeof(struct str2));
    return 0;
}

Output
Size of Str1: 8
Size of Str2: 4

*/