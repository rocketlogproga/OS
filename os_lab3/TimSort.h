#ifndef TIMSORT_H
#define TIMSORT_H

#include "General.h"

void TimSort(int* mas, size_t n){
    if(n < 64){
        InsertSort(mas, n);
        return;
    }
    size_t minrun = GetMinRun(n);
    int* index = malloc(sizeof(int) * n);
    int index_i = 0;
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
            InsertSort(mas + i, j - i + 1);
        }
        index[index_i] = j - i + 1;
        ++index_i;
        i = j + 1;
    }
    size_t size = index_i;
    size_t step = 2;
    while (size > 1) {
        size_t pairs = size / 2;
        size_t j = 0;
        for (size_t i = 0; i < pairs; ++i) {
            size_t i1 = index[i * step];
            size_t i2 = index[i * step + step / 2];
            Merge(mas, j, j + i1, j + i1 + i2);
            j += i1 + i2;
            index[i * step] += index[i * step + step / 2];
        }
        step *= 2;
        size = size / 2 + size % 2;
    }
    free(index);
}

#endif