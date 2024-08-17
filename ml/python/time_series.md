# Time Series

## Model Types

### Autoregression Models

Autoregression (AR) is a time series model that uses observations from previous time steps as input to a regression equation to predict the value at the next time step. AR works in a similar way to **autocorrelation**: in both cases, we're taking data from one part of a set and comparing it to another part. An AR model regresses itself.

### ARMA Models

**ARMA** stands for Auto Regressive Moving Average, and it's a special kind of **time-series** analysis. So far, we've used autoregression (AR) to build our time-series models, and you might recall that AR models rely on values that remain relatively stable over time. That is, they can predict the future very well, as long as the future looks roughly the same as the past. The trouble with predicting the future is that things can suddenly change, and as a result, the future doesn't look much like the past anymore. These sudden changes — economists call them *endogenous shocks* — can be as big as a hurricane destroying a city or an unexpected increase in the minimum wage, and they can be as small as a new restaurant opening in a neighborhood or a single person losing their job. In our data, the air quality might be changed if there was a nearby forest fire, or if a building collapsed near one of the sensors and raised a giant cloud of dust.

## Plots

### ACF Plot

When we've worked with autocorrelations in the past, we've treated them like static relationships, but that's not always how they work. Sometimes, we want to actually see how those autocorrelations change over time, which means we need to think of them as *functions*. When we create a visual representation of an autocorrelation function (ACF), we're making an **ACF plot**.

### PACF Plot

Autocorrelations take into account two types of observations. **Direct observations** are the ones that happen exactly at our chosen time-step interval; we might have readings at one-hour intervals starting at 1:00. **Indirect observations** are the ones that happen between our chosen time-step intervals, at time-steps like 1:38, 2:10, 3:04, etc. Those indirect observations *might* be helpful, but we can't be sure about that, so it's a good idea to strip them out and see what our graph looks like when it's only showing us direct observations.
​
An autocorrelation that only includes the direct observations is called a **partial autocorrelation**, and when we view that partial autocorrelation as a function, we call it a **PACF**.
​
**PACF plots** represent those things visually. We want to compare our ACF and PACF plots to see which model best describes our time series. If the ACF data drops off slowly, then that's going to be a better description; if the PACF falls off slowly, then that's going to be a better description.

## Statistical Concepts

### Walk-Forward Validation

Our predictions lose power over time because the model gets farther and farther away from its beginning. But what if we could move that beginning forward with the model? That's what **walk-forward validation** is. In a walk-forward validation, we re-train the model at for each new observation in the dataset, dropping the data that's the farthest in the past. Let's say that our prediction for what's going to happen at 12:00 is based on what happened at 11:00, 10:00, and 9:00. When we move forward an hour to predict what's going to happen at 1:00, we only use data from 10:00, 11:00, and 12:00, dropping the data from 9:00 because it's now too far in the past.

### Parameters

Parameters are the parts of the model that are **learned** from the training data.

### Hyperparameters

We've already seen that **parameters** are elements that a machine learning model learns from the training data. **Hyperparameters**, on the other hand, are elements of the model that come from somewhere else. Data scientists choose hyperparameters either by examining the data themselves, or by creating some kind of automated testing of different options to see how they perform. Hyperparameters are set before the model is trained, which means that they significantly impact how the model is trained, and how it subsequently performs. One way of thinking about the difference between the two is that parameters come from *inside* the model, and hyperparameters come from *outside* the model.
​
When we think about hyperparameters, we think in terms of `p` values and `q` values. `p` values represent the number of lagged observations included in the model, and the `q` is the size of the moving average window. These values count as hyperparameters because we get to decide what they are. How many lagged observations do we want to include? How big should our window of moving averages be?

### Rolling Averages

A **rolling average** is the mean value of multiple subsets of numbers in a dataset. For example, I might have data relating to the daily income for a shop I own, and as long as the shop stays open, I can calculate a rolling average. On Friday, I might calculate the average income from Monday-Thursday. The next Monday, I might calculate the average income from Tuesday-Friday, and the next day, I might calculate the average income from Wednesday to Monday, and so on. These averages *roll*, giving me a sense for how the data is changing in relation to any kind of static construct. In this case, and in many data science applications, that construct is time. Calculating rolling averages is helpful for making accurate forecasts about the ways data will change in the future.

