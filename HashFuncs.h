#ifndef HASHFUNCS_H_INCLUDED
#define HASHFUNCS_H_INCLUDED

#include <stdint.h>

uint32_t const_hash(const char* str);
uint32_t first_letter_hash(const char* str);
uint32_t ASCII_sum_hash(const char* str);
uint32_t strlen_hash(const char* str);
uint32_t rol_hash(const char* str);
uint32_t ror_hash(const char* str);
uint32_t crc32_hash(const char* str);
uint32_t crc32_hash_intrinsic(const char* str);


inline uint32_t rol(uint32_t value);
inline uint32_t ror(uint32_t value);

#endif // HASHFUNCS_H_INCLUDED

