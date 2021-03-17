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

//Max arraysize
#define arrSize 10
//Max number of threads
#define NUM_THREADS 3
//List for testing
int list[arrSize]={67,3,24,5,42,99,432,77,45,1};
//2 for the sorting, and 1 for merging.
void *sorter(void *arg); //Declare sorter function
void *merger(void *arg); //Declare merger function

int thread = 0;  // what thread number is active

//Struct for the parameters
struct Params
{
    int begin;
    int end;
};

int main(int argc, const char* argv[])
{
	printf("Current Array list: ");
	for(int i = 0; i < arrSize; i++)
	{
    	printf("%d ", list[i]);
	}
	printf("\n");

	pthread_t thread[NUM_THREADS];
    
    
	// Create sorting threads
	printf("Creating sorting threads...\n");
	//First thread for first half of list.
	struct Params sargs1;
	sargs1.begin=0;
	sargs1.end=(arrSize/2)-1;
	pthread_create(&thread[0], NULL, sorter, &sargs1);
	//Second thread for second half of list.
	struct Params sargs2;
	sargs2.begin=arrSize/2;
	sargs2.end=arrSize-1;
	pthread_create(&thread[1], NULL, sorter, &sargs2);

	//Wait for the threads to finish.
	pthread_join(thread[0],NULL);
	pthread_join(thread[1],NULL);

	//create the thread for merger.
	struct Params margs;
	margs.begin = 0;
	margs.end = arrSize / 2;

	printf("\nMerging thread...\n");
	printf("\n");
	pthread_create(&thread[2], NULL, merger, &margs);
	//Waits for the merging thread to finish
	pthread_join(thread[2], NULL);
    
	//Display the sorted list
	printf("Sorted List:\n");
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
	//To show what thread we are in.
	int threadNum = thread++;
	printf("\nSorting thread %d\n", threadNum);
	//Create the variables using struct.
	struct Params *p = (struct Params *) arg;
	int begin = p->begin;
	int end = p->end;
	//Bubble Sort
	int a,b,temp;
	for(a=begin; a<end; a++)
	{
    	    for(b=begin; b<end; b++)
    	    {
         	if(list[b]>list[b+1])
         	{
   			temp=list[b];
   			list[b]=list[b+1];
   			list[b+1]=temp;
         	}
    	    }
	}
	printf("What the list looks like: ");
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
	//Create the merger variables from passed parameters.
	struct Params *p = (struct Params*) arg;
	int begin = p->begin;
	int end = p->end+1;
   	 
	//Perform Bubble sort on the merged list.
	int a,b,temp;
	for(a=begin; a<end; a++)
	{
    	    for(b=begin; b<end; b++)
    	    {
         	if(list[b]>list[b+1])
         	{
   			temp=list[b];
   			list[b]=list[b+1];
   			list[b+1]=temp;
         	}
    	    }
	}
}





