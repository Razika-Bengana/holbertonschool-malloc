#include "malloc.h"

/**
 * _free - program that frees a block of memory previously allocated
 * by naive_malloc
 *
 * this function marks the memory as free by setting the size
 * in the block header to 0;
 * future implementations of naive_malloc may consider reusing this space
 * if they look for free blocks
 *
 * @ptr: a pointer to the memory space to be freed;
 * if ptr is NULL, no operation is performed
 *
 */

void _free(void *ptr)
{
	size_t *block_header;

	if (!ptr)
	{
		return;
	}

	*block_header = (size_t *)((unsigned char *)ptr - sizeof(size_t));

	*block_header = 0;
}
