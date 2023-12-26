#include <iostream>
#include <algorithm>
#include <stdint.h>
#include "include/util.h"
#include "include/tracer.h"

using namespace std;
 
#define N (210*1024)
#define ITER_COUNT (2000*1024)

static bool binarySearch(int32_t* array, int n, int32_t search, int32_t* value) {
	int first = 0;
	int last = n - 1;
	int middle = (first+last)/2;
	
	while (first <= last) {
		if (array[middle] < search)
			first = middle + 1;    
		else if (array[middle] == search) {
			*value=array[middle];
			//printf("%d found at location %d.\n", search, middle+1);
			break;
		}
		else {
			last = middle - 1;
		}
		middle = (first + last)/2;
		if(middle%128==0) Tracer::I()->meet(middle);
	}
	if (first > last) {
		*value=array[middle];
		return false;
	}
	else {
		return true;
	}
}

void run_BinarySearch(uint8_t* seedIn, int seedSize) {
	Pair* arr=new Pair[N/2+ITER_COUNT];
	int32_t* iarr=(int32_t*)arr;
	fillPairArray(seedIn, seedSize, arr, N/2+ITER_COUNT);
	sort(iarr, iarr+N);
	//for(int i=0; i<N; i++) {
	//	cout<<"sort "<<iarr[i]<<endl;
	//}
	Pair* startend = arr + N/2;
	for(int i=0; i<ITER_COUNT; i++) {
		int32_t start=startend[i].a%N;
		int32_t end=startend[i].b%N;
		if(start>end) {
			int32_t temp;
			temp=start; start=end; end=temp;
		}
		int32_t avg=(int64_t(iarr[start])+int64_t(iarr[end]))/2;
		int32_t nearest;
		bool found=binarySearch(iarr+start, end-start, avg, &nearest);
		if(found) {
			Tracer::I()->meet(avg);
			//cout<<"found "<<avg<<endl;
		}
		else {
			Tracer::I()->meet(~nearest);
			//cout<<"not found "<<avg<<" nearest "<<nearest<<endl;
		}
		found=binarySearch(iarr+start, end-start, avg/3, &nearest);
		if(found) {
			Tracer::I()->meet(avg);
			//cout<<"found "<<avg<<endl;
		}
		else {
			Tracer::I()->meet(~nearest);
			//cout<<"not found "<<avg<<" nearest "<<nearest<<endl;
		}
		found=binarySearch(iarr+start, end-start, avg/2, &nearest);
		if(found) {
			Tracer::I()->meet(avg);
			//cout<<"found "<<avg<<endl;
		}
		else {
			Tracer::I()->meet(~nearest);
			//cout<<"not found "<<avg<<" nearest "<<nearest<<endl;
		}
	}
	delete[] arr;
}

#ifdef SELF_TEST
int main() {
	char hello[100]="ae90--i888f--r39invqbj43to;5j46354q3499@#%@#$%^&$&ADGSGWREF";
	int len=strlen(hello);
	uint64_t firstRes[4];
	uint64_t otherRes[4];
	for(int i=0; i<50; i++) {
		Tracer::I()->clear();
		run_BinarySearch((uint8_t*)hello,len);
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
