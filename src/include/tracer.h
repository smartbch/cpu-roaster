#ifndef TRACER_H
#define TRACER_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "../ExpandRand/sha3.h"

class Tracer {
private:
	Tracer() {
		smallBuf=(uint64_t*)malloc(smallBufSize);
		clear();
	}

public:
	static Tracer* I() {
		thread_local static Tracer Inst;
		return &Inst;
	}
	// small Buf will be read and written
	uint64_t* smallBuf;
	const int smallBufSize=128*1024; //128KB
	const int smallBufMask=(smallBufSize/8-1);
	const uint64_t FNV_PRIME=0x100000001b3ULL;
	const uint64_t FNV_INIT=0xcbf29ce484222325ULL;
	int counter;
	uint64_t fnvKey;
	uint64_t fnvHistory[8];
	uint64_t historyCksum() {
		uint64_t res=0;
		for(int i=0; i<8; i++) {
			res^=fnvHistory[i];
		}
		return res;
	}
	void final_result(unsigned char* result) {
		sha3_ctx ctx;
		rhash_sha3_256_init(&ctx);
		rhash_sha3_update(&ctx, (unsigned char*)fnvHistory, 8*8);
		rhash_sha3_update(&ctx, (unsigned char*)smallBuf, smallBufSize);
		rhash_sha3_final(&ctx, result);
	}
	void clear() {
		memset((char*)smallBuf,0,smallBufSize);
		fnvKey=FNV_INIT;
		counter=0;
		for(int i=0; i<8; i++) fnvHistory[i]=0;
	}
	~Tracer() {
		free(smallBuf);
	}

	void meet(uint64_t value) {
		uint64_t oldKey=fnvKey;
		fnvKey*=FNV_PRIME;
		fnvKey^=value;
		counter++;
		// when normal fnv runs for 32 times, update smallBuf and 
		// append new entry to fnvHistory
		if(counter%32==0) {
			int idx=oldKey&smallBufMask;
			assert(idx*8<smallBufSize);
			smallBuf[idx]^=fnvKey;
			fnvHistory[counter/32-1]=fnvKey;
		}
		if(counter==256) {
			counter=0;
		}
	}
};

#endif
