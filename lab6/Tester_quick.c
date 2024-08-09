#include <stdio.h>
#include <stdlib.h>

int count; // Global variable to count comparisons

// Swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition the array and return the index of the pivot
int partition(int *arr, int beg, int end) {
    int pivot = arr[beg]; // Choose the first element as the pivot
    int i = beg + 1; // Start from the next element
    int j = end; // End from the last element

    while (i <= j) {
        // Increment i until finding an element greater than or equal to pivot
        while (i <= end && arr[i] < pivot) {
            count++; // Count comparison
            i++;
        }

        // Decrement j until finding an element less than or equal to pivot
        while (j >= beg && arr[j] > pivot) {
            count++; // Count comparison
            j--;
        }

        // Swap elements if needed
        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }

    // Place the pivot in the correct position
    swap(&arr[beg], &arr[j]);
    return j; // Return the pivot index
}

// Quick Sort function
void quicksort(int *arr, int beg, int end) {
    if (beg < end) {
        int split = partition(arr, beg, end); // Partition the array
        quicksort(arr, beg, split - 1); // Recursively sort the left subarray
        quicksort(arr, split + 1, end); // Recursively sort the right subarray
    }
}

int main() {
    int *arr, n;

    // Input the number of elements
    printf("ENTER THE NUMBER OF ELEMENTS\n");
    scanf("%d", &n);

    arr = (int *)malloc(sizeof(int) * n); // Allocate memory for the array

    // Input the elements of the array
    printf("ENTER THE ELEMENTS OF THE ARRAY\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Print elements before sorting
    printf("THE ELEMENTS OF THE ARRAY BEFORE SORTING\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    quicksort(arr, 0, n - 1); // Sort the array using quicksort

    // Print elements after sorting
    printf("THE ELEMENTS OF THE ARRAY AFTER SORTING\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr); // Free allocated memory
    return 0;
}
