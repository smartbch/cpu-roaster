#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "util.h"
#include "Tracer.h"
 

#define N (1*1024*1024)
#define ITER_COUNT 1
//#define N 480
//#define ITER_COUNT 4

using namespace std;

//template <typename Key>
//void printrange(Key* xs, int l, int u) {
//    printf("xs[%d, %d) = ", l, u);
//    for (; l < u; ++l)
//        printf( l == u - 1 ? "%d\n" : "%d, ", xs[l]);
//}

template <typename Key>
void swap(Key* xs, int i, int j) {
    Key tmp = xs[i]; xs[i] = xs[j]; xs[j] = tmp;
    if(tmp.a%1000==0) Tracer::I()->meet(tmp.v());
}

template <typename Key>
void wmerge(Key* xs, int i, int m, int j, int n, int w) {
    while (i < m && j < n)
        swap(xs, w++, xs[i] < xs[j] ? i++ : j++);
    while (i < m)
        swap(xs, w++, i++);
    while (j < n)
        swap(xs, w++, j++);
}

template <typename Key>
void imsort(Key* xs, int l, int u);

template <typename Key>
void wsort(Key* xs, int l, int u, int w) {
    int m;
    if (u - l > 1) {
        m = l + (u - l) / 2;
        imsort(xs, l, m);
        imsort(xs, m, u);
        wmerge(xs, l, m, m, u, w);
    }
    else
        while (l < u)
            swap(xs, l++, w++);
}

template <typename Key>
void imsort(Key* xs, int l, int u) {
    int m, n, w;
    if (u - l > 1) {
        m = l + (u - l) / 2;
        w = l + u - m;
        wsort(xs, l, m, w); /* the last half contains sorted elements */
        while (w - l > 2) {
            n = w;
            w = l + (n - l + 1) / 2;
            wsort(xs, w, n, l);  /* the first half of the previous working area contains sorted elements */
            wmerge(xs, l, l + n - w, n, u, w);
        }
        for (n = w; n > l; --n) /*switch to insertion sort*/
            for (m = n; m < u && xs[m] < xs[m-1]; ++m)
                swap(xs, m, m - 1);
    }
}

///* test */
//int cmp(const void* x, const void* y) {
//    return *(int*)x - *(int*)y;
//}
//
//#define N  100000
//#define INF N + 1
//void testmsort() {
//    int i, j, n, xs[N], ys[N];
//    for (j = 0; j < 100; ++j) {
//        for (i = 0, n = rand() % N; i < n; ++i)
//            xs[i] = rand() % N;
//        memcpy((void*)ys, (const void*)xs, n * sizeof(int));
//        qsort(xs, n, sizeof(int), cmp);
//        imsort<int>(ys, 0, n);
//        //assert(!memcmp(xs, ys, n * sizeof(int)));
//        if(memcmp(xs, ys, n * sizeof(int))) {
//            printrange(xs, 0, n);
//            printrange(ys, 0, n);
//            exit(-1);
//        }
//    }
//}
//int main() {
//    double t = clock();
//
//    t = clock();
//    testmsort();
//    printf("in-place workarea version tested, average time: %f\n", (clock() - t) / CLOCKS_PER_SEC / 100.0);
//
//    return 0;
//}


void run_MergeSort(uint8_t* seedIn, int seedSize) {
	Pair* arr=new Pair[N];
	PairA* arrA=(PairA*)arr;
	PairB* arrB=(PairB*)arr;
	fillPairArray(seedIn, seedSize, arr, N);
	//for(int j=0; j<N; j++) printf("init %d: %016llx %016llx\n",j,arr[j].a,arr[j].b);
	for(int i=0; i<ITER_COUNT; i++) {
		if(i!=0) mixArray<PairB>(arrB, N);
		imsort<PairA>(arrA, 0, N);
		mixArray<PairA>(arrA, N);
		//for(int j=0; j<N; j++) printf("%d-%d: %016llx %016llx\n",i,j,arr[j].a,arr[j].b);
		imsort<PairB>(arrB, 0, N);
		//for(int j=0; j<N; j++) printf("%d-%d: %016llx %016llx\n",i,j,arr[j].a,arr[j].b);
	}
	Tracer::I()->sha3_update((unsigned char*)arr, 1024);
	delete[] arr;
}

#undef N
#undef ITER_COUNT

#ifdef SELF_TEST
int main() {
	char hello[100]="aer39invqbj43to;5j46354q34534999!@#%@#$%^&$&ADGSGWREF";
	int len=strlen(hello);
	for(int i=0; i<50; i++) {
		run_MergeSort((uint8_t*)hello,len);
	}
	return 0;
}
#endif
