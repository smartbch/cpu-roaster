#ifndef CPUROASTER_H
#define CPUROASTER_H

extern "C" int64_t cpu_roaster_pow(uint32_t d0, uint32_t d1, uint32_t d2, uint32_t d3, uint32_t d4, uint32_t d5, uint32_t d6, uint32_t d7, const uint64_t difficulty, const int64_t nonce_start, const int64_t nonce_stop, const int64_t nonce_step);
extern "C" void cpu_roaster_hash(uint8_t *data, size_t length, unsigned char *hash);

#endif
