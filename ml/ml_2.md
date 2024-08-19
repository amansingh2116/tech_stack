# Housing in Buenos - aries

## Predicting Price with Size

```py
import warnings

import matplotlib.pyplot as plt
import pandas as pd
import wqet_grader
from IPython.display import VimeoVideo
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_absolute_error
from sklearn.utils.validation import check_is_fitted

warnings.simplefilter(action="ignore", category=FutureWarning)
```

In this project, you're working for a client who wants to create a model that can predict the price of apartments in the city of Buenos Aires — with a focus on apartments that cost less than $400,000 USD.

### Prepare Data

In the previous project, we cleaned our data files one-by-one. This isn't an issue when you're working with just three files, but imagine if you had several hundred! One way to automate the data importing and cleaning process is by writing a function. This will make sure that all our data undergoes the same process, and that our analysis is easily reproducible — something that's very important in science in general and data science in particular.

```py
def wrangle(filename):
    # Import csv
    df = pd.read_csv(filename)
    
    # subset to properties in "Capital Federal"
    mask1 = df["place_with_parent_names"].str.contains("Capital Federal")
    
    # subset to "apartments"
    mask2 = df["property_type"]=="apartment"
    
    # subset to where property price < $4,00,000
    mask3 = df["price_aprox_usd"]<400_000
    
    df = df[mask1 & mask2 & mask3]
        
    # Removing Outliers (removes observations that are outliers, 
    # Specifically, all observations should fall between the 0.1 and 0.9 quantiles for "surface_covered_in_m2".)
    low,high = df["surface_covered_in_m2"].quantile([0.1,0.9])
    mask4 = df["surface_covered_in_m2"].between(low, high)
    
    df = df[mask4]

    # Split "lat-lon" column
    df[["lat", "lon"]] = df["lat-lon"].str.split(",", expand=True).astype(float)
    df.drop(columns="lat-lon", inplace=True)
    
    # creating neighbourhood column
    df["neighborhood"] = df["place_with_parent_names"].str.split('|', expand = True)[3]
    df.drop(columns="place_with_parent_names", inplace=True)
    
    return df

df = wrangle("data/buenos-aires-real-estate-1.csv")
print("df shape:", df.shape)
df.head()

df = pd.concat([frame1, frame2]) ## when you have data in two different files

# histogram of "surface_covered_in_m2"
plt.hist(df["surface_covered_in_m2"])
plt.xlabel("Area [sq meters]")
plt.ylabel("Distribution of Apartment Sizes")
# histogram suggests that there are outliers in your dataset. This can affect model performance — especially in the sorts of linear models we'll learn about in this project. To confirm, let's look at the summary statistics for the "surface_covered_in_m2" feature.

df.describe()

# The statistics above confirm what we suspected. While most of the apartments in our dataset are smaller that 73 square meters, there are some that are several thousand square meters. 

# histogram changes now that there are no outliers. 
# Now that our dataset is free of outliers, it's time to start exploring the relationship between apartment size and price. Let's use one of the tools we learned in the last project.

# scatter plot that shows price ("price_aprox_usd") vs area ("surface_covered_in_m2") in our dataset.
plt.scatter(x=df["surface_covered_in_m2"], y=df["price_aprox_usd"])
plt.xlabel("Area [sq meters]")
plt.ylabel("Price [USD]")
plt.title("Buenos: Price vs Area")

# This plot suggests that there's a moderate positive correlation between apartment price and size. This means that if thing we want to predict is price, size will be a good feature to include.

# A key part in any model-building project is separating your target (the thing you want to predict) from your features (the information your model will use to make its predictions).
features = ["surface_covered_in_m2"]
X_train = df[features]
target = "price_aprox_usd"
y_train = df[target]
```

### Build Model

#### Baseline

The first step in building a model is baselining. To do this, ask yourself how you will know if the model you build is performing well?" One way to think about this is to see how a "dumb" model would perform on the same data. Some people also call this a naïve or baseline model, but it's always a model makes only one prediction — in this case, it predicts the same price regardless of an apartment's size.

