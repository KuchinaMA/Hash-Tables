
#include <stdio.h>
#include <cstring>
#include <assert.h>
#include <immintrin.h>

#include "HashFuncs.h"

uint32_t const_hash(const char* str) {

    return 1;

}

uint32_t first_letter_hash(const char* str) {

    return (uint32_t)str[0];

}

uint32_t ASCII_sum_hash(const char* str) {

    int str_length = strlen(str);
    uint32_t hash_sum = 0;

    for (int i = 0; i < str_length; i++) {
        hash_sum += (uint32_t)str[i];
    }

    return hash_sum;
}

uint32_t strlen_hash(const char* str) {

    return (uint32_t)strlen(str);

}

uint32_t rol_hash(const char* str) {

    uint32_t hash_sum = 0;

    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {

        hash_sum = rol(hash_sum) ^ str[i];

    }
    return hash_sum;

}

inline uint32_t rol(uint32_t value) {

    return ((value << 1)) | (value >> 31);

}

uint32_t ror_hash(const char* str) {

    uint32_t hash_sum = 0;

    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {

        hash_sum = ror(hash_sum) ^ str[i];
    }

    return hash_sum;

}

inline uint32_t ror(uint32_t value) {

    return ((value >> 1)) | (value << 31);

}


uint32_t crc32_hash(const char* str) {

    uint32_t crc_table[256];
    uint32_t crc = 0;
    size_t len = strlen(str);

    for (int i = 0; i < 256; i++) {
        crc = i;

        for (int j = 0; j < 8; j++)
            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320U : crc >> 1;

        crc_table[i] = crc;
    }

    crc = 0xFFFFFFFFU;

    while (len--)
        crc = crc_table[(crc ^ *str++) & 0xFF] ^ (crc >> 8);

    return crc ^ 0xFFFFFFFFU;
}

uint32_t crc32_hash_intrinsic(const char* str) {

    uint32_t crc = 0;
    crc = _mm_crc32_u32(crc, *((uint64_t*)str ));
    crc = _mm_crc32_u32(crc, *((uint64_t*)str + 1));
    crc = _mm_crc32_u32(crc, *((uint64_t*)str + 2));
    crc = _mm_crc32_u32(crc, *((uint64_t*)str + 3));

    return crc;
}
