#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<math.h>

int *arr, *arr1, *arr2, n;

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void bubble1()
{
    int size;
    if(n % 2 == 0)
        size = n/2;
    else
        size = n/2 + 1;

    for(int i = 0; i < size-1; i++)
    {
        for(int j = 0; j < size - i - 1; j++)
        {
            if(arr1[j] > arr1[j+1])
                swap(&arr1[j], &arr1[j+1]);
        }
    }
}

void bubble2()
{
    int size = n/2;
    for(int i = 0; i < size-1; i++)
    {
        for(int j = 0; j < size - i - 1; j++)
        {
            if(arr2[j] > arr2[j+1])
                swap(&arr2[j], &arr2[j+1]);
        }
    }
}

void *bubble_sort(void* param)
{
    bubble1();
}

void *bubble_sort1(void* param)
{
    bubble2();
}

void merge()
{
    int i = 0, j = 0, k = 0, n1,n2;
    if(n%2 == 0)
    {
        n1 = n/2; n2 = n/2;
    }
    else
    {
        n1 = n/2 + 1; n2 = n/2;
    }
    while (i<n1 && j <n2)
    {
        if (arr1[i] < arr2[j])
            arr[k++] = arr1[i++];
        else
            arr[k++] = arr2[j++];
    }
 
    while (i < n1)
        arr[k++] = arr1[i++];
 
    while (j < n2)
        arr[k++] = arr2[j++];
}

void *merge_call(void* param)
{
    merge();
}

void scan_arr()
{
    printf("Enter the list to be sorted\n");
    for(int i = 0; i < n; i++)
    {
        printf(">");
        scanf("%d", &arr[i]);
    }
}

void allocater()
{
    if(n%2 == 0)
    {
        arr = (int*)calloc(n, sizeof(int));
        arr1 = (int*)calloc(n/2, sizeof(int));
        arr2 = (int*)calloc(n/2, sizeof(int));

        scan_arr();
        for(int i = 0; i < n/2; i++)
            arr1[i] = arr[i];

        for(int i = n/2, j = 0; i < n; i++, j++)
            arr2[j] = arr[i];
    }
    else
    {
        arr = (int*)calloc(n, sizeof(int));
        arr1 = (int*)calloc(n/2 + 1, sizeof(int));
        arr2 = (int*)calloc(n/2, sizeof(int));

        scan_arr();
        for(int i = 0; i <= n/2 + 1; i++)
            arr1[i] = arr[i];

        for(int i = n/2 + 1, j = 0; i < n; i++, j++)
            arr2[j] = arr[i];
    }
}

void print_arr(int *array, int size)
{
    for(int i = 0; i < size; i++)
        printf("%d ", array[i]);
    
    printf("\n");
}

void main()
{
    printf("Enter the size of list: ");
    scanf("%d",&n);

    allocater();

    pthread_t thread_id1, thread_id2, thread_id3;
    pthread_create(&thread_id1, NULL, bubble_sort, NULL);
    pthread_create(&thread_id2, NULL, bubble_sort1, NULL);
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2,NULL);
    pthread_create(&thread_id3, NULL, merge_call, NULL);
    pthread_join(thread_id3, NULL);

    print_arr(arr, n);
}
