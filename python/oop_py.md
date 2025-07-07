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

So `L= [1,2,3]` is an object of type `list`, it is same as `L = list([1,2,3])` only that python provides special syntax for it (called Object Literal).

### Classes

- Classes are the building blocks in OOP. The full definition of an object is an object's class. Object is an instance of a class.
- A class is like a template that describes the behaviors and states that objects of its type support.
- It can be considered a user-defined entity that combines data and functionality together.
- **Immutable Classes:** Python classes whose objects cannot be modified once created. Any modification in immutable objects results in a new object.
  - Objects of built-in types like `int`, `float`, `bool`, `str`, `tuple`, `unicode` are immutable in Python.
  - Objects of built-in types like `list`, `set`, `dict` are mutable.
- While Python allows flexibility in naming, sticking to the ClassName (PascalCase/CamelCase) convention for classes is highly recommended. It improves code readability, promotes consistency, and aligns your code with the established best practices of the Python community.

### Components of a Class

- **Data Members (Attributes):** These are variables that hold data specific to a class. It's essentially a piece of data associated with an object or a class.
  - **Instance variable**
    - Variables that are specific to each instance of a class. Each instance has its own copy of these variables. Basically, all the attributes that are defined in the `__init__` method are instance variables. Instance variables are accessed using the `self` keyword.
    - It is adviced to encapsulate instance variables by prefixing them with a single underscore (e.g., `_balance`, `_pin`) to indicate that they are intended for internal use only. This is a convention in Python to suggest that these attributes should not be accessed directly from outside the class.
    - Use `getter` and `setter` methods to access and modify instance variables. This way you can control how the data is accessed and modified, ensuring that any necessary validation or logic is applied.
  - **Class variable**: Variables that are shared across all instances of a class. They are defined within the class but outside any instance methods. Class variables are accessed using the class name or through an instance of the class. Also called **static variables**. To access a class variable, use `ClassName.variable_name` or `class_object_name.variable_name`. Class variables are typically used for constants or shared data that should be the same for all instances of the class.
- **Member Functions (Methods):** These are functions defined within a class that describe the behaviors of the objects. Example: `len(L)` is a function while `L.append(4)` is a method of the list class.
  - **Static Methods**: Methods that don't need access to instance-specific data in the same way. Syntax: `ClassName.method()`. These methods are typically called directly on the class.
    - They are defined using the `@staticmethod` decorator.
    - They do not take `self` or `cls` as the first argument.
    - They can be called on the class itself or on an instance of the class.
    - They are used for utility functions that don't require access to instance or class data. Example: `ATM.is_valid_pin(pin)` could be a static method that checks if a given pin is valid without needing to access any instance-specific data.
    - They can be used as getter and setter methods for class variables. Example: `ATM.get_bank_name()` could be a static method that returns the bank name without needing to access any instance-specific data.
  - **Class Methods**: Methods that operate on the class itself rather than on instances. Syntax: `ClassName.method()`. These methods are typically called directly on the class.
    - They are defined using the `@classmethod` decorator.
    - They take `cls` as the first argument, which refers to the class itself.
    - They can be called on the class itself or on an instance of the class.
    - They are used for factory methods, alternative constructors, or methods that need to access class-level data. Example: `ATM.get_total_atms()` could be a class method that returns the total number of ATM instances created.
