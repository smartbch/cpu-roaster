
#include <stdint.h>
#include <iostream>
#include <string.h>
#include <stdio.h>

#include "byte_order.c"
#include "sha3.c"
#include "blake2b-ref.c"

// sha3's output is 256 bits (32 bytes)
// blake2b consumes 128-byte "in" and 64-byte "key" to generate 64-byte hash
// We need 32 "in" blocks and 32 "key" blocks to get 32*32*64=64kilo byte random data
// out must point to a 64KB buffer, which will be filled by random data
void expandRand64KB(uint8_t* seed, int seedSize, uint8_t* out) {
	const int BufSize=(32*128/*in*/+32*64/*key*/);
	uint8_t* tempBuf=(uint8_t*)malloc(BufSize);
	memset(tempBuf, 0, BufSize);
	sha3_ctx ctx;
	// init the first 32 bytes
	rhash_sha3_256_init(&ctx);
	rhash_sha3_update(&ctx, seed, seedSize);
	rhash_sha3_final(&ctx, tempBuf);
	// init the second 32 bytes
	rhash_sha3_256_init(&ctx);
	rhash_sha3_update(&ctx, tempBuf, 32);
	rhash_sha3_final(&ctx, tempBuf+32);
	for(int start=64; start<BufSize; start+=32) {
		// use 64-byte old data to generate the next 32-byte data
		rhash_sha3_256_init(&ctx);
		rhash_sha3_update(&ctx, tempBuf+start-64, 64);
		rhash_sha3_final(&ctx, tempBuf+start);
	}
	uint32_t* i32buf=(uint32_t*)tempBuf;
	//for(int i=0; i<BufSize/4; i++) printf("here %04d %08x\n",i*4,i32buf[i]);
	//printf("here ----- %d-----\n", BufSize/4);

	uint8_t* key=tempBuf + 32*128;
	for(int i=0; i<32; i++) {
		for(int j=0; j<32; j++) {
			int pos=i*32+j;
			blake2b(out+64*pos, 64, /*in*/tempBuf+128*i, 128, /*key*/key+64*j, 64);
		}
	}
	free(tempBuf);
	//uint32_t* i32buf=(uint32_t*)out;
	//for(int i=0; i<1024; i++) printf("here %d %x\n",i*4,i32buf[i]);
}

void expandRand4KB(uint8_t* in, int inSize, uint8_t* out) {
	const int bufSize=8*128;
	uint8_t* tempBuf=(uint8_t*)malloc(8*128+128);
	sha3_ctx ctx;
	rhash_sha3_256_init(&ctx);
	rhash_sha3_update(&ctx, in, inSize);
	rhash_sha3_final(&ctx, tempBuf);
	rhash_sha3_256_init(&ctx);
	rhash_sha3_update(&ctx, tempBuf, 32);
	rhash_sha3_final(&ctx, tempBuf+32);
	for(int start=64; start<bufSize; start+=32) {
		rhash_sha3_256_init(&ctx);
		rhash_sha3_update(&ctx, tempBuf+start-64, 64);
		rhash_sha3_final(&ctx, tempBuf+start);
	}
	//uint32_t* i32buf=(uint32_t*)tempBuf;
	//for(int i=0; i<bufSize/4; i++) printf("here %d %x\n",i*4,i32buf[i]);

	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
			int pos=i*8+j;
			blake2b(out+64*pos, 64, tempBuf+128*i, 128, tempBuf+128*j, 64);
		}
	}
	free(tempBuf);
	//uint32_t* i32buf=(uint32_t*)out;
	//for(int i=0; i<1024; i++) printf("here %d %x\n",i*4,i32buf[i]);
}


#ifdef  SELF_TEST
static void test_expandRand64KB() {
	uint32_t* outBuf=(uint32_t*)malloc(64*1024);
	memset(outBuf, 0, 64*1024);
	char mySeedStr[100]="aeiqfcnq3i0$%$@$%		^&*jdIHIHF:JKWF";
	int l=strlen(mySeedStr);
	expandRand64KB((uint8_t*)mySeedStr, l, (uint8_t*)outBuf);
	for(int i=0; i<64*1024/4; i+=4) {
		printf("%08x %08x %08x %08x\n", outBuf[i],outBuf[i+1],outBuf[i+2],outBuf[i+3]);
	}
	free(outBuf);
}


int main( void ) {
	test_expandRand64KB();
	return 0;
}
#endif

