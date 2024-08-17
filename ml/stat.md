
# Statistics

## Type of Data

### Categorical Data

Categorical data is any type of data that can only be represented by distinct values. Eye color, handedness, and academic attainment are all categorical variables. The other kind of variable is called a continuous variable. Continuous variables can have an infinite number of values, whereas categorical variables have concrete values. For this reason, categorical values require special attention in statistical analysis.

### Location Data

Location data is information about a datapoint’s location in space, and can be expressed in latitude/longitude pairs, street address, altitude, or any other place-specific identifiers.

### Numerical Data

Numerical data is any information that can be represented by numbers.

## Descriptive Statistics

### Quartiles

Quartiles divide a sequence of numbers into four equal parts. Grouping a dataset into quartiles helps us find outliers and provides the basis for the data in a boxplot.
`price.quantile(0.5)`

### Quantiles

A commonly used set of quantiles are the fourth quantiles known as quartiles. You can also find the minimum, first quartile, median, third quartile and maximum values in a series (which are typically the values used to create a boxplot). The median is the middle entry in the ordered list of prices
`price.quantile([0, 0.25, 0.5, 0.75, 1])`

### Series

 series is a one-dimensional array that can hold any type of data. We'll generally use the term to refer to a column in a dataset that's arranged in a table. In fact, this is the reason why, in the library pandas, DataFrame columns are called Series. In a pandas Series, all items in the array must be the same data type.

### Mean

All the data points in a dataset can be added together and then divided by the total number of data points to find the mean. You might be used to calling this number an average, but the two ideas are the same. Means help us understand the central tendency of a dataset.

### Skewed Distributions

For any given activity, there is a range of probable outcomes. All other things being equal, we would expect most of the outcomes to fall in the middle of the possible range, with the number of outcomes diminishing on either side of the peak. In statistics, this is known as a normal distribution, but you may have heard it called a bell curve, because it looks like a bell.
A skewed distribution is a type of distribution where the peak of the curve is shifted, or skewed, either to the right or the left of the distribution.

### Variance

Variance (which is sometimes called volatility in finance), is a measurement of how spread out the points in a dataset are around the mean. It's calculated by first summing up the squared different between each data point and mean, then dividing by the number of data points minus 1.
`df["area_m2"].var()`

### Standard deviation

describes the proportion of records above or below the mean of a given distribution. In a normal distribution, 68% of the values fall within one standard deviation of the mean, 95% of the values fall within two standard deviations from the mean, and 99.7% of the values fall within three standard deviations from the mean.

### Outliers

An outlier is a value in a dataset that falls well beyond the dataset mean — more than three standard deviations. Depending on the analytical strategy, it might be useful to drop outliers from a dataset, because their extreme deviation from the mean can result in misleading conclusions.

## Summary Statistics

`mexico_city1.describe()` # get a summary of information. The describe function will ignore missing values in each column. You can also remove rows and columns with missing values, and then get a summary of the data that's still there.

### Correlation

Correlations tell us about the relationship between two sets of data. When we calculate this relationship, the result is a correlation coefficient. Correlation coefficients can have any value between -1 and 1. Values above 0 indicate a positive relationship (as one variable goes up, the other does too), and values below 0 indicate a negative relationship (as one variable goes up, the other goes down). The closer the coefficient's value is to either 1 or -1, the stronger the relationship is; the closer the coefficient's value is to 0, the weaker the relationship is. Coefficients equal to 0 indicate that there is no relationship between the two values, and are accordingly quite rare.

```py
area_m2 = df2["area_m2"]
price_cop = df2["price_cop"]
correlation = area_m2.corr(price_cop) # order doesn't matter, so same as price_cop.corr(area_m2)
print(correlation)


data["open"].plot() 
```

## Normal Distribution

Normal distribution is the most widely used continuous distribution. It's a bell-shaped distribution that has the following unique characteristics:

1. Normal distributions are defined by only two parameters, the mean ($\mu$) and the standard deviation ($\sigma$).
2. The mean, median and mode are all equal.
3. The distribution is symmetric at the mean.
4. 68% of the area of a normal distribution is within one standard deviation of the mean, 95% of the area is within two standard deviation of the mean, and 99.7% is within three standard deviations of the mean.