```py
y_mean = y_train.mean() # Calculate the mean of your target vector y_train

y_pred_baseline = [y_mean for i in range(len(y_train))] # OR [y_mean] * len(y_train) ; contains the value of y_mean repeated so that it's the same length at y

# Add a line to the plot below that shows the relationship between the observations X_train and our dumb model's predictions y_pred_baseline.
plt.plot(X_train.values, y_pred_baseline, color = "red", label ="Baseline Model")
plt.scatter(X_train, y_train)
plt.xlabel("Area [sq meters]")
plt.ylabel("Price [USD]")
plt.title("Buenos Aires: Price vs. Area")
plt.legend()

# Looking at this visualization, it seems like our baseline model doesn't really follow the trend in the data. 
# But, as a data scientist, you can't depend only on a subjective plot to evaluate a model. You need an exact, mathematically calculate performance metric. There are lots of performance metrics, but the one we'll use here is the mean absolute error.
mae_baseline = mean_absolute_error(y_train, y_pred_baseline)
​
print("Mean apt price", round(y_mean, 2))
# Mean apt price 135527.84
print("Baseline MAE:", round(mae_baseline, 2))
# Baseline MAE: 45199.46

# If we always predicted that an apartment price is $135,527.84, our predictions would be off by an average of $45,199.46. 
# It also tells us that our model needs to have mean absolute error below $45,199.46 in order to be useful.
```

#### Iterate

The next step in building a model is iterating. This involves building a model, training it, evaluating it, and then repeating the process until you're happy with the model's performance. Even though the model we're building is linear, the iteration process rarely follows a straight line. Be prepared for trying new things, hitting dead-ends, and waiting around while your computer does long computations to train your model.

```py
model = LinearRegression() #  Instantiate a LinearRegression model named model.
# The second thing we need to do is use our data to train our model. Another way to say this is fit our model to the training data.
model.fit(X_train, y_train)
```

#### Evaluate

The final step is to evaluate our model. In order to do that, we'll start by seeing how well it performs when making predictions for data that it saw during training.

```py
y_pred_training = model.predict(X_train) # create a list of predictions for the observations in your feature matrix X_train

# Calculate your training mean absolute error for your predictions 
mae_training = mean_absolute_error(y_train, y_pred_training)
print("Training MAE:", round(mae_training, 2))
# Training MAE: 31248.26

# Our model beat the baseline by over $10,000! That's a good indicator that it will be helpful in predicting apartment prices. 
# But the real test is how the model performs on data that it hasn't seen before, data that we call the test set. 

# you'll have to create your own test set before you train your model, but here we'll use one that's pre-made
X_test = pd.read_csv("data/buenos-aires-test-features.csv")[features]
y_pred_test = pd.Series(model.predict(X_test))
```

Ideally, you want your test performance metrics to be the same as its training performance metrics. In practice, test metrics tend to be a little worse (this means a larger number in the case of mean absolute error). But as long as the training and test performance are close to each other, you can be confident that your model will generalize well.

> **Warning:** During the iteration phase, you can change and retrain your model as many times as you want. You can also check the model's training performance repeatedly. But once you evaluate its test performance, you can't make any more changes.
> A test only counts if neither the model nor the data scientist has seen the data before. If you check your test metrics and then make changes to the model, you can introduce biases into the model that compromise its generalizability.

### Communicate Results

Once your model is built and tested, it's time to share it with others. If you're presenting to simple linear model to a technical audience, they might appreciate an equation. When we created our baseline model, we represented it as a line.

```py
# Extract the intercept from your model
intercept = round(model.intercept_, 2)

# Extract the coefficient associated "surface_covered_in_m2" in your model
coefficient = round(model.coef_[0], 2) # since model.coef_ is in a list

print(f"apt_price = {intercept} + {coefficient} * surface_covered")
# apt_price = 11433.31 + 2253.12 * surface_covered

# Add a line to the plot below that shows the relationship between the observations in X_train and your model's predictions y_pred_training.
plt.plot(X_train, model.predict(X_train), color="red", label="Linear Model")
plt.scatter(X_train, y_train)
plt.xlabel("surface covered [sq meters]")
plt.ylabel("price [usd]")
plt.legend()
```

