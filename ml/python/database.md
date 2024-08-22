# Working with Databases

## Working with SQL Databases

A database is a collection of interrelated data. The primary goal of a database is to store and retrieve information in a convenient and efficient way. There are many types of databases. In this section, we will be dealing with a **relational database**. A relational database is a widely used database model that consists of a collection of uniquely named **tables** used to store information. The structure of a database model with its tables, constraints, and relationships is called a **schema**.

A Structured Query Language (**SQL**), is used to retrieve information from a relational database. SQL is one of the most commonly used database languages. It allows data stored in a relational database to be queried, modified, and manipulated easily with basic commands. SQL powers database engines like MySQL, SQL Server, SQLite, and PostgreSQL. The examples and projects in this course will use SQLite.

A **table** refers to a collection of rows and columns in a relational database. When reading data into a pandas DataFrame, an **index** can be defined, which acts as the label for every row in the DataFrame.

### Magic Commands

Jupyter notebooks can run code that is not valid Python code but still affect the notebook . These special commands are called magic commands. Magic commands can have a range of properties. Some commonly used magic functions are below:

| Magic Command | Description of Command |
| --- | --- |
| `%pwd` | Print the current working directory |
| `%cd` | Change the current working directory |
| `%ls` | List the contents of the current directory |
| `%history` | Show the history of the In [ ]: commands |

We will be leveraging magic commands to work with a SQLite database.

`ipython-sql` allows you to write SQL code directly in a Jupyter Notebook. The `%sql` (or `%%sql`) magic command is added to the beginning of a code block and then SQL code can be written.

```py
# connect to a database using the %sql magic function
%load_ext sql
%sql sqlite:////home/jovyan/nepal.sqlite

# OR

# connect to the same database using the sqlite3 package
import sqlite3
conn = sqlite3.connect("/home/jovyan/nepal.sqlite")
```

### SQL queries

There are six common clauses used for querying data:

| Clause Name | Definition |
| --- | --- |
| `SELECT` | Determines which columns to include in the query's result |
| `FROM` | Identifies the table from which to query the data from |
| `WHERE` | filters data |
| `GROUP BY` | groups rows by common values in columns |
| `HAVING` | filters out unwanted groups from GROUP BY |
| `ORDER BY` | Orders the rows using one or more columns |
| `LIMIT` | Outputs the specified number of rows |

All clauses may be used together, but `SELECT` and `FROM` are the only required clauses. The format of clauses is in the example query below:

```sql
SELECT column1, column2
FROM table_name
WHERE "conditions"
GROUP BY "column-list"
HAVING "conditions"
ORDER BY "column-list"
```

* use SELECT * to select all columns in a table
* LIMIT 5 will select only the first five rows
* assign an alias or temporary name to a column using the AS command. Aliases can also be used on a table.

```sql
SELECT household_id AS household_number,
       building_id
FROM id_map
LIMIT 5
```

### Filtering and Sorting Data

SQL provides a variety of comparison operators that can be used with the WHERE clause to filter the data.

| Comparison Operator | Description |
| --- | --- |
| = | Equal |
| > | Greater than |
| < | Less than|
| >= | Greater than or equal to |
| <= | Less than or equal to |
| <> or != | Not equal to |
| LIKE | String comparison test |

### Aggregating Data

Aggregation functions take a collection of values as inputs and return one value as the output. The table below gives the frequently used built-in aggregation functions:

| Aggregation Function | Definition                        |
| -------------------- | --------------------------------- |
| `MIN`                  | Return the minimum value          |
| `MAX`                  | Return the largest value          |
| `SUM`                  | Return the sum of values          |
| `AVG`                  | Return the average of values      |
| `COUNT`                | Return the number of observations |

Aggregation functions are frequently used with a GROUP BY clause to perform the aggregation on groups of data. For example, the query below returns the count of observations in each District:

```sql
SELECT district_id,
       count(*)
FROM id_map
GROUP BY district_id

-- to select unique records in a query result. 
SELECT distinct(district_id)
FROM id_map

-- `DISTINCT` and `COUNT` can be used in combination to count the number of distinct records
SELECT count(distinct(district_id))
FROM id_map
```

### Joining TABLES

Joins link data from two or more tables together by using a column that is common between the two tables. The basic syntax for a join is below, where `table1` and `table2` refer to the two tables being joined, `column1` and `column2` refer to columns to be returned from both tables, and `ID` refers to the common column in the two tables.

