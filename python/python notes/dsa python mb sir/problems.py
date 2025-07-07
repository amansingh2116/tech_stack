# Pascal’s triangle pattern
def print_pascal_triangle(row):
    """
    Prints Pascal's Triangle using three different approaches
    """
    
    print("\n=== IDEA 1: Sum of Two Above Elements ===")
    # The element in row = i, column = j is obtained by adding the elements in row = i - 1, column = j - 1 and row = i - 1, column = j, except for the first and last column
    for i in range(row):
        # Print leading spaces for pyramid shape
        for space in range(row - i + 1):
            print(' ', end='')
        
        current_row = []
        for j in range(i + 1):
            if j == 0 or j == i:  # First and last elements are always 1
                current_row.append(1)
            else:
                # Sum of elements from previous row
                value = triangle[i-1][j-1] + triangle[i-1][j]
                current_row.append(value)
            print(f' {current_row[-1]}', end='')
        
        triangle.append(current_row)
        print()

    print("\n=== IDEA 2: Combination Formula (i C j) ===")
    # The element in row = i, column = j is obtained by computing {i C j} denoting i(C)j
    for i in range(row):
        for space in range(row - i + 1):
            print(' ', end='')
        
        for j in range(i + 1):
            # Calculate combination: i! / (j! * (i-j)!)
            coef = factorial(i) // (factorial(j) * factorial(i - j))
            print(f' {coef}', end='')
        print()

    print("\n=== IDEA 3: Multiplicative Formula ===")
    # The element in row = i, column = j is obtained by multiplying the element in row = i, column = j - 1 with (i-j+1)/j, except for the first row and first column.
    for i in range(row):
        for space in range(row - i + 1):
            print(' ', end='')
        
        coef = 1  # First element is always 1
        for j in range(i + 1):
            print(f' {coef}', end='')
            # Calculate next coefficient using: coef * (i-j)/(j+1)
            coef = coef * (i - j) // (j + 1)
        print()

def factorial(n):
    """Helper function to calculate factorial"""
    if n == 0:
        return 1
    return n * factorial(n - 1)

triangle = [] # Initialize triangle for Idea 1
rows = int(input("Enter number of rows: ")) # Get user input, say 6
print_pascal_triangle(rows) # Print all three versions

#         1
#        1 1
#       1 2 1
#      1 3 3 1
#     1 4 6 4 1
#    1 5 10 10 5 1

# reverse a list of characters (SWAPPING)

