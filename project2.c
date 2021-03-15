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
int sorted[arrSize];  // will hold sorted array

 //2 for the sorting, and 1 for merging.
 #define NUM_THREADS	3
 void *sorter(void *arg); //Declare sorter function
 void *merger(void *arg); //Declare merger function
 void MergeSort(int begin, int end);
 void merge(int begin, int middle, int end);

struct sorterParams
{
	int begin;
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
	
	for(int i = 0; i < arrSize; i++)
	{
		printf("%d ", list[i]);
	}
	//time how long it takes.
	clock_t t1, t2; // Time the both thread 1 and 2.
	t1 = clock();
    
	pthread_t thread[NUM_THREADS];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
    
	int *threads1=(int*)malloc(sizeof(int)*2);
	int *threads2=(int*)malloc(sizeof(int)*2);
	int *threads3=(int*)malloc(sizeof(int)*1);
    
	pthread_t thread1[1];
	pthread_t thread2[1];
	pthread_t thread3[1];


	struct sorterParams args[2];
	args[0].begin = 0;
	args[0].end = arrSize / 2;

	args[1].begin = (arrSize / 2) + 1;
	args[1].end = arrSize - 1;

	//Create the threads for sorting.
	pthread_create(&thread1[1], &attr, sorter, &args[0]);
	pthread_create(&thread2[1], &attr, sorter, &args[1]);

	//Wait for the threads to finish.
	pthread_join(thread1[1],NULL);
	pthread_join(thread2[1],NULL);

	//create the thread for merger.
	struct mergerParams margs;
	margs.begin = 0;
	margs.middle = (arrSize / 2) + 1;
	margs.end = arrSize - 1;
	pthread_create(&thread3[1], &attr, merger, &margs);

	pthread_join(thread3[1], NULL);

	for(int i = 0; i < arrSize; i++)
	{
		printf("%d ", sorted[i]);
	}

    pthread_exit(NULL);
	return 0;
}

void *sorter(void *arg)
{
	struct sorterParams *params = (struct sorterParams*) arg;
	int begin = params->begin;
	int end = params-> end;

	int middle = begin + (end - begin) / 2;
	if (begin < end)
	{
    	MergeSort(begin, middle);
    	MergeSort(middle + 1, end);
    	merge(begin, middle, end);
	}
    
}

void MergeSort(int begin, int end)
{
	int middle = begin + (end - begin) / 2;

	if(begin < end)
	{
    	MergeSort(begin, middle);
    	MergeSort(middle + 1, end);
	}
}
/**
* Merge Thread
*/

void *merger(void *arg)
{
	struct mergerParams *params = (struct mergerParams*) arg;
	int begin = params->begin,
    	middle = params-> middle,
    	end = params-> end;

	if(begin < end)
	{
    	MergeSort(begin, middle);
    	MergeSort(middle + 1, end);
    	merge(begin, middle, end);
	}
    
}

void merge(int begin, int middle, int end)
{
	int *left = (int*)malloc(sizeof(int)*(middle - begin + 1));
	int *right = (int*)malloc(sizeof(int)*(end - middle));

	int arrsize1 = middle - begin - 1;
	int arrsize2 = end - middle;

	int i = 0, j = 0;

	for(i = 0; i < arrsize1; i++)
    	left[i] = list[i + begin];

	for(i = 0; i < arrsize2; i++)
    	right[i] = list[i + middle + 1];

	i = 0;
	int k = begin;

	while (i < arrsize1 && j < arrsize2)
	{
    	if(left[i] <= right[j])
        	list[begin++] = left[i++];
    	else
        	list[k++] = right[j++];
	}

	while(i < arrsize1)
	{
    	list[k++] = left[i++];
	}
	while(j < arrsize2)
	{
    	list[k++] = right[j++];
	}
}

void printArray(int arr[], int n)
{
	for(int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
}