```sql
SELECT table1.column1,
       table2.column2
FROM table_1
JOIN table2 ON table1.id = table1.id
```

```SQL
-- return all the columns from id_map along with the foundation_type from building_structure for the building with building_id 23.
SELECT id_map.*,
       building_structure.foundation_type
FROM id_map
JOIN building_structure ON id_map.building_id = building_structure.building_id
WHERE id_map.building_id = 23
```

In addition to the basic `JOIN` clause, specific join types can be specified, which specify whether the common column needs to be in one, both, or either of the two tables being joined. The different join types are below. The left table is the table specified first, immediately after the `FROM` clause and the right table is the table specified after the `JOIN` clause. If the generic `JOIN` clause is used, then by default the `INNER JOIN` will be used.

| JOIN Type | Definition                        |
| -------------------- | --------------------------------- |
| `INNER JOIN`                  | Returns rows where ID is in both tables         |
| `LEFT JOIN`                  | Returns rows where ID is in the left table. Return NA for values in column, if ID is not in right table.          |
| `RIGHT JOIN`                  | Returns rows where ID is in the right table. Return NA for values in column, if ID is not in left table. |
| `FULL JOIN`                  | Returns rows where ID is in either table. Return NA for values in column, if ID is not in either table. |

### Using pandas with SQL Databases

```PY
# To save the output of a query into a pandas DataFrame, we will use connect to the SQLite database using the SQLite3 package
import sqlite3
conn = sqlite3.connect("/home/jovyan/nepal.sqlite")

# To run a query using sqlite3, we need to store the query as a string.
query = """
    SELECT *
    FROM id_map
    LIMIT 10
    """
# To save the results of the query into a pandas DataFrame, use the pd.read_sql() function. The optional parameter index_col can be used to set the index to a specific column from the query.
import pandas as pd
df = pd.read_sql(query, conn, index_col="building_id")
df.head()
```

## Working with PyMongo

### Introduction & Installation

```PY
import pandas as pd
import PrettyPrinter # a module that lets us see the data in an understandable way
from pymongo import MongoClient # a library for working with MongoDB databases
```

#### **Servers and Clients**

Next, we need to connect to a server. A database server is where the database resides; it can be accessed using a client. Without a client, a database is just a collection of information that we can't work with, because we have no way in. We're going to be learning more about a database called MongoDB, and we'll use PrettyPrinter to make the information it generates easier to understand. Here's how the connection works:

```py
pp = PrettyPrinter(indent=2)
client = MongoClient(host="localhost", port=27017)
```

**Semi-structured Data**
Databases are designed to work with either structured data or semi-structured data. In this part of the course, we're going to be working with databases that contain semi-structured data. Data is semi-structured when it has some kind of organizing logic, but that logic can't be displayed using rows and columns. Your email account contains semi-structured data if it’s divided into sections like Inbox, Sent, and Trash. If you’ve ever seen tweets from Twitter grouped by hashtag, that’s semi-structured data too. Semi-structured data is also used in sensor readings, which is what we'll be working with here.

### Exploring a Database

So, now that we're connected to a server, let's take a look at what's there. Working our way down the specificity scale, the first thing we need to do is figure out which databases are on this server. To see which databases on the server, we'll use the list_databases method, like this:

> **Iterators in python**
> Iterators amounts a same space for a long data to store so help in improving space efficiency.
>```py
>my_list = [0,1,2,3,4,5,6,7,8,9]
>my_range = range(10) # iterator
>```

```py
pp.pprint(list(client.list_databases())) # print out the list of databases
db = client["air-quality"] # choosing a database to work with
# for loop to take a look at the collections in the "air-quality" database
for c in db.list_collections():
    print(c["name"])
lagos = db["lagos"]# choosing a collection to work with
```

**Documents**
A MongoDB document is an individual record of data in a collection, and is the basic unit of analysis in MongoDB. Documents come with metadata that helps us understand what the document is.
`lagos.count_documents({})` # how many documents the "lagos" collection contains

### Retrieving Data

Now that we know how many documents the "lagos" collection contains, let's take a closer look at what's there.
To access documents in the collection, we'll use two methods: `find` and `find_one`. As you might expect, `find` will retrieve all the documents, and `find_one` will bring back only the first document.

