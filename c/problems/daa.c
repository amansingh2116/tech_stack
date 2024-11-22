#include <stdio.h>

// Sorting

// swap two integers
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Bubble sort function that takes an array and its length
void bubble_sort(int a[], int len_a) {
    for (int i = 0; i < len_a - 1; i++) {
        for (int j = 0; j < len_a - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(&a[j], &a[j + 1]);
            }
        }
    }
    printf("Sorted array: ");
    for (int i = 0; i < len_a; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// Insertion sort function that takes an array and its length
void insertion_sort(int a[], int len_a) {
    for (int i = 1; i < len_a; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
    printf("Sorted array: ");
    for (int i = 0; i < len_a; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// Selection sort function that takes an array and its length
void selection_sort(int a[], int len_a) {
    for (int i = 0; i < len_a - 1; i++) {
        int min = i;
        for (int j = i + 1; j < len_a; j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }
        if (min != i) {
            swap(&a[min], &a[i]);
        }
    }
    printf("Sorted array: ");
    for (int i = 0; i < len_a; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// merge sort
// quick sort (time complexity)
// kth order statistic
// kth smallest/largest element

int main() {
    int a[] = {5, 1, 4, 2, 8};
    int len_a = sizeof(a) / sizeof(a[0]);

    bubble_sort(a, len_a);
    insertion_sort(a, len_a);
    selection_sort(a, len_a);
    return 0;
    
}
