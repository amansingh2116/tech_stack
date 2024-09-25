#include <stdio.h>

// Program to print pascal triangle
int factorial(int x){
    int fact = 1;
    for (int i=2;i<=x;i++){
    fact = fact*i;
    }
    return fact;
}
int combination(int n, int r){
    if (n>=r){
    int ncr = factorial(n)/(factorial(r)*factorial(n-r));
    return ncr;
    }
    else{
        return 0;
    }
}

void pascal(int n) {
    for (int i = 0; i <= n; i++) {
        // Print leading spaces to center the triangle
        for (int space = 0; space < n - i; space++) {
            printf("  ");  // 3 spaces for better alignment
        }

        // Print the values in Pascal's triangle
        for (int j = 0; j <= i; j++) {
            printf("%3d", combination(i, j));  // 4 spaces for uniform formatting
        }
        printf("\n");
    }
}

// You are given a staircase with n steps, and you can climb the stairs by taking 1 step, 2 steps, or 3 steps at a time.
// Your task is to find how many distinct ways you can reach the top of the staircase (i.e., the nth step).
int stair(int n) {
    if (n == 0) return 1;   // Base case: 1 way to stay at ground (n=0)
    if (n == 1) return 1;   // Base case: 1 way to reach the first step
    if (n == 2) return 2;   // Base case: 2 ways to reach the second step (1+1, or 2)

    // Recurrence relation considering 1, 2, or 3 steps
    return stair(n - 1) + stair(n - 2) + stair(n - 3);
}

int ways() {
    int n;
    printf("Enter the number of stairs: ");
    scanf("%d", &n);
    
    int ways = stair(n);
    printf("Number of ways to climb %d stairs: %d\n", n, ways);
    
    return 0;
}

// Program to calculate a^b
// Method 1: Loop method
int power_loop(int a, int b) {
    int result = 1;
    for (int i = 0; i < b; i++) {
        result *= a;
    }
    return result;
}
// Method 2: Recursive method to calculate a^b (a^b = a * a^(b-1))
int power_recursive(int a, int b) {
    if (b == 0)
        return 1;  // Base case: a^0 = 1
    return a * power_recursive(a, b - 1);  // Recursive relation: a^b = a * a^(b-1)
}

// Method 3: Logarithmic method to calculate a^b (Divide and conquer approach)
int power_logarithmic(int a, int b) {
    if (b == 0)
        return 1;  // Base case: a^0 = 1
    int temp = power_logarithmic(a, b / 2);  // Recursive call for a^(b/2)
    if (b % 2 == 0)
        return temp * temp;  // If b is even: a^b = (a^(b/2)) * (a^(b/2))
    else
        return a * temp * temp;  // If b is odd: a^b = a * (a^(b/2)) * (a^(b/2))
}

int power() {
    int a, b;
    printf("Enter base (a) and exponent (b): ");
    scanf("%d %d", &a, &b);

    // Method 1: Using loop
    printf("Using Loop: %d^%d = %d\n", a, b, power_loop(a, b));

    // Method 2: Using recursion
    printf("Using Recursion: %d^%d = %d\n", a, b, power_recursive(a, b));

    // Method 3: Using logarithmic approach (divide and conquer)
    printf("Using Logarithmic: %d^%d = %d\n", a, b, power_logarithmic(a, b));

    return 0;
}

// TOWER OF HANOI
// You are given 3 rods: source, auxiliary, and destination.
// The goal is to move n disks from the source rod to the destination rod using the auxiliary rod, following the rules above.
// 1. Only one disk can be moved at a time.
// 2. Each move involves taking the top disk from one of the rods and placing it on another rod.
// 3. No disk may be placed on top of a smaller disk.
#include <stdio.h>

// Function to move disks from source to destination using auxiliary
void towerOfHanoi(int n, char source, char auxiliary, char destination) {
    // Base case: If only 1 disk, move it directly from source to destination
    if (n == 1) {
        printf("Move disk 1 from rod %c to rod %c\n", source, destination);
        return;
    }

    // Step 1: Move top n-1 disks from source to auxiliary
    towerOfHanoi(n - 1, source, destination, auxiliary);

    // Step 2: Move nth disk from source to destination
    printf("Move disk %d from rod %c to rod %c\n", n, source, destination);

    // Step 3: Move n-1 disks from auxiliary to destination
    towerOfHanoi(n - 1, auxiliary, source, destination);
}

int WAY() {
    int n;  // Number of disks
    printf("Enter the number of disks: ");
    scanf("%d", &n);

    // Call the towerOfHanoi function with n disks
    towerOfHanoi(n, 'A', 'B', 'C');  // A is the source, B is auxiliary, C is destination

    return 0;
}

int main(){
    // pascal(5);
    // ways();
    // power();
    WAY();
    return 0;
}