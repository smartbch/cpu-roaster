#include "include/tracer.h"
using namespace std;

const int64_t MIN_SAFE_INTEGER = -9007199254740991;
const int64_t MAX_SAFE_INTEGER = 9007199254740991;

void run_HeapSort(uint8_t* seedIn, int seedSize);
void run_QuickSort(uint8_t* seedIn, int seedSize);
void run_MergeSort(uint8_t* seedIn, int seedSize); 
void run_PrioQueue(uint8_t* seedIn, int seedSize);
void run_FibonacciHeap(uint8_t* seedIn, int seedSize);
void run_Kruskal(uint8_t* seedIn, int seedSize);
void run_BinarySearch(uint8_t* seedIn, int seedSize);
void run_BloomFilter(uint8_t* seedIn, int seedSize);
void run_SuffixArray(uint8_t* seedIn, int seedSize);
void run_BinarySearchTree(uint8_t* seedIn, int seedSize);
void run_RedBlackTree(uint8_t* seedIn, int seedSize);

// extern "C" int64_t cpu_roaster_pow(uint32_t d0, uint32_t d1, uint32_t d2, uint32_t d3, uint32_t d4, uint32_t d5, uint32_t d6, uint32_t d7, const uint64_t difficulty, const int64_t nonce_start, const int64_t nonce_step);
// extern "C" void cpu_roaster_hash(uint8_t *data, size_t length, unsigned char *hash);

extern "C" {

void cpu_roaster_hash(uint8_t *data, size_t length, unsigned char *hash) {
	Tracer::I()->clear();
	for(int i=0; i<length-8; i+=8) {
		uint64_t* d=(uint64_t*)(data+i);
		Tracer::I()->meet(*d);
	}
	run_QuickSort(data, length);
	const size_t seedSize = 64;
	uint8_t seedIn[seedSize];
	for(int counter=1; counter<4; counter++) {
		memcpy(seedIn, Tracer::I()->fnvHistory, seedSize);
		uint64_t cksum = Tracer::I()->historyCksum();
		uint64_t sel = cksum%11;
		//printf("HashC %d cksum %016llx sel %lld\n", counter, cksum, sel);
		switch(sel) {
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
			run_BloomFilter(seedIn, seedSize);
			break;
			case 8:
			run_SuffixArray(seedIn, seedSize);
			break;
			case 9:
			run_BinarySearchTree(seedIn, seedSize);
			break;
			default:
			run_RedBlackTree(seedIn, seedSize);
			break;
		}
	}
	Tracer::I()->final_result(hash);
}

int64_t cpu_roaster_pow(uint32_t d0, uint32_t d1, uint32_t d2, uint32_t d3, uint32_t d4, uint32_t d5, uint32_t d6, uint32_t d7, const uint64_t difficulty, const int64_t nonce_start, const int64_t nonce_stop, const int64_t nonce_step) {
	uint8_t data[40];
	data[0*4+0] = uint8_t(d0 >> 0);
	data[0*4+1] = uint8_t(d0 >> 8);
	data[0*4+2] = uint8_t(d0 >>16);
	data[0*4+3] = uint8_t(d0 >>24);
	data[1*4+0] = uint8_t(d1 >> 0);
	data[1*4+1] = uint8_t(d1 >> 8);
	data[1*4+2] = uint8_t(d1 >>16);
	data[1*4+3] = uint8_t(d1 >>24);
	data[2*4+0] = uint8_t(d2 >> 0);
	data[2*4+1] = uint8_t(d2 >> 8);
	data[2*4+2] = uint8_t(d2 >>16);
	data[2*4+3] = uint8_t(d2 >>24);
	data[3*4+0] = uint8_t(d3 >> 0);
	data[3*4+1] = uint8_t(d3 >> 8);
	data[3*4+2] = uint8_t(d3 >>16);
	data[3*4+3] = uint8_t(d3 >>24);
	data[4*4+0] = uint8_t(d4 >> 0);
	data[4*4+1] = uint8_t(d4 >> 8);
	data[4*4+2] = uint8_t(d4 >>16);
	data[4*4+3] = uint8_t(d4 >>24);
	data[5*4+0] = uint8_t(d5 >> 0);
	data[5*4+1] = uint8_t(d5 >> 8);
	data[5*4+2] = uint8_t(d5 >>16);
	data[5*4+3] = uint8_t(d5 >>24);
	data[6*4+0] = uint8_t(d6 >> 0);
	data[6*4+1] = uint8_t(d6 >> 8);
	data[6*4+2] = uint8_t(d6 >>16);
	data[6*4+3] = uint8_t(d6 >>24);
	data[7*4+0] = uint8_t(d7 >> 0);
	data[7*4+1] = uint8_t(d7 >> 8);
	data[7*4+2] = uint8_t(d7 >>16);
	data[7*4+3] = uint8_t(d7 >>24);

	int64_t nonce=0, counter=0;
	assert(nonce_start >= MIN_SAFE_INTEGER);
	assert(nonce_stop < MAX_SAFE_INTEGER);
	for(nonce = nonce_start; nonce < nonce_stop; nonce += nonce_step) {
		uint64_t n = static_cast<uint64_t>(nonce);
		data[32] = uint8_t(n >>  0);
		data[33] = uint8_t(n >>  8);
		data[34] = uint8_t(n >> 16);
		data[35] = uint8_t(n >> 24);
		data[36] = uint8_t(n >> 32);
		data[37] = uint8_t(n >> 40);
		data[38] = uint8_t(n >> 48);
		data[39] = uint8_t(n >> 56);
		unsigned char hash[32];
		cpu_roaster_hash(data, 40, hash);
		uint64_t m = 0;
		for(int i=0; i<8; i++) {
			m = (m<<8)|uint64_t(hash[i]);
		}
#ifdef POW_TESTER
		printf("counter %lld nonce: %016llx m: %016llx\n", counter++, nonce, m);
#endif
		if(m <= difficulty) {
			return nonce;
		}
	}
	return MAX_SAFE_INTEGER;
}

} // end of extern "C"

#ifdef TOP_TESTER
int main() {
	char hello[100]="ae90..i..8f--r39invqbj43to;5J46354Q3499@#%@#$%^&$&ADGSGWREF";
	int len=strlen(hello);
	uint64_t firstRes[4];
	uint64_t otherRes[4];
	for(int j=1; j<256; j++) {
		printf("Now %d\n", j);
		hello[0] = char(j);
		for(int i=0; i<5; i++) {
			if(i==0) {
				cpu_roaster_hash((uint8_t*)hello, len, (unsigned char*)firstRes);
			} else {
				cpu_roaster_hash((uint8_t*)hello, len, (unsigned char*)otherRes);
				for(int i=0; i<4; i++) {
					//printf("H %016llx %016llx\n", firstRes[i], otherRes[i]);
					assert(firstRes[i]==otherRes[i]);
				}
			}
		}
	}
	return 0;
}
#endif

#ifdef POW_TESTER
int main() {
	const uint64_t MAX = uint64_t(-1);
	uint64_t difficulty = MAX/20;
	int64_t nonce = cpu_roaster_pow(0, 1, 2, 3, 4, 5, 6, 7, difficulty, 0, 1000);
	printf("nonce: %016llx difficulty: %016llx\n", nonce, difficulty);
	return 0;
}
#endif