- **Objects as Instances:** An object is an instance of a class. For each object there is a separate copy of the class's attributes. A fundamental rule of **Object-Oriented Programming (OOP)** is that only an **object (instance)** of a **class** can access its own **data** and **methods**. This means that one method within a class cannot directly access another method or data of the same class without an object reference.
- **Self:** The first argument to any method in a class is the instance of the class upon which the method is being called. Think of a class like a blueprint from which possibly many objects are built. The `self` argument is the mechanism Python uses so that the method can know which instance of the class it is being called upon. `self` refers to the specific object (instance) that is currently calling a method. When you call a method like `my_object.some_method()`, Python implicitly passes `my_object` as the first argument to some_method. This argument is conventionally named `self`. If you define a method without self (e.g., `def create_pin():`), but then call it via an object (e.g., `my_atm.create_pin()`), Python will raise an error because the method received the `my_atm` object as an argument but wasn't expecting any positional arguments (`0 positional arguments were expected, but 1 was given`).
- **Magic Methods:** These are special methods that start and end with double underscores (e.g., `__init__`, `__str__`, `__add__`). They allow you to define how objects of a class behave with built-in operations like addition, string representation, etc.
  - **`__init__`**: This is the **constructor** method that is called when an object of a class is created. It initializes the object's attributes. Think of it as setting up the object's initial state. You might be wondering what kind of attributes should be initialized here. Since the constructor executes every time a new object is made, it's the perfect place to define attributes that are common to all objects of that class, or those that are essential for the object to function correctly from the moment it's created. For example, in an `ATM` class, every `ATM` object would need a `PIN number` and a `debit card number`.
  - **`__str__`**: This method defines the informal string representation of an object. It's what you see when you use `print()` on an object or convert it to a string using `str()`. Think of it as the "user-friendly" description. You'd typically use **`__str__`** to provide a human-readable summary of your object's state, making debugging and logging much clearer. Example: For a `Product` object, **`__str__`** might return `"Product: Laptop (ID: 123)"`.
  - **`__add__`, `__sub__`, `__mul__`, `__truediv__` (and others like `__floordiv__`, `__mod__`)**: These methods define how your objects behave when you use standard arithmetic operators like `+`, `-`, `*`, and `/` (true division). By implementing them, you can perform mathematical operations directly on instances of your custom classes.
    - `__add__(self, other)`: Defines behavior for the + operator.
    - `__sub__(self, other)`: Defines behavior for the - operator.
    - `__mul__(self, other)`: Defines behavior for the * operator.
    - `__truediv__(self, other)`: Defines behavior for the / operator (regular division, always returns a float).
  Example: For a `Vector` class, `__add__` would allow you to add two vector objects like `vector1 + vector2`. For a `Money` class, you could directly add or subtract amounts like `price + tax`.
  - **`__len__`**: This method defines the behavior for the built-in `len()` function. By implementing `__len__`, you can make your custom objects respond to `len()`, returning what their "length" means in context. Example: For a ShoppingCart class, `__len__` could return the total number of items in the cart. For a Playlist object, it might return the number of songs.
  - **`__getitem__`, `__setitem__`, `__delitem__`**: These methods define how your objects behave when you use square bracket notation (like []) for accessing, assigning, or deleting items. Implementing these allows your objects to act like sequences (lists, tuples) or mappings (dictionaries).
    - `__getitem__(self, key)`: Defines behavior for o`bject[key]` (getting an item).
    - `__setitem__(self, key, value)`: Defines behavior for `object[key] = value` (setting an item).
    - `__delitem__(self, key)`: Defines behavior for `del object[key]` (deleting an item).
  Example: For a `Matrix` class, `__getitem__` could allow you to access elements using `matrix[row, col]`. For a `Configuration` object, you could read settings like `config['database_url']`.
  - **`__del__`**: This is the **destructor** method that is called when an object is about to be destroyed. It can be used to clean up resources or perform final actions before the object is removed from memory. However, in Python, you usually don't need to define a destructor because Python has a garbage collector that automatically manages memory.  Python provides better, more reliable mechanisms for resource management: `with` statements, context managers, `finally` blocks, and the `__enter__` and `__exit__` methods. Unlike constructors (`__init__`) which are called when an object is created, `__del__` is called before the object is truly deleted from memory. This happens when: The object's reference count drops to zero (meaning no other part of the program is still pointing to it) OR the program is exiting.

### Encapsulation

When you create objects in Python, their **data (attributes)** and **methods** are, by default, accessible from outside the class. For example, if you have an `ATM` object, you can not only call its `deposit()` method but also directly access and even modify its `balance` or `pin` attributes (`my_atm.balance = 1000`).

This open accessibility can be problematic because:

1. **Accidental Corruption:** An external user or even another part of your own code could inadvertently change an attribute to an invalid type (e.g., setting `balance` to a string instead of a number), leading to crashes later when methods try to operate on that data.
2. **Violation of Logic:** Direct modification bypasses the intended logic and validation built into methods (like a `deposit()` method that might perform checks).

In languages like Java, this is solved with "access modifiers" (like `private`), which truly prevent external access. Python, however, takes a different approach.
Python doesn't have a strict `private` keyword. Instead, it uses a mechanism called **name mangling** for attributes (and methods) prefixed with **double underscores (`__`)**.