Now that you know a basic workflow, lets proceed with trying to predict prices with better models.

## Predicting Prices with Location

### Import and prepare data

```py
import warnings

import numpy as np
import pandas as pd
import plotly.express as px
import plotly.graph_objects as go
import wqet_grader
from IPython.display import VimeoVideo
from sklearn.impute import SimpleImputer
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_absolute_error
from sklearn.pipeline import Pipeline, make_pipeline
from sklearn.utils.validation import check_is_fitted

warnings.simplefilter(action="ignore", category=FutureWarning)

frame1 = wrangle("data/buenos-aires-real-estate-1.csv")
frame2 = wrangle("data/buenos-aires-real-estate-2.csv")

df = pd.concat([frame1, frame2])
```

### Explore

Previously, we built a simple linear model that predicted apartment price based on one feature, "surface_covered_in_m2". In this lesson, we're building a multiple linear regression model that predicts price based on two features, "lon" and "lat". This means that our data visualizations now have to communicate three pieces of information: Longitude, latitude, and price. How can we represent these three attributes on a two-dimensional screen?

One option is to incorporate color into our scatter plot. For example, in the Mapbox scatter plot below, the location of each point represents latitude and longitude, and color represents price.

```py
fig = px.scatter_mapbox(
    df,  # Our DataFrame
    lat=df["lat"],
    lon=df["lon"],
    width=600,  # Width of map
    height=600,  # Height of map
    color=df["price_aprox_usd"],
    hover_data=["price_aprox_usd"],  # Display price when hovering mouse over house
)

fig.update_layout(mapbox_style="open-street-map")

fig.show()
```

Another option is to add a third dimension to our scatter plot. We can plot longitude on the x-axis and latitude on the y-axis (like we do in the map above), and then add a z-axis with price

```py
# Create 3D scatter plot
fig = px.scatter_3d(
    df,
    x="lon",
    y="lat",
    z="price_aprox_usd",
    labels={"lon": "longitude", "lat": "latitude", "price_aprox_usd": "price"},
    width=600,
    height=500,
)

# Refine formatting
fig.update_traces(
    marker={"size": 4, "line": {"width": 2, "color": "DarkSlateGrey"}},
    selector={"mode": "markers"},
)

# Display figure
fig.show()
```

### Model

#### Baseline model

```py
features = ["lon", "lat"]
X_train = df[features]

target = "price_aprox_usd"
y_train = df[target]

y_pred_baseline = [y_train.mean()] * len(y_train)

mae_baseline = mean_absolute_error(y_train, y_pred_baseline)
print("Mean apt price", round(y_mean, 2))
print("Baseline MAE:", round(mae_baseline, 2))
# Mean apt price 134732.97
# Baseline MAE: 45422.75
```

#### Iterate model

Take a moment to scroll up to the output for df.info() and look at the values in the "Non-Null Count" column. Because of the math it uses, a linear regression model can't handle observations where there are missing values. Do you see any columns where this will be a problem?

In the last project, we simply dropped rows that contained NaN values, but this isn't ideal. Models generally perform better when they have more data to train with, so every row is precious. Instead, we can fill in these missing values using information we get from the whole column — a process called imputation. There are many different strategies for imputing missing values, and one of the most common is filling in the missing values with the mean of the column.

In addition to predictors like LinearRegression, scikit-learn also has transformers that help us deal with issues like missing values. Let's see how one works, and then we'll add it to our model.

```py
imputer = SimpleImputer()  
# Initialize a SimpleImputer to handle missing values in the dataset.

imputer.fit(X_train)  
# Fit the imputer on the training data, learning the statistics needed (e.g., mean) to replace missing values.

XT_train = imputer.transform(X_train)  
# Apply the imputer to the training data, replacing any missing values using the learned statistics.

pd.DataFrame(XT_train, columns=X_train.columns).info()  
# Convert the transformed training data into a DataFrame and display information about its structure, such as data types and non-null counts.

model = make_pipeline(  
    # Create a pipeline that sequentially applies a series of transformations and a model.
    SimpleImputer(),     
    # Step 1: Handle missing values in the dataset within the pipeline.
    LinearRegression()   
    # Step 2: Apply a Linear Regression model to the data after handling missing values.
)

model.fit(X_train, y_train)  
# Fit the entire pipeline on the training data, learning the model parameters from X_train and y_train.

```

