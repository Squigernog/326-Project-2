#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/**
 * CECS 326 Project 2
 * The purpose of this program is to use 2 pthreads to sort one array in two parts and merge those two arrays into one sorted array.
 * @author Luke Olsen
 * @author Nicholas Wong
 * @version 0.1
 * @date 3/14/2021
 */

int main(int argc, const char* argv[])
{

}

/**
 * A sorter that implements the use of radix sort
 * @param arr An array of integers
 * @param n Size of the array
 */
void *sorter(int *arr[], int n)
{
    //TODO implement pthreads
    int m = getMax(arr, n);  // find greatest value in array

    for(int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

/**
 * return max integer value in an array
 * @param arr Array to be analyzed for max int value
 * @param n size of array
 * @return max int value in array
 */
int getMax(int arr[], int n)
{
    int max = arr[0];
    for(int i = 1; i < n; i++)
        if(arr[i] > max)
            max = arr[i];
    return max;
}

/**
 * CountSort algorithm for an integer array
 * @param arr array to be sorted
 * @param n size of array
 * @param exp digit required for CountSort
 */
void countSort(int *arr[], int n, int exp)
{
    int output[n];  // output array
    int i, count[10] = {0};

    for(i = 0; i < n; i++)
        count[(*arr[i] / exp) % 10]++;

    for(i = 1; i < 10; i++)
        count[i] += count[i-1];

    for(i = n - 1; i >= 0; i--)
    {
        output[count[(*arr[i] / exp) % 10] - 1] = arr[i];
        count[(*arr[i] / exp) % 10]--;
    }

    // copy from output to arr
    for(i = 0; i < n; i++)
        *arr[i] = output[i]
}

void *merger(int arr1[], int arr2[])
{

}