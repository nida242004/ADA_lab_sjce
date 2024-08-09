#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count; // Global variable to count comparisons

// Swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition the array and return the pivot index
int partition(int *arr, int beg, int end) {
    int pivot = arr[beg]; // Choose the first element as the pivot
    int i = beg + 1;
    int j = end;

    while (i <= j) {
        // Increment i until finding an element greater than or equal to pivot
        while (i <= end && arr[i] < pivot) {
            count++;
            i++;
        }

        // Decrement j until finding an element less than or equal to pivot
        while (arr[j] > pivot) {
            count++;
            j--;
        }

        // Swap elements if needed
        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }

    // Place the pivot in its correct position
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
    srand(time(NULL)); // Seed the random number generator

    // Open files for writing results
    FILE *f1 = fopen("QUICKBEST.txt", "a");
    FILE *f2 = fopen("QUICKWORST.txt", "a");
    FILE *f3 = fopen("QUICKAVG.txt", "a");

    int n = 4; // Start with 4 elements
    while (n <= 1024) {
        int *arr = (int *)malloc(sizeof(int) * n); // Allocate memory for the array

        // Best case: all elements are the same
        for (int i = 0; i < n; i++) {
            arr[i] = 5;
        }
        count = 0;
        quicksort(arr, 0, n - 1);
        fprintf(f1, "%d\t%d\n", n, count);

        // Worst case: sorted array
        for (int i = 0; i < n; i++) {
            arr[i] = i + 1;
        }
        count = 0;
        quicksort(arr, 0, n - 1);
        fprintf(f2, "%d\t%d\n", n, count);

        // Average case: random elements
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % n;
        }
        count = 0;
        quicksort(arr, 0, n - 1);
        fprintf(f3, "%d\t%d\n", n, count);

        free(arr); // Free allocated memory
        n *= 2; // Double the number of elements for the next iteration
    }

    // Close files
    fclose(f1);
    fclose(f2);
    fclose(f3);

    printf("Data has been written to files.\n");
    return 0;
}