#### Evaluate model

```py
y_pred_training = model.predict(X_train)

mae_training = mean_absolute_error(y_train, y_pred_training)
print("Training MAE:", round(mae_training, 2))

# Training MAE: 42962.72
# It looks like our model performs a little better than the baseline. This suggests that latitude and longitude aren't as strong predictors of price as size is.

X_test = pd.read_csv("data/buenos-aires-test-features.csv")[features]
y_pred_test = pd.Series(model.predict(X_test))
y_pred_test.head()
```

#### Communicate

```py
intercept = model.named_steps["linearregression"].intercept_.round(2)
coefficients = model.named_steps["linearregression"].coef_.round(2)

print(
    
    f"price = {intercept} + ({coefficients[0]} * longitude) + ({coefficients[1]} * latitude)"
)
# price = 38113587.05 + (196709.42 * longitude) + (765466.58 * latitude)

# Visualise
# how we would represent our linear model in a 3D plot. If you guessed that we would use a plane, you're right!
# Create 3D scatter plot
fig = px.scatter_3d(
    df,
    x="lon",
    y="lat",
    z="price_aprox_usd",
    labels={"lon": "longitude", "lat": "latitude", "price_aprox_usd": "price"},
    width=600,
    height=500,
)

# Create x and y coordinates for model representation
x_plane = np.linspace(df["lon"].min(), df["lon"].max(), 10)
y_plane = np.linspace(df["lat"].min(), df["lat"].max(), 10)
xx, yy = np.meshgrid(x_plane, y_plane)

# Use model to predict z coordinates
z_plane = model.predict(pd.DataFrame({"lon": x_plane, "lat": y_plane}))
zz = np.tile(z_plane, (10, 1))

# Add plane to figure
fig.add_trace(go.Surface(x=xx, y=yy, z=zz))

# Refine formatting
fig.update_traces(
    marker={"size": 4, "line": {"width": 2, "color": "DarkSlateGrey"}},
    selector={"mode": "markers"},
)

# Display figure
fig.show()
```

## Predictiong price with neighborhood

### prepare data

```py
import warnings
from glob import glob

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import wqet_grader
from category_encoders import OneHotEncoder
from IPython.display import VimeoVideo
from sklearn.linear_model import LinearRegression, Ridge  # noqa F401
from sklearn.metrics import mean_absolute_error
from sklearn.pipeline import make_pipeline
from sklearn.utils.validation import check_is_fitted

warnings.simplefilter(action="ignore", category=FutureWarning)

# Use glob to create a list that contains the filenames for all the Buenos Aires real estate CSV files in the data directory
files = glob("./data/buenos-aires-real-estate-[0-5].csv")

# Use your wrangle function in a for loop to create a list named frames. 
frames = []
for i in files:
    df = wrangle(i)
    frames.append(df)

df = pd.concat(frames, ignore_index = True)
```

### Building the Model

#### Baseline Model

```py
target = "price_aprox_usd"
features = ["neighborhood"]
y_train = df[target]
X_train = df[features]

y_mean = y_train.mean()
y_pred_baseline = [y_mean]*len(y_train)
print("Mean apt price:", y_mean)
mae_baseline = mean_absolute_error(y_train, y_pred_baseline)
print("Baseline MAE:", mae_baseline)
# Mean apt price: 132383.83701458524
# Baseline MAE: 44860.10834274133
```

#### Iterate the model

If you try to fit a LinearRegression predictor to your training data at this point, you'll get an error that looks like this:

ValueError: could not convert string to float
What does this mean? When you fit a linear regression model, you're asking scikit-learn to perform a mathematical operation. The problem is that our training set contains neighborhood information in non-numerical form. In order to create our model we need to encode that information so that it's represented numerically. The good news is that there are lots of transformers that can do this. Here, we'll use the one from the Category Encoders library, called a OneHotEncoder.