- **How it Works:** When you prefix an attribute or method name with two underscores (e.g., `__pin`, `__balance`), Python's interpreter automatically renames it internally. It prefixes the name with `_ClassName` (e.g., `__pin` in an `ATM` class becomes `_ATM__pin`).
- **Effect:** This effectively "hides" the attribute from direct external access by its original name. If you try to access `my_atm.__pin`, it will result in an `AttributeError` because that name doesn't exist anymore for external access.
- **Purpose:** The primary purpose of name mangling is to **prevent naming conflicts** in inheritance scenarios (where a subclass might accidentally override an attribute in a base class). Its secondary effect is to strongly suggest that an attribute is intended for internal use only.
- Now if you try `my_atm.__pin = 'full balance'`, it won't raise an error immediately, but it will create a new attribute `_ATM__pin` that is not the same as the original `__pin`. This can lead to confusion and bugs if someone later try to access `my_atm.__pin` expecting it to be the original attribute.
- If you try to access it using the mangled name (e.g., `my_atm._ATM__pin`), you can still do so, but this is discouraged as it goes against the intended encapsulation.
- So basically **Nothing is really private in Python**. Hiding data members (attributes) using the double underscore prefix is a good practice in class design. It helps prevent accidental misuse and clarifies which parts of your class's state are meant to be internal. However, understand that this is Python's way of encouraging responsible coding through convention, rather than enforcing strict privacy.

**Getter and Setter methods** are used to access and modify private attributes of a class. They provide controlled access to the attributes, allowing you to enforce rules or validation when getting or setting values. This way you have encapsulated the data and provided a controlled interface for accessing and modifying it.

Example:

```py
class ATM:
    # --- 1. Class Variable ---
    # This variable belongs to the class itself, not to any specific ATM object.
    # All ATM instances will share the same BANK_NAME.
    BANK_NAME = "MyPythonBank"
    _ATM_COUNT = 0 # Another class variable to track number of ATMs

    # --- 2. Constructor Method (__init__) ---
    # This is a special method called automatically when you create a new ATM object.
    # It initializes the instance variables (attributes) for that specific object.
    # 'self' is a mandatory first parameter.
    def __init__(self, card_number: str, initial_pin: int, initial_balance: float):
        # --- 'self' ---
        # 'self' refers to the *instance* of the class that is currently being created or operated on.
        # It allows you to access and set the instance's own attributes and call its methods.

        # --- Instance Variables (Encapsulated/Hidden) ---
        # These attributes define the unique state of *each* ATM object.
        # We use double underscores (__) to indicate that these are intended to be
        # "private" or internal to the object, demonstrating encapsulation.
        # Python performs "name mangling" on them, making them harder to access directly from outside.
        self.__card_number = card_number
        self.__pin = initial_pin
        self.__balance = initial_balance

        # We can also increment a class variable here to count instances
        ATM._ATM_COUNT += 1
        print(f"ATM for card {self.__card_number} created with initial balance {self.__balance}.")
        print(f"Total ATMs in service: {ATM._ATM_COUNT}")

    # --- 3. Methods (Behaviors) ---
    # These are functions defined within the class that operate on the object's data.
    # They always take 'self' as their first parameter.

    def deposit(self, amount: float):
        """Allows depositing money into the ATM account."""
        if amount > 0:
            self.__balance += amount # Accessing instance variable via self
            print(f"Deposited {amount}. New balance: {self.__balance}")
        else:
            print("Deposit amount must be positive.")

    def withdraw(self, amount: float, entered_pin: int):
        """Allows withdrawing money from the ATM account after PIN verification."""
        if entered_pin != self.__pin: # Accessing encapsulated instance variable
            print("Invalid PIN. Withdrawal failed.")
            return

        if amount <= 0:
            print("Withdrawal amount must be positive.")
        elif amount > self.__balance: # Accessing encapsulated instance variable
            print("Insufficient funds.")
        else:
            self.__balance -= amount
            print(f"Withdrew {amount}. New balance: {self.__balance}")

    # --- 4. Getter Method ---
    # A method used to safely retrieve the value of an encapsulated (private) attribute.
    # This provides controlled access to the internal state.
    def get_balance(self) -> float:
        """Returns the current balance of the ATM account."""
        return self.__balance

    # --- 5. Setter Method ---
    # A method used to safely modify the value of an encapsulated (private) attribute.
    # Setters often include validation logic to ensure data integrity.
    def set_pin(self, old_pin: int, new_pin: int):
        """Allows changing the PIN after verifying the old PIN."""
        if old_pin == self.__pin: # Verify old PIN
            if 1000 <= new_pin <= 9999: # Simple PIN validation
                self.__pin = new_pin # Update encapsulated instance variable
                print("PIN successfully changed.")
            else:
                print("New PIN must be a 4-digit number.")
        else:
            print("Incorrect old PIN. PIN change failed.")

    def display_info(self):
        """Displays public information about the ATM account."""
        print(f"\n--- ATM Account Info for Card: {self.__card_number} ---")
        print(f"Bank Name: {ATM.BANK_NAME}") # Accessing class variable
        print(f"Current Balance: {self.get_balance()}") # Using the getter method
        print("---------------------------------------")

# --- Demonstrating the ATM Class and Concepts ---

print("--- Creating ATM Objects ---")
# Creating the first ATM object (instance)
# The __init__ constructor runs here.
atm1 = ATM("1234-5678-9012-3456", 1234, 1500.0)

# Creating a second ATM object
atm2 = ATM("9876-5432-1098-7654", 5678, 250.0)

print("\n--- Accessing Class Variables ---")
print(f"Bank Name (via class): {ATM.BANK_NAME}")
print(f"Total ATMs (via class): {ATM._ATM_COUNT}")
print(f"Bank Name (via instance): {atm1.BANK_NAME}") # Can also access via instance

print("\n--- Demonstrating Encapsulation and Getters/Setters ---")

# Accessing balance using the getter method (preferred way)
atm1.display_info()
atm2.display_info()

# Attempting to directly access "private" attributes (will fail or be mangled)
# print(atm1.__pin) # This would result in an AttributeError
# print(atm1.__balance) # This would result in an AttributeError

# How Python internally renames it (don't do this in real code!)
# print(atm1._ATM__pin) # This works, but breaks encapsulation principle

# Using methods to interact with the object's state
print("\n--- Performing Operations on atm1 ---")
atm1.deposit(500.0)
atm1.withdraw(200.0, 1234) # Correct PIN
atm1.withdraw(2000.0, 1234) # Insufficient funds
atm1.withdraw(100.0, 9999) # Incorrect PIN

print("\n--- Changing PIN for atm1 ---")
atm1.set_pin(1234, 9876) # Correct old PIN
atm1.set_pin(1111, 5432) # Incorrect old PIN

atm1.display_info() # Display updated info

print("\n--- Performing Operations on atm2 ---")
atm2.deposit(100.0)
atm2.withdraw(300.0, 5678) # Correct PIN, but exact amount
atm2.display_info()
```

