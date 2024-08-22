# Air Quality in Nairobi

## Wrangling Data with MongoDB

### Importing Libraries

```py
from pprint import PrettyPrinter

import pandas as pd
from IPython.display import VimeoVideo
from pymongo import MongoClient
```

### Connect to database

```py
pp = PrettyPrinter(indent=2) # Instantiate a PrettyPrinter, and assign it to the variable pp.
client = MongoClient(host="localhost", port=27017) #  Create a client that connects to the database running at localhost on port 27017.
```

### EDA

```py
pp.pprint(list(client.list_databases())) # Print a list of the databases available on client.
db = client["air-quality"] # Assign the "air-quality" database to the variable db.
# print a list of the collections available in db
for i in db.list_collections():
    print(i["name"])
nairobi = db["nairobi"] # Assign the "nairobi" collection in db to the variable name nairobi.
nairobi.count_documents({}) # how many documents are in the nairobi collection.
result = nairobi.find_one({})
pp.pprint(result) # retrieve one document from the nairobi collection
nairobi.distinct("metadata.site") # how many sensor sites are included in the nairobi collection.
nairobi.distinct("metadata.measurement") # how many types of measurements have been taken in the nairobi collection.
print("Documents from site 6:", nairobi.count_documents({"metadata.site": 6}))
# determine how many readings there are for each site in the nairobi collection.
result = nairobi.aggregate(
    [
        {"$group": {"_id": "$metadata.site", "count": {"$count": {}}}}     
    ]
)
pp.pprint(list(result))
# calculate how many readings there are for each type ("humidity", "temperature", "P2", and "P1") in site 6
result = nairobi.aggregate(
    [
        {"$match": {"metadata.site": 6}},
        {"$group": {"_id": "$metadata.measurement", "count": {"$count": {}}}}     
    ]
)
pp.pprint(list(result))
# retrieve the PM 2.5 readings from site 29.
# Since we won't need the metadata for our model, use the projection argument to limit the results to the "P2" and "timestamp" keys only.
result = nairobi.find(
    {"metadata.site": 29, "metadata.measurement": "P2"},
    projection = {"P2": 1, "timestamp": 1, "_id": 0}
)
pp.pprint(result.next())

# Read records from your result into the DataFrame df. Be sure to set the index to "timestamp".
df = pd.DataFrame(result).set_index("timestamp")
```

## Linear Regression with Time Series

### Import

```py
import matplotlib.pyplot as plt
import pandas as pd
import plotly.express as px
import pytz
from IPython.display import VimeoVideo
from pymongo import MongoClient
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_absolute_error
```

### Prepare Data

```py
def wrangle(collection):
    results = collection.find(
        {"metadata.site": 29, "metadata.measurement": "P2"},
        projection={"P2": 1, "timestamp": 1, "_id": 0},
    )
    
    # Add to your wrangle function so that the DatetimeIndex for df is localized to the correct timezone, "Africa/Nairobi".
    # Localize Timezone
    df = pd.DataFrame(results).set_index("timestamp")
    df.index = df.index.tz_localize("UTC").tz_convert("Africa/Nairobi")
    
    # Remove outlier since boxplot shows values too extreme which are not practical in this scenario
    df = df[df["P2"] < 500]
    
    # Resample to 1hr and forward fill missing values
    df = df["P2"].resample("1H").mean().fillna(method="ffill").to_frame()
    
    # Adding Lag; `shift(1), the `1` is the lagged interval.
    df["P2.L1"] = df["P2"].shift(1)

    # Finally, let's drop our null values:
    df.dropna(inplace=True)
    
    return df

df = wrangle(nairobi)

# Create a boxplot of the "P2" readings in df.
fig, ax = plt.subplots(figsize=(15, 6))
df["P2"].plot(kind="box", vert = False, title = "Distribution of PM2.5 Readings", ax = ax)
# Conclusion, we have to remove outliers. Add to your wrangle function so that all "P2" readings above 500 are dropped from the dataset. 

# Create a time series plot of the "P2" readings in df.
fig, ax = plt.subplots(figsize=(15, 6))
df["P2"].plot(xlabel = "Time", ylabel = "PM2.5", title = "PM2.5 Time Series",ax=ax)
# Conclusion, Add to your wrangle function to resample df to provide the mean "P2" reading for each hour. Use a forward fill to impute any missing values. To make the readings at regular intervals and to fill missing values using mean using forward fill.

# Plot the rolling average of the "P2" readings in df. Use a window size of 168 (the number of hours in a week).
fig, ax = plt.subplots(figsize=(15, 6))
df["P2"].rolling(168).mean().plot(ax=ax, ylabel = "PM2.5", title = "Weekly Rolling Average")
# Conclusion, Add to your wrangle function to create a column called "P2.L1" that contains the mean"P2" reading from the previous hour. Since this new feature will create NaN values in your DataFrame, be sure to also drop null rows from df.

