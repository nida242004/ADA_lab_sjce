#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count; // Global variable to count comparisons

void merge(int *arr, int beg, int mid, int end) {
    int n1 = mid - beg + 1;
    int n2 = end - mid;

    int *left = (int *)malloc(n1 * sizeof(int));
    int *right = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) {
        left[i] = arr[beg + i];
    }
    for (int j = 0; j < n2; j++) {
        right[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = beg;
    while (i < n1 && j < n2) {
        count++;
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    while (i < n1) {
        arr[k++] = left[i++];
    }
    while (j < n2) {
        arr[k++] = right[j++];
    }

    free(left);
    free(right);
}

void mergesort(int *arr, int beg, int end) {
    if (beg < end) {
        int mid = beg + (end - beg) / 2;

        mergesort(arr, beg, mid);
        mergesort(arr, mid + 1, end);
        merge(arr, beg, mid, end);
    }
}

void print_array(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int *arr, n;

    printf("ENTER THE NUMBER OF ELEMENTS\n");
    scanf("%d", &n);

    arr = (int *)malloc(n * sizeof(int));

    printf("ENTER THE ELEMENTS OF THE ARRAY\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("THE ELEMENTS OF THE ARRAY BEFORE SORTING\n");
    print_array(arr, n);

    mergesort(arr, 0, n - 1);

    printf("THE ELEMENTS OF THE ARRAY AFTER SORTING\n");
    print_array(arr, n);

    free(arr); // Free the allocated memory

    return 0;
}
