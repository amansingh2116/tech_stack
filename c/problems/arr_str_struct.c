#include<stdio.h>
#include<limits.h> // For INT_MIN

// Program to print second largest elemnt of an array
int secL() {
    int arr[] = {5, 2, 7, 8, 3}; // Sample array
    int n = sizeof(arr)/sizeof(arr[0]); // Calculate the size of the array

    // Finding the largest element
    int max = INT_MIN; // Initialize max to the smallest possible integer
    for(int i = 0; i < n; i++) {
        if (max < arr[i]) { // Update max if a larger value is found
            max = arr[i];
        }
    }
    printf("%d is the largest\n", max);

    // Finding the second largest element
    int smax = INT_MIN; // Initialize second max to the smallest possible integer
    for(int i = 0; i < n; i++) {
        if (arr[i] != max && smax < arr[i]) { // Ignore max and find the next largest
            smax = arr[i];
        }
    }
    if (smax == INT_MIN) {
        printf("No second largest element\n"); // In case all elements are the same
    } else {
        printf("%d is the second largest\n", smax);
    }
    // similarly minimum can also be found
    return 0;
}

// Program to check whether any of the digits in a number appears more than once
int repeat() {
    int seen[10] = {0};  // Array to keep track of digits (0-9)
    int N, rem;

    // Input the number
    printf("Enter a number: ");
    scanf("%d", &N);

    // Loop through each digit of the number
    while (N > 0) {
        rem = N % 10;  // Get the last digit
        if (seen[rem] == 1) {  // If digit is already seen
            printf("Digit %d appears more than once.\n", rem);
            return 0;
        }
        seen[rem] = 1;  // Mark digit as seen
        N = N / 10;  // Remove the last digit
    }

    printf("No digit appears more than once.\n");
    return 0;
}

// Program to reverse the array without using any extra array.
int reverse() {
    int arr[] = {5, 2, 7, 8, 3}; // Sample array
    int n = sizeof(arr)/sizeof(arr[0]); // Calculate number of elements in the array
    
    // Printing the array
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Reversing the array
    int i = 0;
    int j = n - 1;
    while (i < j) {
        // Swap arr[i] and arr[j]
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
    }

    // Printing the reversed array
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

// Program to calculate and print matrix C = A x B
#include <stdio.h>

int matrixmul() {
    int rowsA, colsA, rowsB, colsB;

    // Input dimensions of matrix A
    printf("Enter the number of rows and columns of matrix A: ");
    scanf("%d %d", &rowsA, &colsA);

    // Input dimensions of matrix B
    printf("Enter the number of rows and columns of matrix B: ");
    scanf("%d %d", &rowsB, &colsB);

    // Check if matrix multiplication is possible
    if (colsA != rowsB) {
        printf("Matrix multiplication not possible (columns of A must equal rows of B).\n");
        return -1;
    }

    // Declare matrices
    int A[rowsA][colsA];
    int B[rowsB][colsB];
    int C[rowsA][colsB]; // Result matrix will have dimensions rowsA x colsB

    // Input elements of matrix A
    printf("Enter elements of matrix A:\n");
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsA; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    // Input elements of matrix B
    printf("Enter elements of matrix B:\n");
    for (int i = 0; i < rowsB; i++) {
        for (int j = 0; j < colsB; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    // Initialize the result matrix C to 0
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            C[i][j] = 0;
        }
    }

    // Matrix multiplication logic
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            for (int k = 0; k < colsA; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // Output the result matrix C
    printf("Resultant Matrix C (%d x %d):\n", rowsA, colsB);
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}

// Program to reverse a string
#include <stdio.h>
#include <string.h>

int strreverse() {
    char p[20];
    char *s = "string";  // `s` points to the string "string\0"
    int length = strlen(s);  // Length of the string "string" is 6 (not 7)
    int i;

    // METHOD 1
    // Loop to copy elements from `s` to `p` in reverse order
    for (i = 0; i < length; i++)
        p[i] = s[length - i -1]; 
        // note that if yoy write length-i then first element in p would be the null character,
        // so print will ignore what is after it and nothing will be printed

    printf("%s", p);  // Print the result stored in `p`
    return 0;
}

// METHOD 2
void strrev(char *a){
    if(*a){
    foo(a+1);
    putchar(*a);
    }
}

int main(){
    // secL();
    // repeat();
    // reverse();
    // matrixmul();
    // strreverse();
    // char *s = "gitl";
    // strrev(s);
    return 0;
}