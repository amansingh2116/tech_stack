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

## Data Wrangling

The first part of any data science project is preparing your data, which means making sure its in the right place and format for you to conduct your analysis. The first step of any data preparation is importing your raw data and cleaning it.

```py
df1 = pd.read_csv("data/mexico-real-estate-1.csv") # # Load CSV files into DataFrames
print("df1 type:", type(df1)) # df1 type: <class 'pandas.core.frame.DataFrame'>
print("df1 shape:", df1.shape) # df1 shape: (700, 6)
# Get output of df1 head
df1.head()

# Drop null values from df1
df1.dropna(inplace = True)

# Clean "price_usd" column in df1
df1["price_usd"] = df1["price_usd"].str.replace("$","")

# Create "price_usd" column for df2 (19 pesos to the dollar in 2014)
df2["price_usd"] = (df2["price_mxn"]/19).round(2)

# Drop "price_mxn" column from df2
df2 = df2.drop("price_mxn",axis = "columns")

# Create "lat" and "lon" columns for df3
df3[["lat", "lon"]] = df3["lat-lon"].str.split(",", expand = True)

# Create "state" column for df3
df3["state"] = df3["place_with_parent_names"].str.split("|",expand = True)[2]

# Concatenate df1, df2, and df3
df = pd.concat([df1, df2, df3])

# Save df
df.to_csv("./data/mexico-real-estate-clean.csv", index = False)
```

## EDA

After importing, the next step in many data science projects is exploratory data analysis (EDA), where you get a feel for your data by summarizing its main characteristics using descriptive statistics and data visualization. A good way to plan your EDA is by looking each column and asking yourself questions what it says about your dataset.

there are three categories of data: location, categorical, and numeric. Each of these require a different kind of exploration in our analysis.

Since latitude and longitude are based on a coordinate system, a good way to visualize them is to create a scatter plot on top of a map. A great tool for this is the scatter_mapbox from the plotly library.

```py
# Use plotly express to create figure
fig = px.scatter_mapbox(
    df,  # Our DataFrame
    lat=df["lat"],
    lon=df["lon"],
    center={"lat": 19.43, "lon": -99.13},  # Map will be centered on Mexico City
    width=600,  # Width of map
    height=600,  # Height of map
    hover_data=["price_usd"],  # Display price when hovering mouse over house
)

# Add mapbox_style to figure layout
fig.update_layout(mapbox_style="open-street-map")

# Show figure
fig.show()
```

Even though we can get a good idea of which states are most common in our dataset from looking at a map, we can also get the exact count by using the "state" column.

```py
# Get value counts of "state" column
df["state"].value_counts()
```

We have a sense for where the houses in our dataset are located, but how much do they cost? How big are they? The best way to answer those questions is looking at descriptive statistics.

```py
# Describe "area_m2", "price_usd" columns
df["area_m2"].describe()
df["price_usd"].describe()
```

>count    1865.000000
mean      171.000536
std        80.044505
min        60.000000
25%       103.000000
50%       159.000000
75%       220.000000
max       385.000000
Name: area_m2, dtype: float64

Let's start by looking at "area_m2". It's interesting that the mean is larger than the median (another name for the 50% quartile). Both of these statistics are supposed to give an idea of the "typical" value for the column, so why is there a difference of almost 15 m2 between them? To answer this question, we need to see how house sizes are distributed in our dataset. Let's look at two ways to visualize the distribution: a histogram and a boxplot.

```py
# Use Matplotlib to create histogram of "area_m2"
plt.hist(df["area_m2"], bins = 20)

# Add x-axis label
plt.xlabel("Area in meter square")

# Add y-axis label
plt.ylabel("Numbers")

# Add title
plt.title("Histogram distribution of area in meter square for mexico real estate data")
```

Looking at our histogram, we can see that "area_m2" skews right. In other words, there are more houses at the lower end of the distribution (50–200m2) than at the higher end (250–400m2). That explains the difference between the mean and the median.

```py
# Use Matplotlib to create boxplot of "area_m2"
plt.boxplot(df["area_m2"], vert = False)

# Add x-axis label
plt.xlabel("Area [sq meters]")

# Add title
plt.title("Distribution of Home Sizes")
```

