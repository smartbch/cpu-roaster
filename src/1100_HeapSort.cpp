#include <iostream>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "include/util.h"
#include "include/tracer.h"
 
#define N (2*1024*1024)
#define ITER_COUNT 1
//#define N 480
//#define ITER_COUNT 4

using namespace std;

// A function to heapify the array.
template <typename T>
static void maxHeapify(T a[], int i, int n)
{
	int j;
	T temp;
	temp = a[i];
	j = 2*i;
 
 	while (j <= n)
	{
		if (j < n && a[j+1] > a[j])
		j = j+1;
		// Break if parent value is already greater than child value.
		if (temp > a[j])
			break;
		// Switching value with the parent node if temp < a[j].
		else if (temp <= a[j])
		{
			a[j/2] = a[j];
			if(a[j].a%128==0) Tracer::I()->meet(a[j].v());
			j = 2*j;
		}
	}
	a[j/2] = temp;
	return;
}

template <typename T>
static void heapSortCore(T a[], int n)
{
	int i;
	T temp;
	for (i = n; i >= 2; i--)
	{
		// Storing maximum value at the end.
		temp = a[i];
		a[i] = a[1];
		a[1] = temp;
		// Building max heap of remaining element.
		maxHeapify(a, 1, i - 1);
	}
}

template <typename T>
static void buildMaxHeap(T a[], int n)
{
	int i;
	for(i = n/2; i >= 1; i--)
		maxHeapify(a, i, n);
}

template <typename T>
static void heapSort(T arr[], int n) {
	buildMaxHeap<T>(arr, n-1);
	heapSortCore<T>(arr, n-1);
}

void run_HeapSort(uint8_t* seedIn, int seedSize) {
	Pair* arr=(Pair*)malloc(N*sizeof(Pair));
	assert(arr!=NULL);
	PairA* arrA=(PairA*)arr;
	PairB* arrB=(PairB*)arr;
	fillPairArray(seedIn, seedSize, arr, N);
	//for(int j=0; j<N; j++) printf("init %d: %016llx %016llx\n",j,arr[j].a,arr[j].b);
	for(int i=0; i<ITER_COUNT; i++) {
		if(i!=0) mixArray<PairB>(arrB, N);
		heapSort<PairA>(arrA, N);
		mixArray<PairA>(arrA, N);
		//for(int j=0; j<N; j++) printf("%d-%d: %016llx %016llx\n",i,j,arr[j].a,arr[j].b);
		heapSort<PairB>(arrB, N);
		//for(int j=0; j<N; j++) printf("%d-%d: %016llx %016llx\n",i,j,arr[j].a,arr[j].b);
	}
	free(arr);
}

#undef N
#undef ITER_COUNT

#ifdef SELF_TEST
int main() {
	char hello[100]="aer39invqbj43to;5j46354q34534999!@#%@#$%^&$&ADGSGWREF";
	int len=strlen(hello);
	uint64_t firstRes[4];
	uint64_t otherRes[4];
	for(int i=0; i<50; i++) {
		Tracer::I()->clear();
		run_HeapSort((uint8_t*)hello,len);
		if(i==0) {
			Tracer::I()->final_result((unsigned char*)firstRes);
		} else {
			Tracer::I()->final_result((unsigned char*)otherRes);
			for(int i=0; i<4; i++) {
				//printf("H %016llx %016llx\n", firstRes[i], otherRes[i]);
				assert(firstRes[i]==otherRes[i]);
			}
		}
	}
	return 0;
}
#endif
