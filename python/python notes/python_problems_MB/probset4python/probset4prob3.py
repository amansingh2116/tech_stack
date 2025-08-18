'''Write a program that takes a 9 × 9 matrix as input and
checks whether it is a valid Sudoku matrix or not. Recall that
a Sudoku matrix is filled in with numbers from 1-9 with no
repeated numbers in each line, horizontally or vertically
'''
def valid_sudoku(M):
    for row in M:
        if len(set(row)) != 9:
            return False

    for col in range(9):
        column = [M[row][col] for row in range(9)]
        if len(set(column)) != 9:
            return False

    return True
M = [[ int(input('enter element')) for i in range(9)] for j in range(9)]
if valid_sudoku(M):
    print('Yes, it is a valid Sudoku matrix.')
else:
    print('No, it is not a valid Sudoku matrix.')

