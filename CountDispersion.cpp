#include <stdio.h>
//#include <assert.h>
#include <math.h>

//static const char* INPUT_FILE = "assets/output/crc32_hash.txt";

float find_average(FILE* input);
float count_disperce(FILE* input, float avg_length);

int main() {

    FILE* input = fopen("Results/Crc32Hash.txt", "r");
    float avg = find_average(input);
    fseek(input, 0, SEEK_SET);

    float disperce = count_disperce(input, avg);

    printf("%f\n", disperce);

    fclose(input);
}

float find_average(FILE* input) {

    //FILE* fp = fopen(input, "r");

    int cells_num = 0;
    int current_sum = 0;
    int cell_num = 0;
    int cell_length = 0;

    while (fscanf(input, "%d %d", &cell_num, &cell_length) != EOF) {

        current_sum += cell_length;
        cells_num++;
    }

    //fclose(fp);

    return ((float) current_sum) / cells_num;
}


float count_disperce(FILE* input, float avg_length) {

    //FILE* fp = fopen(INPUT_FILE, "r");

    int cells_num = 0;
    int cell_num = 0;
    int cell_length = 0;

    float sum = 0;

    while (fscanf(input, "%d %d", &cell_num, &cell_length) != EOF) {

        sum += ((float) cell_length - avg_length) * ((float) cell_length - avg_length);
        cells_num++;
    }

    //fclose(fp);

    return sqrt((sum / cells_num));
}