```py
ohe = OneHotEncoder(use_cat_names = True)
ohe.fit(X_train)
XT_train = ohe.transform(X_train)

model = make_pipeline(
    OneHotEncoder(use_cat_names = True),
    Ridge()
)
model.fit(X_train, y_train)

y_pred_training = model.predict(X_train)
mae_training = mean_absolute_error(y_train, y_pred_training)
print("Training MAE:", round(mae_training, 2))
# Training MAE: 39341.34

X_test = pd.read_csv("data/buenos-aires-test-features.csv")[features]
y_pred_test = pd.Series(model.predict(X_test))

# Too high mean absolute error, i.e., the model which fit on training data did not get fit enough for actual or general data so we have to do some generalisation, one way for which could be applying ridge regression instead of linear regression

model = make_pipeline(
    OneHotEncoder(use_cat_names = True),
    Ridge()
)
model.fit(X_train, y_train)

y_pred_training = model.predict(X_train)
mae_training = mean_absolute_error(y_train, y_pred_training)
print("Training MAE:", round(mae_training, 2))
# Training MAE: 39350.22

# And Now, model's mean absolute error is 44533.576 for the general data.
```

#### Communicate results

```py
intercept = model.named_steps["ridge"].intercept_
coefficients = model.named_steps["ridge"].coef_

# Extract the feature names of your encoded data from the OneHotEncoder in your model.
feature_names = model.named_steps["onehotencoder"].get_feature_names()

#  pandas Series named feat_imp where the index is your features and the values are your coefficients.
feat_imp = pd.Series(coefficients, index = feature_names)

# print the equation that your model has determined for predicting apartment price based on neighborhood
print(f"price = {intercept.round(2)}")
for f, c in feat_imp.items():
    print(f"+ ({round(c, 2)} * {f})")

# Visualise
# Create a horizontal bar chart that shows the top 15 coefficients for your model, based on their absolute value.
feat_imp.sort_values(key = abs).tail(15).plot(kind = 'barh')
plt.xlabel("Importance [USD]")
plt.ylabel("Features")
plt.title("Feature Importance for Apartment Price")

# Looking at this bar chart, we can see that the poshest neighborhoods in Buenos Aires like Puerto Madero and Recoleta increase the predicted price of an apartment, while more working-class neighborhoods like Villa Soldati and Villa Lugano decrease the predicted price.
```

## Predicting Price with Size, Location, and Neighborhood

### Prepare Data & Import

```py
import warnings
from glob import glob
​
import pandas as pd
import seaborn as sns
import wqet_grader
from category_encoders import OneHotEncoder
from IPython.display import VimeoVideo
from ipywidgets import Dropdown, FloatSlider, IntSlider, interact
from sklearn.impute import SimpleImputer
from sklearn.linear_model import LinearRegression, Ridge  # noqa F401
from sklearn.metrics import mean_absolute_error
from sklearn.pipeline import make_pipeline
from sklearn.utils.validation import check_is_fitted
​
warnings.simplefilter(action="ignore", category=FutureWarning)

def wrangle(filepath):
    # Read CSV file
    df = pd.read_csv(filepath)
​
    # Subset data: Apartments in "Capital Federal", less than 400,000
    mask_ba = df["place_with_parent_names"].str.contains("Capital Federal")
    mask_apt = df["property_type"] == "apartment"
    mask_price = df["price_aprox_usd"] < 400_000
    df = df[mask_ba & mask_apt & mask_price]
​
    # Subset data: Remove outliers for "surface_covered_in_m2"
    low, high = df["surface_covered_in_m2"].quantile([0.1, 0.9])
    mask_area = df["surface_covered_in_m2"].between(low, high)
    df = df[mask_area]
​
    # Split "lat-lon" column
    df[["lat", "lon"]] = df["lat-lon"].str.split(",", expand=True).astype(float)
    df.drop(columns="lat-lon", inplace=True)
​
    # Get place name
    df["neighborhood"] = df["place_with_parent_names"].str.split("|", expand=True)[3]
    df.drop(columns="place_with_parent_names", inplace=True)
    
    # dropping columns with more than half NaN values
    cols_to_drop = [col for col in df.columns if df[col].count() < len(df)//2] # OR if df.isnull().sum() / len(df) > 0.5
    df.drop(columns=cols_to_drop, inplace=True)

    # The first thing we need to consider when trying to use all the features df is missing values. While it's true you can impute missing values, there still needs to be enough data in a column to do a good imputation. A general rule is that, if more than half of the data in a column is missing, it's better to drop it then try imputing.
    
    # Drop low and high cardinality categorical variables
    df.drop(columns=["operation","property_type","currency","properati_url"], inplace = True)
    
    # The next thing we need to look out for are categorical columns with low or high cardinality. If there's only one category in a column, it won't provide any unique information to our model. At the other extreme, columns where nearly every row has its own category won't help our model in identifying useful trends in the data.
    # df.select_dtypes("object").nunique()

    # Drop leaky columns
    df.drop(columns=["price", "price_aprox_local_currency", "price_usd_per_m2", "price_per_m2"], inplace = True)

    # It's also important for us to drop any columns that would constitute leakage, that is, features that were created using our target or that would give our model information that it won't have access to when it's deployed. It involves the columns that are indirectly related to the target that is the price.
    
    # Drop columns with multicollinearity
    df.drop(columns = ["surface_total_in_m2", "rooms"], inplace = True)

    # Finally, the last issue we need to keep an eye out for is multicollinearity, that is, features in our feature matrix that are highly correlated with each other. A good way to detect this is to use a heatmap.
    # corr = df.select_dtypes("number").drop(columns="price_aprox_usd").corr()
    # sns.heatmap(corr)
    
    return df

files = glob("./data/buenos-aires-real-estate-*.csv")

frames = []
for i in files:
    df = wrangle(i)
    frames.append(df)

df = pd.concat(frames, ignore_index = True)
```

