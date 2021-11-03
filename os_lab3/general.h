#ifndef GENERAL_H
#define GENERAL_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

size_t GetMinRun(size_t n){
    int r = 0;
        while (n >= 64){
            r |= n & 1;
            n >>= 1;
        }
    return n + r; 
}

bool Compare1 (int a, int b) {
    return a <= b;
}

bool Compare2 (int a, int b) {
    return a > b;
}

void InsertSort (int* mas, size_t n) {
    for (size_t i = 1; i < n; ++i) {
        int prev = mas[i - 1];
        int next = mas[i];
        size_t n = i;
        while (next < prev) {
            int el = mas[n];
            mas[n] = mas[n - 1];
            mas[n - 1] = el;
            if (n > 1) {
                n--;
                prev = mas[n - 1];
            } else {
                prev = 0;
            }
        }
    }
}

void Reverse (int* mas, size_t n) {
    size_t i = 0;
    --n;
    while (i < n) {
        mas[i] += mas[n];
        mas[n] = mas[i] - mas[n];
        mas[i] = mas[i] - mas[n];
        ++i;
        --n;
    }
}

void Merge (int* mas, size_t left, size_t mid, size_t right) {
    int tmp[right - left + 1];
    size_t j = 0;
    size_t i1 = left, i2 = mid;
    while (i1 != mid && i2 != right) {
        if (mas[i1] > mas[i2]) {
            tmp[j] = mas[i2];
            ++i2;
        } else {
            tmp[j] = mas[i1];
            ++i1;
        }
        ++j;
    }
    size_t i = i1 == mid ? i2 : i1;
    for (i; i < mid; ++i) {
        tmp[j] = mas[i];
        ++j;
    }
    memcpy(mas + left, tmp, j * sizeof(int));
}

#endif