# Python for ML

## Basics

### Order of Operations

Just like everywhere else, Python works on a specific order of operations. That order is:
**P**arentheses -> **E**xponents -> **M**ultiplication -> **A**ddition -> **S**ubtraction

### Zipping Items

Finally, it might be useful to combine -- or zip -- two lists together. For example, we might want to create a new list that pairs the values in our price_usd list with our area_m2 list. To do that, we use the zip method. The code looks like this:

```py
new_list = zip(price_usd, area_m2)
print(new_list)
zipped_list = list(new_list)
print(zipped_list)
```

**OUTPUT:**

<zip object at 0x7d5a5450db80>
[(97919.38, 187.0), (300511.2, 82.0), (293758.14, 235.0)]

You might have noticed that the above code involving putting one list (in this case, new_list) inside another list (in this case, list). This approach is called a generator.

#### Example

```py
def find_max_price(area_meter2, price_per_meter2):
    """
    Given two lists, the first with areas of properties
    and the second with price per unit area, this function
    returns the most expensive property using list comprehension

    input: area_meter2, list with the total area of each property
    input: price_per_meter2, list with price per unit area of each property
    output: the price of the most expensive property
    """
    
    return [i*j for i,j in list(zip(area_meter2, price_per_meter2))] #list comprehension


find_max_price(surface_total_in_m2, price_usd_per_m2)
```

### JSON

JSON stands for Java Script Object Notation, and it's a text format for storing and transporting data.

#### Working with JSON

JSON works by creating key-value pairs, where the key is data that can be represented by letters (called a string). JSON values can be strings, numbers, objects, arrays, boolean data, or null. JSON usually comes as a list of dictionaries, which look like this:

Here's an example from our colombia-real-estate-1 dataset with two key-value pairs that both include string values:

```py
[
    {"property_type": "house", "department": "bogota"},
    {"property_type": "house", "department": "bogota"},
    {"property_type": "house", "department": "bogota"},
]
```

### glob

When the list of files is short like this one, it's not difficult to find the ones we want, but if the list were longer, we might need some help. If we're only interested in finding files that deal with Mexico, we could search the files for files beginning with mexico-city-real-estate-. To do this, we'll use the .glob function. The code looks like this:

```py
import glob
​
glob.glob("./data/mexico-city-real-estate-[0-9].csv")
```

The `.glob` function allows for pattern matching. In this example [0-9] allows for any digit between 0 and 9, but there are lots of other patterns that .glob can find. Here are a few of the more common ones:

- \* Match any number of characters
- ? Match a single character of any kind
- [a-z] Match any lower case alphabetical character in the current locale
- [A-Z] Match any upper case alphabetical character in the current locale
- [!a-z] Do not match any lower case alphabetical character in the current locate

So, if we wanted to find all the files from Mexico City, we would use code like this: `glob.glob("./data/mexico-city*")`

> TRY:
Change "mexico-city-real-estate-1" to "mexico-city-real-estate" using replace. Hint: To delete a character, we can replace it with an empty string ("").
>`file_name = "mexico-city-real-estate-1"`
`modified_file_name = file_name.replace("-1", "")`
`modified_file_name`
​
**OUTPUT**:-
'mexico-city-real-estate'

### Working with f-strings

We usually use print to examine output in Python, but most of the examples we've been printing have been relatively short. Formatted strings are helpful for all sorts of reasons, but when we're assembling and formatting a long string, using the print function can be difficult and time-consuming. Along the same lines, it's also useful to directly evaluate variables and expressions within strings. To do those things, we create f"" strings. The code looks like this:

```py
import datetime
​
python_birthday = datetime.datetime(year=1991, month=2, day=20)
print(python_birthday)
print(
    f"Python first appeared on {python_birthday:%B %d} in the year {python_birthday:%Y}."
)
​
now = datetime.datetime.now()
print(f"Python is {now.year - python_birthday.year} years old.")
```

**Output**:-

> 1991-02-20 00:00:00
Python first appeared on February 20 in the year 1991.
Python is 33 years old.

### Working with Error

#### Error Handling

Error handling is a very important part of coding. It will make sure our code runs smoothly even with edge cases. try and except are the syntax we use in error handling. Let's create a function to demonstrate how this works.

We start with a function that calculates the quotient of two numbers. There are two inputs of the function: nominator and denominator. The function works only when:

- both inputs are numerical numbers
- the denominator is not zero

