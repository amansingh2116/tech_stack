# Pandas

Pandas is a Python library used for working with datasets. It does that by helping us make sense of DataFrames, which are a form of two-dimensional structured data, like a table with columns and rows.

## CSV Files

CSV stands for Comma Separated Values, and it's a file type that allows data to be saved in a table. Data presented in a table is called structured data, because it adheres to the idea that there is a meaningful relationship between the columns and rows. A CSV might also show panel data, which is data that shows observations of the same behavior at various different times.

```git
Example.csv
property_type,department,lat,lon,area_m2,price_usd
house,Bogotá D.C,4.69,-74.048,187.0,"$330,899.98"
house,Bogotá D.C,4.695,-74.082,82.0,"$121,555.09"
house,Quindío,4.535,-75.676,235.0,"$219,474.47"
house,Bogotá D.C,4.62,-74.129,195.0,"$97,919.38"
```

```py
import pandas as pd

data = {"col_1": [3, 2, 1, 0], "col_2": ["a", "b", "c", "d"]}
pd.DataFrame.from_dict(data) # You can create a DataFrame from a Python dictionary using from_dict function. By default, DataFrame will be created using keys as columns. Note the length of the values should be equal for each key for the code to work.
pd.DataFrame.from_dict(data, orient="index") # We can also let keys to be index instead of the columns
pd.DataFrame.from_dict(data, orient="index", columns=["A", "B", "C", "D"]) # We can also specify column names
```

|| A     | B     | C     | D     |
|-------|-------|-------|-------|-------|
|col_1| 3     | 2     | 1     | 0     |
|col_2| a     | b     | c     | d     |

## JSON Files

JSON is short for JavaScript Object Notation. It is another widely used data format to store and transfer the data. It is light-weight and very human readable. In Python, we can use the json library to read JSON files. Here is an example of a JSON string.

```py
info = """{
    "firstName": "Jane",
    "lastName": "Doe",
    "hobby": "running",
    "age": 35
}"""
```

```py
import json
data = json.loads(info) #  Parses a JSON-formatted string and converts it into a Python dictionary

data["firstName"] # 'Jane' ; We can load a json string or file into a dictionary because they are organized in the same way: key-value pairs.

"A dictionary may not be as convenient as a DataFrame in terms of data manipulation and cleaning. But once we've turned our json string into a dictionary, we can transform it into a DataFrame using the from_dict method."

df = pd.DataFrame.from_dict(data, orient="index", columns=["subject 1"])
```

## Load Compressed file in Python

In the big data era, it is very likely that we'll need to read data from compressed files. One way to unzip the data is to use gzip.

```py
import gzip
import json
​
with gzip.open("data/poland-bankruptcy-data-2008.json.gz", "r") as f:
    poland_data_gz = json.load(f) # Reads JSON data from a file-like object and parses it into a Python dictionary 

poland_data_gz.keys() # dict_keys(['schema', 'data', 'metadata'])

df = pd.DataFrame().from_dict(poland_data_gz["data"])
df.head() # display the first five rows of a DataFrame by default. ; poland_data_gz is a dictionary, and we only need the data portion of it.
```

## Pickle Files

Pickle in Python is primarily used in serializing and deserializing a Python object structure. Serialization is the process of turning an object in memory into a stream of bytes so you can store it on disk or send it over a network. Deserialization is the reverse process: turning a stream of bytes back into an object in memory.

```py

sample_list = [1, 2, 3, 4, 5]
import pickle
pickle.dump(sample_list, open("./data/clothes.pkl", "wb"))
with open("./data/clothes.pkl", "rb") as bin:
    unpickled = pickle.load(bin)
```

## Working with DataFrames

```py
import pandas as pd

df = pd.read_csv("data/colombia-real-estate-1.csv")
df1 = pd.read_csv("data/colombia-real-estate-1.csv", usecols=["department"]) # reads data from the CSV file "colombia-real-estate-1.csv" located in the data directory and creates a DataFrame df1 containing only the department column. usecols can be a variable that should be a list of column names or indices that you want to include.
df.to_csv("data/small-df.csv", index=False) # saves the DataFrame excluding dataframe index

# DataFrame Index is a special kind of column that helps identify the location of each row. The default Index uses integers starting at zero
df.index[:5] # RangeIndex(start=0, stop=5, step=1)
df.index[:5] # Index(['Bogotá D.C', 'Bogotá D.C', 'Quindío', 'Bogotá D.C', 'Atlántico'], dtype='object', name='department')
df.reset_index(inplace=True) # reset index back to default integer counts

df.shape # tuple, dimensionality of the DataFrame
df.info() # tells us all sorts of things about the DataFrame: the number of columns, the names of the columns, the data type for each column, how many non-null rows are contained in the DataFrame.
print(df) #  to see all the rows in our new DataFrame
df.head() # returns the first five rows of data
print(df.head(2)) # specify as many rows as you like

df.sort_values("area_m2").head() # sort the whole DataFrame by values of a column.
df.set_index("lat").sort_index().head() # sort the DataFrame by it's index.
```

## Working with Rows & Columns

