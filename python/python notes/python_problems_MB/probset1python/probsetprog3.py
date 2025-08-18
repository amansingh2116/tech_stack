'''Let us define a string, comprising English alphabets, as NICE
if each vowel within it is equidistant from its successor and
predecessor vowel, if applicable. E.g., “rhythm”, “cool”,
“malayalam” are NICE strings. Write a program to verify
whether a given string is NICE or not. You are required to
take the string as a direct input without asking for its length'''
n=input("Enter string to check :")
l=[]
for i in range(len(n)):
    if n[i] in "aeiouAEIOU":
        l.append(i)
count=0
if len(l)>2:
    d=l[1]-l[0]
    for i in range(len(l)-1):
        if l[i+1]-l[i]!=d:
            count+=1
else:
    print("yes entered string is NICE")
if count==0:
    print("yes entered string is NICE")