# Object Oriented Programming in Python

Python allows for various programming paradigms:

- **Procedural Programming:** Code using procedures and functions.
- **Functional Programming:** Utilizes higher-order functions, lambda functions, and manipulates functions as first-class citizens.
- **Object Oriented Programming (OOP):** Involves creating and using classes and objects, organizing code to model real-world entities using concepts like inheritance, encapsulation, and polymorphism.

## Key Concepts

### Objects

- Objects are the basic runtime entities in an object-oriented system.
- They can represent real-world entities like a car, a person, or a bank account.
- They encapsulate data and methods.

In Python, concepts we are already very familiar with like integers, strings and dictionaries are all objects. Every object has a type, which defines what you can do with the object. For example, the int type defines what happens when adding something to an integer and what happens when trying to convert it to a string.

```py
x = 42
print("%d is an object of %s" % (x, type(x)))
​# 42 is an object of <class 'int'>

x = "Hello world!"
print("%s is an object of %s" % (x, type(x)))
# Hello world! is an object of <class 'str'>
```

### Classes

- Classes are the building blocks in OOP. The full definition of an object is an object's class.
- A class is like a template that describes the behaviors and states that objects of its type support.
- It can be considered a user-defined entity that combines data and functionality together.

### Components of a Class

- **Data Members (Attributes):** These are variables that hold data specific to a class.
- **Member Functions (Methods):** These are functions defined within a class that describe the behaviors of the objects.
- **Objects as Instances:** An object is an instance of a class.
- **Self:** The first argument to any method in a class is the instance of the class upon which the method is being called. Think of a class like a blueprint from which possibly many objects are built. The self argument is the mechanism Python uses so that the method can know which instance of the class it is being called upon.

## Immutable Classes

- **Immutable Classes:** Python classes whose objects cannot be modified once created. Any modification in immutable objects results in a new object.
- Objects of built-in types like `int`, `float`, `bool`, `str`, `tuple`, `unicode` are immutable in Python.
- Objects of built-in types like `list`, `set`, `dict` are mutable.

## Classes and Objects implementation

```py

#CLASSES (blueprint of an object)
class class_super1 :
    #attributes (variables)
    #class variable (shared by all instances of a class)
    atrbute4 = arg4

    # "self" refers/points to the object we are calling a function or attribute

    #instance variable (variable specific to an instance of a class)
    #constructors (used to initialize instance variables when an object is created) ; A constructor is executed as soon as an object of a class is instantiated.
    def __init__(self,para1,para2=None):    #: If no value is passed to a method for an argument though it is defined, its default value (e.g., None) is taken
        self.atrbute1 = para1
        self.atribute2 = para2
        #inner class object constructor
        self.inneratr =self.class_name2()

    #destructors (used to clean up resources when an object is destroyed.)
    #Python has a garbage collector that handles memory management automatically and efficiently even though you do not use a destructor.
      #Note: A destructor is executed as soon as an object of a class is deleted.

    def __del__(self):
        print("Done")


     #methods
     #instance methods :defined within a class that operate on instance variables; must take the first parameter as self.
    def meth1(self):
        print('this is', self, 'it has', self.atribute1)
    #classmethods (operate on class variables and don't need access to instance-specific data)
    @classmethod
    def meth2(cls):
          return cls.atrbute4
    #static methods (defined within a class but don't depend on class or instance data)
    @staticmethod
    def meth3():
          print('this is used for diferrentiating between classes')


      # Getter method
    def get_my_variable(self):
        return self.atrbute1

      # Setter method
    def set_my_variable(self, value):
        self.atrbute1 = value


    #inner class (class defined inside another class. It's often used for encapsulation (wrap data and the methods that work on that data into a single entity (a class)) and organization.)
    class class_name2:
            def __init__(self,para3):
                self.atrbute5 = para3
            def meth4(self):
                  print(self.atrbute5)
```

```py

#Objects
obj1 = class_super1() #print(obj1) <__main__.class_super1 object at 0x7f3d6b7f4da0>
obj1.atribute3 = arg3 # definining new attribute to obj1. Attributes are always public and can be accessed using the dot(.) operator.
# using constructors
obj2 = class_super1(arg1,arg2)
# instances of the same class, they represent two distinct objects in memory

#using a destructor
del obj1


#calling methods
#instance methods
class_super1.method(object)
            #OR
object.method()
#class or instance methods
class_super1.method()

#calling inner class object atrribute 
obj1.inneratr.atrbute5
#creating inner class object
obj3 = obj1.inneratr     ##inner class object constructor
      #OR 
obj3 = class_super1.class_name2()
```

## Inheritance

**Inheritance** allows a subclass (child class/derived class) to inherit the properties (methods, attributes) of the superclass (parent class/base class). The subclass can override the inherited properties.
  
### Key Points

- The priority of an attribute/method in the subclass is always higher than in the superclass. This is known as **attribute/method overriding**.
  
- When you create an object of a subclass:
  - It will first try to find the `__init__` method in the subclass.
  - If not found, it will call the `__init__` method of the superclass.

- Using `super()`:
  - When you call `super().__init__()`, it will first call the `__init__` method of the superclass, then the `__init__` method of the subclass.

- **Multiple Inheritance**:
  - In the case of multiple inheritance, Python uses the **Method Resolution Order (MRO)**, which calls the `__init__` methods and other methods of superclasses from left to right as they are defined in the inheritance hierarchy.