```py
from scipy.stats import norm

fig, ax = plt.subplots()
# Define a normal distribution with mean 0 and standard deviation 1
x = np.arange(-4, 4, 0.001)
ax.plot(x, norm.pdf(x, loc=0, scale=1))
ax.set_ylim(0, 0.45)

ax.set_xlabel("x")
ax.set_ylabel("pdf(x)")
ax.grid(True)

# fill one standard deviation of mean with red
px = np.arange(-1, 1, 0.01)
ax.fill_between(px, norm.pdf(px, loc=0, scale=1), alpha=0.5, color="r")

# fill two standard deviation of mean with blue
px = np.arange(-2, -1, 0.01)
ax.fill_between(px, norm.pdf(px, loc=0, scale=1), alpha=0.5, color="b")

px = np.arange(1, 2, 0.01)
ax.fill_between(px, norm.pdf(px, loc=0, scale=1), alpha=0.5, color="b")

# fill two standard deviation of mean with green
px = np.arange(-4, -2, 0.01)
ax.fill_between(px, norm.pdf(px, loc=0, scale=1), alpha=0.5, color="g")

px = np.arange(2, 4, 0.01)
ax.fill_between(px, norm.pdf(px, loc=0, scale=1), alpha=0.5, color="g")

# 68% of the area of a normal distribution is within one standard deviation of the mean
ax.text(-0.5, 0.2, "68%", fontsize=20)
# 95% of the area is within two standard deviation of the mean
ax.text(-2.5, 0.01, "5%", fontsize=10)

plt.show()
```

![Normal Distribution Plot](python/images/norm.png)

## Probability Densities

If you were an engineer designing the interior of an airplane, you'd need to balance precision and uncertainty. On the one hand, you'd need to provide exact specifications and measurements for the airplane seats, but those seats need to accommodate passengers whose height and weight you don't know. After all, there is a lot of variation from one passenger to the next! So how can you mathematically represent the measurements for height and weight in such a way that you can incorporate them into the engineering formulas needed to create your design specifications? The answer is a **probability density function (PDF)**.

By definition, a probability density function shows the chance of observing an instance of random variable $X$ that equals a particular value $x$.

$$ f(x) = P(X = x)$$

Going back to our airplane seat example, $X$ could represent the height of an adult male passenger. It turns out that, if you measure thousands of American men, you'll end up with a mean height of 177cm and a standard deviation of 7cm. With that information, you can create a PDF that looks like a normal distribution.

Using the SciPy library, we can use a probability density function to plot the distribution of heights for American men.

```py
import numpy as np
from scipy.stats import norm

# define plot range for x axis
x = np.linspace(149, 205, 1000)

# plot PDF for a normal distribution with mean equals to 0 and standard deviation equals 1.
y = norm.pdf(x, loc=177, scale=7)

plt.plot(x, y)
plt.title("Distribution of Heights for American Men")
plt.xlabel("Height [cm]")
plt.ylabel("Frequency [%]");
```

## Cumulative Density Functions

The Cumulative Density Function **CDF** is the function that evaluates the probability of the random variable $X$ takes on a value less than or equal to $x$ for a distribution. In formula, we have:

$$ F_X(x) = P(X \leq x)$$

We can calculate the **CDF** of a normal distribution using `SciPy`. First we define a normal distribution from `Scipy` stats library. By default, the normal distribution has mean equals to 0 and standard deviation equals to 1.

```py
from scipy.stats import norm
​
# get mean and standard deviation
mean = norm.mean()
std = norm.std()
​
print(f"The mean of this Normal Distribution is: {mean}")
print(f"The standard deviation of this Normal Distribution is: {std}")
```

>The mean of this Normal Distribution is: 0.0
The standard deviation of this Normal Distribution is: 1.0

By definition, the area under the PDF is 1 by definition, and since the normal distribution is symmetric around the mean, the CDF at 0 should be 0.5.

```py
# Get `cdf` at 0
cdf_value = norm.cdf(0)
​
print(f"CDF at 0 is: {cdf_value}") # CDF at 0 is: 0.5

# We can also pass a list of values to check CDF:
cdf_value = norm.cdf([-std, std])
cdf_value # array([0.15865525, 0.84134475])
```

Note the difference between `norm.cdf(1)` and `norm.cdf(-1)` is the probability of $x$ being within one standard deviation of the mean, either left or right. According to normal distribution property, the probability should be around 68%:

```py
norm.cdf(1) - norm.cdf([-1])
# array([0.68268949])
```

## Central Limit Theorem

The Central Limit Theorem (CTL) states that no matter what the population’s original distribution is, when taking random samples from the population, the distribution of the means or sums from the random samples approaches a normal distribution, where the mean equals the population mean, as the random sample size gets larger.

**CTL for Random Samples**
We can simulate the Central Limit Theorem by taking sub samples from a random sampled population, then taking the means of each sub sample and plot the means to see whether they follow a normal distribution. Here is the code for the simulation:

```py
import matplotlib.pyplot as plt
import numpy as np
​
# generate a sample from a random sample whose size is 10000
lis = np.random.random(size=10000)

means = []
# take 1000 random sub sample, whose size is also 1000
for i in range(1000):
    # take a random sub sample by the index numbers of the previous random sample
    lis_index = np.random.randint(0, 10000, 1000)
​
    # collect the means from each sub sample
    means.append(lis[lis_index].mean())
​
    # continue taking sub samples and collect means
    i += 1
​
# plot the distribution of means
plt.hist(means)

sums = []
# take 1000 random sub sample, whose size is also 1000
for i in range(1000):
    # take a random sub sample
    lis_index = np.random.randint(0, 10000, 1000)

    # collect the sums from each sub sample
    sums.append(lis[lis_index].sum())
    i += 1

plt.hist(sums)
```

## Hypothesis Testing

**Hypothesis Testing** is a method of statistical inference. First, we define a **null hypothesis** ($H_0$), which usually proposes that no statistical relationship or significance exists. Next, we have an **alternative hypothesis** ($H_a$ or $H_a$), which proposes that there is a statistical relationship. For example, if we want to test whether there is a significant difference in salaries between employees with and without advanced degrees:

- The **null hypothesis** is there **is no significant difference** in salaries between employees with and without advanced degrees

- The **alternative hypothesis** is there **is a significant difference** in salaries between employees with and without advanced degrees.
​
Hypothesis testing is a two-step process that tests whether the null hypothesis is true based on data collected from a survey or an experiment. First, we calculate the probability of observing some effect in the data, assuming the null hypothesis is true. Second, we compare the probability from the previous calculation with the p-value we've chosen (usually 0.05). If the probability is smaller than the p-value, we reject the null hypothesis because the effect we're observing is probably true. If the probability is larger than the p-value, we fail to reject the null hypothesis because the effect we're observing is probably false.
​
Either way, we can never be 100% certain our observed results are real, because we're dealing with probability. Even if we're almost certainly correct, the closest we can get is *almost*, because there's always a possibility — no matter how small — that our results are wrong. Maybe we found something that wasn't actually there, or we didn't find something that actually was. In statistics, we call those two mistakes **type errors**. They work like this:
​
- In a **Type I error**, the null hypothesis is actually true, but we reject it, which is called **False Positive**, we also call it $\alpha$;
- In a **Type II error**, the null hypothesis is actually False, but we fail to reject it, which is called **False Negative**, we also call it $\beta$;

|                          | $H_0$ is rejected        | $H_0$ is not rejected    |
|--------------------------|--------------------------|--------------------------|
| **$H_0$ is False**        | $1 - \beta$              | False Negative $\beta$   |
| **$H_0$ is True**         | False Positive $\alpha$  | $1 - \alpha$|

**For example**, False Positive is when salaries between employees with and without advanced degrees are not significantly different ($H_0$ True), however, we conclude that they are significantly different (rejecting $H_0$). While False Negative is when salaries between employees with and without advanced degrees are significantly different ($H_0$ False), but we find that they are not significantly different (not rejecting $H_0$).

### Power

In the table above when we rejected $H_0$ when $H_0$ is False, the probability is 1-$\beta$, which is also called the **statistical power** of the test. It represents the correct rejection of the null hypothesis. You want the value of the statistical power to be as large as possible for a test.

### Effect Size

**Effect size** measures the strength of a relationship between two variables or same variable from different samples. For example, we compare an experiment result from treatment group and control group, and we measure the different between the two groups to see the effect size of the experiment. One common measurement for effect size in this case is called **Cohen's d**, which measures the difference between two means from treatment and control group, divided by the standard deviation of the data:
 $$ d = \frac{\bar{x}_1 - \bar{x}_2}{s} $$

## Chi Square

Among all hypothesis testing via statistical models, the **Chi-square test of independence** is widely used to test whether there is a significant relationship between two nominal variables. The Null Hypothesis $H_0$ and the Alternative Hypothesis $H_a$ for testing the independence between variable X and variable Y are framed as follows:

- Null Hypothesis ($H_0$): There is no relationship between X and Y, i.e. X and Y are independent to each other;

- Alternative Hypothesis ($H_a$): There is a relationship to X and Y.

```py
import pandas as pd

df = pd.read_csv("data/colombia-real-estate-chi-square.csv")

df["advertising"].value_counts()
>radio       1533
internet    1533
Name: advertising, dtype: int64

df["sold_in_2_wks"].value_counts()
>sold      1809
unsold    1257
Name: sold_in_2_wks, dtype: int64
```

We then use the Chi-square test of independence and state the Null Hypothesis and Alternative Hypothesis:

- Null Hypothesis ($H_0$):  `"advertising"` and `"sold_in_2_wks"` are independent of each other.
- Alternative Hypothesis ($H_a$): `"advertising"` and `"sold_in_2_wks"` dependent on each other.

