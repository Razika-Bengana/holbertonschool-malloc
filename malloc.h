#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

size_t get_page_size(void);
size_t align_size(size_t size);
void *naive_malloc(size_t size);
void *_malloc(size_t size);

#endif /* MAIN_H */