## Statistical Models

### Autoregression

Autoregression (AR) is a time series model that uses observations from previous time steps as input to a regression equation to predict the value at the next time step. AR works similarly to autocorrelation: in both cases, we're taking data from one part of a set and comparing it to another part. An AR model regresses itself.

**Cleaning the Data**
Just like with linear regression, we'll start by bringing in some tools to help us along the way.

```py
import warnings
​
import matplotlib.pyplot as plt
import pandas as pd
import plotly.express as px
from arch import arch_model
from IPython.display import YouTubeVideo
from pymongo import MongoClient
from sklearn.metrics import mean_absolute_error
from statsmodels.graphics.tsaplots import plot_acf, plot_pacf
from statsmodels.tsa.ar_model import AutoReg
warnings.simplefilter(action="ignore", category=FutureWarning)

# Since we'll be working with the "air-quality" data again, we need to connect to the server, start our client, and grab the data we need.

client = MongoClient(host="localhost", port=27017)
db = client["air-quality"]
lagos = db["lagos"]
```

In order to get our data into a form we can use to build our model, we're going to need to transform it in several key ways. The first thing we need to do is to get the data we need, and save the results in a DataFrame. Since we're interested in predicting the changes in air quality over time, let's set the DataFrame's index to "timestamp":

```py
results = lagos.find(
    # Note that the `3` refers to Site 3.
    {"metadata.site": 3, "metadata.measurement": "P2"},
    projection={"P2": 1, "timestamp": 1, "_id": 0},
)
df = pd.DataFrame(list(results)).set_index("timestamp")
```

**Localizing the Timezone**
Because MongoDB stores all timestamps in UTC, we need to figure out a way to localize it. Having timestamps in UTC might be useful if we were trying to predict some kind of global trend, but since we're only interested in what's happening with the air in Lagos, we need to change the data from UTC to Africa/Lagos. Happily, pandas has a pair of tools to help us out: tz_localize and tz_convert. We use those methods to transform our data like this:

```py
df.index = df.index.tz_localize("UTC").tz_convert("Africa/Lagos")
```

**Resampling Data**
The most important kind of data in our time-series model is the data that deals with time. Our "timestamp" data tells us when each reading was taken, but in order to create a good predictive model, we need the readings to happen at regular intervals. Our data doesn't do that, so we need to figure out a way to change it so that it does. The resample method does that for us.

Let's resample our data to create 1-hour reading intervals by aggregating using the mean:

```python
# `"1H"` represents our one-hour window
df = df["P2"].resample("1H").mean().fillna(method="ffill").to_frame()
```

Notice the second half of the code:

```python
fillna(method="ffill").to_frame()
```

That tells the model to **forward-fill** any empty cells with **imputed** data. Forward-filling means that the model should start imputing data based on the closest cell that actually has data in it. This helps to keep the imputed data in line with the rest of the dataset.
​
**Adding a Lag**
We've spent some time elsewhere thinking about how two sets of data — apartment price and location, for example — compare to *each other*, but we haven't had any reason to consider how a dataset might compare to *itself*. If we're predicting the future, we want to know how good our prediction will be, so it might be useful to build some of that accountability into our model. To do that, we need to add a **lag**.
​
Lagging data means that we're adding a delay. In this case, we're going to allow the model to test itself out by comparing its predictions with what actually happened an hour before. If the prediction and the reality are close, then it's a good model; if they aren't, then the model isn't a very good one.

```py
# So, let's add a one-hour lag to our dataset:

# In `shift(1), the `1` is the lagged interval.
df["P2.L1"] = df["P2"].shift(1)

# Finally, let's drop our null values:
df.dropna(inplace=True)
y = df["P2"].resample("1H").mean().fillna(method="ffill")
```
