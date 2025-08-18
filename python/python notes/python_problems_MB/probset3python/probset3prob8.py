'''Consider a 2-D matrix of size 2m × 2m. The entries of the
matrix are, in row-major order, 1, 2, 3, . . . , 2^2m. Print the
entries of the matrix in Z-curve order'''
def z_func(x1, y1, x2, y2, arr):
    if x1 == x2 and y1 == y2:
        print(arr[x1][y1], end=" ")
    else:
        z_func(x1, y1, (x1 + x2) // 2, (y1 + y2) // 2, arr)
        z_func(x1, (y1 + y2) // 2 + 1, (x1 + x2) // 2, y2, arr)
        z_func((x1 + x2) // 2 + 1, y1, x2, (y1 + y2) // 2, arr)
        z_func((x1 + x2) // 2 + 1, (y1 + y2) // 2 + 1, x2, y2, arr)

m = int(input("Please enter m to create 2^m * 2^m matrix: "))

size = 2**m
my_arr = [[0 for _ in range(size)] for _ in range(size)]

# Populate the matrix with values from 1 to 2^(2m)
current_value = 1
for i in range(size):
    for j in range(size):
        my_arr[i][j] = current_value
        current_value += 1

print("Original matrix:")
for row in my_arr:
    for value in row:
        print(value, end="\t")
    print()

print("\nZ-curve order:")
z_func(0, 0, size - 1, size - 1, my_arr)
