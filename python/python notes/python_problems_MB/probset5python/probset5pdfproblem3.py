# Write a program in Python following the object-oriented
# paradigm to take the length of sides of a triangle or rectangle
# as user inputs and calculate its area accordingly.
class triangle:
    def __init__(self,a,b,c):
        self.side1 = a
        self.side2 = b
        self.side3 = c
    def areafn(self):
        a =self.side1
        b = self.side2
        c = self.side3
        s =(a+b+c)/2
        self.area = (s*(s-a)*(s-b)*(s-c))**(1/2)
        print(self.area)
class rectangle:
    def __init__(self,a,b):
        self.side1 = a
        self.side2 = b
    def areafn(self):
        self.area = self.side1*self.side2
        print(self.area)
x = int(input('enter 1 for traingle, 2 for rectangle : '))
if x==1:
    m = int(input('enter side 1 : '))
    n = int(input('enter side 2 : '))
    q = int(input('enter side 3 : '))
    tr1 = triangle(m,n,q)
    tr1.areafn()
elif x==2:
    n = int(input('enter length : '))
    q = int(input('enter breadth : '))
    sq1 = rectangle(n,q)
    sq1.areafn()
else:
    print('enter 1 or 2 only')