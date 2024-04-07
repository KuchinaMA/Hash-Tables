#include <stdio.h>
#include <strings.h>
#include <assert.h>

#include "HashTables.h"
#include "HashFuncs.h"


Node* node_ctor(const char* value) {

    Node* new_node = (Node*)calloc(1, sizeof(Node));
    new_node->value = (char*)calloc(MAX_WORD_LEN, sizeof(char));
    strcpy(new_node->value, value);

    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;

}

void node_dtor(Node* node) {

    node->value = "";
    node->next = NULL;
    node->prev = NULL;

    free(node);

}


List* list_ctor(Node* head) {

    List* new_list = (List*)calloc(1, sizeof(List));

    new_list->head = head;
    new_list->size = 1;

    return new_list;

}

void list_dtor(List* list) {

    while (list->head->next != NULL) {

        list->head = list->head->next;
        node_dtor(list->head->prev);
    }
    node_dtor(list->head);
    list->size = 0;

    free(list);

}

HashTable* hashtable_ctor(size_t cells_num) {

    HashTable* new_table = (HashTable*)calloc(1, sizeof(HashTable));

    new_table->cells = (List*)calloc(cells_num, sizeof(List));

    for (int i = 0; i < cells_num; i++) {

        new_table->cells[i].head = NULL;
        new_table->cells[i].size = 0;
    }

    new_table->cells_num = cells_num;

    return new_table;

}

void hashtable_dtor(HashTable* table) {

    table->cells_num = 0;
    free(table->cells);

    free(table);

}


void hashtable_add(HashTable* table, const char* value, uint32_t (*hash_func) (const char* str)) {

    Node* new_node = node_ctor(value);

    uint32_t hash_val = hash_func(value) % table->cells_num;

    if (hashtable_find_key(table, hash_val, value) == NOT_FOUND) {

        if (table->cells[hash_val].size == 0) {

            table->cells[hash_val].head = new_node;
            table->cells[hash_val].size++;


        }

        else {

            new_node->next = table->cells[hash_val].head;
            table->cells[hash_val].head->prev = new_node;
            table->cells[hash_val].head = new_node;

            table->cells[hash_val].size++;

        }
    }

}

int hashtable_find_key(HashTable* table, uint32_t hash_val, const char* value) {

    Node* key_cell = table->cells[hash_val].head;

    while (key_cell != NULL) {

        if (strcmp(value, key_cell->value) == 0)
            return FOUND;

        key_cell = key_cell->next;

    }

    return NOT_FOUND;

}

void get_list_sizes(size_t htabe_capacity, TextData text, const char* output_name, uint32_t (*hash_func) (const char* str)) {

    FILE* output_file = fopen(output_name, "w");

    HashTable* table = hashtable_ctor(htabe_capacity);

    for (int i = 0; i < text.nLines; ++i) {
        hashtable_add(table, (text.text[i]).pointer, hash_func);
    }

    for (int i = 0; i < table->cells_num; i++)
        fprintf(output_file, "%d %d\n", i, (table->cells[i]).size);


    hashtable_dtor(table);

    fclose(output_file);

    printf("done\n");

}







/*uint32_t hash_1(const char* str) {

    return 1;

}

uint32_t hash_2(const char* str) {

    return (uint32_t)(str[0] - 'a');

}

uint32_t hash_3(const char* str) {

    int str_length = strlen(str);
    uint32_t hash_sum = 0;

    for (int i = 0; i < str_length; i++) {
        hash_sum += (uint32_t)str[i];
    }
    //printf("%u\n", hash_sum);
    return hash_sum;
}

uint32_t hash_4(const char* str) {

    //printf("%s %d", str, strlen(str));
    return (uint32_t)strlen(str);

}

uint32_t hash_5(const char* str) {

    uint32_t hash_sum = 0;

    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {

        hash_sum = rol(hash_sum) ^ str[i];                 //в ридми привести текст этой функции
                                                           //+ как компилирует gcc без оптимизаций, с -O2 и -O3
    }
    //printf("%u\n", hash_sum);
    return hash_sum;

}

uint32_t hash_6(const char* str) {

    uint32_t hash_sum = 0;

    size_t len = strlen(str);
    printf("%d\n", len);

    for (size_t i = 0; i < len; i++) {

        hash_sum = ror(hash_sum) ^ str[i];
        printf("%u\n", hash_sum);
    }

    printf("\n%u\n", hash_sum);
    return hash_sum;

}  */

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

/*uint32_t hash_7(const char* str) {

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

	printf("%u\n", crc ^ 0xFFFFFFFFU);
	return crc ^ 0xFFFFFFFFU;
}


uint32_t rol(uint32_t value) {

    return ((value << 1)) | (value >> 31);

}

uint32_t ror(uint32_t value) {

    return ((value >> 1)) | (value << 31);

} */
