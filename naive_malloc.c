#include <stdio.h>
#include <unistd.h>
#include <stdint.h>


#define ALIGN sizeof(void *)


/**
 * get_page_size - program that gets the size of a memory page
 *
 * Return: the size_t size of a memory page in bytes
 */

size_t get_page_size(void)
{
	return (sysconf(_SC_PAGESIZE));
}


/**
 * align_size - program that adjusts the provided size to ensure
 * proper alignment
 *
 * @size: the original size in bytes
 *
 * Return: the size_t adjusted size in bytes that is suitably aligned
 */

size_t align_size(size_t size)
{
	return ((size + ALIGN - 1) & ~(ALIGN - 1));
}


/**
 * naive_malloc - program that naively allocates a memory block in the heap
 *
 * this function allocates a block of memory of the specified size in the heap,
 * ensuring it is suitably aligned for any kind of variable;
 * the function naively allocates new memory without reusing
 * previously allocated blocks
 *
 * @size: the number of bytes to allocate
 *
 * Return: void* pointer to the allocated memory block
 */

void *naive_malloc(size_t size)
{
	size_t total_size;
	void *new_block;

	size = align_size(size);

	total_size = size + sizeof(size_t);

	size_t page_size = get_page_size();

	size_t pages_needed = total_size / page_size + (total_size %
							page_size != 0);

	new_block = sbrk(pages_needed * page_size);

	if (new_block == (void *)-1)
	{
		perror("naive_malloc: sbrk failed");
		return (NULL);
	}

	*((size_t *)new_block) = size;

	return ((unsigned char *)new_block + sizeof(size_t));
}
