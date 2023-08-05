#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <assert.h>
#include <math.h>

void merge(int A[], int low, int mid, int high)
{
    int i, j, k;
    int s = high + 1;
    int B[s];
    // printf("%d ",s);
    i = low;
    j = mid + 1;
    k = low;
    while (i <= mid && j <= high)
    {
        if (A[i] < A[j])
        {
            B[k] = A[i];
            k++;
            i++;
        }
        else
        {
            B[k] = A[j];
            k++;
            j++;
        }
    }
    while (i <= mid)
    {
        B[k] = A[i];
        k++;
        i++;
    }
    while (j <= high)
    {
        B[k] = A[j];
        k++;
        j++;
    }
    for (int i = low; i <= high; i++)
    {
        A[i] = B[i];
    }
}

void mergeSort(int A[], int low, int high)
{
    int mid;
    if (low < high)
    {
        mid = (low + high) / 2;
        mergeSort(A, low, mid);
        mergeSort(A, mid + 1, high);
        merge(A, low, mid, high);
    }
}

double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size)
{
    int new_size = nums1Size + nums2Size;
    int A[new_size];
    int k = 0;
    for (int i = 0; i < nums1Size; i++)
    {
        A[k] = nums1[i];
        k++;
    }
    for (int i = 0; i < nums2Size; i++)
    {
        A[k] = nums2[i];
        k++;
    }
    // printArray(A, new_size);
    mergeSort(A, 0, new_size - 1);
    // printArray(A, new_size);
    float median = 0.0;
    int a = new_size / 2;
    if (new_size % 2 == 0)
    {
        // printf("%d ", a);
        median = floor(A[a] + A[a - 1]) / 2;
    }
    else
    {
        median = A[a];
    }
    return median;
}

int main(void)
{
    int nums1[] = {1, 2, 3, 4, 5};
    int nums2[] = {6, 7, 8, 9, 10};

    double val = findMedianSortedArrays(nums1, 5, nums2, 4);

    int size = sizeof(nums1) / sizeof(nums1[0]) + sizeof(nums2) / sizeof(nums2[0]);

    printf("%f\n", val);

    return 0;
}