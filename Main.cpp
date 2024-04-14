#include <stdio.h>

#include "HashTables.h"
#include "HashFuncs.h"
#include "ReadData.h"

extern "C" uint64_t get_time();

int main() {

    TextData text = { 0, 0, 0, 0 };
    read_from_file("GoneWithTheWind.txt", &text);

   HashTable* table = hashtable_ctor(TABLE_LEN);

    /*get_list_sizes(TABLE_LEN, text, "Results/ConstHash.txt", const_hash);
    get_list_sizes(TABLE_LEN, text, "Results/FirstLetterHash.txt", first_letter_hash);
    get_list_sizes(TABLE_LEN, text, "Results/ASCIISumHash.txt", ASCII_sum_hash);
    get_list_sizes(SMALL_TABLE_LEN, text, "Results/ASCIISumHashSmall.txt", ASCII_sum_hash);
    get_list_sizes(TABLE_LEN, text, "Results/StrlenHash.txt", strlen_hash);
    get_list_sizes(TABLE_LEN, text, "Results/RolHash.txt", rol_hash);
    get_list_sizes(TABLE_LEN, text, "Results/RorHash.txt", ror_hash);
    get_list_sizes(TABLE_LEN, text, "Crc32Hash.txt", crc32_hash);*/

    //insert_all_data(table, text, crc32_hash);
   insert_all_data(table, text, crc32_hash_intrinsic);

    uint64_t start_time = get_time();
    printf("%lld\n", start_time);

    //find_words(table, text, crc32_hash);
    find_words(table, text, crc32_hash_intrinsic);

    uint64_t end_time = get_time() - start_time;
    printf("%lld\n", end_time);


    hashtable_dtor(table);

    free(text.buf);
    free(text.text);

    return 0;

}

