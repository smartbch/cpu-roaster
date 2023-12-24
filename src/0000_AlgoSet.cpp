#include "Tracer.h"
using namespace std;

void run_HeapSort(uint8_t* seedIn, int seedSize);
void run_QuickSort(uint8_t* seedIn, int seedSize);
void run_MergeSort(uint8_t* seedIn, int seedSize); 
void run_PrioQueue(uint8_t* seedIn, int seedSize);
void run_FibonacciHeap(uint8_t* seedIn, int seedSize);
void run_Kruskal(uint8_t* seedIn, int seedSize);
void run_BinarySearch(uint8_t* seedIn, int seedSize);
void run_KthSmallest(uint8_t* seedIn, int seedSize);
void run_CuckooHash(uint8_t* seedIn, int seedSize);
void run_BloomFilter(uint8_t* seedIn, int seedSize);
void run_SuffixArray(uint8_t* seedIn, int seedSize);
void run_BinarySearchTree(uint8_t* seedIn, int seedSize);
void run_BTree(uint8_t* seedIn, int seedSize);
void run_RedBlackTree(uint8_t* seedIn, int seedSize);
void run_RerverPolishNotation(uint8_t* seedIn, int seedSize);

extern "C" void run_all(const char *data, size_t length, unsigned char *hash);

void run_all(const char *data, size_t length, unsigned char *hash) {
	Tracer::I()->clear();
	for(int i=0; i<length-8; i+=8) {
		uint64_t* d=(uint64_t*)(data+i);
		Tracer::I()->meet(*d);
	}
	uint8_t buf[64];
	for(int counter=0; counter<4; counter++) {
		uint8_t* seedIn;
		int seedSize;
		if(counter==0) {
			seedSize=length;
			seedIn=(uint8_t*)data;
		}
		else {
			seedSize=64;
			seedIn=buf;
			memcpy(seedIn,Tracer::I()->fnvHistory,64);
		}
		switch(Tracer::I()->historyCksum()%15) {
			case 0:
			run_HeapSort(seedIn, seedSize);
			break;
			case 1:
			run_QuickSort(seedIn, seedSize);
			break;
			case 2:
			run_MergeSort(seedIn, seedSize); 
			break;
			case 3:
			run_PrioQueue(seedIn, seedSize);
			break;
			case 4:
			run_FibonacciHeap(seedIn, seedSize);
			break;
			case 5:
			run_Kruskal(seedIn, seedSize);
			break;
			case 6:
			run_BinarySearch(seedIn, seedSize);
			break;
			case 7:
			run_KthSmallest(seedIn, seedSize);
			break;
			case 8:
			run_CuckooHash(seedIn, seedSize);
			break;
			case 9:
			run_BloomFilter(seedIn, seedSize);
			break;
			case 10:
			run_SuffixArray(seedIn, seedSize);
			break;
			case 11:
			run_BinarySearchTree(seedIn, seedSize);
			break;
			case 12:
			run_BTree(seedIn, seedSize);
			break;
			case 13:
			run_RedBlackTree(seedIn, seedSize);
			break;
			default:
			run_RerverPolishNotation(seedIn, seedSize);
			break;
		}
	}
	Tracer::I()->final_result(hash);
}
