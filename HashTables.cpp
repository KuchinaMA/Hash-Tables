#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstring>
#include <assert.h>

#include "HashTables.h"
#include "HashFuncs.h"

extern "C" int find_key_asm(HashTable * table, uint32_t hash_val, const char* value);

Node* node_ctor(const char* value) {

    Node* new_node = (Node*)calloc(1, sizeof(Node));
    new_node->value = (char*)calloc(MAX_WORD_LEN, sizeof(char));
    strcpy(new_node->value, value);

    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;

}

void node_dtor(Node* node) {

    //node->value = "";
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


void hashtable_add(HashTable* table, const char* value, uint32_t(*hash_func) (const char* str)) {

    Node* new_node = node_ctor(value);

    uint32_t hash_val = hash_func(value) % table->cells_num;

    //if (hashtable_find_key(table, hash_val, value) == NOT_FOUND) {
    if (find_key_asm(table, hash_val, value) == NOT_FOUND) {

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

        //if (strcmp(value, key_cell->value) == 0)
        if (strcmp_asm(value, key_cell->value) == 0)
            return FOUND;

        key_cell = key_cell->next;

    }

    return NOT_FOUND;

}

void get_list_sizes(size_t htable_capacity, TextData text, const char* output_name, uint32_t(*hash_func) (const char* str)) {

    FILE* output_file = fopen(output_name, "w");

    HashTable* table = hashtable_ctor(htable_capacity);

    for (int i = 0; i < text.nLines; ++i) {
        hashtable_add(table, (text.text[i]).pointer, hash_func);
    }

    for (int i = 0; i < table->cells_num; i++)
        fprintf(output_file, "%d %d\n", i, (table->cells[i]).size);


    hashtable_dtor(table);

    fclose(output_file);

    //printf("done\n");

}

void insert_all_data(HashTable* table, TextData text, uint32_t(*hash_func) (const char* str)) {

    for (int i = 0; i < text.nLines; ++i) {
        hashtable_add(table, (text.text[i]).pointer, hash_func);
    }

    printf("done\n");

}

void find_words(HashTable* table, TextData text, uint32_t(*hash_func) (const char* str)) {

    for (size_t i = 0; i < FIND_WORDS_NUM; i++) {

        for (int i = 0; i < text.nLines; i++) {

            const char* key = (text.text[i]).pointer;
            uint32_t hash_val = hash_func(key) % table->cells_num;
            hashtable_find_key(table, hash_val, key);
        }
    }
}

inline int strcmp_asm(const char* str1, const char* str2) {

    __asm {
        push esi
        push edi

        mov esi, str1
        mov edi, str2

        xor eax, eax

        vmovdqu ymm0, YMMWORD PTR [esi]
        vmovdqu ymm1, YMMWORD PTR [edi]

        vptest     ymm0, ymm1
        setnc      eax

        pop edi
        pop esi

    }
}