### Contingency Tables

In the Chi-Square test, we display the data in a cross-tabulation (contingency) format showing frequency count of each group of the two categorical variable rows and columns, which is call the contingency table. We can get the contingency table for "advertising" and "sold_in_2_wks" directly using Pandas crosstab.

```py
tab = pd.crosstab(df["advertising"], df["sold_in_2_wks"])
tab
```

| sold/advertising | sold | unsold |
|------------------|------|--------|
| internet         | 1104 | 429    |
| radio            | 705  | 828    |

Alternatively, we can also use statsmodels to construct contingency table and conduct more analysis.

```py
from statsmodels.stats.contingency_tables import Table2x2
​
contingency_table = Table2x2(tab.values)

contingency_table.table_orig
'''
array([[1104,  429],
       [ 705,  828]])'''
```

The fitted values are the estimated frequency counts for each cell under the assumption that `"advertising"` and `"sold_in_2_wks"` are independent to each other. Suppose the probability of `"internet"` and `"radio"` are $p$ and $1-p$, and the probability of `"sold"` and `"unsold"` is $q$ and $1-q$, the probability for each cell should be as follows:
​
|       | $p$           | $1 - p$        |
|-------|---------------|----------------|
| $q$   | $p \cdot q$   | $(1 - p) \cdot q$ |
| $1 - q$ | $p \cdot (1 - q)$ | $(1 - p) \cdot (1 - q)$ |

We can check the joint distribution of the contingency table through `independence_probabilities`:

```py
contingency_table.independence_probabilities.round(2)
'''
array([[0.3, 0.2],
       [0.3, 0.2]])'''
```

Then we apply the total sample size N to each cell's probability to calculate the fitted value. That's where the fittedvalues comes from.

```py
# Get fitted value
​
contingency_table.fittedvalues
'''
array([[904.5, 628.5],
       [904.5, 628.5]])'''
```

Another useful information we can get from the probability of the contingency table is called the **odds ratio**. **odds** for an event with probability $p$ is:
​
$$\frac{p}{1-p}$$.
​
The **odds ratio** is a ratio of **odds** between two groups, one with probability $p$ and one with probability $q$, the formula is:
​
$$\frac{p/(1-p)}{q/(1-q)}$$
​
From the table of probability above, we can calculate odds ratio for the contingency table.

```py
# Get odds ratio
contingency_table.oddsratio
# 3.0224073798541884
```

### Test for Independence

Before moving to Chi square test statistic, we need to check whether we have enough observations to drive meaningful conclusions. For an effect size at `0.2`, significance level at 95% ($\alpha$ is `0.05`), and power at `0.8`, we can use the `GofChisquarePower` function to conduct power analysis. First we check whether we have enough observations, then we can manipulate different effect sizes to see how sample sizes, power and effect sizes are correlated with each other.

```py
import math
​
from statsmodels.stats.power import GofChisquarePower
​
chi_square_power = GofChisquarePower()
​
group_size = math.ceil(
    chi_square_power.solve_power(effect_size=0.2, alpha=0.05, power=0.8)
)
​
print("Group size:", group_size)
print("Total # observations for two groups:", group_size * 2)
print("Total # observations in the data:", df.shape[0])
```

>Group size: 197
Total # observations for two groups: 394
Total # observations in the data: 3066

In the following graph, let's see how effect size is correlated with sample size. If we assume power is at 0.8, to detect a 0.2 effect size, we need around 250 samples. While for an effect size at 0.5, we only need 50 observations, and the number reduced further for an even bigger effect size at 0.8. This means it is much harder to detect a smaller effect size.

```py
import numpy as np
​
n_observations = np.arange(0, group_size * 2)
effect_sizes = np.array([0.2, 0.5, 0.8])
​
# Plot power curve using `chi_square_power`
​
chi_square_power.plot_power(
    dep_var="nobs", nobs=n_observations, effect_size=effect_sizes, alpha=0.05, n_bins=2
)
```

![Plot for Power of test](python/images/indep.png)

Lastly, we can conduct the test and calculate the p values using test_nominal_association():

```py
chi_square_test = contingency_table.test_nominal_association()
​
print("chi_square_test type:", type(chi_square_test))
print(chi_square_test)
```

> chi_square_test type: <class 'statsmodels.stats.contingency_tables._Bunch'>
df        1
pvalue      0.0
statistic   214.65652643702725

We can see the *p-value* is around 0, which is much smaller than 0.05, the $\alpha$ value we set ahead. We can then reject the Null Hypothesis, which states `"advertising"` and `"sold_in_2_wks"` are independent to each other. This is the same as saying `"advertising"` and `"sold_in_2_wks"` are somewhat dependent with each other.
