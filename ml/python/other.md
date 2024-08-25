# Other useful things

## RESTful APIs

An Application Programming Interface (**API**) is a way for two or more computer programs to communicate with each other — either when they are running on the same computer or when they are running on different computers across the internet. **RESTful API** is a type of API that follows the constraints of **REST** architectural style and allows for interaction with RESTful web services. REST stands for Representational State Transfer, and API stands for application programming interface.

RESTful API is an interface to exchange information securely over the internet. The server needs to first identify the resource with unique resource identifiers. For REST services, the server will use Uniform Resource Locator (URL), which is a path to the resource. A URL is like a website address that you enter into your browser to visit any webpage. It usually contains with useful information that we could extract.

RESTful APIs is implemented by using the Hypertext Transfer Protocol (HTTP). HTTP is a messaging protocol that describes the types and structure of messages that can be used for communication between servers and clients. Communication occurs by clients sending a request to a server and the server replying with a response.

There are 4 kinds of requests clients can send:

1. **GET**: The most common request is GET. Anytime you open a web browser and click a website, you are making a GET request. GET is a request for the server to send the client information. When GET returns an HTTP response code of 200, it means the request is successful. In an error case, it most often returns a 404 (NOT FOUND ERROR) or 400 (BAD REQUEST ERROR).

2. **POST**: POST is used to send data to the server. They include the data representation with the request. It's also used to when you want the server to execute some sort of operation.

3. **PUT**: PUT is used to update existing resources on the server.

4. **DELETE**: DELETE is used to remove the resource.

### Making an HTTP Request

We can specify the URL and use the request library to make HTTP requests:

```py
import requests
url = "http://www.google.com"
response = requests.get(url)
response
```

> <Response [200]>
The output of the previous code stands for the status codes of a response, and recall that 200 means the request is successful.

As mentioned earlier, we can specify parameters in a URL to get specific information. Take the AlphaVantage API as an example. We can specify which stock we want to extract and how frequently we want to extract it, along with our API key.

```py
# Get IBM's stock prices
ticker = "IBM"
​
​
url = (
    "https://www.alphavantage.co/query?"
    f"function=TIME_SERIES_DAILY&"
    f"symbol={ticker}&"
    f"apikey=demo"
)
​
url
# 'https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=IBM&apikey=demo'
# Now we have the URL ready, we can extract the information using request:

response = requests.get(url=url)
​
# Get the data in json format
data = response.json()
​
# Get the daily stock prices
stock_data = data["Time Series (Daily)"]
We will see the stock prices for IBM at any date.

list(stock_data.items())[0]
'''('2024-08-15',
 {'1. open': '193.5200',
  '2. high': '194.2400',
  '3. low': '193.3200',
  '4. close': '194.0100',
  '5. volume': '2471186'})'''
```

### Building Your Own API

**Declaring Environment Variables**
Environment variables are variables whose value is defined outside the code, typically through built-in operating system function or in a configuration file. The most common reason to use environment variables is to limit the need to modify and re-release an application just because of the changes in configuration data. Another use case of environment variables is to define API keys in the configuration file due to security concerns. If you are building an application calling different API with API keys, you don't want to show the keys in your code.

**Creating a Path**
There are lots of tools to build an API using Python. We will use the FastAPI module to show an example on how to create your own API. We can first set up the import the library and set up an application:

```py
from fastapi import FastAPI
​
app = FastAPI()
# Next, we create a path for the app to request content from. Then we use the @app.get function and specify the path with a forward slash (/):

@app.get("/ping")
def pong():
    return {"ping": "pong!"}

# In this example, we define a path called /ping. When make a get request to this path, and the app should return what we defined in the pong() function. We can use the requests library to check the app is working fine.


%%bash
cd /textbook
uvicorn main:app --reload --workers 1 --host localhost --port 8009

import requests
​
url = "http://localhost:8009/ping"
response = requests.get(url=url)
​
print("response code:", response.status_code)
response.json()

# Note we can also create a main file so that we can include more functions for more complicated applications.
```

