This lab demonstrates how to visualize 2D vectors and their operations using Python's NumPy and Matplotlib libraries.

### Plotting Vectors

A 2D vector, such as $\vec{v} = \begin{bmatrix} 1 \\ 1 \end{bmatrix}$, is created as a NumPy array. It can be plotted on a 2D graph using Matplotlib, typically as an arrow starting from the origin (0,0) and ending at the vector's coordinates.

```python
import numpy as np
import matplotlib.pyplot as plt

# Define and plot a vector
v = np.array([1, 1])
ax = plt.axes()
ax.plot(0, 0, 'or') # Origin point
ax.arrow(0, 0, *v, color='b', head_width=0.2, head_length=0.25)
plt.xlim(-2, 2)
plt.ylim(-1, 2)
plt.grid()
plt.show()
```

### Scaling a Vector

Multiplying a vector by a scalar (a single number) scales its length. For example, multiplying vector $\vec{v}$ by a scalar $a=3$ results in a new vector $a\vec{v}$ that points in the same direction but is three times as long.

```python
a = 3
av = a * v # Result is [3, 3]

# Plot original and scaled vectors
ax.arrow(0, 0, *v, color='b', ...)
ax.arrow(0, 0, *av, color='c', linestyle='dotted', ...)
```

### Adding Vectors

Adding two vectors, $\vec{v} = \begin{bmatrix} 1 \\ 1 \end{bmatrix}$ and $\vec{w} = \begin{bmatrix} -2 \\ 2 \end{bmatrix}$, results in a new vector found by adding their corresponding components: $\vec{v} + \vec{w} = \begin{bmatrix} -1 \\ 3 \end{bmatrix}$.

Graphically, this is shown using the "tip-to-tail" method, where the second vector is drawn starting from the tip of the first. The resultant vector is then drawn from the origin to the tip of the translated second vector.

```python
w = np.array([-2, 2])
vw = v + w # Result is [-1, 3]

# Plot the "tip-to-tail" addition and the resultant vector
ax.arrow(0, 0, *v, color='b', ...) # Vector v
ax.arrow(v[0], v[1], *w, color='c', linestyle='dotted', ...) # Vector w from v's tip
ax.arrow(0, 0, *vw, color='k', ...) # Resultant vector vw from origin
```


This lab shows how to determine if a vector is within the **span** of a set of other vectors using Python's NumPy library.

### The Problem: Linear Combinations

To check if a target vector $\vec{t}$ is in the span of vectors $\vec{v}$ and $\vec{w}$, we must find scalars ($a$, $b$) that solve the linear combination equation:

$$a\vec{v} + b\vec{w} = \vec{t}$$

This vector equation is equivalent to a system of linear equations.

-----

### The Solution: `numpy.linalg.solve`

NumPy's `linalg.solve` function can find these scalars efficiently.

1.  **Arrange the vectors**: Create a matrix `A` from the "building block" vectors ($\vec{v}$, $\vec{w}$) and a vector `b` for the target vector ($\vec{t}$).
2.  **Solve**: Call `np.linalg.solve(A, b)`.

<!-- end list -->

```python
import numpy as np

# Check if t is in the span of the columns of vw
# a[1, 3] + b[2, 5] = [4, 11]
vw = np.array([[1, 2], [3, 5]])
t = np.array([4, 11])

try:
    # linalg.solve finds the vector of scalars [a, b]
    scalars = np.linalg.solve(vw, t)
    print(f"Vector is in the span. Scalars: {scalars}")
except np.linalg.LinAlgError:
    print("Vector is NOT in the span (no unique solution).")

# Output: Vector is in the span. Scalars: [2. 1.]
```

The result `[2. 1.]` corresponds to the scalars $a=2$ and $b=1$.

-----

### Possible Outcomes

When solving a system of linear equations, there are three possibilities:

1.  **One Unique Solution**: The function returns the scalars. The vectors are linearly independent, and the target vector is **in the span**. Graphically, the lines intersect at one point.
2.  **Infinite Solutions**: `linalg.solve` will fail with a "Singular matrix" error. The vectors are linearly dependent, and the target lies on the same line. Graphically, the lines are identical.
3.  **No Solution**: `linalg.solve` will fail with a "Singular matrix" error. The vectors are linearly dependent, but the target is not on their line. Graphically, the lines are parallel.


This lab shows that matrix multiplication is a **linear transformation** by demonstrating two equivalent computational methods in Python.

-----

### Method 1: Transforming Basis Vectors

A linear transformation is defined by where the basis vectors $\vec{i}$ and $\vec{j}$ land. A vector $\vec{v} = x\vec{i} + y\vec{j}$ is transformed by applying its components ($x, y$) to the new, transformed basis vectors ($\vec{i_t}$, $\vec{j_t}$).

The Python implementation is a direct linear combination in NumPy.

```python
import numpy as np

v = np.array([-1, 2])
ihat_t = np.array([3, 1])
jhat_t = np.array([1, 2])

# Scale the new basis vectors by the original vector's components and add them
v_t = v[0] * ihat_t + v[1] * jhat_t
print(v_t)
```

```
[-1  3]
```

-----

### Method 2: Matrix-Vector Multiplication

The same result is achieved by creating a **transformation matrix** whose columns are the transformed basis vectors and then multiplying this matrix by the original vector using **`numpy.matmul()`**.

This method is computationally more direct.

```python
v = np.array([-1, 2])
# The transformation matrix's columns are ihat_t and jhat_t
M = np.array([[3, 1], [1, 2]])

# Use matmul() for matrix-vector multiplication
v_t = np.matmul(M, v)
print(v_t)
```

```
[-1  3]
```

Both Python methods yield the identical transformed vector, confirming the geometric meaning of matrix multiplication.

This lab demonstrates how to solve a practical currency conversion problem using matrix multiplication, illustrating the `outputs = inputs @ weights` pattern common in data science and machine learning.

### The Setup

The problem involves converting a portfolio of 8 currencies into a total amount for each of those same 8 currencies.

  * **Inputs (`money`):** A $1 \times 8$ vector where each element is the amount of a specific currency you hold.
  * **Weights (`conversion_rates`):** An $8 \times 8$ matrix where each element `[i, j]` represents the conversion rate from currency `i` to currency `j`.

### The Python Implementation

The entire conversion is performed with a single matrix multiplication operation using NumPy. An **inputs** vector is multiplied by a **weights** matrix to produce an **outputs** vector.

```python
import numpy as np

# 1. Define the input vector of currency amounts you hold.
# (USD, EUR, JPY, GBP, CHF, CAD, AUD, HKD)
money = np.array([70, 100, 20, 80, 40, 70, 60, 100])

# 2. Define the weights matrix of conversion rates.
# This is an 8x8 matrix where conversion_rates[i, j] converts from currency i to j.
# (Loaded from a CSV in the lab)
conversion_rates = np.array(
    [[1.0000, 0.8364, 111.370, 0.7404, 0.9781, 1.2548, 1.2760, 7.8218],
     [1.1956, 1.0000, 133.154, 0.8852, 1.1694, 1.5002, 1.5256, 9.3517],
     # ... (remaining rows of the 8x8 matrix)
     [0.1278, 0.1069, 14.2384, 0.0947, 0.1250, 1.604, 0.1631, 1.0000]]
)

# 3. Compute the output vector using matrix multiplication.
# A (1x8) vector @ (8x8) matrix results in a (1x8) vector.
money_totals = np.matmul(money, conversion_rates)

print(money_totals)
```

```
[454.277  379.965  50593.59  336.338  444.326  570.034  579.667 3553.307]
```

### The Result

The output vector `money_totals` contains 8 values. The first value (454.28) is the total worth of all your currencies converted to USD, the second (379.97) is the total worth in EUR, and so on. This single operation efficiently solves the entire conversion problem.
