# Data Visualisation

## Matplotlib

### Boxplots

A boxplot is a graph that shows the minimum, first quartile, median, third quartile, and the maximum values in a dataset. Boxplots are useful, as they provide a visual summary of the data enabling researchers to quickly identify mean values, the dispersion of the data set, and signs of skewness.
A boxplot always contains a box with two lines above and below it. Those lines are called whiskers, and the ends of those lines represent the upper and lower bounds of the dataset. There are also some values above the top whisker, but we'll come back to them a little later. In the meantime, notice that the plot divides the data into four sections:

- the bottom of the lower whisker to the bottom of the box,
- the bottom of the box to the line in the middle,
- the middle line to the top line of the box, and
- the top of the box to the end of the upper whisker.

These sections are called intervals, and the three lines that divide them are called quartiles. Each interval contains 25% of the observations in the dataset, which means that the box created by the first and third quartiles represents the middle 50% of observations. The second quartile — the orange line on our graph — represents the dataset's median value.

Keeping all that in mind, the boxplot here shows that while there are some very large properties in our Colombia dataset, half the properties tend to be much smaller. Remember those data points above the top whisker? Those are called outliers, and they represent values so extreme that they fall outside the meaningful spread of observations in the dataset. Since half of our properties are small — one-bedroom apartments, say — we don't really need to pay attention to eighty-room mansions nestled in the middle of thousand-acre estates. Not for this project anyway. Part of the purpose of making a boxplot is to find those outliers and discard them from future analyses.

```py
import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv("data/colombia-real-estate-1.csv", usecols=["area_m2"])
plt.boxplot(df["area_m2"] '''vert=False to create horizontal boxplot''') 
plt.ylabel("Area [sq. meters]")
plt.title("Area in Square Meters")
```

![Boxplot](\images\boxplot.png)

### Histograms
A histogram is a graph that shows the frequency distribution of numerical data. In addition to helping us understand frequency, histograms are also useful for detecting outliers.

```py
df = pd.read_csv("data/colombia-real-estate-1.csv", usecols=["area_m2"])
plt.hist(df, bins=10, rwidth=0.9, color="b")
plt.title("The Area of Real Estate in Colombia")
plt.xlabel("Property Area")
plt.ylabel("Number of Properties")
plt.grid(axis="y", alpha=0.75)
```

![Histogram](\images\hist.png)

There are two things to consider in this histogram. First and foremost is its interpretation: the distribution is skewed significantly to the left. In this case, the data suggest that the majority of properties in Colombia are smaller than 150 square meters.
You might also have noticed that there are ten bars. In a histogram, we call these bars bins. A bin is simply a way to group data to make it easier to see trends. You can use as many or as few as you like; just recognize that the fewer bins you use, the less detailed the output will become.

Depending on the story you want your histogram to tell, it might be more important for a trend to be smooth, or it might be more important to show smaller levels of variation. Here, we can still see that the properties in Colombia tend to be small, but the size of the properties are not evenly distributed. This histogram doesn't tell us anything about why this might be true, but it does suggest that there might be something more interesting going on in the background.

### Bar Charts
A bar chart is a graph that shows all the values of a categorical variable in a dataset. They consist of an axis and a series of labeled horizontal or vertical bars. The bars depict frequencies of different values of a variable or simply the different values themselves. The numbers on the y-axis of a vertical bar chart or the x-axis of a horizontal bar chart are called the scale.

```py
mexico_city1 = pd.read_csv("./data/mexico-city-real-estate-1.csv")
mexico_city1.head()
new_columns = ["empty1", "country", "city", "borough", "empty2"] # since place_with_parent_names column looks like |México|Distrito Federal|Álvaro Obregón|
mexico_city1[new_columns] = mexico_city1["place_with_parent_names"].str.split("|", 4, expand=True)
mexico_city1 = mexico_city1.drop(["empty1", "empty2"], axis=1)

by_borough = mexico_city1["borough"].value_counts()

plt.bar(x=by_borough.index, height=by_borough.values)
plt.ylabel("Number of Properties")
plt.xticks(rotation=90)
```

![Barplot](\images\barplot.png)

### Scatter Plots
A scatter plot is a graph that uses dots to represent values for two different numeric variables. The position of each dot on the horizontal and vertical axis indicates values for an individual data point. Scatter plots are used to observe relationships between variables, and are especially useful if you're looking for correlations.

