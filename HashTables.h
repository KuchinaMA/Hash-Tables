#ifndef HASHTABLES_H_INCLUDED
#define HASHTABLES_H_INCLUDED

#include <stdint.h>
#include "ReadData.h"

const size_t TABLE_LEN = 5003;
const size_t SMALL_TABLE_LEN = 383;

const size_t MAX_WORD_LEN = 32;

const size_t FIND_WORDS_NUM = 1;

enum Is_found {

    NOT_FOUND = 0,
    FOUND = 1,

};

struct Node {

    char* value;
    Node* next;
    Node* prev;
};

struct List {

    Node* head;
    size_t size;

};

struct HashTable {

    List* cells;
    size_t cells_num;

};

Node* node_ctor(const char* value);
void node_dtor(Node* node);

List* list_ctor(Node* head);
void list_dtor(List* list);

HashTable* hashtable_ctor(size_t cells_num);
void hashtable_dtor(HashTable* table);
void hashtable_add(HashTable* table, const char* value, uint32_t(*hash_func) (const char* str));
int hashtable_find_key(HashTable* table, uint32_t hash_val, const char* value);
void get_list_sizes(size_t htable_capacity, TextData text, const char* output_name, uint32_t(*hash_func) (const char* str));
void insert_all_data(HashTable* table, TextData text, uint32_t(*hash_func) (const char* str));
void find_words(HashTable* table, TextData text, uint32_t(*hash_func) (const char* str));

inline int strcmp_asm(const char* str1, const char* str2);

#endif // HASHTABLES_H_INCLUDED
