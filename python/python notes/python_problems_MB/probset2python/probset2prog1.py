'''Suppose there are two separate files containing sufficiently
large integer values. Write a program that will take those two
filenames as user inputs and return the addition result.'''
a=input("Enter first file name (with location):")
b=input("Enter second file name (with location):")
def reader(file):
    f = open(file,'r')
    output = f.read()
    f.close()
    return output
print('Result after adding :',int(reader(a)) + int(reader(b)))