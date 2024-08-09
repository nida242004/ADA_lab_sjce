#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count; // Global variable to count the number of comparisons

// Function to merge two sorted subarrays into one sorted array
void merge(int *arr, int beg, int mid, int end) {
    int n1 = mid - beg + 1; // Size of the first subarray
    int n2 = end - mid;     // Size of the second subarray

    // Create temporary arrays to hold the subarrays
    int *left = (int *)malloc(n1 * sizeof(int));
    int *right = (int *)malloc(n2 * sizeof(int));

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) {
        left[i] = arr[beg + i];
    }
    for (int j = 0; j < n2; j++) {
        right[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = beg;

    // Merge the two subarrays back into the original array
    while (i < n1 && j < n2) {
        count++; // Increment comparison count
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    // Copy remaining elements of left[], if any
    while (i < n1) {
        arr[k++] = left[i++];
    }

    // Copy remaining elements of right[], if any
    while (j < n2) {
        arr[k++] = right[j++];
    }
}

// Function to perform merge sort on the array
void mergesort(int *arr, int beg, int end) {
    if (beg < end) {
        int mid = beg + (end - beg) / 2;
        mergesort(arr, beg, mid);
        mergesort(arr, mid + 1, end);
        merge(arr, beg, mid, end);
    }
}

// Function to generate the worst-case scenario for merge sort
void generate_worst_case(int *arr, int beg, int end) {
    if (beg < end) {
        int mid = beg + (end - beg) / 2;
        int n1 = mid - beg + 1;
        int n2 = end - mid;

        // Temporary arrays for the worst-case generation
        int *a = (int *)malloc(n1 * sizeof(int));
        int *b = (int *)malloc(n2 * sizeof(int));
        
        // Splitting the array into odd and even indexed elements
        for (int i = 0; i < n1; i++) {
            a[i] = arr[2 * i];
        }
        for (int j = 0; j < n2; j++) {
            b[j] = arr[2 * j + 1];
        }

        generate_worst_case(a, beg, mid);
        generate_worst_case(b, mid + 1, end);

        // Combine the results back into the original array
        for (int i = 0; i < n1; i++) {
            arr[i] = a[i];
        }
        for (int j = 0; j < n2; j++) {
            arr[j + n1] = b[j];
        }
    }
}

int main() {
    int *arr, n;
    srand(time(NULL));

    // Open files for writing results
    FILE *f_best = fopen("MERGESORTBEST.txt", "a");
    FILE *f_worst = fopen("MERGESORTWORST.txt", "a");
    FILE *f_avg = fopen("MERGESORTAVG.txt", "a");
    FILE *f_worst_data = fopen("WORSTDATA.txt", "a");

    for (n = 2; n <= 1024; n *= 2) {
        arr = (int *)malloc(n * sizeof(int));

        // Initialize the array for best-case scenario
        for (int i = 0; i < n; i++) {
            arr[i] = i + 1;
        }

        // Best-case scenario
        count = 0;
        mergesort(arr, 0, n - 1);
        fprintf(f_best, "%d\t%d\n", n, count);

        // Worst-case scenario
        generate_worst_case(arr, 0, n - 1);
        for (int i = 0; i < n; i++) {
            fprintf(f_worst_data, "%d ", arr[i]);
        }
        fprintf(f_worst_data, "\n");

        count = 0;
        mergesort(arr, 0, n - 1);
        fprintf(f_worst, "%d\t%d\n", n, count);

        // Average-case scenario
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % n;
        }
        count = 0;
        mergesort(arr, 0, n - 1);
        fprintf(f_avg, "%d\t%d\n", n, count);

        free(arr);
    }

    // Close the files
    fclose(f_best);
    fclose(f_worst);
    fclose(f_avg);
    fclose(f_worst_data);

    printf("DATA IS ENTERED INTO FILE\n");

    return 0;
}