def reverse_list(ls):
    """
    Reverses a list of characters using four different swapping approaches
    """
    
    # Make copies of the original list for each approach
    ls1 = ls.copy()
    ls2 = ls.copy()
    ls3 = ls.copy()
    ls4 = ls.copy()
    
    L = len(ls)
    
    print("\nOriginal list:", ls)
    
    # IDEA 1: Using temporary variable
    # Swapping the values between two variables:
    # // Let a = 10, b = 20
    # t = a // t = 10, a = 10, b = 20
    # a = b // t = 10, a = 20, b = 20
    # b = t // t = 10, a = 20, b = 10
    # // Now a = 20, b = 10
    for i in range(L//2):
        # Traditional swap with temp variable
        t = ls1[i]
        ls1[i] = ls1[L-i-1]
        ls1[L-i-1] = t
    print("\nIdea I (Temp Variable):", ls1)
    
    # IDEA 2: Using multiplication/division
    # Swapping the values between two variables:
    # // Let a = 10, b = 20
    # a = a * b // a = 200, b = 20
    # b = a // b // a = 200, b = 10
    # a = a // b // a = 20, b = 10
    # // Now a = 20, b = 10
    for i in range(L//2):
        # Multiplication/division swap (only works with numbers)
        ls2[i] = ls2[i] * ls2[L-i-1]
        ls2[L-i-1] = ls2[i] // ls2[L-i-1]
        ls2[i] = ls2[i] // ls2[L-i-1]
    print("Idea II (Mult/Div):", ls2)
    
    # IDEA 3: Using addition/subtraction
    # Swapping the values between two variables:
    # // Let a = 10, b = 20
    # a = a + b // a = 30, b = 20
    # b = a - b // a = 30, b = 10
    # a = a - b // a = 20, b = 10
    # // Now a = 20, b = 10
    for i in range(L//2):
        # Addition/subtraction swap (only works with numbers)
        ls3[i] = ls3[i] + ls3[L-i-1]
        ls3[L-i-1] = ls3[i] - ls3[L-i-1]
        ls3[i] = ls3[i] - ls3[L-i-1]
    print("Idea III (Add/Sub):", ls3)
    
    # IDEA 4: Using XOR bitwise operation
    # Swapping the values between two variables:
    # // Let a = 10 (i.e., 00001010), b = 20 (i.e., 00010100)
    # a = a ^ b // a = 00011110, b = 00010100
    # b = a ^ b // a = 00011110, b = 00001010
    # a = a ^ b // a = 00010100, b = 00001010
    # // Now a = 20 (i.e., 00010100), b = 10 (i.e., 00001010)
    # Recall that, 0 ^ 0 and 1 ^ 1 both returns 0, whereas 0 ^ 1 and
    # 1 ^ 0 both returns 1.
    for i in range(L//2):
        # XOR swap (works with any data type that supports bitwise operations)
        ls4[i] = ls4[i] ^ ls4[L-i-1]
        ls4[L-i-1] = ls4[i] ^ ls4[L-i-1]
        ls4[i] = ls4[i] ^ ls4[L-i-1]
    print("Idea IV (XOR):", ls4)

# Get user input
user_input = input("Enter characters separated by spaces: ")
char_list = [int(x) if x.isdigit() else x for x in user_input.split()]

# Reverse using all approaches
reverse_list(char_list)

"""
Finds the last repeating character in a string (case-sensitive for lowercase letters)

Problem:
- We need to identify if any character repeats in the string
- We must check from the end of the string to find the LAST repeating character
- Need an efficient solution better than O(n^2) nested loops

Solution Approach:
We can avoid nested loops by using two separate loops.-
Using an auxiliary array to store frequencies can help us detect repetition more efficiently.-
Precomputing the frequencies of characters can help us find the last repeating character quickly.-
Using the ASCII value of a character as an index to the array allows us to quickly look up its frequency.-
Note that, Frequency[ord('a') - 97] denotes the element Frequency[0].
"""

def find_last_repeating_char(input_str):
    frequency = [0] * 26  # For lowercase English letters a-z
    last_repeating_index = -1
    
    # Count character frequencies
    for char in input_str:
        frequency[ord(char) - 97] += 1
    
    # Find last repeating character
    for i in range(len(input_str)-1, -1, -1):
        if frequency[ord(input_str[i]) - 97] > 1:
            last_repeating_index = i
            break
    
    if last_repeating_index == -1:
        print('No repeating character')
    else:
        print('Last repeating character:', input_str[last_repeating_index])

# Test case
# Get user input
user_input = input("Enter a string (lowercase letters only): ").strip().lower()

find_last_repeating_char(user_input)

"""
Problem:
Simulate an environment that generates 1000 random values with the following requirements:
- Values within [0, 0.5) are generated with a probability 0.7
- Values within (0.5, 1] are generated with a probability 0.3
- 0.5 is never generated

Solution Approach:
We can generate random values with conditional control flows over the values generated.
To simplify the problem, we will generate random values up to two decimal places only.
The probability values 0.7 and 0.3 signify 7 out of 10 cases and 3 out of cases, respectively.
We can control the probability of occurrence with randomization.
Generating a random value is nothing but a probabilistic event.
We can generate random values with randomization.
1. Generate a random value between [0, 9].
2. If the random value is less than 7 execute the steps 3-4 and exit, else execute the steps 5-6 and exit.
3. Generate a random value within [0, 49].
4. Map it to [0, 0.5)
5. Generate a random value within [51, 100].
6. Map it to (0.5, 1]
"""

import random

def generate_random_values(count=1000):
    results = []
    
    for _ in range(count):
        # Step 1: Decide which range to use (70/30 probability)
        if random.randint(0, 9) < 7:  # 70% chance
            # Generate value in [0, 0.5)
            value = random.randint(0, 49) / 100
        else:  # 30% chance
            # Generate value in (0.5, 1]
            value = (51 + random.randint(0, 49)) / 100
            
        results.append(value)
    
    return results

# Generate and print 1000 values
random_values = generate_random_values(1000)

# Verification (optional)
low_range = sum(1 for x in random_values if 0 <= x < 0.5)
high_range = sum(1 for x in random_values if 0.5 < x <= 1)
exact_05 = sum(1 for x in random_values if x == 0.5)

print(f"Values in [0, 0.5): {low_range} (~{low_range/10}%)")
print(f"Values in (0.5, 1]: {high_range} (~{high_range/10}%)")
print(f"Values exactly 0.5: {exact_05}")
print("\nFirst 10 values:", random_values[:10])


"""
Problem:
Write a program that takes an angle (any one of the possible two) between the other pair of hands (minute and hour) and
returns whether there is any valid time satisfying the given angle or not, assuming that the second hand of a clock is
residing at 12. Consider that an angle between a pair of hands of a clock will always remain within [0, 2π]. The input is a
pair of integers (say m and n) representing the fractional angle between the minute and hour hands (in radian), i.e. the
angle is mπ n radian.

Solution Approach:
1. Precompute all possible angles created by the minute hand (60 possible values).
2. Precompute all possible angles created by the hour hand (720 possible values).
3. Calculate the difference of angles between the minute and hour hands for all possible combinations.
4. Verify whether it is the same as m/n or not.
"""

import math

def is_valid_clock_angle(m, n):
    """
    Checks if a given angle (mπ/n radians) between minute and hour hands is valid
    when the second hand is at 12 position.
    
    Approach:
    1. Minute hand moves 2π radians in 60 minutes → π/30 rad/min
    2. Hour hand moves 2π radians in 12 hours (720 minutes) → π/360 rad/min
    3. Calculate all possible angle differences between hands
    4. Check if given angle matches any possible difference
    
    Args:
        m (int): numerator of angle in π radians
        n (int): denominator of angle in π radians
        
    Returns:
        bool: True if valid time exists, False otherwise
    """
    target_angle = math.pi * m / n
    
    # Precompute minute and hour angles (in radians)
    minute_angles = [2 * math.pi * i / 60 for i in range(60)]
    hour_angles = [2 * math.pi * j / 720 for j in range(720)]
    
    for min_angle in minute_angles:
        for hr_angle in hour_angles:
            # Calculate both possible angles between hands
            angle_diff = abs(min_angle - hr_angle)
            complement = 2 * math.pi - angle_diff
            
            # Check with floating point tolerance
            if (math.isclose(angle_diff, target_angle, abs_tol=1e-9) or 
                math.isclose(complement, target_angle, abs_tol=1e-9)):
                return True
    return False

# Most efficient version (mathematically optimized)
def is_valid_clock_angle_optimized(m, n):
    """
    Optimized version using integer arithmetic to avoid floating-point errors
    and reduce computations.
    
    Mathematical insight:
    The angle between hands must satisfy either:
    1. |12*i - j| = 360*m/n (mod 720)
    2. 720 - |12*i - j| = 360*m/n (mod 720)
    where i is minutes (0-59) and j is minutes (0-719)
    """
    for i in range(60):
        for j in range(720):
            diff = abs(12 * i - j)
            if (n * diff == 360 * m) or (n * (720 - diff) == 360 * m):
                return True
    return False

# User input and verification
if __name__ == "__main__":
    m = int(input("Enter numerator (m) for angle (mπ/n): "))
    n = int(input("Enter denominator (n) for angle (mπ/n): "))
    
    if is_valid_clock_angle_optimized(m, n):
        print("VALID - Time exists with this angle")
    else:
        print("INVALID - No such time exists")