df.corr() # Create a correlation matrix for df
# Create a scatter plot that shows PM 2.5 mean reading for each our as a function of the mean reading from the previous hour. 
fig, ax = plt.subplots(figsize=(6, 6))
ax.scatter(x=df["P2.L1"], y=df["P2"])
ax.plot([0,120], [0,120],linestyle="--",color = "red")
plt.xlabel("P2.L1")
plt.xlabel("P2")
plt.title("PM2.5 Autocorrelation")
# Conclusion, there is a good correlation between PM 2.5 at T and at T-1
```

### Model

```py
target = "P2"
y = df[target]
X = df.drop(columns=target)

# since we are  dealing with time series data we cannot just randomly split the data we define a cutoff after which is the testing data and before which is the testing data

cutoff = int(len(X) * 0.8) 

X_train, y_train = X.iloc[:cutoff], y.iloc[:cutoff]
X_test, y_test = X.iloc[cutoff:], y.iloc[cutoff:]

y_pred_baseline = [y_train.mean() for i in range(len(y_train))]
mae_baseline = mean_absolute_error(y_train, y_pred_baseline)
print("Mean P2 Reading:", round(y_train.mean(), 2))
print("Baseline MAE:", round(mae_baseline, 2))
# Mean P2 Reading: 9.27
# Baseline MAE: 3.89

model = LinearRegression()
model.fit(X_train, y_train)
```

### Evaluate and Communicate

```py
training_mae = mean_absolute_error(y_train, model.predict(X_train))
test_mae = mean_absolute_error(y_test, model.predict(X_test))
print("Training MAE:", round(training_mae, 2))
print("Test MAE:", round(test_mae, 2))
# Training MAE: 2.46
# Test MAE: 1.8

intercept = model.intercept_.round(2)
coefficient = model.coef_[0].round(2)
​
print(f"P2 = {intercept} + ({coefficient} * P2.L1)")
# P2 = 3.36 + (0.64 * P2.L1)

# Create a DataFrame df_pred_test that has two columns: "y_test" and "y_pred".
df_pred_test = pd.DataFrame(
    {
        "y_test": y_test,
        "y_pred": model.predict(X_test)
    }
)

# Create a time series line plot for the values in test_predictions using plotly express.
fig = px.line(df_pred_test, labels={"value": "P2"})
fig.show()
```

## Auto Regressive Models

### Import Library

```py
import warnings

import matplotlib.pyplot as plt
import pandas as pd
import plotly.express as px
from IPython.display import VimeoVideo
from pymongo import MongoClient
from sklearn.metrics import mean_absolute_error
from statsmodels.graphics.tsaplots import plot_acf, plot_pacf
from statsmodels.tsa.ar_model import AutoReg

warnings.simplefilter(action="ignore", category=FutureWarning)
```

### Prepare and Visualise data

``` py
def wrangle(collection):
    results = collection.find(
        {"metadata.site": 29, "metadata.measurement": "P2"},
        projection={"P2": 1, "timestamp": 1, "_id": 0},
    )

    # Read data into DataFrame
    df = pd.DataFrame(list(results)).set_index("timestamp")

    # Localize timezone
    df.index = df.index.tz_localize("UTC").tz_convert("Africa/Nairobi")

    # Remove outliers
    df = df[df["P2"] < 500]

    # Resample to 1hr window
    y = df["P2"].resample("1H").mean().fillna(method='ffill') # removed .to_frame() since it is series now only single column with timestamp as index

    return y

y = wrangle(nairobi)

# Create an ACF plot for the data in y
fig, ax = plt.subplots(figsize=(15, 6))
plot_acf(y, ax=ax)
plt.xlabel("Lag [hours]")
plt.ylabel("Correlation Coefficient")
# Conclusion, lag 1, 12 and 24 shows some level of correlation, but since every lag is good correlated with lag-1 we have to perform pacf plot

# Create an PACF plot for the data in y
fig, ax = plt.subplots(figsize=(15, 6))
plot_pacf(y, ax=ax)
plt.xlabel("Lag [hours]")
plt.ylabel("Correlation Coefficient")
# Coclusion, any lag beyond 26 is insignificant in terms of correlation with y
```

### Auto Reg Model

```py
# split y into training and test sets. The first 95% of the data should be in your training set. The remaining 5% should be in the test set.
cutoff_test = int(len(y)*0.95)

y_train = y.iloc[:cutoff_test]
y_test = y.iloc[cutoff_test:]

# Baseline
y_train_mean = y_train.mean()
y_pred_baseline = [y_train_mean] * len(y_train)
mae_baseline = mean_absolute_error(y_train, y_pred_baseline)