```py
df1 = pd.read_csv("data/colombia-real-estate-3.csv", usecols=["area_m2", "price_usd"])
plt.scatter(df1["area_m2"], df1["price_usd"], color="r") # order matters, changing the order that is price then area will change the plot
plt.xlabel("Property Area")
plt.ylabel("Price in US Dollars")
plt.title("Property Area vs Price in US Dollars")
```

![Scatterplot](\images\scatter_plot.png)

there are lots of cheap, small properties, and as the size of the property goes up, so does the price

You may have noticed that there are lots of data points here, which makes it difficult to see if there's really a trend going on. This issue is called **over-plotting**, and it's very common in large datasets.

One solution to over-plotting is to use the `df.sample` method to select a random sample from the dataset. In the example below, note that the `frac=0.50` indicates that the random sample will consist of 50% of the data points in the set.

```py
df3 = pd.read_csv("data/colombia-real-estate-3.csv", usecols=["area_m2", "price_usd"])
df4 = df3.sample(frac=0.50, replace=True, random_state=1)
plt.scatter(df4["area_m2"], df4["price_usd"], color="r")
plt.xlabel("Property Area")
plt.ylabel("Price in US Dollars")
plt.title("Property Area vs Price in US Dollars")
```
### Add a vertical or horizontal line across a plot
```py
# Vertical lines can be added to an existing plot in Matplotlib
plt.axvline(250, linestyle="--", color="blue", label="Line Title") 
# Creating a horizontal line at y=0.5
plt.axhline(y=0.5, linestyle="--", color="blue", label="Horizontal Line Title")

# Adding some other plot elements for context
plt.plot([0, 1], [0, 1])  # A simple line plot

# Display the legend
plt.legend()
```

## Pandas

### Correlation Matrices
When examining numerical data in columns of a DataFrame, you might want to know how well one column can be approximated as a linear function of another column.

```py
import pandas as pd

columns = ["price_aprox_usd", "surface_covered_in_m2"]
mexico_city1 = pd.read_csv("./data/mexico-city-real-estate-1.csv", usecols=columns)
corr = mexico_city1.corr()
corr.style.background_gradient(axis=None)
```

|                       | price_aprox_usd | surface_covered_in_m2 |
|-----------------------|-----------------|-----------------------|
| **price_aprox_usd**   | 1.000000        | 0.553326              |
| **surface_covered_in_m2** | 0.553326        | 1.000000              |

### Bar Charts
A bar chart is a graph that shows all the values of a categorical variable in a dataset. They consist of an axis and a series of labeled horizontal or vertical bars. The bars depict frequencies of different values of a variable or simply the different values themselves. The numbers on the y-axis of a vertical bar chart or the x-axis of a horizontal bar chart are called the scale.

```py
df1["property_type"].value_counts().plot(
    kind="bar", title="Property Types in Colombia", ylabel="Count"
) # kind = "barh" for horizontal
```

### Histograms
A histogram is a graph that shows the frequency distribution of numerical data. In addition to helping us understand frequency, histograms are also useful for detecting outliers. We can use the .hist() function from Pandas DataFrame to draw histograms for a specific column, as long as the data type is numerical.

```py
df1["price"].hist(bins=100)
```

### Scatter Plots
A scatter plot is a graph that uses dots to represent values for two different numeric variables. The position of each dot on the horizontal and vertical axis indicates values for an individual data point. Scatter plots are used to observe relationships between variables, and are especially useful if you're looking for correlations.

```py
df1.plot(kind="scatter", x="price", y="surface_covered_in_m2")
```

### Line Plots
Line plots demonstrate relationships between two variables which have some order.
```py
mexico_city1.plot.scatter(x="surface_covered_in_m2", y="price_aprox_local_currency")

df.plot(
    x="x_coords",
    y="y_coords",
    xlabel="surface_covered_in_m2",
    ylabel="price_aprox_local_currency",
    label="linear model",
) # creates a plot with "x_coords" on the x-axis and "y_coords"
```

## PLotly

