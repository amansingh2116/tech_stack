### What is a Vector?

At its core, a **vector** is a list of numbers that describes a point or a movement in space. Think of it as a set of instructions containing two key pieces of information: **magnitude** (how far) and **direction** (where to go).

Let's start in 2D space ($\mathbb{R}^2$), which is just a standard flat plane. Imagine you need to get from a starting point to a destination. The instructions might be: "move 4 steps to the right and 2 steps up."

This movement can be captured by the vector $ \vec{v} $:

$$\vec{v} = \begin{bmatrix} 4 \\ 2 \end{bmatrix}$$

Visually, we represent this as an arrow starting from the origin and ending at the point (4, 2).



While we can easily draw 2D or 3D vectors, the same concept applies to **n-dimensions** ($\mathbb{R}^n$). A vector with 100 elements is just a point in a 100-dimensional space—we can't picture it, but the mathematical rules are the same.

***

### Describing a Vector: Magnitude & Direction

Every vector has a length and a direction. Let's calculate these for our vector $\vec{v} = \begin{bmatrix} 4 \\ 2 \end{bmatrix}$.

#### Magnitude (Length) 📏
The **magnitude** is simply the length of the vector's arrow. We use the symbol $\Vert \vec{v} \Vert$ to denote it. You can find it using the Pythagorean Theorem.

For a 2D vector $ \begin{bmatrix} x \\ y \end{bmatrix} $, the formula is:
$$\Vert \vec{v} \Vert = \sqrt{x^2 + y^2}$$

In our example:
$$\Vert \vec{v} \Vert = \sqrt{4^2 + 2^2} = \sqrt{16 + 4} = \sqrt{20} \approx 4.47$$

So, the length of our arrow is about 4.47 units.

#### Direction (Angle) 🧭
The **direction** is the angle the vector makes with the horizontal axis, usually denoted by theta ($\theta$). We can find it using basic trigonometry.

The formula is:
$$\theta = \arctan\left(\frac{y}{x}\right)$$

In our example:
$$\theta = \arctan\left(\frac{2}{4}\right) = \arctan(0.5) \approx 26.57^{\circ}$$

This means our vector is pointed at an angle of about 26.57 degrees above the horizontal axis.

***

### Essential Vector Operations

Just like regular numbers, we can perform operations on vectors. These operations are the building blocks for how neural networks learn by adjusting their internal values.

#### Vector Addition ➕
Adding two vectors is like following one set of instructions and then the other. If we have $\vec{a} = \begin{bmatrix} 4 \\ 2 \end{bmatrix}$ and $ \vec{b} = \begin{bmatrix} 1 \\ 3 \end{bmatrix} $, their sum is:

$$\vec{a} + \vec{b} = \begin{bmatrix} 4+1 \\ 2+3 \end{bmatrix} = \begin{bmatrix} 5 \\ 5 \end{bmatrix}$$

You simply add the corresponding components. Visually, this is like placing the tail of vector $\vec{b}$ at the tip of vector $\vec{a}$.



#### Scalar Multiplication ✖️
Multiplying a vector by a single number (a **scalar**) scales its magnitude.

If we take our vector $\vec{v} = \begin{bmatrix} 4 \\ 2 \end{bmatrix}$ and multiply it by the scalar $ \alpha = 2 $:

$$2 \cdot \vec{v} = 2 \begin{bmatrix} 4 \\ 2 \end{bmatrix} = \begin{bmatrix} 2 \cdot 4 \\ 2 \cdot 2 \end{bmatrix} = \begin{bmatrix} 8 \\ 4 \end{bmatrix}$$

The result is a new vector pointing in the **same direction** but is **twice as long**.
* Multiplying by a negative scalar would flip the vector's direction.
* Multiplying by a fraction (e.g., 0.5) would shrink it.

***

### A Note on Formatting: The Transpose

Finally, it's important to know how a vector is written. So far, we've used **column vectors**.

$$\text{Column Vector:} \begin{bmatrix} a_1 \\ a_2 \\ \vdots \\ a_n \end{bmatrix}$$

The same vector can also be written as a **row vector**.

$$\text{Row Vector:} \begin{bmatrix} a_1 & a_2 & \dots & a_n \end{bmatrix}$$

Flipping between these two formats is called a **transpose**, indicated by a superscript $T$.

$$\begin{bmatrix} a_1 \\ a_2 \\ \vdots \\ a_n \end{bmatrix}^T = \begin{bmatrix} a_1 & a_2 & \dots & a_n \end{bmatrix}$$

This simple operation is crucial for more advanced topics like matrix multiplication, which is fundamental to how neural networks process data.