### Using Objects

- **Creating Objects:** You create an object by calling the class as if it were a function. This invokes the `__init__` method of the class. For example, if you have a `Customer` class and you want to create an object for a specific customer, you would do something like `customer1 = Customer("John Doe", "Male")`.
- Note that Customer("John Doe", "Male") creates an object of the Customer class, and the `__init__` method is called with the arguments `"John Doe"` and `"Male"`. But `customer1` is not the object, rather `customer1` is a reference to the object created by the `Customer` class and called reference variable. The object itself is stored in memory, and `customer1` points to that memory location.
- **Pass by reference**: When you pass an object to a function, you're passing a reference to the object. This means that the function can modify the object directly, without making a copy of it. Example:

    ```py
    def update_customer(customer):
        customer.name = "Jane Doe"  # Modifies the original object
        print(id(customer)) # prints id of passed object
    cust = Customer()
    print(id(cust)) # some id
    update_customer(cust) # prints same id
    ```

- **Collection of Objects**: You can store multiple objects in a collection, such as a list or a dictionary. Example: `customers = [customer1, customer2, customer3]`. Also you can run a loop on a collection of objects and access their attributes. Example: `for customer in customers: print(customer.name)`
- **Calling Instance Methods**: Instance methods operate on the data unique to an individual object. There are two primary ways to call them:
  - **Using the Object Directly (Most Common)**: This is the standard way you'll see instance methods called. You simply use dot notation on your object. Syntax: `object.method()`. When you call a method this way, Python automatically passes the object itself as the first argument (which gets received by the self parameter in the method's definition). Example: `customer1.deposit(100)`
  - **Calling via the Class (Less Common for Instance Methods)**: While less frequent for instance methods, you can call them directly through the class name. However, when you do this, you must explicitly pass the object that the method should operate on as the first argument. Syntax: `ClassName.method(object, other_arguments...)`. You're bypassing Python's automatic self passing. You need to provide the self argument yourself. Example: `Customer.deposit(customer2, 50)`
- **Calling Class Methods (and Static Methods)**: Class methods (and static methods) are associated with the class itself, not a specific instance. They don't operate on instance-specific data in the same way. Syntax: `ClassName.method()`. These methods are typically called directly on the class.
  - **Class methods** (decorated with `@classmethod`) receive the class itself as the first argument (conventionally `cls`). Example: `Customer.get_total_customers()`
  - **Static methods** (decorated with `@staticmethod`) receive no special first argument (neither self nor cls). Example: `Customer.is_valid_name("")`
