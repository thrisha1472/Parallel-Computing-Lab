#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 100000

// Merge two sorted parts
void merge(int a[], int low, int mid, int high)
{
    int i = low, j = mid + 1, k = 0;
    int temp[N];

    while (i <= mid && j <= high)
    {
        if (a[i] < a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= mid)
        temp[k++] = a[i++];

    while (j <= high)
        temp[k++] = a[j++];

    for (i = low, k = 0; i <= high; i++, k++)
        a[i] = temp[k];
}

// Sequential merge sort
void mergeSort(int a[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;

        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);

        merge(a, low, mid, high);
    }
}

// Parallel merge sort
void parallelMergeSort(int a[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergeSort(a, low, mid);
            }

            #pragma omp section
            {
                mergeSort(a, mid + 1, high);
            }
        }

        merge(a, low, mid, high);
    }
}

int main()
{
    int a[N], b[N];
    double start, end;
    double sequentialTime, parallelTime;

    // Generate random numbers
    for (int i = 0; i < N; i++)
    {
        a[i] = rand() % 100000;
        b[i] = a[i];
    }

    // Sequential Merge Sort
    start = omp_get_wtime();

    mergeSort(a, 0, N - 1);

    end = omp_get_wtime();
    sequentialTime = end - start;

    // Parallel Merge Sort
    start = omp_get_wtime();

    parallelMergeSort(b, 0, N - 1);

    end = omp_get_wtime();
    parallelTime = end - start;

    // Display results
    printf("Number of elements = %d\n", N);

    printf("\nSequential Merge Sort Time = %f seconds",
           sequentialTime);

    printf("\nParallel Merge Sort Time = %f seconds",
           parallelTime);

    printf("\nTime Difference = %f seconds\n",
           sequentialTime - parallelTime);

    return 0;
}