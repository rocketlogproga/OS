#include "stdio.h"
#include "string.h"

int main(int argc, char **argv){
    if(argc != 2){
        return -1;
    }

    float result;
    float num;
    char ch;

    FILE *file;
    file = fopen(argv[1], "w");

    scanf("%f ", &result);
    while(scanf("%f%c", &num, &ch) != EOF){
        if(num == 0){
            fclose(file);
            return -2;
        }

        result /= num;

        if(ch == '\n'){
            fprintf(file, "%f\n", result);
            scanf("%f ", &result);
        }
    }
    fprintf(file, "%f\n", result);
    fclose(file);
    return 0;
}