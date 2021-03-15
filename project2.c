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
 
 //List for testing
int list[10]={67,3,24,5,2,99,432,77,45,1};

 //2 for the sorting, and 1 for merging.
 #define NUM_THREADS 3

 
int main(int argc, const char* argv[])
{
    //time how long it takes.
    clock_t t1, t2; // Time the both thread 1 and 2.
    //determine the size of the list.
    int size = sizeof(list)/sizeof(int);
    int arrsize1;
    int arrsize2;
    
    
    //check if the array size is even.
    //if not then add 1 more to the first array.
    if(size%2 == 0){
   	    arrsize1=size/2;
   	    arrsize2=size/2;
    }
    else
    {
   	    arrsize1=(size/2) + 1;
   	    arrsize2=size/2;
    }
    pthread_t thread[NUM_THREADS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    //Create the threads for sorting.
    pthread_create(&thread[0], &attr, countSort,(void*)NULL);
    pthread_create(&thread[1], &attr, countSort,(void*)NULL);
    
    //Wait for the threads to finish.
    pthread_join(thread[0],NULL);
    pthread_join(thread[1],NULL);
    
    
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
  	  	*arr[i] = output[i];
}

/**
* Merge Thread
*/

void *merger(int arr1[], int arr2[])
{

}
