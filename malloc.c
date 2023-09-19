#include "malloc.h"


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
 * _malloc - program that naively allocates a memory block in the heap
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

void *_malloc(size_t size)
{
	static void *current_break, *page_end;
	void *block_ptr;
	size_t block_size, total_size, page_size, pages_needed;

	size = align_size(size);
	total_size = size + sizeof(size_t);
	page_size = get_page_size();

	block_ptr = current_break;
	while (block_ptr && block_ptr < page_end)
	{
		block_size = *((size_t *)block_ptr);

		if (block_size == 0 && (unsigned char *)block_ptr + total_size
		    <= (unsigned char *)page_end)
		{

			*((size_t *)block_ptr) = size;
			return ((unsigned char *)block_ptr + sizeof(size_t));
		}

		block_ptr = (unsigned char *)block_ptr + block_size +
			sizeof(size_t);
	}

	if (current_break == NULL || (unsigned char *)current_break +
	    total_size > (unsigned char *)page_end)
	{
		pages_needed = total_size / page_size + (total_size %
							 page_size != 0);

		block_ptr = sbrk(pages_needed * page_size);
		if (block_ptr == (void *)-1)
		{
			perror("naive_malloc: sbrk failed");
			return (NULL);
		}
		current_break = block_ptr;
		page_end = (unsigned char *)block_ptr + pages_needed *
			page_size;
	}
	else
	{
		block_ptr = current_break;
	}

	*((size_t *)block_ptr) = size;
	current_break = (unsigned char *)block_ptr + total_size;

	return ((unsigned char *)block_ptr + sizeof(size_t));
}
