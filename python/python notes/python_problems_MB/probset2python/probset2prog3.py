'''A number is PSEUDOPERFECT if the sum of all or some of
its proper divisors is equal to the number itself. Write a
program to verify whether a given number is pseudoperfect or
not'''
n=int(input('Enter number :'))
l1=[]   
for i in range(1,(n//2)+1):
    if n%i==0 :
        l1.append(i)
def pseudo(m):
    if sum(m)==n:
        return True
    return False
l3=[]
def checkpseudo(lst, k=0):
    #If k is equal to the length of the list lst, it means that we have considered all possible combinations of divisors. At this point, we check whether the sum of divisors in the list l3 (a separate (sub)list used to accumulate divisors) is equal to the input number n.
    if k == len(lst):
        if pseudo(l3):
            print('Yes, the given number is PSEDOPERFECT due to the following divisors:', l3)
        #Regardless of whether the sum is equal to n, the function returns, effectively backtracking and continuing the search for other combinations.
        return
    
    #In the first recursive call, we include the divisor at index k in the l3 list (i.e., l3.append(lst[k]) and then recursively call checkpseudo with k incremented by 1.
    l3.append(lst[k])
    checkpseudo(lst, k + 1)

    #In the second recursive call, we remove the divisor at index k from the l3 list (i.e., l3.remove(lst[k]) and then recursively call checkpseudo with k incremented by 1.
    l3.remove(lst[k])
    checkpseudo(lst, k + 1)

    #These two recursive calls effectively explore two possibilities for each divisor: one where the divisor is included in the sum, and one where it is not included. This recursive branching continues until all possible combinations of divisors have been considered.
checkpseudo(l1)





#second approach
def proper_divisors(n):
    divisors = [1]
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            divisors.append(i)
            if i != n // i:
                divisors.append(n // i)
    return divisors

def is_pseudoperfect(n):
    divisors = proper_divisors(n)
    for i in range(1, 2 ** len(divisors)):
        subset_sum = sum(divisors[j] for j in range(len(divisors)) if (i >> j) & 1)
        if subset_sum == n:
            return True
    return False

n = int(input('Enter number: '))
if is_pseudoperfect(n):
    print(f'{n} is pseudoperfect.')
else:
    print(f'{n} is not pseudoperfect.')

# We iterate from 1 to 2^len(divisors) - 1. This loop generates all possible binary representations of numbers from 1 to 2^len(divisors) - 1. Each binary representation corresponds to a subset of the proper divisors.

# Inside the loop, we use (i >> j) & 1 to check if the j-th bit of the binary representation of i is set (i.e., equal to 1). If it is set, we include the j-th proper divisor in the current subset.