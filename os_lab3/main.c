#include <stdio.h>
#include "MTimSort.h"

size_t threads_count;

int main (int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "wrong number of args\n");
        exit(-1);
    }
    threads_count = atoi(argv[1]);
    size_t n;
    scanf("%ld",&n);
    int* mas = malloc(sizeof(int) * n);
    int el;
    for (int i = 0; i < n; ++i) {
        if(scanf("%d", &el) != 1) {
            fprintf(stderr, "out of data\n");
            exit(-1);
        }
        mas[i] = el;
    }

    MTimSort(mas, n);

    for (int i = 0; i < n; ++i) {
        printf("%d ", mas[i]);
    }
    printf("\n");
    free(mas);
    return 0;
}