```py
dataframe = df[["surface_covered_in_m2"]] # returns a Pandas DataFrame with a single column.
series = df["surface_covered_in_m2"] # returns a Pandas Series. A Series is a one-dimensional array-like object containing the data for the specified column.
df3["price_m2"] = df3["price_usd"] / df3["area_m2"] # create a new column
df["price_cop"] = df["price_cop"] / 1e6 # scales the values in the price_cop column of the DataFrame df by dividing them by 10^6
df2 = df.drop("department", axis="columns") # new dataframe after dropping a column
df2.drop(columns="price_mxn", inplace = True) # drop a column in a dataframe
df2 = df.drop(2, axis="index") # drop a row
df.dropna(inplace=True) #  drop rows with empty cells from the dataset to avoid radical skewness of the results of our analysis. By default (inplace = False), pandas will keep the original DataFrame, and will create a copy that reflects the changes we just made.
df.rename(columns={"property_type": "type_property"}) # renames the column property_type to type_property in the DataFrame df.
df["property_type"].unique() # returns an array of unique values from the property_type column in the DataFrame df.
df["area_m2"].replace(235.0, 0) # replaces all occurrences of the value 235.0 with 0 in the area_m2 column 
replace_value = {235: 0, 130: 1, 137: 2}
df["area_m2"].replace(replace_value) # replaces multiple values in the area_m2 column of the DataFrame df according to the mapping provided in the replace_value dictionary.
concat_df = pd.concat([df1, df2]) # combines two DataFrames by concatenating them along the rows (default behavior). If you want to reset the index or avoid duplicate indices, you can use the ignore_index=True parameter.
df = pd.concat(frames, ignore_index = True) # combine a list of dataframes ignoring the index
concat_sr = pd.concat([sr1, sr2]) # combines two Series
```

## Working with strings

```py
df3[["lat", "lon"]] = df3["lat-lon"].str.split(",", expand=True) # splits the values in the lat-lon column of df3 at the comma and expands the result into two new columns, lat and lon, within the same DataFrame.
df3[["department", "state", "place"]] = df3["place_with_parent_names"].str.split("|", expand=True, n=3).iloc[:, 1:] # The code splits the `place_with_parent_names` column into three parts using `"|"` as a delimiter (limiting to 3 splits), discards the first empty part (.iloc[:, 1:]), and assigns the remaining parts to the `department`, `state`, and `place` columns in the DataFrame.
newdf = df.astype("str") # creates a new DataFrame newdf where all the columns in the original DataFrame df are converted to string data type.
df["area_m2"] = df.area_m2.astype(int) # converts the values in the area_m2 column of the DataFrame df from their current data type to integers and updates the column with these integer values.
df["department"].str[0:5:2] # slices each string in the department column starting from index 0 to index 5 (not inclusive) with a step of 2.
df["property_type"] = df["property_type"].str.replace("house", "single_family") # replaces all occurrences of the substring "house" with "single_family" in the property_type column of the DataFrame df.
# replace with "" to delete a character
```

## Working with series and dataframe

```py
surface_covered_in_m2 = mexico_city2["surface_covered_in_m2"] # Select a Series from a DataFrame
mexico_city4_subset = mexico_city4[
    ["operation", "property_type", "place_with_parent_names", "price"]] # select some columns from a DataFrame and make a new DataFrame with them
mexico_city5_numbers = mexico_city5.select_dtypes(include="number") # subset just the numerical entries
mexico_city5_no_numbers = mexico_city5.select_dtypes(exclude="number") # non numerical entries
df1["department"].value_counts() # how often each value occurs in the Series.
dept_group = df1.groupby("department") # groups the rows of the DataFrame df1 based on the unique values in the department column.
dept_group2 = df1.groupby(["department", "property_type"]) # make groups based on more than one category
dept_group.first() # provides the first occurrence of each unique department value in the original DataFrame.
dept_group1.get_group("Santander") # retrieves all the rows from the DataFrame df1 that belong to the group where the department is "Santander."
# Declare variable `df_morelos` by subsetting `df`
df_morelos = df.groupby("state").get_group("Morelos")
# OR
df_morelos = df[df["state"] == "Morelos"]
dept_group = df1.groupby("department")["area_m2"].mean() # calculates the mean (average) value of the area_m2 column for each unique department in the DataFrame df1. The result is a Series where the index is the unique department values and the values are the mean area_m2 for each department.
# To subset a DataFrame by column names, either define a list of columns to include or define a list of columns to exclude.
mexico_city3_subsetted = mexico_city3[keep_cols] # creates a new DataFrame containing columns specified in the keep_cols list or array
mexico_city3_subsetted = mexico_city3.drop(columns=drop_cols) # creates a new DataFrame by dropping the columns specified in the drop_cols list or array
```

## summarizing and aggregating data

