# Housing in mexico

## Tabular and Tidy data

When working with this sort of **tabular data**, it's important to organize row and columns following the principles of "**tidy data**". What does that mean: 

1. Each row corresponds to a single house in our dataset. We'll call each of these houses an observation.
2. Each column corresponds to a characteristic of each house. We'll call these features.
3. Each cell contains only one value.

Python comes with several data structures that we can use to organize tabular data. One option would be to create a list for each observation and then put those together in another list. This is called a nested list.
```py
houses_nested_list = [
    [115910.26, 128.0, 4.0],
    [48718.17, 210.0, 3.0],
    [28977.56, 58.0, 2.0],
    [36932.27, 79.0, 3.0],
    [83903.51, 111.0, 3.0],
]
```
Lists are a good way to organize data, but one drawback is that we can only represent values. Why is that a problem? For example, someone looking at [115910.26, 128.0, 4] wouldn't know which values corresponded to price, area, etc. A better option might be a dictionary, where each value is associated with a key.
```py
[{'price_approx_usd': 115910.26, 'surface_covered_in_m2': 128, 'rooms': 4},
 {'price_approx_usd': 48718.17, 'surface_covered_in_m2': 210, 'rooms': 3},
 {'price_approx_usd': 28977.56, 'surface_covered_in_m2': 58, 'rooms': 2},
 {'price_approx_usd': 36932.27, 'surface_covered_in_m2': 79, 'rooms': 3},
 {'price_approx_usd': 83903.51, 'surface_covered_in_m2': 111, 'rooms': 3}]
```
 This way of storing data is so popular, it has its own name: JSON. We'll learn more about it later in the course.
 
 JSON is a great way to organize data, but it does have some downsides. Note that each dictionary represents a single house or, if we think about it as tabular data, a row in our dataset. This means that it's pretty easy to do row-wise calculations (like we did with price per square meter), but column-wise calculations are more complicated. For instance, what if we wanted to know the mean house price for our dataset? First we'd need to collect the price for each house in a list and then calculate mean.

 One way to make this sort of calculation easier is to organize our data by features instead of observations. We'll still use dictionaries and lists, but we'll implement them a slightly differently.
```py
 houses_columnwise = {
    "price_approx_usd": [115910.26, 48718.17, 28977.56, 36932.27, 83903.51],
    "surface_covered_in_m2": [128.0, 210.0, 58.0, 79.0, 111.0],
    "rooms": [4.0, 3.0, 2.0, 3.0, 3.0],
}
```
While you've shown that you can wrangle data using lists and dictionaries, it's not as intuitive as working with, say, a spreadsheet. Fortunately, there are lots of libraries for Python that make it an even better tool for tabular data — way better than spreadsheet applications like Microsoft Excel or Google Sheets! One of the best known data science libraries is pandas, which allows you to organize data into DataFrames.

| price_approx_usd | surface_covered_in_m2 | rooms |
|------------------|-----------------------|-------|
| 115910.26        | 128.0                 | 4.0   |
| 48718.17         | 210.0                 | 3.0   |
| 28977.56         | 58.0                  | 2.0   |
| 36932.27         | 79.0                  | 3.0   |
| 83903.51         | 111.0                 | 3.0   |

# Data Wrangling

The first part of any data science project is preparing your data, which means making sure its in the right place and format for you to conduct your analysis. The first step of any data preparation is importing your raw data and cleaning it. 

```py
df1 = pd.read_csv("data/mexico-real-estate-1.csv") # # Load CSV files into DataFrames
```
