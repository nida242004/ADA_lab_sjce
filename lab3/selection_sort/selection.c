#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count;

void selectionsort(int *a, int n)
{
    int i, j, min, t;
    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            if (a[j] < a[min]) // Using a[j] notation
                min = j;
            count++;
        }

        if (min != i)
        {
            t = a[min];
            a[min] = a[i];
            a[i] = t;
        }
    }
}

void tester()
{
    int *arr, n;
    printf("ENTER THE NUMBER OF ELEMENTS\n");
    scanf("%d", &n);

    arr = (int *)malloc(sizeof(int) * n);
    printf("ENTER THE ELEMENTS OF THE ARRAY\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("THE ELEMENTS OF THE ARRAY BEFORE SORTING\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    selectionsort(arr, n);

    printf("THE ELEMENTS OF THE ARRAY AFTER SORTING\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    free(arr);
}

void plotter()
{
    FILE *f;
    f = fopen("selectionsort.txt", "a");
    int n = 10;
    while (n <= 30000)
    {
        int *a = (int *)malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++)
        {
            a[i] = i; // Using a[i] notation
        }
        count = 0;
        selectionsort(a, n);
        fprintf(f, "%d\t%d\n", n, count);
        printf("%d\t%d\n", n, count);
        if (n < 10000)
            n *= 10;
        else
            n += 10000;

        free(a); // Free the memory after use
    }
    fclose(f); // Close the file after writing
}

int main()
{
    for (;;)
    {
        int key;
        printf("ENTER THE CHOICE \n1.TO TEST \n2.TO PLOT\n0  TO EXIT\n"); 
        scanf("%d", &key); 
        switch (key) 
        {
            case 1:
                tester();
                break;
            case 2:
                plotter();
                break;
            case 0:
                exit(0); // Exit with 0 for normal termination
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
