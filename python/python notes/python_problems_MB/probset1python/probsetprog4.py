'''take the string as a direct input without asking for its length.
4 Implement the Chatterjee Correlation Coefficient (Chatterjee,
JASA 2001) in python. Note that, your inputs are two sets of
real values and the output is also a real value.
Link to the paper: https://www.tandfonline.com/doi/full/10.1080/01621459.2020.1758115'''
import random
n=int(input("enter size of data :"))
l2=[]
for i in range(n):
    x=int(input("Enter Xi:"))
    y=int(input("Enter Yi:"))
    l2.append((x,y))
random.shuffle(l2) #randomly shuffles the tuples in the list
sorted_list = sorted(l2, key=lambda x: x[0]) #sort the randomly shuffles list's tuples of form (x,y) only on basis first elent of tuple that is x
def r(k,l1):
    count=0
    for i in range(len(l1)):
        if l1[i][1]<=l1[k][1] :
            count+=1
    return count
def l(k,l1):
    count=0
    for i in range(len(l1)):
        if l1[i][1]>=l1[k][1] :
            count+=1
    return count
f=0
g=0
for i in range(n-1):
    f+=abs(r(i+1,l2)-r(i,l2))
    g+=l(i,l2)*(n-l(i,l2))
e = 1-((n/2)*(f/g))
print(e)