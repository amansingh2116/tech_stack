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
    
    return df

df = wrangle("data/buenos-aires-real-estate-1.csv")
print("df shape:", df.shape)
df.head()

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

**Warning:** During the iteration phase, you can change and retrain your model as many times as you want. You can also check the model's training performance repeatedly. But once you evaluate its test performance, you can't make any more changes.

A test only counts if neither the model nor the data scientist has seen the data before. If you check your test metrics and then make changes to the model, you can introduce biases into the model that compromise its generalizability.

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
