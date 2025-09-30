### Linear Combinations: The Building Blocks 🧱

A **linear combination** is a way of creating a new vector by scaling and adding other vectors. Think of it as a recipe where your starting vectors are the ingredients and numbers (scalars) are the amounts you use.

If you have a set of vectors $\vec{v_1}, \vec{v_2}, \dots, \vec{v_n}$ and a set of corresponding scalars $a_1, a_2, \dots, a_n$, a linear combination is the new vector $\vec{w}$ created by:

$$\vec{w} = a_1\vec{v_1} + a_2\vec{v_2} + \dots + a_n\vec{v_n}$$

For example, to create the vector $\vec{w} = \begin{bmatrix} 7 \\ 2 \end{bmatrix}$ using the standard basis vectors $\vec{i} = \begin{bmatrix} 1 \\ 0 \end{bmatrix}$ and $\vec{j} = \begin{bmatrix} 0 \\ 1 \end{bmatrix}$, the recipe is:

$$\vec{w} = 7\vec{i} + 2\vec{j} = 7\begin{bmatrix} 1 \\ 0 \end{bmatrix} + 2\begin{bmatrix} 0 \\ 1 \end{bmatrix} = \begin{bmatrix} 7 \\ 2 \end{bmatrix}$$

---

### Span: The Universe of What You Can Build 🌐

The **span** of a set of vectors is the collection of *all possible vectors* you can create using any linear combination of them. It’s the entire space you can "reach" with your given set of building blocks.

* The span of a single vector like $\begin{bmatrix} 2 \\ 1 \end{bmatrix}$ is an infinite line passing through the origin and the point (2, 1).
* The span of two independent 2D vectors, like $\begin{bmatrix} 1 \\ 0 \end{bmatrix}$ and $\begin{bmatrix} 0 \\ 1 \end{bmatrix}$, is the entire 2D plane ($\mathbb{R}^2$). You can reach any point on the plane.
* Similarly, the span of the three standard basis vectors in 3D is all of 3D space ($\mathbb{R}^3$).



---

### Linear Independence: Efficient Building Blocks ✅

This concept checks for **redundancy** in your set of vectors.

* A set of vectors is **linearly independent** if each vector adds a new, unique direction. None of the vectors can be created as a linear combination of the others. This is an "efficient" set of building blocks.
    * **Example**: $\left\{ \begin{bmatrix} 1 \\ 0 \end{bmatrix}, \begin{bmatrix} 0 \\ 1 \end{bmatrix} \right\}$. You can't make one from the other. You need both to span the 2D plane.

* A set of vectors is **linearly dependent** if at least one vector is redundant—it's just a combination of the others. It doesn't add anything new to the span.
    * **Example**: $\left\{ \begin{bmatrix} 2 \\ 2 \end{bmatrix}, \begin{bmatrix} 4 \\ 4 \end{bmatrix} \right\}$. The second vector is just $2 \times$ the first. They point in the same direction, so the second one doesn't help you reach any new places.

---

### Putting It Together: Solving for a Specific Recipe 🎯

Now for the practical part. Let's say we have a target vector and want to find the exact recipe to build it from our building blocks.

**Problem**: Find the scalars $a$ and $b$ that create the vector $\begin{bmatrix} -13 \\ 3 \end{bmatrix}$ as a linear combination of $\vec{x} = \begin{bmatrix} -14 \\ 2 \end{bmatrix}$ and $\vec{y} = \begin{bmatrix} 5 \\ -1 \end{bmatrix}$.

Our vector equation is:
$$a\begin{bmatrix} -14 \\ 2 \end{bmatrix} + b\begin{bmatrix} 5 \\ -1 \end{bmatrix} = \begin{bmatrix} -13 \\ 3 \end{bmatrix}$$

This single vector equation can be broken into a **system of two linear equations**, one for each component:
1.  $-14a + 5b = -13$
2.  $2a - b = 3$

We can solve this system using a few methods:

#### 1. Substitution Method
Isolate a variable in one equation and substitute it into the other.
From equation (2), we can easily find $b$:
$$b = 2a - 3$$
Now, substitute this into equation (1):
$$-14a + 5(2a - 3) = -13$$
$$-14a + 10a - 15 = -13$$
$$-4a = 2 \implies \mathbf{a = -0.5}$$
Finally, find $b$:
$$b = 2(-0.5) - 3 = -1 - 3 \implies \mathbf{b = -4}$$

#### 2. Elimination Method
Multiply one or both equations so that one variable has opposite coefficients, then add the equations to eliminate it.
Let's multiply equation (2) by 5:
$$-14a + 5b = -13$$
$$10a - 5b = 15$$
Now, add the two equations together:
$$(-14a + 10a) + (5b - 5b) = -13 + 15$$
$$-4a = 2 \implies \mathbf{a = -0.5}$$
Substitute $a = -0.5$ back into any original equation to find $\mathbf{b = -4}$.

#### 3. Graphical Method
Plot both linear equations as lines. The point where they intersect is the one and only solution $(a, b)$ that satisfies both.



The intersection point is **(-0.5, -4)**, confirming our algebraic solutions.

#### Final Answer
The unique recipe to create our target vector is $a = -0.5$ and $b = -4$. This brings up an important question: Will a system of equations always have one unique solution? The answer depends on the linear independence of the vectors involved!