print("Mean P2 Reading:", round(y_train_mean, 2))
print("Baseline MAE:", round(mae_baseline, 2))
# Mean P2 Reading: 9.22
# Baseline MAE: 3.71

model = AutoReg(y_train, lags=26).fit() # Instantiate an AutoReg model and fit it to the training data y_train. Be sure to set the lags argument to 26.


y_pred = model.predict().dropna() # since first (model.predict().isnull().sum()) 26 predictions are NaN due to lag of 26
training_mae = mean_absolute_error(y_train.iloc[26:],y_pred) # making them same size
print("Training MAE:", training_mae)
# Training MAE: 2.2809871656467036, Training mae is good

# Use y_train and y_pred to calculate the residuals for your model.
y_train_resid = model.resid # OR y_train-y_pred
y_train_resid.tail()

# Create a plot of y_train_resid.
fig, ax = plt.subplots(figsize=(15, 6))
y_train_resid.plot(ylabel="Residual Values", ax=ax)
# Residuals are close to zero

# Create a histogram of y_train_resid.
y_train_resid.hist(bins = 200)
plt.xlabel("Residual Value")
plt.ylabel("Frequency")
plt.title("AR(26), Distribution of Residuals")
# Residuals are most likely normal distributed

# Create an ACF plot of y_train_resid.
fig, ax = plt.subplots(figsize=(15, 6))
plot_acf(y_train_resid, ax=ax)
# There is merely any correlation for any lag other than 0 that is itself
```

### Evaluate

```py
# Calculate the test mean absolute error for your model.
y_pred_test = model.predict(y_test.index.min(), y_test.index.max())
test_mae = mean_absolute_error(y_test, y_pred_test)
print("Test MAE:", test_mae)
# Test MAE: 3.0136439495039054, test mae is very poor, lets see why

# Create a DataFrame test_predictions that has two columns: "y_test" and "y_pred".
df_pred_test = pd.DataFrame(
    {"y_test": y_test, "y_pred": y_pred_test}, index=y_test.index
)

# Create a time series plot for the values in test_predictions using plotly express. 
fig = px.line(df_pred_test, labels={"value": "P2"})
fig.show()
# Conclusion, prediction are pretty bad because after the point we split the data the model is predicting using data points that are not real but the predicted ones

# Perform walk-forward validation for your model for the entire test set y_test. Store your model's predictions in the Series y_pred_wfv.
​
y_pred_wfv = pd.Series()
history = y_train.copy()
for i in range(len(y_test)):
    model=AutoReg(history, lags = 26).fit()
    next_pred = model.forecast()
    y_pred_wfv = y_pred_wfv.append(next_pred)
    history = history.append(y_test[next_pred.index])

# Calculate the test mean absolute error for your model.
test_mae = mean_absolute_error(y_test, y_pred_wfv)
print("Test MAE (walk forward validation):", round(test_mae, 2))
# Test MAE (walk forward validation): 1.4
```

### Communicate Results

```py
print(model.params) # Print out the parameters for your trained model.

# Create a line plot in plotly express. Put the values for y_test and y_pred_wfv into the DataFrame df_pred_test (don't forget the index). Then plot df_pred_test using plotly express.

test1_predictions = pd.DataFrame(
    {"y_test": y_test, "y_pred": y_pred_wfv}, index=y_test.index
)
fig = px.line(test1_predictions)
fig.show()
```

## ARMA Models

### Importing libraries

```py
import inspect
import time
import warnings
​
import matplotlib.pyplot as plt
import pandas as pd
import plotly.express as px
import seaborn as sns
from IPython.display import VimeoVideo
from pymongo import MongoClient
from sklearn.metrics import mean_absolute_error
from statsmodels.graphics.tsaplots import plot_acf, plot_pacf
from statsmodels.tsa.arima.model import ARIMA
​
warnings.filterwarnings("ignore")
```

### Prepare data

```py
# Access a collection in a database using PyMongo.
client = MongoClient(host="localhost", port=27017)
db = client["air-quality"]
nairobi = db["nairobi"]

# Change your wrangle function so that it has a resample_rule argument that allows the user to change the resampling interval. The argument default should be "1H".

def wrangle(collection, resample_rule = "1H"):
​
    results = collection.find(
        {"metadata.site": 29, "metadata.measurement": "P2"},
        projection={"P2": 1, "timestamp": 1, "_id": 0},
    )
​
    # Read results into DataFrame
    df = pd.DataFrame(list(results)).set_index("timestamp")
​
    # Localize timezone
    df.index = df.index.tz_localize("UTC").tz_convert("Africa/Nairobi")
​
    # Remove outliers
    df = df[df["P2"] < 500]
​
    # Resample and forward-fill
    y = df["P2"].resample(resample_rule).mean().fillna(method='ffill')
​
    return y