We can use try and except to make sure the function runs smoothly even with error inputs.

```py
def get_quotient(nominator, denominator):
    try:
        quotient = nominator / denominator
        return quotient
    except:  # noQA E722
        return print("function not working")
```

The function will return the quotient as long as there are no errors.

`get_quotient(1, 2)`
> 0.5

The function will go the except section and print a message when inputs are wrong:

`get_quotient(1, 0)`
> function not working

#### Raising Errors

Even though the previous function can handle the errors, it doesn't tell us what is the error causing the issue. In this case, we can print out the error message:

```py
def get_quotient(nominator, denominator):
    try:
        quotient = nominator / denominator
        return quotient
    except Exception as e:
        return print(e)
```

Now we can see the error message when denominator is zero:

`get_quotient(1, 0)`
> division by zero

### Saving and Loading Files with joblib

We can also use joblib's dump and load functions to save and load data. Besides saving and loading data, we can also save and load trained models for later use. Let's say an example here. First, we import joblib and train a model for the iris dataset:

```py
from joblib import dump, load
from sklearn import datasets, svm
​
iris = datasets.load_iris()
X, y = iris.data, iris.target
​
clf = svm.SVC()
clf.fit(X, y)
```

#### Saving model to a path

```py
dump(clf, "data/trained_model.pkl")
```

#### Load data from a path and make predictions again

```py
model = load("data/trained_model.pkl", mmap_mode="r")
model.predict(X)
```

### Working with Filepaths

A filepath is a directory to a specific file. Python uses the os module to work with path names and access files in the local directory. Here are some common use cases of the os module:

`os.getcwd()` points to the current working directory:

```py
import os
​
print(f"Current working directory is at {os.getcwd()}")
```

> Current working directory is at /home/jovyan/work/ds-curriculum/@textbook

Let's see the following functions with an example.

`pathname = "/home/jovyan/work/ds_curriculum/myfile.txt"`

`os.path.abspath(pathname) # returns a path name to the path passed as the parameter to this function`

> '/home/jovyan/work/ds_curriculum/myfile.txt'

If you only give a file name as the parameter, it will return a path with the current working directory and the file name:

`filename = "myfile.txt"`

`os.path.abspath(filename)`
> '/home/jovyan/work/ds-curriculum/@textbook/myfile.txt'

```py
os.path.dirname(pathname) # will leave the file name part, and only show the directory of a path name
'/home/jovyan/work/ds_curriculum'

os.path.basename(pathname) # will only show the file name of a path name
'myfile.txt'

os.path.split(pathname) # splits a full path name and returns a tuple containing the path and filename. The first part of the tuple is the path to the file, the second part is the file
('/home/jovyan/work/ds_curriculum', 'myfile.txt')

print(os.path.join("/new_directory", "myfile.txt")) # constructs a path name out of one or more partial path names. Note the function will add an extra slash to the path name before joining it to the filename
/new_directory/myfile.txt
```

### Testing Code

Python has a very useful function isinstance that can be used to check the type of an object. The following example checks whether the object is an integer.

`isinstance(1, int)`
You can leverage the any and all function to apply conditions on multiple objects. For example, the following function checks whether any element of the inputs list is string:

`inputs = [1, 2]`
`isinstance(any(inputs), str)`
> False # Since they are all integers

`isinstance(all(inputs), (int, float))`
> True

You can add an `assert` function to your code to make sure you are using the right input data before you run the code. If the statement after assert is True, the code will continue and nothing will be produced. If assert is False, then it will throw an error. You will use the error to debug your code.

`assert isinstance(1, int)`

**Example:**

```py
def get_quotient(nominator, denominator):
    inputs = [nominator, denominator]
    if isinstance(all(inputs), (int, float)):
        quotient = nominator / denominator
        return quotient
    else:
        return print("denominator cannot be zero")
```

Another function that is useful is `hasattr`, which checks what are the attributes for an object. The object can be a defined class, or a customized class. In the following example, I am checking whether the str class has the isupper and isstring attributes using hasattr. The function will return a boolean variable, either True or False:

```py
print("string has isupper method: ", hasattr(str, "isupper"))
print("string has isstring method: ", hasattr(str, "isstring"))
```

>string has isupper method:  True
>string has isstring method:  False

```py
class Cat:
    age = 3
    name = "Lily"
cat = Cat()
```

`hasattr(cat, "age")`
>True

`hasattr(cat, "gender")`
>False
