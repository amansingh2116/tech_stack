'''The sequence of central polygonal numbers describes the
maximum number of bounded/unbounded regions (not
necessarily of the same shape or area) a circle that can be
made with a given number of straight cuts. For example, 3
straight cuts across a circle will produce 6 regions if the cuts
are made intersecting at a common point, but 7 if they do
not. Write a program to print the sequence of central
polygonal numbers up to a given number of terms.'''
n = int(input('enter number'))
def seq(n):
   if n<0:
    return ValueError
   elif n==0:
     return 1
   elif n==1:
     return 2 
   else:
     return seq(n-1) + n # since for max no of regions the nth line should be drawn so that it cuts every of the previous n-1 giving us (n-1) + 1 = n new regions
for i in range(n+1):
  print(seq(i))