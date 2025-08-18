# Given a list of numbers (provided as command line
# arguments), write a Python program to compute the nearest
# larger value for the number at position i (nearness is measured
# in terms of the difference in array indices). For example, in
# the array [1, 4, 3, 2, 5, 7], the nearest larger value for 4 is 5.
# Note: You are expected to design an O(n) time algorithm.
def nlv(list1, pos):
    N = list1[pos]
    k1, k2 = None, None
    for i in range(pos + 1, len(list1)):
        if list1[i] > N:
            k1 = list1[i]
            break

    for i in range(pos - 1, -1, -1):
        if list1[i] > N:
            k2 = list1[i]
            break

    return k1 if k1 is not None else k2

h = list(map(int, input('Enter list of list1: ').split()))
l = int(input('Enter pos: '))

if 0 <= l < len(h):
    result = nlv(h, l)
    if result is not None:
        print(f"The nearest larger value for {h[l]} at pos {l} is {result}")
    else:
        print(f"No larger value found for {h[l]} at pos {l}")
else:
    print("Invalid pos")


#where is O(n) and stack