**Data Classes and Type Checking**
When setting up an application, it is very important to ensure the input and output of the application are in the desired format. pydantic is a widely used tool in data validation and type hinting enforcement, which provides user-friendly errors and help catch any invalid data type. Defining an object means creating a new class which inherits from the pydantic BaseModel. pydantic guarantees that the fields of the model instance will conform to the field types defined on the model. Let's define a Person class that has two attributes, name and age. We then use pydantic BaseModel to ensure the name is a string, and age is an integer.

```py
from pydantic import BaseModel
​
​
class Person(BaseModel):
    name: str
    age: int
​
​
person = Person(name="Lily", age=3)
print(person)
# If we are not putting the desired data format, pydantic will help correct the error:

person = Person(name="Lily", age="3")
print(person)
```

pydantic BaseModel provides support for most of the common types from the Python standard library. We can define bool, int, float, str, list, tuple, dict, datetime.date, etc

## Linux Command Line

### Navigating Files and Directories

We can run command directly in Jupyter Notebook using by adding the magic command %%bash:

```jupyter
%%bash
​
pwd # look at current director
ls # From the current directory, what files are inside this directory
cd .. # go back to the previous directory
cd # go directly back to home directory
cd dir_name # go further, into dir_name
```

### Viewing File Contents

```jupyter
%%bash

cd data
head example.txt # View the head of this file

cd data
tail -1 example.txt # View the tail of this file
```

### Compressing and Decompressing Files

**Data Compressing**
Data Compression is the process of encoding information using fewer bits than a decoded representation would use through the use of specific encoding schemes. Compression is needed because it helps to reduce the consumption of expensive resources such as a hard disk or transmission bandwidth.

`gzip` is a form of data compression. The original data can be restored by unzipping the compressed file. `gzip` can compress all files; it doesn't make any difference what the file type is or the encoding. Obviously, some files can be compressed more effectively than others, so the bandwidth saving will vary - text files like HTML give the best results; images are not compressed so much by `gzip` because they already have some compression built-in.

```jupyter
%%bash

cd data
gzip example.txt # zip file

cd data
gzip -c example.txt > output.txt.gz # customized the name of the zipped file

cd data
gzip -d example.txt.gz # unzip file

```

## Stack Overflow

```py
df = pd.read_json("data/poland-bankruptcy-data-2009.json")
```

<code style="background-color:#FEDDDE;"><span style="color:#E45E5C">ValueError</span>: Mixing dicts with non-Series may lead to ambiguous ordering.</code>

What should we do? That error sounds serious, but the world is big, and we can't possibly be the first people to encounter this problem. When you come across an error, copy the message into a search engine and see what comes back. You'll get lots of results. The web has lots of places to look for solutions to problems like this one, and [Stack Overflow](https://stackoverflow.com/) is one of the best. [Click here to check out a possible solution to our problem.](https://stackoverflow.com/questions/57018859/valueerror-mixing-dicts-with-non-series-may-lead-to-ambiguous-ordering)

There are three things to look for when you're browsing through solutions on Stack Overflow.

1. **Context:** A good question is specific; if you click through that link, you'll see that the person asks a **specific** question, gives some relevant information about their OS and hardware, and then offers the code that threw the error. That's important, because we need...
2. **Reproducible Code:** A good question also includes enough information for you to reproduce the problem yourself. After all, the only way to make sure the solution actually applies to your situation is to see if the code in the question throws the error you're having trouble with! In this case, the person included not only the code they used to get the error, but the actual error message itself. That would be useful on its own, but since you're looking for an actual solution to your problem, you're really looking for...
3. **An answer:** Not every question on Stack Overflow gets answered. Luckily for us, the one we've been looking at did. There's a big green check mark next to the first solution, which means that the person who asked the question thought that solution was the best one.
