'''Solve the Tower of Hanoi problem (as shown in the picture below)
where the objective is to move an entire stack of disks from the
source (leftmost) tower to the target (rightmost) tower using a
spare (middle one) tower, abiding by the following rules:
Only one disk may be moved at a time.
Each move consists of taking the upper disk from one tower
and placing it on top of another tower or on an empty tower.
No disk may be placed on top of a disk that is smaller than it.
Given the number of disks n as user input, output the total count
of moves and print the individual moves'''

'''Move n − 1 disks from the source to the spare tower, by the
same general solving procedure. Rules are not violated, by
assumption. This leaves the disk n as a top disk on the source
tower.
2 Move the disk n from the source to the target tower.
3 Move the n − 1 disks that we have just placed on the spare
tower, from the spare to the target tower by the same general
solving procedure, so they are placed on top of the disk n
without violating the rules.
4 The base case is to move no disks (in steps 1 and 3).
'''
def ToI(n, source, target, spare):
    if n == 1:
        print('Move disk 1 from', source, 'to', target)
        return
    ToI(n-1, source, spare, target)
    print('Move disk', n, 'from', source, 'to', target)
    ToI(n-1, spare, target, source)
n = int(input('Enter the number of disks: '))
ToI(n, 'Source', 'Spare', 'Target')