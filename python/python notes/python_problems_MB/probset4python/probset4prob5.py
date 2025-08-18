'''Write a program in Python to show its soure code as output
on stdout.
'''
with open(__file__, 'r') as source_file:
    source_code = source_file.read()
    print(source_code)
