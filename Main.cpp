#include <stdio.h>

#include "HashTables.h"
#include "HashFuncs.h"
#include "ReadData.h"


int main() {

    TextData text = {0, 0, 0, 0};
    read_from_file("GoneWithTheWind.txt", &text);


    get_list_sizes(TABLE_LEN, text, "Results/ConstHash.txt", const_hash);
    get_list_sizes(TABLE_LEN, text, "Results/FirstLetterHash.txt", first_letter_hash);
    get_list_sizes(TABLE_LEN, text, "Results/ASCIISumHash.txt", ASCII_sum_hash);
    get_list_sizes(SMALL_TABLE_LEN, text, "Results/ASCIISumHashSmall.txt", ASCII_sum_hash);
    get_list_sizes(TABLE_LEN, text, "Results/StrlenHash.txt", strlen_hash);
    get_list_sizes(TABLE_LEN, text, "Results/RolHash.txt", rol_hash);
    get_list_sizes(TABLE_LEN, text, "Results/RorHash.txt", ror_hash);
    get_list_sizes(TABLE_LEN, text, "Results/Crc32Hash.txt", crc32_hash);


    free(text.buf);
    free(text.text);

    return 0;

}