- **Calling Inner Class Methods**: If you have an inner class (a class defined within another class), you can create an instance of the inner class and call its methodsin a similar, but nested, fashion.
  - **Creating an Inner Class Object:** You create an instance of the inner class by referencing it through the outer class. Syntax: `obj_of_inner_class = OuterClass.InnerClass()`. You're telling Python to find `InnerClass` within `OuterClass` and then call its constructor.
  - **Accessing Inner Class Object Attributes:** Once you have an object of the inner class, you access its attributes using standard dot notation. Syntax: `obj_of_inner_class.attribute_name`. **Or**, if the inner class object is an attribute of the outer class object (`self.inneratr = self.InnerClass()` inside `__init__` of `outer_class`), you chain the dot notation. Syntax: `outer_obj.inner_obj_attribute_name.attribute_of_inner_obj`, so in this case `obj2.attribute_name` where `obj2 = obj1.inneratr` and `obj1 = outer_class()` thus creating an `InnerClass` object. Example: `customer1.account.deposit(100)`
  - Note that if you have an `OuterClass` that defines an `InnerClass` inside it, and within the `OuterClass`'s `__init__` method you write `self.inner_attribute = self.InnerClass()`, you are creating a new instance of `InnerClass` and immediately assigning it to an attribute (e.g., `inner_attribute`) of the *current* `OuterClass` instance. When you then create an `OuterClass` object (like `obj1 = OuterClass()`), this assignment happens automatically, and `obj1.inner_attribute` now holds a specific `InnerClass` object that "belongs" to `obj1`. If you then set `obj3 = obj1.inner_attribute`, `obj3` becomes a reference to *that exact `InnerClass` object* which is an integral part of `obj1`. This `InnerClass` object is tied to `obj1`'s existence. In contrast, if you create an `InnerClass` object directly using `obj3 = OuterClass.InnerClass()`, you are creating a completely separate, standalone `InnerClass` object that has no inherent connection or "ownership" by any particular `OuterClass` instance. Both `obj3` from `obj1.inner_attribute` and `obj3` from `OuterClass.InnerClass()` are indeed objects of `InnerClass`, and once you have either of them, you access their own methods (like `obj3.inner_method()`) in the exact same way. However, the crucial difference lies in their relationship with any `OuterClass` instance: the `InnerClass` object obtained via `obj1.inner_attribute` is implicitly associated with `obj1`, whereas the one created directly is not linked to any specific outer instance. Neither type of `InnerClass` object can directly access `OuterClass` methods or attributes on its own; for that, you would typically need to explicitly pass a reference to the `OuterClass` instance (e.g., `parent=self`) into the `InnerClass`'s constructor if that bidirectional communication is required. Continuing, while both `obj3 = obj1.inneratr` and `obj3 = OuterClass.InnerClass()` yield an object of `InnerClass`, their relationship to the outer class and thus their ability to access its methods fundamentally differs. When you have `obj3 = obj1.inneratr`, `obj3` is a specific `InnerClass` instance that was created *by* `obj1` (an `OuterClass` instance) and lives as one of `obj1`'s attributes; this implies a direct ownership, so calling `obj3.inner_method()` correctly executes a method belonging to that specific inner object. Conversely, when `obj3 = OuterClass.InnerClass()` is used, `obj3` is an entirely standalone `InnerClass` object, created independently, with no inherent link to any specific `OuterClass` instance. Despite this difference in creation and relationship, the way you call *their own* `InnerClass` methods (e.g., `obj3.some_inner_method()`) is identical for both, as they are both valid `InnerClass` instances. The crucial distinction arises when attempting to access `OuterClass` methods or attributes *from within* the `InnerClass` object: by default, neither type of `InnerClass` object possesses an implicit reference to its enclosing `OuterClass` instance. This means that an `InnerClass` method cannot simply call `self.outer_method()` to reach a method of `OuterClass`; if an `InnerClass` object needs to interact with its "parent" `OuterClass` instance, that `OuterClass` instance must be explicitly passed to the `InnerClass`'s constructor (e.g., `self.inner_obj = self.InnerClass(parent=self, ...)`) so the `InnerClass` object retains a reference (`self.parent`) through which it can then access `self.parent.outer_method()`. Without such an explicit reference, the `InnerClass` remains conceptually isolated from its outer container, regardless of how it was instantiated.

## Classes and Objects implementation

