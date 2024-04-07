#include <stdio.h>

#include "HashTables.h"
#include "HashFuncs.h"
#include "ReadData.h"


int main() {

    TextData text = {0, 0, 0, 0};
    read_from_file("DorianGray.txt", &text);

    //FILE* fresult = fopen("Output.txt", "w");

    //printf("%d\n", text.nLines);

    /*for (int i = 0; i < textdata.nLines; ++i) {
        printf("%s\n", (textdata.text[i]).pointer);
    } */

    get_list_sizes(TABLE_LEN, text, "Results/ConstHash.txt", const_hash);
    get_list_sizes(TABLE_LEN, text, "Results/FirstLetterHash.txt", first_letter_hash);
    get_list_sizes(TABLE_LEN, text, "Results/ASCIISumHash.txt", ASCII_sum_hash);
    get_list_sizes(SMALL_TABLE_LEN, text, "Results/ASCIISumHashSmall.txt", ASCII_sum_hash);
    get_list_sizes(TABLE_LEN, text, "Results/StrlenHash.txt", strlen_hash);
    get_list_sizes(TABLE_LEN, text, "Results/RolHash.txt", rol_hash);
    get_list_sizes(TABLE_LEN, text, "Results/RorHash.txt", ror_hash);
    get_list_sizes(TABLE_LEN, text, "Results/Crc32Hash.txt", crc32_hash);


    /*HashTable* table = hashtable_ctor(SMALL_TABLE_LEN);

    for (int i = 0; i < text.nLines; ++i) {
        hashtable_add(table, (text.text[i]).pointer, const_hash);
    }

    for (int i = 0; i < table->cells_num; i++)
        fprintf(fresult, "%d %d\n", i, (table->cells[i]).size);


    hashtable_dtor(table);*/

    free(text.buf);
    free(text.text);

    return 0;

}
