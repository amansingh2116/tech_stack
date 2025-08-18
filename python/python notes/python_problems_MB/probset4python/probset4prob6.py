'''Write a program in Python to reverse the content of a file
whose name is provided as command line argument.
'''
import sys

filename = sys.argv[1]
with open(filename, 'r+') as file:
    content = file.read()
    reverse = content[::-1]

with open(filename, 'w') as file:
    file.write(reverse)