```py

#CLASSES (blueprint of an object)
class class_super1 :
    #attributes (variables)
    #class variable (shared by all instances of a class)
    atrbute4 = arg4

    # "self" refers/points to the object we are calling a function or attribute, that is id(object) == id(self).

    #instance variable (variable specific to an instance of a class)
    #constructors (used to initialize instance variables when an object is created) ; A constructor is executed as soon as an object of a class is instantiated. Since, a constructor has attributes that define the state of an object and end user can not access those attributes, ideally one should use it to define those attributes that are common to all objects, for example in a `Atm` class it could be the pin number, debit card number etc.
    def __init__(self,para1,para2=None):    #: If no value is passed to a method for an argument though it is defined, its default value (e.g., None) is taken
        self.atrbute1 = para1
        self.atribute2 = para2
        #inner class object constructor
        self.inneratr = self.class_name2()

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

## Aggregation

## Inheritance

**Inheritance** allows a subclass (child class/derived class) to inherit the properties (methods, attributes) of the superclass (parent class/base class). The subclass can override the inherited properties (means it can provide its own implementation). It is a way to create a new class based on an existing class, allowing for code reuse and the creation of hierarchical relationships between classes.

### Key Points

- The priority of an attribute/method in the subclass is always higher than in the superclass. This is known as **attribute/method overriding**.
  
- When you create an object of a subclass:
  - It will first try to find the `__init__` method in the subclass.
  - If not found, it will call the `__init__` method of the superclass.
  - If there is no constructor (`__init__`) defined in the subclass, the constructor of the superclass will be called implicitly.

```py
class Parent:
    def __init__(self,num):
        self.__num=num
    def get_num(self):
        return self.__num

class Child(Parent):
    def __init__(self,val,num):
        self.__val=val
    def get_val(self):
        return self.__val

son=Child(100,10) # Since Child class does not call Parent's constructor, it will not initialize __num
print(son.get_val()) # prints 100
print("Parent: Num:",son.get_num()) # This will raise an AttributeError because __num is not initialized in Child class (Not because it is encapsulated)
```

- Encapsulated methods and attributes (those prefixed with double underscores, like `__hidden_item`) **are not directly inherited** by subclasses in Python. This is because Python's double-underscore mechanism implements **name mangling** (renaming `__hidden_item` to `_ClassName__hidden_item` internally within the defining class) rather than true privacy. While a subclass cannot directly access these inherited items using their original `__name` (e.g., `self.__hidden_item`), they can be accessed via their mangled name (e.g., `self._ParentClassName__hidden_item`) or, more commonly and properly, through public getter/setter methods defined in the parent class that are themselves inherited. **Note** that the following will still work:

    ```py
    class parent:
        def __init__(self,num):
            self.__num = num
        def get_num(self):
            return self.__num

    class Child(Parent):
        def show(self):
            print("This is in child class")

    son = Child(100) # Uses the parent class constructor to initialize the object
    print(son.get_num()) # prints 100, since it uses the inherited getter method
    # son.__num # This will raise an AttributeError because __num is not directly accessible
    # However, you can access it using the mangled name:
    print(son._parent__num) # prints 100
    son.show() # "This is in child class"
    ```

- **Using `super()`**:
  - The `super()` function provides a way to access methods and attributes of a parent or sibling class from within a child class. It's particularly vital in complex inheritance hierarchies to ensure that methods are called in the correct order across the inheritance chain.
  - **`super().__init__()` for Constructor Chaining:** When you call `super().__init__(*args, **kwargs)` within a child class's `__init__` method, you are explicitly telling Python to invoke the `__init__` method of the immediate parent class. This is crucial because it allows the parent class to perform its own essential initialization steps, such as creating its specific instance attributes. It is standard practice to make this call the first line in your child class's `__init__` method. Doing so ensures that all of the parent's necessary attributes are properly set up before the child class adds its own attributes or relies on inherited ones, preventing potential `AttributeError` issues.
  - `super()` is designed to be used exclusively inside class definitions, typically within methods. It's not meant for use outside of a class context.
  - It's important to clarify that attributes are indeed inherited in Python. While `super().__init__()` doesn't directly inherit attributes in the sense of making copies, it is the mechanism that ensures the parent class's `__init__` method is executed. When the parent's `__init__` runs, it sets up its instance variables (e.g., self.__num) on the object, making those attributes a part of the child's instance state. Class attributes, on the other hand, are inherited directly by default simply by virtue of the class hierarchy. We can inherit attributes from parents class by using the `super()` function. Example: `super().attribute_name`.
  - We can also inherit methods from parents class by using the `super()` function. Example: `super().method_name(*args)`. If there is a case of Multilevel Inheritance (e.g., Grandparent -> Parent -> Child), `super()` will call the method of the Parent class that is closest to the child class in the inheritance hierarchy. Similarly, in Multiple Inheritance (e.g., Child(ParentA, ParentB)), `super()` resolves which parent's method to call based on the **Method Resolution Order (MRO)**. The MRO is the specific order in which Python searches for methods and attributes in a class hierarchy, typically moving from left to right among parent classes and then upwards. You can inspect a class's MRO using `ClassName.mro()` or `help(ClassName)`.

```py
class Parent:
    def __init__(self,num):
        self.__num=num
    def get_num(self):
        return self._num