y = wrangle(nairobi)
```

### Explore

```py
# Create an ACF plot for the data in y. Be sure to label the x-axis as "Lag [hours]" and the y-axis as "Correlation Coefficient".
fig, ax = plt.subplots(figsize=(15,6))
plot_acf(y, ax = ax)
plt.xlabel("Lag [hours]")
plt.ylabel("Correlation Coefficient")

# Create an PACF plot for the data in y. Be sure to label the x-axis as "Lag [hours]" and the y-axis as "Correlation Coefficient".
fig, ax = plt.subplots(figsize=(15, 6))
plot_pacf(y, ax=ax)
plt.xlabel("Lag [hours]")
plt.ylabel("Correlation Coefficient")
```

### Build Model

```py
# Create a training set y_train that contains only readings from October 2018, and a test set y_test that contains readings from November 1, 2018.
y_train = y.loc["2018-10-01":"2018-10-31"]
y_test = y.loc["2018-11-01"]

# Baseline
y_train_mean = y_train.mean()
y_pred_baseline = [y_train_mean] * len(y_train)
mae_baseline = mean_absolute_error(y_train, y_pred_baseline)
print("Mean P2 Reading:", round(y_train_mean, 2))
print("Baseline MAE:", round(mae_baseline, 2))
# Mean P2 Reading: 10.12
# Baseline MAE: 4.17


# Create ranges for possible  𝑝 and  𝑞 values.
p_params = range(0,25,8)
q_params = range(0,3,1)

# train a model with every combination of hyperparameters in p_params and q_params.

# Create dictionary to store MAEs
mae_grid = dict()
# Outer loop: Iterate through possible values for `p`
for p in p_params:
    # Create key-value pair in dict. Key is `p`, value is empty list.
    mae_grid[p] = list()
    # Inner loop: Iterate through possible values for `q`
    for q in q_params:
        # Combination of hyperparameters for model
        order = (p, 0, q) # ARIMA actually has 3 parameters
        # Note start time
        start_time = time.time()
        # Train model
        model = ARIMA(y_train, order=order).fit()
        # Calculate model training time
        elapsed_time = round(time.time() - start_time, 2)
        print(f"Trained ARIMA {order} in {elapsed_time} seconds.")
        # Generate in-sample (training) predictions
        y_pred = model.predict()
        # Calculate training MAE
        mae = mean_absolute_error(y_train, y_pred)
        # Append MAE to list in dictionary
        mae_grid[p].append(mae)

print()
print(mae_grid)

# Organize all the MAE's from above in a DataFrame names mae_df.
mae_df = pd.DataFrame(mae_grid)
mae_df.round(4)


# Create heatmap of the values in mae_grid. Be sure to label your x-axis "p values" and your y-axis "q values".

# Create a heatmap in seaborn.
sns.heatmap(mae_df, cmap="Blues")
plt.xlabel("p values")
plt.ylabel("q values")
plt.title("ARMA Grid Search (Criterion: MAE)")
# Conclusion, Not all p = 0 were good, but when p is not zero we almost got similar performance. As a data scientist our task is to minimize resources and maximize performance. The (24,2) and (8,1) are giving similar performances but the time and the resources they are using is significantly different. Trained ARIMA (8, 0, 1) in 39.3 seconds. Trained ARIMA (24, 0, 2) in 342.67 seconds

# Use the plot_diagnostics method to check the residuals for your model.
fig, ax = plt.subplots(figsize=(15, 12))
model.plot_diagnostics(fig=fig)
```

### Evaluate Model

```py
# perform walk-forward validation for your model for the entire test set y_test. 
# Store your model's predictions in the Series y_pred_wfv. Choose the values for  𝑝 and  𝑞 that best balance model performance and computation time.
y_pred_wfv = pd.Series()
history = y_train.copy()
for i in range(len(y_test)):
    model = ARIMA(history, order = (8,0,1)).fit()
    next_pred = model.forecast()
    y_pred_wfv = y_pred_wfv.append(next_pred)
    history = history.append(y_test[next_pred.index])
y_pred_wfv = pd.Series()
history = y_train.copy()
for i in range(len(y_test)):
    model = ARIMA(history, order = (8,0,1)).fit()
    next_pred = model.forecast()
    y_pred_wfv = y_pred_wfv.append(next_pred)
    history = history.append(y_test[next_pred.index])
test_mae = mean_absolute_error(y_test, y_pred_wfv)
print("Test MAE (walk forward validation):", round(test_mae, 2))
# Test MAE (walk forward validation): 1.67

# communicate results
# create a DataFrame df_predictions with the true values y_test and your predictions y_pred_wfv (don't forget the index). Finally, plot df_predictions using plotly express. 
df_predictions = pd.DataFrame(
    {"y_test": y_test, "y_pred_wfv": y_pred_wfv}
)
fig = px.line(df_predictions, labels={"value": "PM2.5"})
fig.show()
```
