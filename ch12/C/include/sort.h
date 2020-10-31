#ifndef SORT_H
#define SORT_H

#include <stdlib.h>

void selection_sort(int *arr, int len);

void insertion_sort(int *arr, int len);

void bubble_sort(int *arr, int len);

void shell_sort(int arr[], int len);

void (*quick_sort)(void *__base, size_t __nmemb, size_t __size,
                   __compar_fn_t __compar) = qsort;

#endif