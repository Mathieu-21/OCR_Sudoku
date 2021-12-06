#ifndef HOUGH_H
#define HOUGH_H

#include <stddef.h>

void hough(int mat[], int houg[], size_t matcolls, size_t matlines, size_t hougcolls);

size_t angle(int houg[], size_t x, size_t y);

int is_on_line(int houg[], size_t x, size_t y, size_t hougcolls, size_t houglines);

void cut(int mat[], int cas[], size_t x1, size_t y1, size_t x2, size_t y2, size_t matcolls);

int test_cas(int mat[], size_t colls, size_t lines);

#endif

