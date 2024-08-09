#include <stdio.h>

int count, count2 = 0;  // Counters for heap operations

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to maintain the heap property
void heapify(int *heap, int n, int root) {
    int largest = root;  // Assume the root is the largest
    int left = 2 * root + 1;  // Left child index
    int right = 2 * root + 2;  // Right child index

    // If left child exists and is greater than root
    if (left < n) {
        count++;  // Increment operation counter
        if (heap[left] > heap[largest]) {
            largest = left;
        }
    }

    // If right child exists and is greater than largest so far
    if (right < n) {
        count++;  // Increment operation counter
        if (heap[right] > heap[largest]) {
            largest = right;
        }
    }

    // If largest is not root, swap and continue heapifying
    if (largest != root) {
        swap(&heap[root], &heap[largest]);
        heapify(heap, n, largest);  // Recursive call to heapify the affected subtree
    }
}

// Function to perform heap sort
void heapSort(int *heap, int n) {
    // Build max heap
    for (int i = (n / 2) - 1; i >= 0; i--) {
        heapify(heap, n, i);
    }
    
    count2 = count;  // Store count of operations for heap construction
    count = 0;  // Reset count for sorting phase

    // Extract elements from the heap one by one
    for (int i = n - 1; i >= 0; i--) {
        swap(&heap[0], &heap[i]);  // Move current root to end
        heapify(heap, i, 0);  // Heapify the reduced heap
    }
}

// Main function
int main() {
    int arr[100], n;
    printf("ENTER THE NUMBER OF ELEMENTS\n");
    scanf("%d", &n);

    printf("ENTER THE ELEMENTS OF THE ARRAY\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("THE ELEMENTS OF THE ARRAY BEFORE SORTING\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    heapSort(arr, n);  // Perform heap sort

    printf("THE ELEMENTS OF THE ARRAY AFTER SORTING\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