## Asking Questions - Size or location

You've wrangled the data, you've gained an understanding of its basic characteristics in your EDA, and now it's time to ask some research questions.

* Which state has the most expensive real estate market?

Do housing prices vary by state? If so, which are the most expensive states for purchasing a home? During our exploratory data analysis, we used descriptive statistics like mean and median to get an idea of the "typical" house price in Mexico. Now, we need to break that calculation down by state and visualize the results.

We know in which state each house is located thanks to the "state" column. The next step is to divide our dataset into groups (one per state) and calculate the mean house price for each group.

```py
# Declare variable `mean_price_by_state`
mean_price_by_state = df.groupby("state")["price_usd"].mean().sort_values(ascending = False)

# Print object type, shape, and head
print("mean_price_by_state type:", type(mean_price_by_state))
print("mean_price_by_state shape:", mean_price_by_state.shape)
mean_price_by_state.head()

# Create bar chart from `mean_price_by_state` using pandas
mean_price_by_state.plot(
    kind='bar', 
    title='Mean House Price by State', 
    xlabel = "State", 
    ylabel = "Mean Price [USD]"
)
```

It seems odd that Querétaro would be the most expensive real estate market in Mexico when, according to recent GDP numbers, it's not in the top 10 state economies. With all the variations in house sizes across states, a better metric to look at would be price per m2. In order to do that, we need to create a new column.

```py
# Create "price_per_m2" column
df["price_per_m2"] = df["price_usd"]/df["area_m2"]

# Group `df` by "state", create bar chart of "price_per_m2"
mean_price_per_m2 = df.groupby("state")["price_per_m2"].mean().sort_values(ascending = False)
mean_price_per_m2.plot(kind = "bar", title="Mean House Price per M^2 by State", xlabel = "State", ylabel = "Mean Price per M^2[USD]")
```

Now we see that the capital Mexico City (Distrito Federal) is by far the most expensive market. Additionally, many of the top 10 states by GDP are also in the top 10 most expensive real estate markets. So it looks like this bar chart is a more accurate reflection of state real estate markets.

* Is there a relationship between home size and price?

From our previous question, we know that the location of a home affects its price (especially if it's in Mexico City), but what about home size? Does the size of a house influence price?

A scatter plot can be helpful when evaluating the relationship between two columns because it lets you see if two variables are correlated — in this case, if an increase in home size is associated with an increase in price.

```py
# Create scatter plot of "price_usd" vs "area_m2"
plt.scatter(df["price_usd"], df["area_m2"])

# Add x-axis label
plt.xlabel("Area [sq meters]")

# Add y-axis label
plt.ylabel("Price [USD]")

# Add title
plt.title("Scatter plot between price and area")

# While there's a good amount of variation, there's definitely a positive correlation — in other words, the bigger the house, the higher the price. But how can we quantify this correlation?

# Calculate correlation of "price_usd" and "area_m2"
p_correlation = df["area_m2"].corr(df["price_usd"])

# Print correlation coefficient
print("Correlation of 'area_m2' and 'price_usd' (all Mexico):", p_correlation)
# Calculate correlation of "price_usd" and "area_m2"
p_correlation = df["area_m2"].corr(df["price_usd"])
​
# Print correlation coefficient
print("Correlation of 'area_m2' and 'price_usd' (all Mexico):", p_correlation)
# Correlation of 'area_m2' and 'price_usd' (all Mexico): 0.5909760275626652
```

But does this relationship hold true in every state? Let's look at a couple of states, starting with Morelos.

```py
# Declare variable `df_morelos` by subsetting `df`
df_morelos = df.groupby("state").get_group("Morelos")
# OR
df_morelos = df[ df["state"] == "Morelos"]

# after same steps
# Correlation of 'area_m2' and 'price_usd' (Morelos): 0.8433668444446696
```

With a correlation coefficient that high, we can say that there's a strong relationship between house size and price in Morelos.

To conclude, let's look at the capital Mexico City (Distrito Federal).

> Correlation of 'area_m2' and 'price_usd' (Mexico City): 0.4111500981683044

One interpretation is that the relationship we see between size and price in many states doesn't hold true in the country's biggest and most economically powerful urban center because there are other factors that have a larger influence on price.