```py
result = lagos.find_one({})
pp.pprint(result)
```

> { '_id': ObjectId('6525d785f44bfedd84322730'),
  'metadata': { 'lat': 6.501,
                'lon': 3.367,
                'measurement': 'temperature',
                'sensor_id': 10,
                'sensor_type': 'DHT11',
                'site': 4},
  'temperature': nan,
  'timestamp': datetime.datetime(2018, 1, 7, 7, 7, 3, 88000)}

#### **Dictionary**

The first thing you'll notice is that the output starts out with a curly bracket ({), and ends with a curly bracket (}). That tells us that this information is a dictionary.

#### **Key-Value Pairs**

```python
{
    'temperature': 27.0,
    'timestamp': datetime.datetime(2017, 9, 6, 13, 18, 10, 120000)
}
```

The actual data is labeled `temperature` and `timestamp`, and if seeing it presented this way seems familiar, that's because what you're seeing at the bottom are two key-value pairs.

#### **MetaData**

```python
'metadata': { 'lat': 6.602,
              'lon': 3.351,
              'measurement': 'temperature',
              'sensor_id': 9,
              'sensor_type': 'DHT11',
              'site': 2}
```

This is the document's metadata. Metadata is data about the data. If you’re working with a database, its data is the information it contains, and its metadata describes what that information is. In MongoDB, each document often has metadata of its own. If we go back to the example of your email account, each message in your Sent folder includes both the message itself and information about when you sent it and who you sent it to; the message is data, and the other information is metadata.
The metadata we see in this block of code tells us what the key-value pairs from the last code block mean, and where the information stored there comes from. There's location data, a line telling us what about the format of the key-value pairs, some information about the equipment used to gather the data, and where the data came from.

#### **Identifiers**

```python
{ 
    '_id': ObjectId('6126f1780e45360640bf240a')
}
```

This is the document's unique identifier, which is similar to the index label for each row in a pandas DataFrame.
In PyMongo, `"_id"` is always the **primary key**. Primary keys are the column(s) which contain values that uniquely identify each row in a table; we'll talk about that more in a minute.

```py
# Retreiving data from database
from pprint import PrettyPrinter

import pandas as pd
from pymongo import MongoClient

nai = db["nairobi"]
nai.count_documents({})

result = nai.find_one({})
pp.pprint(result)
```

### Analysing Data

Since our metadata includes information about each sensor's "site", we might be curious to know how many sites are in the "lagos" collection.

`lagos.distinct("metadata.site")` # [3, 4]

Notice that in order to grab the "site" number, we needed to include the "metadata" tag.

This tells us that there are 2 sensor sites in Lagos: one labeled 3 and the other labeled 4.

```py
# how many documents are associated with each site
print("Documents from site 3:", lagos.count_documents({"metadata.site": 3})) # Documents from site 3: 140586
print("Documents from site 4:", lagos.count_documents({"metadata.site": 4})) # Documents from site 4: 25910
```

Finding the number of readings for each site this way can be very time and labour consuming. We'll now do this with the aggregate method.

```py
result = lagos.aggregate(
    # Here's the `$` and the `"_id"`
    [{"$group": {"_id": "$metadata.site", "count": {"$count": {}}}}]
)
pp.pprint(list(result))
```

> [{'_id': 3, 'count': 140586}, {'_id': 4, 'count': 25910}]

notice that there are several dollar signs ($) in the list. This is telling the collection that we want to create something new. Here, we're saying that we want there to be a new group, and that the new group needs to be updated with data from metadata.site, and then updated again with data from count.

With that information in mind, we might want to know what those readings actually are. Since we're really interested in measures of air quality, let's take a look at the P2 values in the "lagos" collection. P2 measures the amount of particulate matter in the air, which in this case is something called PM 2.5. If we wanted to get all the documents in a collection, we could, but that would result in an unmanageably large number of records clogging up the memory on our machines.

```sql
result = lagos.find({"metadata.measurement": "P2"}).limit(3)
pp.pprint(list(result))
```

