// C++ program for building suffix array of a given text
#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdint.h>
#include "include/util.h"
#include "include/tracer.h"

using namespace std;

// Structure to store information of a suffix
struct suffix
{
    int index; // To store original index
    int rank[2]; // To store ranks and next rank pair
};
 
// A comparison function used by sort() to compare two suffixes
// Compares two pairs, returns 1 if first pair is smaller
int cmp(struct suffix a, struct suffix b)
{
    return (a.rank[0] == b.rank[0])? (a.rank[1] < b.rank[1] ?1: 0):
               (a.rank[0] < b.rank[0] ?1: 0);
}
 
// This is the main function that takes a string 'txt' of size n as an
// argument, builds and return the suffix array for the given string
void buildSuffixArray(char *txt, int n)
{
    // A structure to store suffixes and their indexes
    struct suffix suffixes[n];
 
    // Store suffixes and their indexes in an array of structures.
    // The structure is needed to sort the suffixes alphabatically
    // and maintain their old indexes while sorting
    for (int i = 0; i < n; i++)
    {
        suffixes[i].index = i;
        suffixes[i].rank[0] = txt[i] - 'a';
        suffixes[i].rank[1] = ((i+1) < n)? (txt[i + 1] - 'a'): -1;
    }
 
    // Sort the suffixes using the comparison function
    // defined above.
    sort(suffixes, suffixes+n, cmp);
 
    // At his point, all suffixes are sorted according to first
    // 2 characters.  Let us sort suffixes according to first 4
    // characters, then first 8 and so on
    int ind[n];  // This array is needed to get the index in suffixes[]
                 // from original index.  This mapping is needed to get
                 // next suffix.
    for (int k = 4; k < 2*n; k = k*2)
    {
        // Assigning rank and index values to first suffix
        int rank = 0;
        int prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        ind[suffixes[0].index] = 0;
 
        // Assigning rank to suffixes
        for (int i = 1; i < n; i++)
        {
            // If first rank and next ranks are same as that of previous
            // suffix in array, assign the same new rank to this suffix
            if (suffixes[i].rank[0] == prev_rank &&
                    suffixes[i].rank[1] == suffixes[i-1].rank[1])
            {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            }
            else // Otherwise increment rank and assign
            {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            ind[suffixes[i].index] = i;
        }
 
        // Assign next rank to every suffix
        for (int i = 0; i < n; i++)
        {
            int nextindex = suffixes[i].index + k/2;
            suffixes[i].rank[1] = (nextindex < n)?
                                  suffixes[ind[nextindex]].rank[0]: -1;
        }
 
        // Sort the suffixes according to first k characters
        sort(suffixes, suffixes+n, cmp);
    }
	uint32_t tmp=0;
    for (int i = 0; i < n; i++) tmp+=(tmp>>16)^suffixes[i].index;
	Tracer::I()->meet(tmp);
 
    //// Store indexes of all sorted suffixes in the suffix array
    //cout << "Following is suffix array for " << txt << endl;
    //for (int i = 0; i < n; i++)
    //    cout << suffixes[i].index << " ";
    //cout << endl;
}
 
 
//// Driver program to test above functions
//int main()
//{
//    char txt[] = "banana";
//    int n = strlen(txt);
//    int *suffixArr = buildSuffixArray(txt,  n);
//    printArr(suffixArr, n);
//    return 0;
//}

void run_SuffixArray(uint8_t* seedIn, int seedSize) {
	const int Count=12*1024*1024;
	Pair* tmp=new Pair[Count/4];
	fillPairArray(seedIn, seedSize, tmp, Count/4);
	uint16_t* arr=(uint16_t*)tmp;
	char txt[33];
	txt[32]=0;
	for(int i=0; i<Count; i+=32) {
		for(int j=0; j<32; j++) {
			txt[j]=arr[i+j]%64+'a';
		}
		buildSuffixArray(txt, 32);
	}
	delete[] tmp;
}

#ifdef SELF_TEST
int main() {
	char hello[100]="ae90..i..8f--r39invqbj43to;5j46354q3499@#%@#$%^&$&ADGSGWREF";
	int len=strlen(hello);
	uint64_t firstRes[4];
	uint64_t otherRes[4];
	for(int i=0; i<50; i++) {
		Tracer::I()->clear();
		run_SuffixArray((uint8_t*)hello,len);
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
