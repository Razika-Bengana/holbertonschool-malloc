#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

/* task 0 */
size_t get_page_size(void);
size_t align_size(size_t size);
void *naive_malloc(size_t size);

/* task 1 */
void *_malloc(size_t size);

/* task 2 */
void _free(void *ptr);


#endif /* MAIN_H */
