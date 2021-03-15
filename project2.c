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
 void MergeSort(int list[], int begin, int end);
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
	printf("\n");
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
		printf("%d ", list[i]);
	}
	printf("\n");
    pthread_exit(NULL);
	return 0;
}

void *sorter(void *arg)
{
	struct sorterParams *params = (struct sorterParams*) arg;
	int begin = params->begin;
	int end = params-> end;

	int i = begin, j, num;

	while(i <= end)
	{
		num = list[i];
		j = i - 1;
		while(j >= begin && num < list[j])
			list[j+1] = list[j--];
		
		list[j+1] = num;
		i++;
	}
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

	int i = begin, j = middle, k = begin;

	while (i < middle && j <= end)
	{
		if(list[i] < list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}

	while(i < middle)
		sorted[k++] = list[i++];

	while(j <= end)
		sorted[k++] = list[j++];
    
}

void merge(int begin, int middle, int end)
{
	

	int arrsize1 = middle - begin - 1;
	int arrsize2 = end - middle;
	int left[arrsize1];
	int right[arrsize2];
	int i = 0, j = 0;

	for(i = 0; i < arrsize1; i++)
    	left[i] = list[begin + i];

	for(i = 0; j < arrsize2; j++)
    	right[j] = list[middle + 1 + j];

	i = 0, j = 0;
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