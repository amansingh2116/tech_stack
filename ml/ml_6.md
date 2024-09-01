# 6.5. Small Business Owners in the United States🇺🇸

In this assignment, you're going to focus on business owners in the United States. You'll start by examining some demographic characteristics of the group, such as age, income category, and debt vs. home value. Then you'll select high-variance features, and create a clustering model to divide small business owners into subgroups. Finally, you'll create some visualizations to highlight the differences between these subgroups.

```python
# Import libraries here
import pandas as pd
import plotly.express as px
from IPython.display import VimeoVideo
from jupyter_dash import JupyterDash
from scipy.stats.mstats import trimmed_var
from sklearn.cluster import KMeans
from sklearn.decomposition import PCA
from sklearn.metrics import silhouette_score
from sklearn.pipeline import make_pipeline
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt
import seaborn as sns

JupyterDash.infer_jupyter_proxy_config()
```

## Prepare Data

### Import

Let's start by bringing our data into the assignment.

**Task 6.5.1:** Read the file `"data/SCFP2019.csv.gz"` into the DataFrame `df`.

```python
df = pd.read_csv("data/SCFP2019.csv.gz")
print("df shape:", df.shape)
df.head()
```

### Explore

As mentioned at the start of this assignment, you're focusing on business owners. But what percentage of the respondents in `df` are business owners?

**Task 6.5.2:** Calculate the proportion of respondents in `df` that are business owners, and assign the result to the variable `pct_biz_owners`. You'll need to review the documentation regarding the `"HBUS"` column to complete these tasks.

```python
pct_biz_owners = df["HBUS"].mean()

print("proportion of business owners in df:", pct_biz_owners)
```

Is the distribution of income different for business owners and non-business owners?

**Task 6.5.3:** Create a DataFrame `df_inccat` that shows the normalized frequency for income categories for business owners and non-business owners. Your final DataFrame should look something like this:

```git
    HBUS   INCCAT  frequency
0      0     0-20   0.210348
1      0  21-39.9   0.198140
...
11     1     0-20   0.041188
```

```python
inccat_dict = {
    1: "0-20",
    2: "21-39.9",
    3: "40-59.9",
    4: "60-79.9",
    5: "80-89.9",
    6: "90-100",
}

df_inccat = (
    df["INCCAT"].replace(inccat_dict)
    .groupby(df["HBUS"])
    .value_counts(normalize=True)
    .rename("frequency")
    .to_frame()
    .reset_index()
)

df_inccat
```

**Task 6.5.4:** Using seaborn, create a side-by-side bar chart of `df_inccat`. Set `hue` to `"HBUS"`, and make sure that the income categories are in the correct order along the x-axis. Label to the x-axis `"Income Category"`, the y-axis `"Frequency (%)"`, and use the title `"Income Distribution: Business Owners vs. Non-Business Owners"`.

```python
# Create bar chart of `df_inccat`
sns.barplot(x="INCCAT", y="frequency", hue="HBUS", data=df_inccat, order=inccat_dict.values())
plt.xlabel("Income Category")
plt.ylabel("Frequency (%)")
plt.title("Income Distribution: Business Owners vs. Non-Business Owners")
# Don't delete the code below 👇
plt.savefig("images/6-5-4.png", dpi=150)
```

We looked at the relationship between home value and household debt in the context of the credit fearful, but what about business owners? Are there notable differences between business owners and non-business owners?

**Task 6.5.5:** Using seaborn, create a scatter plot that shows `"HOUSES"` vs. `"DEBT"`. You should color the datapoints according to business ownership. Be sure to label the x-axis `"Household Debt"`, the y-axis `"Home Value"`, and use the title `"Home Value vs. Household Debt"`.

```python
# Plot "HOUSES" vs "DEBT" with hue=label
sns.scatterplot(x="HOUSES", y="DEBT", data=df)
# Don't delete the code below 👇
plt.savefig("images/6-5-5.png", dpi=150)
```

For the model building part of the assignment, you're going to focus on small business owners, defined as respondents who have a business and whose income does not exceed $500,000.

**Task 6.5.6:** Create a new DataFrame `df_small_biz` that contains only business owners whose income is below $500,000.

