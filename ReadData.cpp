#include <stdio.h>
#include <assert.h>

#include "ReadData.h"


int size_of_file(FILE *fp) {

    assert(fp != NULL);

    fseek(fp, 0, SEEK_END);

    int sz = (int)ftell(fp);

    fseek(fp, 0, SEEK_SET);

    return sz;
}


int number_of_symbs(const char *buf, size_t len, char symb) {

    assert(buf != NULL);

    int nSymbs = 0;

    for (size_t i = 0; i < len; ++i) {

        if (buf[i] == symb) {
            nSymbs ++;
        }
    }

    return nSymbs;
}



LinesData *create_pointer_arr(char *buf, size_t sz, int nLines) {

    assert(buf != NULL);
    assert(nLines >= 0);

    LinesData *text = (LinesData*) calloc(nLines, sizeof(LinesData));

    if (text == NULL) {
        printf(" Sorry! Can't open your fie because it's too big\n");
    }
    for(int i = 0; i < nLines; i++) {
        (text[i]).pointer = NULL;
        (text[i]).len = 0;
    }

    (text[0]).pointer = buf;

    int line = 1;

    for(size_t i = 0; i < sz; ++i) {
        if (buf[i] == '\n') {
            buf[i] = '\0';

            (text[line - 1]).len = (buf + i + 1) - (text[line - 1]).pointer;

            if (line < nLines) {
                (text[line]).pointer = buf + i + 1;
                line ++;
            }
        }
    }
    return text;
}


char *read_data_from_file(FILE *fp, size_t sz) {

    if (fp == NULL) {
        printf("There's no file with text of poem\n");
    }


    char *buf = (char*) calloc(sz + 1, sizeof(char));
    assert(buf != NULL);

    size_t nRead = fread(buf, sizeof(char), sz, fp);
    assert (nRead <= sz);

    //printf("%d %d\n", nRead, sz);

    buf[nRead] = '\n';

    return buf;
}


void read_from_file(const char *InputFile, TextData *textdata) {

    assert(textdata != NULL);

    FILE *finput = fopen(InputFile , "r" );

    assert(finput != NULL);

    textdata->sz = size_of_file(finput);
    textdata->buf = read_data_from_file(finput, textdata->sz);

    fclose(finput);

    textdata->nLines = number_of_symbs(textdata->buf, textdata->sz, '\n');

    /*if (textdata->buf[textdata->sz - 1] != '\n') {
        textdata->nLines ++;
    } */
    //textdata->nLines -= 2;

    textdata->text = create_pointer_arr(textdata->buf, textdata->sz, textdata->nLines);
}