class Child(Parent):
    def __init__(self,num,val):
        super().__init__(num) # Call the parent class constructor to initialize __num
        # Now we can safely use self.__num in this class
        self.__val=val
    def get_val(self):
        return self.__val

son=Child(100,200) # Initialize the object
print(son.get_num()) # prints 100, since it uses the inherited getter method
print(son.get_val()) # prints 200, since it uses the child class's own getter method
```

### Types of Inheritance

1. **Single Inheritance**:
   - A single superclass and a single subclass.
   - Example: `A --> B`. Now `B` can access the attributes and methods of `A`.
   - Syntax: `class Subclass(Superclass):`
  
2. **Multilevel Inheritance**:
   - A chain of inheritance where a class is derived from another derived class.
   - Example: `A --> B --> C`. Now `C` can access the attributes and methods of both `B` & `A`, and `B` can access the attributes and methods of `A`. If a method exists in both `B` and `A`, `B`’s version takes priority.
   - Syntax: `class Subclass(Superclass):` where `Superclass` is also a subclass of another class.
  
3. **Hierarchical Inheritance**:
   - Multiple subclasses inherit from the same superclass.
   - Example: `A --> B`, `A --> C`. Now `B` and `C` can access the attributes and methods of `A`.
   - Syntax: `class Subclass1(Superclass):` and `class Subclass2(Superclass):`
  
4. **Multiple Inheritance**:
   - A subclass inherits from multiple superclasses.
   - Example: `A, B --> C`. Now `C` can access the attributes and methods of both `A` and `B`.
   - Syntax: `class Subclass(Superclass1, Superclass2):`
   - If there is no `__init__` method in the child class, Python will traverse the inheritance hierarchy and call the `__init__` method of the first parent class that has one. If there are multiple parent classes with an `__init__` method, then we have a conflict and Python uses the **Method Resolution Order (MRO)** to resolve it, which calls the `__init__` methods and other methods of superclasses from left to right as they are defined in the inheritance hierarchy. The same MRO is followed for resolving methods with the same name across multiple parent classes.
  
5. **Hybrid Inheritance**:
   - A combination of multiple types of inheritance.
   - Example: `A, B --> C --> D`. Now `D` can access the attributes and methods of `A`, `B` and `C`, and `C` can access the attributes and methods of `A` and `B`.

```py
# Tricky example
class A:
    def m1(self):
        return 20

class B(A):
    def m1(self):
        val = super().m1() + 30
        return val

class C(B):
    def m1(self):
        val = self.m1() + 20  # This will cause infinite recursion!
        return val

obj = C()
print(obj.m1()) # Error: maximum recursion depth exceeded
```

### Inheritance Implementation

```py

# Initializing class_super1
class class_super1:
    def __init__(self):
        pass # placeholder

# single level inheritance (class inherits from only one parent class)
class subclass1(class_super1):
    def __init__(self):
        super().__init__()  # Correctly placed inside the __init__ method
        pass 
# multi level inheritance (chain of inheritance where a class derives from another derived class)
class subclass2(subclass1):
      pass
# multiple inheretence (class inherits from more than one parent class.)
class subclass3(class_super1,class_super2):
      pass
# hybrid inheritance (more than one forms of inheritance working at once)
class subclass3(subclass1,subclass3):
      pass
# hierarichal inheritance (multiple classes inherit from a single base class)
class subclass4(class_super1):
      pass

