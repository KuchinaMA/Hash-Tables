#ifndef READDATA_H_INCLUDED
#define READDATA_H_INCLUDED

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/** Data about one string
 * pointer to the srting, len of the string
*/
struct LinesData {
    char *pointer;
    int len;
};

/** Data about the text
 * size of file with text, buffer with strings in right order
 * number of strings in the poem, array with data about every string
*/
struct TextData {
    size_t sz;
    char *buf;
    int nLines;
    LinesData *text;
};

/** Calculates the size of opened file
 * \param [in] *fp file size of which is calculated
 * \returns size of the file
*/
int size_of_file(FILE *fp);

/** Counts the number of specified symbols in a string
 * \param [in] *str pointer to a string
 * \param [in] len string length
 * \param [in] symb type of symbols that we need to count
 * \returns number of symbols in string
*/
int number_of_symbs(const char *str, size_t len, char symb);

/** Creates an array with data about every string
 * \param [in] *buf buffer with strings
 * \param [in] sz size of the buffer
 * \param [in] nLines number of strings
 * \returns array with data about strings
*/
LinesData *create_pointer_arr(char *buf, size_t sz, int nLines);

/** Opens file and saves strings of the poem in buffer
 * \param [in] *fp file which is opened
 * \param [in] sz size of the file
 * \returns buffer with strings
*/
char *read_data_from_file(FILE *fp, size_t sz);

/** Reads from file all information about the text
 * \param [in] *InputFile file with text
 * \param [in] *textdata pointer to structure with data about the text
*/
void read_from_file(const char *InputFile,TextData *textdata);


#endif // READDATA_H_INCLUDED