```python
mask = ((df["HBUS"] == 1) & (df["INCOME"] < 500_000))
df_small_biz = df[mask]
print("df_small_biz shape:", df_small_biz.shape)
df_small_biz.head()
```

We saw that credit-fearful respondents were relatively young. Is the same true for small business owners?

**Task 6.5.7:** Create a histogram from the `"AGE"` column in `df_small_biz` with 10 bins. Be sure to label the x-axis `"Age"`, the y-axis `"Frequency (count)"`, and use the title `"Small Business Owners: Age Distribution"`.

```python
# Plot histogram of "AGE"
df_small_biz["AGE"].hist()
# Don't delete the code below 👇
plt.savefig("images/6-5-7.png", dpi=150)
```

So, can we say the same thing about small business owners as we can about credit-fearful people?

Let's take a look at the variance in the dataset.

**Task 6.5.8:** Calculate the variance for all the features in `df_small_biz`, and create a Series `top_ten_var` with the 10 features with the largest variance.

```python
# Calculate variance, get 10 largest features
top_ten_var = df_small_biz.var().nlargest(n=10, keep='first')
top_ten_var
```

We'll need to remove some outliers to avoid problems in our calculations, so let's trim them out.

**Task 6.5.9:** Calculate the trimmed variance for the features in `df_small_biz`. Your calculations should not include the top and bottom 10% of observations. Then create a Series `top_ten_trim_var` with the 10 features with the largest variance.

```python
# Calculate trimmed variance
top_ten_trim_var = df_small_biz.apply(trimmed_var).sort_values().tail(10)
type(top_ten_trim_var)
```

Let's do a quick visualization of those values.

**Task 6.5.10:** Use plotly express to create a horizontal bar chart of `top_ten_trim_var`. Be sure to label your x-axis `"Trimmed Variance [$]"`, the y-axis `"Feature"`, and use the title `"Small Business Owners: High Variance Features"`.

```python
# Create horizontal bar chart of `top_ten_trim_var`
fig = px.bar(x=top_ten_trim_var, y=top_ten_trim_var.index, title="Small Business Owners:

 High Variance Features")
fig.show()
```

What patterns do you see in this plot? Are there any surprises?

**Task 6.5.11:** In the cell below, share at least one observation or insight from the plot above.

For the next step, you'll cluster the rows of `df_small_biz` based on the top-variance features you've just identified.

### Model

Before we start building a model, let's transform our top-variance features with PCA.

**Task 6.5.12:** Use `PCA` and `StandardScaler` to transform the features in `top_ten_trim_var`. Be sure to use at least 5 components.

```python
# PCA transform of `df_small_biz` using top 10 features, 5 components
top_ten_features = df_small_biz[top_ten_trim_var.index].dropna()
pca = make_pipeline(StandardScaler(), PCA(n_components=5)).fit(top_ten_features)
X_pca = pca.transform(top_ten_features)
print(X_pca.shape)
```

Now let's build the model.

**Task 6.5.13:** Create a k-means clustering model with 3 clusters.

```python
# 3-cluster k-means model
model = KMeans(n_clusters=3)
model.fit(X_pca)
labels = model.predict(X_pca)
print(labels)
```

For each cluster, find the average value of the original features in `df_small_biz`.

**Task 6.5.14:** Calculate the mean value of each original feature in `df_small_biz` by cluster.

```python
# Calculate cluster means
cluster_means = df_small_biz[top_ten_trim_var.index].groupby(labels).mean()
cluster_means
```

Let's wrap up by visualizing the clusters.

**Task 6.5.15:** Create a scatter plot of the clusters in the transformed PCA space.

```python
# Scatter plot of clusters in PCA space
df_pca = pd.DataFrame(X_pca, columns=[f"PCA{i+1}" for i in range(X_pca.shape[1])])
df_pca["cluster"] = labels
px.scatter(df_pca, x="PCA1", y="PCA2", color="cluster")
```

Finally, we'll take a look at the silhouette score for this model.

```python
# Calculate silhouette score
sil_score = silhouette_score(X_pca, labels)
sil_score
```

You've built a clustering model that segments small business owners in the United States based on high-variance features. You're also starting to understand the different subgroups within the small business owner community.
