#include <stdio.h>
#include <omp.h>
#include <math.h>

int is_prime(int num)
{
    if (num <= 1)
    return 0;

    if (num == 2)
    return 1;

    if (num % 2 == 0)
    return 0;

    for (int i = 3; i <= sqrt(num); i += 2)
    {
        if (num % i == 0)
        return 0;
    }

    return 1;
}

int main()
{
    int n;

    printf("Enter the upper limit (n): ");
    scanf("%d", &n);

    if (n < 2)
    {
        printf("There are no prime numbers up to %d.\n", n);
        return 0;
    }

    /* Serial execution */
    double start = omp_get_wtime();
    int serial_count = 0;

    for (int i = 1; i <= n; i++)
    {
        if (is_prime(i))
    serial_count++;
    }

    double serial_time = omp_get_wtime() - start;
    printf("\nSerial: Found %d primes in %f seconds\n",
    serial_count, serial_time);

    /* Parallel execution */
    start = omp_get_wtime();
    int parallel_count = 0;

    #pragma omp parallel for reduction(+:parallel_count)
    for (int i = 1; i <= n; i++)
    {
        if (is_prime(i))

        parallel_count++;
    }

    double parallel_time = omp_get_wtime() - start;

    printf("Parallel:Found %d primes in %f seconds\n", parallel_count, parallel_time);

    if(parallel_time > 0)
        printf("Speedup = %.2fx\n", serial_time / parallel_time);
    return 0;
}