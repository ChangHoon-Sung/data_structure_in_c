#ifndef TOOLS_H
#define TOOLS_H

int compare(const void *a, const void *b);

int *random_array(int n);

void print_array(int *arr, int len);

int *copy_array(int *arr, int len);

int is_equal(int *arr1, int *arr2, int len);

#endif