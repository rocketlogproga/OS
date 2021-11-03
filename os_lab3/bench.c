#include <stdio.h>
#include <time.h>
#include "sys/time.h"
#include "TimSort.h"
#include "MTimSort.h"

size_t threads_count;

long long current_timestamp() {
   struct timeval te;
   if(gettimeofday(&te, NULL) != 0)
   {
      fprintf(stderr, "GETTIME ERROR\n");
      exit(-1);
   }

   long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
   return milliseconds;
}

int main (int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "wrong number of args\n");
        exit(-1);
    }
    threads_count = atoi(argv[1]);
    long long start, end, MT, ST;
    size_t n;
    scanf("%ld",&n);
    int* mas1 = malloc(sizeof(int) * n);
    int* mas2 = malloc(sizeof(int) * n);
    int el;
    for (int i = 0; i < n; ++i) {
        if(scanf("%d", &el) != 1) {
            fprintf(stderr, "out of data\n");
            exit(-1);
        }
        mas1[i] = el;
        mas2[i] = el;
    }

    start = current_timestamp();
    MTimSort(mas1, n);
    end = current_timestamp();
    MT = end - start;

    start = current_timestamp();
    TimSort(mas2, n);
    end = current_timestamp();
    ST = end - start;

    printf("\nsize: %ld\nthreads: %ld\n", n, threads_count);
    printf("single-threaded: %lld\nmulti-threaded: %lld\n", ST, MT);
    free(mas1);
    free(mas2);
    return 0;
}