> [ { 'P2': 14.42,
    '_id': ObjectId('6525d786f44bfedd84327318'),
    'metadata': { 'lat': 6.501,
                  'lon': 3.367,
                  'measurement': 'P2',
                  'sensor_id': 6,
                  'sensor_type': 'PPD42NS',
                  'site': 4},
    'timestamp': datetime.datetime(2018, 1, 7, 7, 7, 3, 39000)},
  { 'P2': 19.66,
    '_id': ObjectId('6525d786f44bfedd84327319'),
    'metadata': { 'lat': 6.501,
                  'lon': 3.367,
                  'measurement': 'P2',
                  'sensor_id': 6,
                  'sensor_type': 'PPD42NS',
                  'site': 4},
    'timestamp': datetime.datetime(2018, 1, 7, 7, 11, 23, 870000)},
  { 'P2': 24.79,
    '_id': ObjectId('6525d786f44bfedd8432731a'),
    'metadata': { 'lat': 6.501,
                  'lon': 3.367,
                  'measurement': 'P2',
                  'sensor_id': 6,
                  'sensor_type': 'PPD42NS',
                  'site': 4},
    'timestamp': datetime.datetime(2018, 1, 7, 7, 21, 53, 981000)}]

So far, we've been dealing with relatively small subsets of the data in our collections, but what if we need to work with something bigger? Let's start by using distinct to remind ourselves of the kinds of data we have at our disposal.

Similarly we can use the find method to retrieve the PM 2.5 readings from site 29. Using the projection argument we can limit the results to the "P2" and "timestamp" keys only.

```py
result = nairobi.find(
    {"metadata.site": 29, "metadata.measurement": "P2"},
    projection = {"P2": 1, "timestamp": 1, "_id": 0}
)
pp.pprint(result.next()) # prints one at a time and next every time
```

```py
lagos.distinct("metadata.measurement")
```

>['temperature', 'humidity', 'P1', 'P2']

There are also comparison query operators that can be helpful for filtering the data. In total, we have:

* `$gt`:  greater than (>)
* `$lt`:  less than (<)
* `$gte`: greater than equal to (>=)
* `$lte`: less than equal to (<= )
​
Let's use the `timestamp` to see how we can use these operators to select different documents:
import datetime

```py
result = nairobi.find({"timestamp": {"$gt": datetime.datetime(2018, 9, 1)}}).limit(3)
pp.pprint(list(result))
result = nairobi.find({"timestamp": {"$lt": datetime.datetime(2018, 12, 1)}}).limit(3)
pp.pprint(list(result))
result = nairobi.find(
    {"timestamp": {"$eq": datetime.datetime(2018, 9, 1, 0, 0, 2, 472000)}}
).limit(3)
pp.pprint(list(result))
```

### Updating Documents

We can also update documents by passing some filter and new values using update_one to update one record or update_many to update many records.

```py
result = nai.update_many(
    {"metadata.sensor_type": {"$eq": "SDS101"}},
    {"$set": {"metadata.sensor_type": "SDS"}},
)
result.raw_result
result = nai.update_many(
    {"metadata.sensor_type": {"$eq": "SDS101"}},
    {"$set": {"metadata.sensor_type": "SDS"}},
)
result.raw_result
{'n': 0, 'nModified': 0, 'ok': 1.0, 'updatedExisting': False}

result = nai.find(
    {"timestamp": {"$eq": datetime.datetime(2018, 9, 1, 0, 0, 2, 472000)}}
).limit(3)

pp.pprint(list(result))
```

### Aggregation

Since we're looking for big numbers, we need to figure out which one of those dimensions has the largest number of measurements by aggregating the data in each document. Since we already know that site 3 has significantly more documents than site 2, let's start looking at site 3. We can use the $match syntax to only select site 3 data.

```py
result = nai.aggregate(
    [
        {"$match": {"metadata.site": 29}},
        {"$group": {"_id": "$metadata.sensor_type", "count": {"$count": {}}}},
    ]
)
​
pp.pprint(list(result))
```

> [{'_id': 'SDS011', 'count': 65814}, {'_id': 'DHT22', 'count': 66038}]

After aggregation, there is another useful operator called $project, which allows you to specify which fields to display by adding new fields or deleting fields. We can see there are two sensor types and the corresponding counts. If we only want to display what are the types but do not care about the counts, we can suppress the count filed by setting it at 0 in `\$project`:

```py
result = nai.aggregate(
    [
        {"$match": {"metadata.site": 29}},
        {"$group": {"_id": "$metadata.sensor_type", "count": {"$count": {}}}},
        {"$project": {"count": 0}},
    ]
)
​
pp.pprint(list(result))
```

