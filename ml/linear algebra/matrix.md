### What is a Matrix? 📝

A **matrix** is a rectangular grid of numbers arranged into rows and columns. Think of it like a spreadsheet. A matrix with $m$ rows and $n$ columns is called an $m \times n$ (read "m by n") matrix.

Each number in the matrix is called an element, and we can locate it by its row and column position. The element $a_{ij}$ is in the $i$-th row and $j$-th column.

$$A = \begin{bmatrix} a_{11} & a_{12} & \dots & a_{1n} \\ a_{21} & a_{22} & \dots & a_{2n} \\ \vdots & \vdots & \ddots & \vdots \\ a_{m1} & a_{m2} & \dots & a_{mn} \end{bmatrix}$$

---

### Simple Matrix Operations (Element-by-Element)

These basic operations work by applying the math to each corresponding element individually.

#### Matrix Addition ➕

You can only add two matrices if they have the **exact same dimensions**. The process is simple: add the elements in the corresponding positions.

**Example:**
$$A = \begin{bmatrix} 1 & 2 \\ 3 & 4 \end{bmatrix}, \quad B = \begin{bmatrix} 5 & 6 \\ 7 & 8 \end{bmatrix}$$$$A+B = \begin{bmatrix} 1+5 & 2+6 \\ 3+7 & 4+8 \end{bmatrix} = \begin{bmatrix} 6 & 8 \\ 10 & 12 \end{bmatrix}$$

#### Scalar Multiplication ✖️

Multiplying a matrix by a single number (a **scalar**) involves multiplying **every single element** in the matrix by that scalar.

**Example:**
$$\alpha = 3, \quad A = \begin{bmatrix} 1 & 2 \\ 3 & 4 \end{bmatrix}$$$$\alpha A = 3 \begin{bmatrix} 1 & 2 \\ 3 & 4 \end{bmatrix} = \begin{bmatrix} 3 \times 1 & 3 \times 2 \\ 3 \times 3 & 3 \times 4 \end{bmatrix} = \begin{bmatrix} 3 & 6 \\ 9 & 12 \end{bmatrix}$$

---

### Matrix Multiplication: The Main Event 🧠

Matrix multiplication is more complex but is a cornerstone of linear algebra and neural networks. It does **not** work element-by-element.

#### The Golden Rule: Checking Dimensions

Before you can multiply two matrices, $A \times B$, the **number of columns in the first matrix ($A$) must equal the number of rows in the second matrix ($B$)**.

* If $A$ is $m \times \mathbf{n}$ and $B$ is $\mathbf{n} \times p$, multiplication is **possible**.
* The resulting matrix, $C$, will have dimensions $m \times p$.

**Example:**
* A $(2 \times \mathbf{3})$ matrix can be multiplied by a $(\mathbf{3} \times 4)$ matrix. The result will be a $(2 \times 4)$ matrix.
* A $(2 \times \mathbf{3})$ matrix **cannot** be multiplied by a $(\mathbf{2} \times 2)$ matrix because the inner dimensions (3 and 2) do not match.

#### The "Row-by-Column" Method

To find the element in the $i$-th row and $j$-th column of the resulting matrix, you calculate the **dot product** of the **$i$-th row of the first matrix** and the **$j$-th column of the second matrix**.

Let's calculate $C = A \times B$ where:
$$A = \begin{bmatrix} 1 & 2 \\ 3 & 4 \end{bmatrix}, \quad B = \begin{bmatrix} 5 & 6 \\ 7 & 8 \end{bmatrix}$$

The result $C$ will be a $2 \times 2$ matrix: $C = \begin{bmatrix} c_{11} & c_{12} \\ c_{21} & c_{22} \end{bmatrix}$

* **To find $c_{11}$**: Use Row 1 of A and Column 1 of B.
    $c_{11} = (1 \times 5) + (2 \times 7) = 5 + 14 = \mathbf{19}$

* **To find $c_{12}$**: Use Row 1 of A and Column 2 of B.
    $c_{12} = (1 \times 6) + (2 \times 8) = 6 + 16 = \mathbf{22}$

* **To find $c_{21}$**: Use Row 2 of A and Column 1 of B.
    $c_{21} = (3 \times 5) + (4 \times 7) = 15 + 28 = \mathbf{43}$

* **To find $c_{22}$**: Use Row 2 of A and Column 2 of B.
    $c_{22} = (3 \times 6) + (4 \times 8) = 18 + 32 = \mathbf{50}$

The final result is:
$$C = A \times B = \begin{bmatrix} 19 & 22 \\ 43 & 50 \end{bmatrix}$$

#### A Crucial Point: Order Matters!
Unlike with regular numbers, the order of matrix multiplication is critical. In general:
$$A \times B \neq B \times A$$
This property is called being **non-commutative**. Reversing the order will usually produce a different result, or it may make the multiplication impossible.