### Models

```py
target = "price_aprox_usd"
y_train= df[target]
X_train = df.drop(columns=target)

y_mean = y_train.mean()
y_pred_baseline = [y_mean]*len(y_train)
print("Mean apt price:", y_mean)
mae_baseline = mean_absolute_error(y_train, y_pred_baseline)
print("Baseline MAE:", mae_baseline)
# Mean apt price: 132383.83701458524
# Baseline MAE: 44860.10834274133

model = make_pipeline(
    OneHotEncoder(use_cat_names = True),
    SimpleImputer(),
    Ridge()
)
model.fit(X_train, y_train)

y_pred_training = model.predict(X_train)
​
mae_training = mean_absolute_error(y_train, y_pred_training)
print("Training MAE:", mae_training)
# Training MAE: 24207.107190330295

X_test = pd.read_csv("data/buenos-aires-test-features.csv")
y_pred_test = pd.Series(model.predict(X_test))
```

### Result communication

**Method 1**: Create a function make_prediction that takes four arguments (area, lat, lon, and neighborhood) and returns your model's prediction for an apartment price.

```py
def make_prediction(area, lat, lon, neighborhood):
    data ={
        "surface_covered_in_m2": area,
        "lat": lat,
        "lon": lon,
        "neighborhood": neighborhood
    }
    df = pd.DataFrame(data, index = [0])
    prediction = model.predict(df).round(2)[0]
    return f"Predicted apartment price: ${prediction}"

make_prediction(110, -34.60, -58.46, "Villa Crespo")
'Predicted apartment price: $250775.11'
```

**Method 2**: Add your make_prediction to the interact widget below, run the cell, and then adjust the widget to see how predicted apartment price changes.

```py
# Create an interact function in Jupyter Widgets.

interact(
    make_prediction,
    area=IntSlider(
        min=X_train["surface_covered_in_m2"].min(),
        max=X_train["surface_covered_in_m2"].max(),
        value=X_train["surface_covered_in_m2"].mean(),
    ),
    lat=FloatSlider(
        min=X_train["lat"].min(),
        max=X_train["lat"].max(),
        step=0.01,
        value=X_train["lat"].mean(),
    ),
    lon=FloatSlider(
        min=X_train["lon"].min(),
        max=X_train["lon"].max(),
        step=0.01,
        value=X_train["lon"].mean(),
    ),
    neighborhood=Dropdown(options=sorted(X_train["neighborhood"].unique())),
)
```