### Scatter Plots
A scatter plot is a graph that uses dots to represent values for two different numeric variables. The position of each dot on the horizontal and vertical axis indicates values for an individual data point. Scatter plots are used to observe relationships between variables, and are especially useful if you're looking for correlations.
```py
import pandas as pd
import plotly.express as px

mexico_city1 = pd.read_csv("./data/mexico-city-real-estate-1.csv")

# clean the data and drop `NaNs`
mexico_city1 = mexico_city1.drop(
    ["floor", "price_usd_per_m2", "expenses", "rooms"], axis=1
)
mexico_city1 = mexico_city1.dropna(axis=0)

fig = px.scatter(mexico_city1, x="price", y="surface_covered_in_m2")
fig.show()
```
![Scatterplot](\images\scatter2.png)

### 3D Scatter Plots
Scatter plots can summarize information in a DataFrame. Three dimensional scatter plots look great, but be careful: it can be difficult for people who might not be sure what they're looking at to accurately determine values of points in the plot. Still, scatter plots are useful for displaying relationships between three quantities that would be more difficult to observe in a two dimensional plot.

```py
fig = px.scatter_3d(
    mexico_city1_subset,
    x="Borough",
    y="surface_covered_in_m2",
    z="price",
    symbol="property_type",
    color="property_type",
    labels={
        "surface_covered_in_m2": "Surface Covered in m^2",
        "price": "Price",
        "property_type": "Property Type",
    },
)

fig.show()
```
![3d Scatter plot](\images\3d.png)

### Mapbox Scatter Plots
A mapbox scatter plot is a special kind of scatter plot that allows you to create scatter plots in two dimensions and then superimpose them on top of a map. Our mexico-city-real-estate-1.csv dataset is a good place to start, because it includes location data. After importing the dataset and removing rows with missing data, split the lat-lon column into two separate columns: one for latitude and the other for longitude. Then use these to make a mapbox plot. Unfortunately, at present this type of plot does not easily allow for marker shape to vary based on a column of the DataFrame.

```py
fig = px.scatter_mapbox(
    mexico_city1,
    lat="latitude",
    lon="longitude",
    color="property_type",
    mapbox_style="carto-positron",
    labels={"property_type": "Property Type"},
    title="Distribution of Property Types for Sale in Mexico City",
)
fig.show()
```
![Mapbox](\images\mapbox.png)

### Choropleth Maps
A Choropleth Map is a map composed of colored polygons, showing the variable of interest at different color depth across geographies.Plotly express has a function called px.choropleth that be used to plot Choropleth Map. The challenges here are getting the geometry information. There are two ways, one is to use the built-in geometries in plotly when plot US States (use the state name directly) and world countries (use ISP-3 code). Another way is to look for GeoJSON files where each location has geometry information. In the following example, we will show the plot in US States with a synthetic data set.

```py
# Create Synthetic Dataset
df = pd.DataFrame.from_dict(
    {"State": ["CA", "TX", "NY", "HI", "DE"], "Temparature": [100, 120, 110, 90, 105]}
)
# Plot the data set in US map
fig = px.choropleth(
    df, locations="State", locationmode="USA-states", color="Temparature", scope="usa"
)
fig.show()
```
![Choropleth Map](\images\newplot.png)

### Histogram
A histogram is a graph that shows the frequency distribution of numerical data. In addition to helping us understand frequency, histograms are also useful for detecting outliers. We can use the px.histogram() function from Plotly to draw histograms for specific columns, as long as the data type is numerical.

```py
import plotly.express as px
​
df = pd.read_csv("data/mexico-city-real-estate-1.csv")
fig = px.histogram(df, x="price")
fig.show()
```

### Boxplots
A boxplot is a graph that shows the minimum, first quartile, median, third quartile, and the maximum values in a dataset. Boxplots are useful because they provide a visual summary of the data, enabling researchers to quickly identify mean values, the dispersion of the data set, and signs of skewness. In the following example, we will explore how to draw boxplots for specific columns of a DataFrame.
```py
# Read Data
mexico_city1 = pd.read_csv("./data/mexico-city-real-estate-1.csv")
​
# Clean the data and drop `NaNs`
mexico_city1 = mexico_city1.drop(
    ["floor", "price_usd_per_m2", "expenses", "rooms"], axis=1
)
mexico_city1 = mexico_city1.dropna(axis=0)
​
# Exclude some outliers
mexico_city1 = mexico_city1[mexico_city1["price"] < 100000000]

import plotly.express as px

fig = px.box(mexico_city1, y="price")
fig.show()
```
```py
fig = px.box(mexico_city1, x="property_type", y="price")
fig.show() # to check the distribution of a column value by different categories, defined by another categorical column, you can add an x argument to specify the name of the categorical column.
```
![Boxplot](\images\boxplot_2.png)