# Checking inheritance
isinstance(O, A) # returns True if the object O is an instance of the class A or other classes derived from it.
print(isinstance(obj1, subclass2)) #FALSE
issubclass(X, A) # returns True if the class X is a subclass of the class A.
print(issubclass(subclass2, class_super1)) # TRUE
```

## Polymorphism

**Polymorphism** is the ability of different classes to be treated as instances of a common base class, allowing them to be used interchangeably.
In simple terms, it allows objects of different classes to be treated as objects of a common type, or for a single interface to represent multiple underlying forms.

### Operator Overloading

**Operator overloading** refers to defining custom behaviors for standard operators (e.g., `+`, `-`, `*`, `/`, `>`, `==`, `[]`) in a class. It allows objects of the class to use these operators in a way that makes sense for the objects' context.
Python achieves operator overloading by implementing specific "magic methods" (also known as "dunder methods" because of their double underscores, like `__add__` for `+`, `__sub__` for `-`, `__eq__` for `==`, etc.). When Python sees an operator used with your object, it automatically calls the corresponding magic method behind the scenes.

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

In many languages (like Java or C++), method overloading allows you to define multiple methods within the same class that have the same name but differ in their parameter list (e.g., number of parameters, types of parameters, or order of parameters). The compiler then determines which method to call based on the arguments provided. Python does NOT support traditional method overloading in the same way. Due to Python's dynamic typing and the way it handles function definitions (the last definition of a function with a given name simply overwrites previous ones in the same scope), you cannot have multiple methods with the exact same name but different signatures within a single class.

Python prioritizes flexibility and readability. Instead of strict overloading, Python provides more flexible ways to achieve similar functionality:

- **Default Argument Values:** Provide default values for parameters, making some arguments optional.
- **Variable-Length Arguments (`*args`and `**kwargs`)**: Allow a method to accept an arbitrary number of positional (*args) or keyword (**kwargs) arguments.

#### Example: Calculator Class

```python
class Calculator:
    def add(self, a, b=None, c=None):
        """
        A flexible 'add' method demonstrating Python's approach to 'overloading'.
        It can add two or three numbers.
        """
        if b is None and c is None:
            # If only one argument is provided, maybe it's not meant for addition
            # or it's an error for this context. We'll just return it.
            print("Please provide at least two numbers to add.")
            return a
        elif c is None:
            # Add two numbers
            return a + b
        else:
            # Add three numbers
            return a + b + c

    def display(self, message, style="normal", prefix=""):
        """
        A flexible display method using default arguments.
        """
        formatted_message = message
        if style == "upper":
            formatted_message = formatted_message.upper()
        if prefix:
            formatted_message = f"[{prefix}] {formatted_message}"
        print(formatted_message)

# --- Demonstration ---
calc = Calculator()
print("\n--- Method 'Overloading' (Pythonic Way) ---")
print(f"Adding two: {calc.add(10, 20)}") # Calls add with two numbers
print(f"Adding three: {calc.add(1, 2, 3)}") # Calls add with three numbers
calc.add(5) # Example with one argument, handled by the logic

calc.display("Hello world") # Uses default style and no prefix
calc.display("Important message", style="upper") # Uses upper style
calc.display("Debug info", prefix="DEBUG") # Uses prefix
```

### Method Overriding

**Method overriding** occurs when a subclass (child class) provides its own specific implementation for a method that is already defined in its superclass (parent class). The method in the subclass has the exact same name, number of parameters, and return type (in strongly typed languages) as the method in the superclass.
It allows you to customize or specialize the behavior inherited from a parent class without modifying the parent class itself. This is crucial for creating hierarchical structures where common actions exist but need different specifics for different types of objects.

#### Example: Vehicle Class with Method Overriding

```python
class Vehicle:
    def __init__(self, name):
        self.name = name

    def move(self):
        """A generic way for a vehicle to move."""
        print(f"{self.name} is moving in a generic way.")

class Car(Vehicle):
    def __init__(self, name, model):
        super().__init__(name) # Call parent's constructor
        self.model = model

    def move(self): # Method Overriding: specific implementation for Car
        """How a Car moves."""
        print(f"{self.name} ({self.model}) is driving on the road.")

class Bicycle(Vehicle):
    def __init__(self, name, type):
        super().__init__(name) # Call parent's constructor
        self.type = type

    def move(self): # Method Overriding: specific implementation for Bicycle
        """How a Bicycle moves."""
        print(f"{self.name} ({self.type}) is pedaling along.")

# --- Demonstration ---
generic_vehicle = Vehicle("Generic Transporter")
my_car = Car("Ford", "Mustang")
my_bike = Bicycle("Mountain Bike", "MTB")

# Calling 'move()' on different objects, but each behaves differently due to overriding
print("--- Method Overriding ---")
generic_vehicle.move() # Generic Transporter is moving in a generic way.
my_car.move() # Ford (Mustang) is driving on the road.
my_bike.move() # Mountain Bike (MTB) is pedaling along.
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
