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
    int m = getMax(arr, n);  // find greatest value in array
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
void countSort(int arr[], int n, int exp)
{
    
}

void *merger(int arr1[], int arr2[])
{

}