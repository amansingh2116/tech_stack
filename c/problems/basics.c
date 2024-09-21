#include <stdio.h>

// Program to print volume of a sphere with given radius
int volume(){
    float r = 5;
    printf("The volume of sphere with radius %f is %f", r, 4*(3.14)*r*r*r/3); 
    // 4/3 will not work
    return 0;
}

// Program to add two numbers without using + operator
int add() {
    int x, y;
    printf("Enter the two numbers you want to add: ");
    scanf("%d %d", &x, &y);  // Input two numbers
    
    // METHOD 1
    if (y > 0) {
        while (y != 0) {
            x++;  // Increment x
            y--;  // Decrement y
        }
    }
    else if (y < 0) {
        while (y != 0) {
            x--;  // Decrement x
            y++;  // Increment y
        }
    }

    printf("Sum of two values is %d\n", x);  // Output the result

    // METHOD 2
    int sum, carry, a, b;
    printf("Enter the two numbers: ");
    scanf("%d %d", &a, &b);  // Input two numbers

    while (b != 0) {
        sum = a ^ b;         // Bitwise XOR adds without carrying
        carry = (a & b) << 1; // Bitwise AND and left shift to calculate carry
        a = sum;             // Update a with the sum
        b = carry;           // Update b with the carry
    }

    printf("Sum of two numbers is: %d", sum);  // Output the sum

    return 0;
}


// Program to calculate simple interest
int interest(){
    float p, r, t, si;
    printf("Enter Principle:");
    scanf("%f", &p);
    // & gives address and thus with scanf specifies the location where the input is to be stored
    printf("Enter Rate:");
    scanf("%f", &r);
    printf("Enter Time:");
    scanf("%f", &t);

    si = (p*r*t)/100;
    printf("Simple Interest is : %f", si);

    return 0;
}

// Program to calculate fractional part of a number
int fractional_part(){
    float num;
    printf("Enter number :");
    scanf("%f", &num);
    int z = num >= 0 ? num : num - 1; // calculate GIF of num
    printf("The fractional part of %f is %f", num, num - z); // frac = num - gif
    return 0;
}

// Program to print reverse of a given number
int reverse(){
    int num, j, reverse = 0;
    printf("Enter number: ");
    scanf("%d", &num);
    while(num>0){
        reverse = reverse*10; // order matters
        reverse = reverse + num%10; // %10 gives last digit
        num = num/10; // /10 removes last digit
    }
    printf("The reversed number is %d", reverse);
    return 0;
}

//Program to print nth fibonacci number
int fibonacci(){
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    int f0 =1, f1 = 1, f2;
    for(int i=1; i<=n-2; i++){
        f2 = f0 + f1;
        f0 = f1;
        f1 = f2;
    }
    printf("Nth fiboncci number is %d", f2);
    return 0;
}

// For pattern printing question, find the pattern using observation, explain that mathematically, code it, use nested loops.
// Program to print following pattern given number of lines
//     1
//    AB
//   123
//  ABCD
// 12345

int pattern() {
    int n;
    printf("Enter side of square: ");
    scanf("%d", &n);  // Input for the number of rows (or side length)

    // METHOD 1
    // Nested loops for the pattern
    for (int i = 1; i <= n; i++) {  // Rows
        // Print spaces
        for (int j = 1; j <= n - i; j++) {
            printf("  ");
        }
        // Print stars
        for (int k = 1; k <= i; k++) {
            if(i%2==0) printf("%c ", k+64);
            else printf("%d ", k);
        }
        // Move to the next line
        printf("\n");
    }

    // METHOD 2
    for (int i = 1; i <= n; i++) {  // Rows
        for (int j = 1; j <= n; j++) { // Columns
            if((i+j) >= n+1){
                if(i%2==0) printf("%c ", j-(n-i)+64);
                else printf("%d ", j-(n-i));
            }
            else printf("  ");
        }
        printf("\n");
        }
        return 0;
    }


int main(){
    // volume();
    // add();
    // interest();
    // fractional_part();
    // reverse();
    // fibonacci();
    // pattern();
    return 0;
}