### Types of Inheritance

1. **Single Inheritance**:
   - A single superclass and a single subclass.
   - Example: `A --> B`
  
2. **Multilevel Inheritance**:
   - A chain of inheritance where a class is derived from another derived class.
   - Example: `A --> B --> C`
  
3. **Hierarchical Inheritance**:
   - Multiple subclasses inherit from the same superclass.
   - Example: `A --> B`, `A --> C`
  
4. **Multiple Inheritance**:
   - A subclass inherits from multiple superclasses.
   - Example: `A, B --> C`
  
5. **Hybrid Inheritance**:
   - A combination of multiple types of inheritance.
   - Example: `A, B --> C --> D`

### Inheritance Implementation

```py

# Initializing class_super1
class class_super1:
    def __init__(self):
        pass # placeholder

#single level inheritance (class inherits from only one parent class)
class subclass1(class_super1):
    def __init__(self):
        super().__init__()  # Correctly placed inside the __init__ method
        pass 
#multi level inheritance (chain of inheritance where a class derives from another derived class)
class subclass2(subclass1):
      pass
#multiple inheretence (class inherits from more than one parent class.)
class subclass3(class_super1,class_super2):
      pass
#hybrid inheritance (more than one forms of inheritance working at once)
class subclass3(subclass1,subclass3):
      pass
#hierarichal inheritance (multiple classes inherit from a single base class)
class subclass4(class_super1):
      pass

#Checking inheritance
isinstance(O, A) #returns True if the object O is an instance of the class A or other classes derived from it.
print(isinstance(obj1, subclass2)) #FALSE
issubclass(X, A) #returns True if the class X is a subclass of the class A.
print(issubclass(subclass2, class_super1))#TRUE

```

Here's the provided notes on polymorphism, operator overloading, method overloading, and more in Python, converted into Markdown format:

## Polymorphism

- **Polymorphism** is the ability of different classes to be treated as instances of a common base class, allowing them to be used interchangeably.

### Operator Overloading

**Operator overloading** refers to defining custom behaviors for standard operators (e.g., `+`, `-`, `*`, `/`) in a class. It allows objects of the class to use these operators in a way that makes sense for the objects' context.

#### Example: ComplexNumber Class

```python
class ComplexNumber:
    def __init__(self, real, imag):
        self.real = real
        self.imag = imag
        
    def __add__(self, other):
        real_sum = self.real + other.real
        imag_sum = self.imag + other.imag
        return ComplexNumber(real_sum, imag_sum)
    
    def __str__(self):
        return f"{self.real} + {self.imag}i"

# Create two complex numbers
num1 = ComplexNumber(2, 3)
num2 = ComplexNumber(1, 4)

# Use the + operator to add the numbers
result = num1 + num2

# Print the result
print(result)  # Output: 3 + 7i
```

### Method Overloading

**Method overloading** is customizing the behavior of standard methods for objects in a class. It involves defining multiple methods with the same name in a class, differing in the number or types of their parameters.

#### Example: Calculator Class

```python
class Calculator:
    def add(self, a, b):
        return a + b
    
    def add(self, a, b, c):
        return a + b + c

# Creating an instance of the Calculator class
calculator = Calculator()

# Call the add method with two arguments
result1 = calculator.add(2, 3)
print("Result with two arguments:", result1)

# Call the add method with three arguments
result2 = calculator.add(2, 3, 4)
print("Result with three arguments:", result2)
```

### Method Overriding

**Method overriding** is replacing a method in a subclass with a customized implementation that has the same name, return type, and parameters as the method in the superclass.

#### Example: Animal Class and Subclasses

```python
class Animal:
    def speak(self):
        print("This is an animal speaking.")
        
class Dog(Animal):
    def speak(self):
        print("Woof! I'm a dog.")
        
class Cat(Animal):
    def speak(self):
        print("Meow! I'm a cat.")

# Create instances of Dog and Cat
dog = Dog()
cat = Cat()

# Call the speak method on both objects
dog.speak()  # Output: Woof! I'm a dog.
cat.speak()  # Output: Meow! I'm a cat.
```

### Dunder/Magic/Special Methods in Python

**Dunder (Double Underscore) Methods** are special methods with double underscores at the beginning and end of their names. These methods allow the customization of standard Python behavior for user-defined classes.

#### Common Dunder Methods

- `__init__()` for object initialization.
- `__call__()` for callable objects.
- `__repr__()` for object representation.
- `__str__()` for object representation.
- `__add__()` for operator overloading.
- `__eq__()` for operator overloading.
- `__lt__()` for operator overloading.
- `__getitem__()` for iteration.
- `__len__()` for iteration.
- `__reversed__()` for iteration.
- `__enter__()` for context manager support.
- `__exit__()` for context manager support.

#### Example: PythonProgrammer Class

```python
class PythonProgrammer:
    def __init__(self, fullname):
        self.fullname = fullname
    
    def __repr__(self):
        return 'Items: {}'.format(self.fullname.split())
    
    def show(self):
        print(self.fullname)

# Create an instance of the PythonProgrammer class with the name "Guido van Rossum"
PP = PythonProgrammer("Guido van Rossum")

# When you print PP, it calls the __repr__ method, which returns a formatted string
print(PP)

# Call the show method, which prints the full name
PP.show()
```
