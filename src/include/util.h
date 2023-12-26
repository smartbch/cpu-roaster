#ifndef UTIL_H
#define UTIL_H

#include <assert.h>
#include <stdint.h>

void expandRand64KB(uint8_t* in, int inSize, uint8_t* out);
void expandRand4KB(uint8_t* in, int inSize, uint8_t* out);

inline uint64_t mulxor(uint64_t a, uint64_t b) {
	uint64_t c = a * b;
	return (c + (a>>32)) ^ b;
}

struct Pair {
	uint64_t a;
	uint64_t b;
};
struct PairA: public Pair {// sort according to the value of a
	bool operator< (const PairA& other) {return a <other.a;}
	bool operator<=(const PairA& other) {return a<=other.a;}
	bool operator>=(const PairA& other) {return a>=other.a;}
	bool operator> (const PairA& other) {return a >other.a;}
	bool operator==(const PairA& other) {return a==other.a;}
	void mix(const PairA& other) {b^=other.b;}
	uint64_t v() {return b;}
};
struct PairB: public Pair {// sort according to the value of b
	bool operator< (const PairB& other) {return b <other.b;}
	bool operator<=(const PairB& other) {return b<=other.b;}
	bool operator>=(const PairB& other) {return b>=other.b;}
	bool operator> (const PairB& other) {return b >other.b;}
	bool operator==(const PairB& other) {return b==other.b;}
	void mix(const PairB& other) {a^=other.a;}
	uint64_t v() {return a;}
};
template <typename T>
inline void mixArray(T a[], int n) {
	for(int i=1; i<n; i++) {
		a[i].mix(a[i-1]);
	}
}

inline void fillPairArray(uint8_t* seedIn, int seedSize, Pair* arr, int n) {
	const int C=64*1024/8;
	uint64_t* randData=(uint64_t*)malloc(64*1024);
	assert(randData!=NULL);
	expandRand64KB(seedIn, seedSize, (uint8_t*)randData);
	int counter=0;
	for(int i=0; i<C; i++) {
		for(int j=0; j<C; j+=2) {
			if(j==i) continue;
			arr[counter].a=mulxor(randData[i],randData[j]);
			arr[counter].b=mulxor(randData[i],randData[j+1]);
			//printf("%d-%d: a:%016llx b:%016llx %016llx %016llx \n",i,j,
			//		arr[counter].a,arr[counter].b,
			//		randData[i],randData[j]);
			counter++;
			if(counter==n) {
				free(randData);
				return;
			}
		}
	}
	assert(false);
}

#endif