>[{'_id': 'SDS011'}, {'_id': 'DHT22'}]

The `\$project` syntax is also useful for deleting the intermediate fields that we used to generate our final fields but no longer need. In the following example, let's calculate the date difference for each sensor type. We'll first use the aggregation method to get the start date and last date.

```py
result = nai.aggregate(
    [
        {"$match": {"metadata.site": 29}},
        {
            "$group": {
                "_id": "$metadata.sensor_type",
                "date_min": {"$min": "$timestamp"},
                "date_max": {"$max": "$timestamp"},
            }
        },
    ]
)
​
pp.pprint(list(result))
```

>[ { '_id': 'DHT22',
    'date_max': datetime.datetime(2018, 12, 31, 23, 57, 37, 257000),
    'date_min': datetime.datetime(2018, 9, 1, 0, 0, 4, 301000)},
  { '_id': 'SDS011',
    'date_max': datetime.datetime(2018, 12, 31, 23, 55, 4, 811000),
    'date_min': datetime.datetime(2018, 9, 1, 0, 0, 2, 472000)}]

Then we can calculate the date difference using `\$dateDiff`, which gets the date difference through specifying the start date, end date and unit for timestamp data. We can see from the results above that the dates, are very close to each other. The only differences are in the minutes, so we can specify the unit as minute to show the difference. Since we don't need the start date and end dates, we can define a "dateDiff" field inside $project, so that it will be shown in the final display:

```py
result = nai.aggregate(
    [
        {"$match": {"metadata.site": 29}},
        {
            "$group": {
                "_id": "$metadata.sensor_type",
                "date_min": {"$min": "$timestamp"},
                "date_max": {"$max": "$timestamp"},
            }
        },
        {
            "$project": {
                "dateDiff": {
                    "$dateDiff": {
                        "startDate": "$date_min",
                        "endDate": "$date_max",
                        "unit": "minute",
                    }
                }
            }
        },
    ]
)
​
pp.pprint(list(result))
```

> [{'_id': 'SDS011', 'dateDiff': 175675}, {'_id': 'DHT22', 'dateDiff': 175677}]

If we specify unit as day, it will show the difference between the dates:

```py
result = nai.aggregate(
    [
        {"$match": {"metadata.site": 29}},
        {
            "$group": {
                "_id": "$metadata.sensor_type",
                "date_min": {"$min": "$timestamp"},
                "date_max": {"$max": "$timestamp"},
            }
        },
        {
            "$project": {
                "dateDiff": {
                    "$dateDiff": {
                        "startDate": "$date_min",
                        "endDate": "$date_max",
                        "unit": "day",
                    }
                }
            }
        },
    ]
)
​
pp.pprint(list(result))
```

>[{'_id': 'DHT22', 'dateDiff': 121}, {'_id': 'SDS011', 'dateDiff': 121}]

We can do more with the date data using `\$dateTrunc`, which truncates datetime data. We need to specify the datetime data, which can be a Date, a Timestamp, or an ObjectID. Then we need to specify the unit (year, month, day, hour, minute, second) and binSize (numerical variable defining the size of the truncation). Let's check the example below, where we group data by the month using `\$dateTrunc` and then count how many observations there are for each month.

```py
result = nai.aggregate(
    [
        {"$match": {"metadata.site": 29}},
        {
            "$group": {
                "_id": {
                    "truncatedDate": {
                        "$dateTrunc": {
                            "date": "$timestamp",
                            "unit": "month",
                            "binSize": 1,
                        }
                    }
                },
                "count": {"$count": {}},
            }
        },
    ]
)
pp.pprint(list(result))
```

>[ { '_id': {'truncatedDate': datetime.datetime(2018, 9, 1, 0, 0)},
    'count': 31734},
  { '_id': {'truncatedDate': datetime.datetime(2018, 12, 1, 0, 0)},
    'count': 34896},
  { '_id': {'truncatedDate': datetime.datetime(2018, 10, 1, 0, 0)},
    'count': 35364},
  { '_id': {'truncatedDate': datetime.datetime(2018, 11, 1, 0, 0)},
    'count': 29858}]

**Read records from your result into the DataFrame df and set the index to "timestamp".**

`df = pd.DataFrame(result).set_index("timestamp")`
