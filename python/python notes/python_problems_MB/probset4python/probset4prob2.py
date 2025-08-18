'''Write a program to print the following matrix pattern
(increasing prime numbers from the centre toward the
boundaries) using generic controls over print. You are not
allowed to use any auxiliary space to keep the matrix. Let the
line number be user input.'''
def is_prime(num):
    if num <= 1:
        return False
    if num <= 3:
        return True
    if num % 2 == 0 or num % 3 == 0:
        return False
    i = 5
    while i * i <= num:
        if num % i == 0 or num % (i + 2) == 0:
            return False
        i += 6
    return True

def print_prime_matrix(n):
    if n <= 0:
        print("Please enter a positive integer.")
        return

    if n % 2 == 0:
        n += 1  # Ensure the number of lines is odd for a center 1

    current_num = 1
    mid = n // 2  # Calculate the middle index

    for i in range(n):
        for j in range(n):
            distance = max(abs(i - mid), abs(j - mid))
            num = current_num + distance
            while not is_prime(num):
                num += 1
            print(num, end="\t")
        print()

try:
    lines = int(input("Enter the number of lines (should be odd): "))
    print_prime_matrix(lines)
except ValueError:
    print("Invalid input. Please enter a valid positive odd integer.")