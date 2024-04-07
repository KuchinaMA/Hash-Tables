#include <stdio.h>
#include <strings.h>
#include <assert.h>

#include "HashFuncs.h"

uint32_t const_hash(const char* str) {

    return 1;

}

uint32_t first_letter_hash(const char* str) {

    return (uint32_t)(str[0]);

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

        hash_sum = rol(hash_sum) ^ str[i];                 //в ридми привести текст этой функции
                                                           //+ как компилирует gcc без оптимизаций, с -O2 и -O3
    }
    return hash_sum;

}

uint32_t ror_hash(const char* str) {

    uint32_t hash_sum = 0;

    size_t len = strlen(str);
    //printf("%d\n", len);

    for (size_t i = 0; i < len; i++) {

        hash_sum = ror(hash_sum) ^ str[i];
        //printf("%u\n", hash_sum);
    }

    //printf("\n%u\n\n", hash_sum);
    return hash_sum;

}

/*uint32_t hash_7(const char* str) {

    const uint32_t crc_table[256] = {0x00000000, 0x04C11DB7, 0x09823B6E, 0x0D4326D9,
        // остальные значения таблицы CRC32
    };

    uint32_t hash_sum = 0xFFFFFFFF;
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {

        hash_sum = hash_sum ^ ((uint32_t)str[i] << 24);

        for (int j = 0; j < 8; j++) {
            //hash_sum = (hash_sum << 1) ^ (crc_table[hash_sum >> 24]);
            if (hash_sum & (1L << 31))
                hash_sum = (hash_sum << 1) ^ 0x04C11DB7;
            else
                hash_sum = (hash_sum << 1);
        }
    }

    return hash_sum;

} */

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

	//printf("%u\n", crc ^ 0xFFFFFFFFU);
	return crc ^ 0xFFFFFFFFU;
}


inline uint32_t rol(uint32_t value) {

    return ((value << 1)) | (value >> 31);

}

inline uint32_t ror(uint32_t value) {

    return ((value >> 1)) | (value << 31);

}
