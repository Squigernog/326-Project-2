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
void *sorter(void *arg); //Declare sorter function
void *merger(void *arg); //Declare merger function
void MergeSort(int list[], int begin, int end);
void merge(int begin, int middle, int end);

int thread = 0;  // what thread number is active

#define NUM_THREADS 3

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
    printf("\n");

	pthread_t thread[NUM_THREADS];
    
	// Create sorting threads
	printf("Creating sorting threads...\n");
	pthread_create(&thread[0], NULL, sorter, NULL);
	pthread_create(&thread[1], NULL, sorter, NULL);

	//Wait for the threads to finish.
	printf("Joining thread 0...\n");
	printf("\n");
	pthread_join(thread[0],NULL);
	pthread_join(thread[1],NULL);

	//create the thread for merger.
	struct mergerParams margs;
	margs.begin = 0;
	margs.middle = (arrSize / 2) + 1;
	margs.end = arrSize - 1;

	printf("Merging thread...\n");
	printf("\n");
	pthread_create(&thread[2], NULL, merger, &margs);

	pthread_join(thread[2], NULL);



	for(int i = 0; i < arrSize; i++)
	{
		printf("%d ", list[i]);
	}

	printf("\n");


	

    pthread_exit(NULL);
	return 0;
}

void mergeSort(int begin, int end)
{
	// calculate middle value
	int middle = (begin + end) / 2;
	
	if(begin < end)
	{
		mergeSort(begin, middle);

		mergeSort(middle + 1, end);

		merge(begin, middle, end);
	}
}

void *sorter(void *arg)
{
	int threadNum = thread++;
	printf("Sorting thread %d\n", threadNum);
	printf("\n");
	
	int begin = thread * (arrSize / 2);
	int end = (thread + 1) * (arrSize / 2) - 1;
	int middle = (begin + end) / 2;

	if(begin < end)
	{
		printf("sorting left");
		printf("\n");
		mergeSort(begin, middle);

		printf("sorting right\n");
		mergeSort(middle + 1, end);

		printf("merging \n");
		merge(begin, middle, end);
	}
	printf("Array in thread %d", threadNum);
	printf("\n");
    for(int i = 0; i < arrSize; i++)
	{
		printf("%d ", list[i]);
	}
	printf("\n");
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

	merge(begin, middle, end);
    
}

void merge(int begin, int middle, int end)
{

	int arrsize1 = middle - begin + 1;
	int arrsize2 = end - middle;
	int *left = malloc(arrsize1 * sizeof(int));
	int *right = malloc(arrsize2 * sizeof(int));
	int i = 0, j = 0;

	printf("Merging left");
	for(i = 0; i < arrsize1; i++)
    	left[i] = list[begin + i];

	printf("Merging right");
	for(i = 0; i < arrsize2; j++)
    	right[j] = list[middle + 1 + i];

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

	printf("dealloc\n");
	// deallocate memory for arrays
	free(left);
	free(right);
}