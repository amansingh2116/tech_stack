'''Given a list of non-negative digits (0-9), not necessarily
distinct, write a program to find out the largest multiple of 3
that can be formed from these digits.''' 
l1 = [4, 5, 4, 0, 6, 4, 6, 7, 4]
l3 = []

def pseudo(m):
    if sum(m) % 3 == 0:
        return True
    return False

l3 = []
list1 = []

def checkpseudo(lst, k=0):
    if k == len(lst):
        if pseudo(l3):
            copy = list(l3)
            list1.append(copy)
        return

    l3.append(lst[k])
    checkpseudo(lst, k + 1)

    l3.remove(lst[k])
    checkpseudo(lst, k + 1)

checkpseudo(l1)

# Filter out empty strings and convert to integers
integers = [int(''.join(map(str, l))) for l in list1 if ''.join(map(str, l))]

# Sort integers in descending order
integers.sort(reverse=True)

# Find the largest multiple of 3
largest_multiple_of_3 = None
for num in integers:
    if num % 3 == 0:
        largest_multiple_of_3 = num
        break

print("The largest multiple of 3 is:", largest_multiple_of_3)