```py
# A pivot table in pandas is a powerful tool for summarizing and aggregating data, allowing you to compute statistics like mean, sum, count, etc., across different categories or variables in your DataFrame.
pivot_table = mexico_city3.pivot_table(values='price', index='property_type', aggfunc='np.mean') # creates a pivot table that calculates the mean (average) value of the price column for each unique property_type in the mexico_city3 DataFrame.
# Another way to create subsets from a larger dataset is through masking. Masks are ways to filter out the data you're not interested in so that you can focus on the data you are. 
mask = (df1["area_m2"] > 400) & (df1["department"] == "Atlántico") # creates a boolean mask that identifies which rows in the df1 DataFrame have a value greater than 200 in the area_m2 column.
filtered_df = df1[mask] # select all the rows from df1 that evaluate as True
top_10 = df2["department"].value_counts().head(10).index # Extracts the index of the top 10 most frequent values from the Counts of the occurrences of each unique value in the department column sorted in descending order.
df2["department"] = df2["department"].apply(lambda x: x if x in top_10 else "Other") # Applies lambda function to each value in the department column that checks if each department value (x) is in the top_10 list. If it is, it keeps the value; otherwise, it replaces it with "Other".
# The pandas crosstab function is a useful for working with grouped summary statistics for categorical data. It starts by picking two categorical columns, then defines one as the index and the other as the column. If the aggregate function and value column is not defined, crosstab will simply calculate the frequency of each combination by default.
pd.crosstab(index=df["department"], columns=df["property_type"]) # calculates the frequency of each combination for two variables, department and property_type, in the data set. created a DataFrame with the index showing unique observation in variable department, while the columns are the unique observation for the variable property_type. Each cell shows how many data points there are for each combination of department type and property_type.
pd.crosstab(
    index=df["department"],
    columns=df["property_type"],
    values=df["area_m2"],
    aggfunc=np.mean,
).round(0) # shows the average area_m2 for each combination of department and property_type, rounding the results to the nearest whole number.
# Apply function
df.apply(np.sqrt)  # Applies the square root function to each element in the DataFrame.
df.apply(np.sum, axis=0)  # Computes the sum of each column in the DataFrame.
df.apply(np.sum, axis=1)  # Computes the sum of each row in the DataFrame.
df["area_sqrt"] = df["area_m2"].apply(np.sqrt)  # Adds a new column 'area_sqrt' with the square root of each value in 'area_m2'.

# df.aggregate(), or df.agg(), shares the same concept as df.apply() in terms of applying functions to a DataFrame, but df.aggregate() can only apply aggregate functions like sum, mean, min, max, etc. 
df.agg(["sum", "max"]) # calculate both sum and max for each column, and store the result as index.
df.agg({"area_m2": "sum", "price_cop": "min"}) # calculates the total sum of the area_m2 column and the minimum value of the price_cop column in the DataFrame.
```

## Working with Dates

```py
print(pd.Timestamp("January 8, 2022")) # 2022-01-08 00:00:00
print(pd.Timestamp("01/08/22 20:13")) # 2022-01-08 20:13:00
# We can also do date math with Timestamps, also compatible with Python's datetime module.
time_delta = pd.Timestamp("Feb. 11 2016 2:30 am") - pd.Timestamp("2015-08-03 5:14 pm")

import datetime
pd.Timestamp("Feb 11, 2016") - datetime.datetime(2015, 8, 3)

print(pd.Timestamp("January 9, 2017") - Day(4)) # Subtracts 4 days from the timestamp.
print(pd.Timestamp("January 9, 2017") - BDay(4)) # # Subtracts 4 bussiness days from the timestamp.
# BMonthEnd(n) to find the last business day  𝑛 months later. 
print(pd.Timestamp("February 9, 2017") + BMonthEnd(4)) # shows the last business day for May 2017, which is four months after February
# transform string to date format
date = datetime.strptime("16 Oct 2022 12:14:05", "%d %b %Y %H:%M:%S") # datetime.datetime(2022, 10, 16, 12, 14, 5)
pd.DatetimeIndex(data.index) # converts the index of a DataFrame or Series data into a DatetimeIndex object.
pd.date_range(start="1/8/2022", end="3/2/2022", freq="D") # generates a DatetimeIndex with daily frequency between the specified start and end dates. freq="B" for business dates
```

### Descriptive Statistics

#### Quartiles

Quartiles divide a sequence of numbers into four equal parts. Grouping a dataset into quartiles helps us find outliers and provides the basis for the data in a boxplot.
`price.quantile(0.5)`

#### Quantiles

A commonly used set of quantiles are the fourth quantiles known as quartiles. You can also find the minimum, first quartile, median, third quartile and maximum values in a series (which are typically the values used to create a boxplot). The median is the middle entry in the ordered list of prices
`price.quantile([0, 0.25, 0.5, 0.75, 1])`

#### Variance

Variance (which is sometimes called volatility in finance), is a measurement of how spread out the points in a dataset are around the mean.
`df["area_m2"].var()`

### Summary Statistics

`mexico_city1.describe()` # get a summary of information. The describe function will ignore missing values in each column. You can also remove rows and columns with missing values, and then get a summary of the data that's still there.

### Correlation

Correlations tell us about the relationship between two sets of data.

```py
area_m2 = df2["area_m2"]
price_cop = df2["price_cop"]
correlation = area_m2.corr(price_cop) # order doesn't matter, so same as price_cop.corr(area_m2)
print(correlation)


data["open"].plot() 
```
