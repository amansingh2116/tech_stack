#write a python program to convert a given algebric expression to postfix expression.
inp = input('algebraic expr: ')

def ins(stk, n):
    stk.append(n)

def delt(stk):
    return stk.pop()

def precedence(op):
    precedence = {'+': 1, '-': 1, '*': 2, '/': 2, '^': 3}
    return precedence.get(op, 0)

def is_operator(char):
    return char in "+-*/^"

l = []
exp = ''

for i in inp:
    if i.isalpha():
        exp += i
    elif i == '(':
        ins(l, i)
    elif i == ')':
        while l and l[-1] != '(':
            exp += delt(l)
        if l and l[-1] == '(':
            delt(l)
    elif is_operator(i):
        while l and precedence(i) <= precedence(l[-1]):
            exp += delt(l)
        ins(l, i)

while l:
    exp += delt(l)

print("Postfix expression:", exp)
