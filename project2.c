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

#define arrSize 10
 //List for testing
int list[arrSize]={67,3,24,5,2,99,432,77,45,1};

 //2 for the sorting, and 1 for merging.
 #define NUM_THREADS 3

struct sortParams
{
	int start;
	int end;
};

struct mergerParams
{
	int begin;
	int middle;
	int end;
};

int main(int argc, const char* argv[])
{
    //time how long it takes.
    clock_t t1, t2; // Time the both thread 1 and 2.
    
	t1 = clock();
    pthread_t thread[NUM_THREADS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

	struct sortParams args[2];
	args[0].start = 0;
	args[0].end = arrSize / 2;

	args[1].start = (arrSize / 2) + 1;
	args[1].end = arrSize;

    //Create the threads for sorting.
    pthread_create(&thread[0], &attr, sorter, &args[0]);
    pthread_create(&thread[1], &attr, sorter, &args[1]);

    //Wait for the threads to finish.
    pthread_join(thread[0],NULL);
    pthread_join(thread[1],NULL);
    
}

void* sorter(void* arg)
{
	
}

/**
 * Merge Sort algorithm
 * @param begin Starting index
 * @param end last index
 */
void MergeSort(int begin, int end)
{
	int middle = end / 2;  // middle point of array

	MergeSort(begin, middle);  // sort left half
	MergeSort(middle + 1, end);  // sort right half
}

/**
* Merge Thread
*/

void *merger(void* args)
{
	struct mergerParams *params = (struct mergerParmas*) args;
	int begin = params->begin,
		middle = params-> middle,
		end = params-> end;

	for(int i = 0; i < middle; i++)
	{
		
	}
}