### Bar Chart
A bar chart is a graph that shows all the values of a categorical variable in a dataset. They consist of an axis and a series of labeled horizontal or vertical bars. The bars depict frequencies of different values of a variable or simply the different values themselves. The numbers on the y-axis of a vertical bar chart or the x-axis of a horizontal bar chart are called the scale.

```py
# Read Data
mexico_city1 = pd.read_csv("./data/mexico-city-real-estate-1.csv")

# Clean the data and drop `NaNs`
mexico_city1 = mexico_city1.drop(
    ["floor", "price_usd_per_m2", "expenses", "rooms"], axis=1
)

# find location columns from place_with_parent_names
mexico_city1[
    ["First Empty", "Country", "City", "Borough", "Second Empty"]
] = mexico_city1["place_with_parent_names"].str.split("|", 4, expand=True)
mexico_city1 = mexico_city1.drop(["First Empty", "Second Empty"], axis=1)
mexico_city1 = mexico_city1.dropna(axis=0)

# Exclude some outliers
mexico_city1 = mexico_city1[mexico_city1["price"] < 100000000]
mexico_city1 = mexico_city1[mexico_city1["Borough"] != ""]

# Plot value_counts() data
fig = px.bar(mexico_city1["Borough"].value_counts())
fig.show()
```
```py
#  plot the number of observations by borough and property type. First of all, we need use groupby to calculate the aggregated counts for each Borough and property type combination. By specifying x, y and color, the following bar graph shows the total counts by Borough, with different property types showing in different colors. Note y has to be numerical, while x and color are usually categorical variables.
size_df = mexico_city1.groupby(["Borough", "property_type"], as_index=False).size()
fig = px.bar(size_df, x="Borough", y="size", color="property_type", barmode="relative")
fig.show()
# Note the argument barmode is specified as 'relative', which is also the default value. In this mode, bars are stacked above each other. We can also use 'overlay' where bars are drawn on top of each other. If we want bars to be placed beside each other, we can specify barmode as "group".
```
![Barplot barmode = "group"](images\barplot_2.png)

## Seaborn

### Scatter Plots
`sns.scatterplot(
    data=mexico_city1, x="price", y="surface_covered_in_m2", hue="property_type"
)`

### Bar plot
```py
# Read Data
mexico_city1 = pd.read_csv("./data/mexico-city-real-estate-1.csv")

# Clean the data and drop `NaNs`
mexico_city1 = mexico_city1.drop(
    ["floor", "price_usd_per_m2", "expenses", "rooms"], axis=1
)

# find location columns from place_with_parent_names
mexico_city1[
    ["First Empty", "Country", "City", "Borough", "Second Empty"]
] = mexico_city1["place_with_parent_names"].str.split("|", 4, expand=True)
mexico_city1 = mexico_city1.drop(["First Empty", "Second Empty"], axis=1)
mexico_city1 = mexico_city1.dropna(axis=0)

# Exclude some outliers
mexico_city1 = mexico_city1[mexico_city1["price"] < 100000000]
mexico_city1 = mexico_city1[mexico_city1["Borough"] != ""]

bar_df = pd.DataFrame(mexico_city1["Borough"].value_counts()).reset_index() # reate a DataFrame showing the value counts

# Increase plot size
sns.set(rc={"figure.figsize": (15, 4)})

# Plot the bar plot
ax = sns.barplot(data=bar_df, x="index", y="Borough")

# Rotate the x axis
ax.set_xticklabels(ax.get_xticklabels(), rotation=75)
```

### Correlation Heatmaps
A correlation heatmap shows the relative strength of correlations between the variables in a dataset.

```py
import pandas as pd
import seaborn as sns

mexico_city1 = pd.read_csv("./data/mexico-city-real-estate-1.csv")
mexico_city1 = mexico_city1.drop(
    ["floor", "price_usd_per_m2", "expenses", "rooms"], axis=1
)
mexico_city1 = mexico_city1.dropna(axis=0)
mexico_city1_numeric = mexico_city1.select_dtypes(include="number")
corr = mexico_city1_numeric.corr(method="pearson")
sns.heatmap(corr)
```
![Heat map](images\heatmap.png)