#include<stdio.h>
#include<omp.h>

int main()
{
    int n;
    printf("Enter the number of iterations: ");
    scanf("%d", &n);

    for(int i=0; i < n; i++)
    {
        printf("Thread %d: Iteration %d\n",
            omp_get_thread_num(),i);
    }
    return 0;
}