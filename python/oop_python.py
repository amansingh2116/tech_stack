# OBJECT ORIENTED PROGRAMMING IN PYTHON
#python allows procedural (code using procedures and functions), functional (higher-order functions, lambda functions, and manipulate functions as first-class citizens.) and object oriented programming ( create and use classes and objects, and organize your code in a way that models real-world entities using inheritance, encapsulation, and polymorphism.)

# Objects are the basic runtime entities in an object-oriented system. Objects encapsulate data and method.
# Classes are the building blocks in OOP
# A class is like a template that describes the behaviors/states that objects of its type support. It can be considered as a user-defined entity that can combine data and functionality together.
# A class contains:
# Data members known as attributes of the class
# Member functions known as methods of the class
# An object is an instance of a class


# Immutable classes are Python classes whose objects can not be modified once created, and such objects are known as immutable objects. Any modification in immutable objects results into a new object.
# Objects of built-in types like int, float, bool, str, tuple, unicode are immutable in Python.
# Objects of built-in types like list, set, dict are mutable.


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


#INHERITANCE #subclass (child class/derived class) inherits the properties(methods,attributes) of the superclass (parent class/base class) and not vice versa
#Priority of an attribute/method in the subclass is always more than in the superclass. This is reflected through attribute/method overriding
#if you create object of subclass it will first try find init of subclass, if not found  it will call init of superclass.
#if you call super (super().__init__()), then it will first call init of super class then call init of sub class
#In case of multiple inheritance by method resolution order (MRO), it will call init and methods of left to right superclasses

# Single Inheritance: A --> B
# Multilevel Inheritance: A --> B --> C
# Hierarchical Inheritance: A --> B, A --> C
# Multiple Inheritance: A, B --> C
# Hybrid Inheritance: A, B --> C --> D


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


#POLYMORPHISM ( ability of different classes to be treated as instances of a common base class, allowing them to be used interchangeably.)


#operator overloading (Operator overloading refers to defining custom behaviors for standard operators (e.g., +, -, *, /) in a class. It allows objects of the class to use these operators in a way that makes sense for the objects' context.)
#we have different methods for different operators called as magic methods, all these operators behind the scene they work as methods, so we can define them/change their definitions explicitly

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



#method overloading ( Customizing the behavior of standard METHODS for objects in a class. OR Defining multiple methods with the same name in a class, differing in the number or types of their parameters.)

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



#method overriding (Replacing a method in a subclass with a customized implementation that has the same name, return type, and parameters as the method in the superclass.)

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



# Dunder/Magic/Special methods in Python
# __init__() for object initialization
# __call__() for callable objects
# __repr__() for object representation
# __str__() for object representation
# __add__() for operator overloading
# __eq__() for operator overloading
# __lt__() for operator overloading
# __getitem__() for iteration
# __len__() for iteration
# __reversed__() for iteration
# __enter__() for context manager support
# __exit__() for context manager support
# Note: Dunder signifies Double Underscores.

#example:
# Define a class called PythonProgrammer
class PythonProgrammer:
    # Constructor method to initialize an instance with a 'fullname' attribute
    def __init__(self, fullname):
        self.fullname = fullname
    # Custom string representation method
    def __repr__(self):
        # Format and return a string with the fullname split into a list of words
        return 'Items: {}'.format(self.fullname.split())
    # Method to print the full name
    def show(self):
        print(self.fullname)
# Create an instance of the PythonProgrammer class with the name "Guido van Rossum".
PP = PythonProgrammer("Guido van Rossum")
# When you print PP, it calls the __repr__ method, which returns a formatted string.
print(PP)
# Call the show method, which prints the full name.
PP.show()