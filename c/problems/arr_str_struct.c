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

int main() {
    char arr[] = {'r', 'a', 'g', '\0', 'a', 'v'};  // Character array with manual null terminator
    // int n = sizeof(arr) / sizeof(arr[0]);
    int n = sizeof(arr) / sizeof(arr[0]); 
    printf("%c ", arr[0]);  // Print first character 'r'
    printf("%s ", arr);     // Print the string from arr, up to the null terminator
    printf("%d", n);  // Print the length of the array (size)
    printf("\n");
    
    return 0;
}

// int main(){
//     // secL();
//     // reverse();
//     matrixmul();
//     return 0;
// }