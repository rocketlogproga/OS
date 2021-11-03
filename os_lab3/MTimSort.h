#ifndef MTIMSORT_H
#define MTIMSORT_H

#include <unistd.h>
#include <pthread.h>
#include "General.h"

extern size_t threads_count;

typedef enum RUN_COMM {
    EXIT = -1,
    INSERT_SORT,
    REVERSE,
    MERGE,
    PAUSE
} RUN_COMM;

typedef struct FuncArgs {
    int* mas;
    size_t right, mid, left;
    size_t n;
} FuncArgs;

typedef struct RunArgs {
    RUN_COMM comm;
    FuncArgs args;
} RunArgs;

void* Run (void* data) {
    RunArgs* a = (RunArgs*) data;
    while (1) {
        while (a->comm == PAUSE) {}
        switch (a->comm) {
            case INSERT_SORT:
                InsertSort(a->args.mas, a->args.n);
                break;
            case REVERSE:
                Reverse(a->args.mas, a->args.n);
                break;
            case MERGE:
                Merge(a->args.mas, a->args.left, a->args.mid, a->args.right);
                break;
            case EXIT:
                pthread_exit(NULL);
                break;
        }
        a->comm = PAUSE;
    }
    pthread_exit(NULL);
}

void MTimSort (int* mas, size_t n) {
    if (n < 64) {
        InsertSort(mas, n);
        return;
    }

    pthread_t* tid = malloc(sizeof(pthread_t) * threads_count);
    RunArgs* Arg = malloc(sizeof(RunArgs) * threads_count);
    for (int i = 0; i < threads_count; ++i) {
        Arg[i].comm = PAUSE;
        if(pthread_create(&tid[i], NULL, Run, (void*) &Arg[i]) != 0) {
            fprintf(stderr, "pthread_create error\n");
            exit(-1);
        }
    }

    size_t minrun = GetMinRun(n);
    FuncArgs* arr = malloc(sizeof(FuncArgs) * (n / 32));
    size_t arr_i = 0;

    int index[n], index_i = 0; 
    int i = 0;
    while (i <= n) {
        if (n - i <= 2) {
            if (n - i == 0) {
                break;
            }
            index[index_i] = n - i;
            ++index_i;
            InsertSort(mas + i, n - i);
            break;
        }
        int j = i;
        bool(*Compare)(int, int);
        Compare = mas[j] <= mas[j + 1] ? Compare1 : Compare2;
        while (j + 1 < n && Compare(mas[j], mas[j + 1])) {
            ++j;
        }
        if (Compare == &Compare2) {
            Reverse(mas + i, j - i + 1);
        }
        if (j - i + 1 < minrun) {
            if (n - j - 1 < minrun) {
                j = n - 1;
            } else {
                j = minrun + i - 1;
            }
            arr[arr_i].mas = mas + i; arr[arr_i].n = j - i + 1;
            ++arr_i;
        }
        index[index_i] = j - i + 1;
        ++index_i;
        i = j + 1;
    }

    int div = arr_i / threads_count, mod = arr_i % threads_count;
    for (int j = 0; j < div; ++j) {
        for (int i = 0; i < threads_count; ++i) {
            Arg[i].args = arr[threads_count * j + i];
            Arg[i].comm = INSERT_SORT;
        }
        for (int i = 0; i < threads_count; ++i) {
            while (Arg[i].comm != PAUSE) {}
        }
    }
    for (int i = 0; i < mod; ++i) {
        Arg[i].args = arr[div * threads_count + i];
        Arg[i].comm = INSERT_SORT;
    }
    for (int i = 0; i < threads_count; ++i) {
        while (Arg[i].comm != PAUSE) {}
    }

    size_t size = index_i;
    size_t step = 2;
    while (size > 1) {
        size_t pairs = size / 2;
        size_t j = 0;
        arr_i = 0;
        for (size_t i = 0; i < pairs; ++i) {
            size_t i1 = index[i * step];
            size_t i2 = index[i * step + step / 2];
            arr[arr_i].mas = mas; arr[arr_i].left = j; arr[arr_i].mid = j + i1; arr[arr_i].right = j + i1 + i2;
            ++arr_i;
            j += i1 + i2;
            index[i * step] += index[i * step + step / 2];
        }
        div = pairs / threads_count, mod = pairs % threads_count;
        for (int j = 0; j < div; ++j) {
            for (int i = 0; i < threads_count; ++i) {
                Arg[i].args = arr[threads_count * j + i];
                Arg[i].comm = MERGE;
            }
            for (int i = 0; i < threads_count; ++i) {
                while (Arg[i].comm != PAUSE) {}
            }
        }
        for (int i = 0; i < mod; ++i) {
            Arg[i].args = arr[div * threads_count + i];
            Arg[i].comm = MERGE;
        }
        for (int i = 0; i < threads_count; ++i) {
            while (Arg[i].comm != PAUSE) {}
        }
        arr_i = 0;
        step *= 2;
        size = size / 2 + size % 2;
    }

    for (int i = 0; i < threads_count; ++i) {
        Arg[i].comm = EXIT;
        if (pthread_join(tid[i], NULL) != 0) {
            fprintf(stderr, "pthread_join error\n");
            exit(-1);
        }
    }
    free(tid);
    free(Arg);
    free(arr);
}

#endif