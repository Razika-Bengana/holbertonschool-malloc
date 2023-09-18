#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 * main - the entr point
 *
 * program that demonstrates the use of the sbrk() system call,
 * which is used to control the program break;
 * the program break is the end of the process's data segment
 * (just beyond the end of the uninitialized data segment);
 * increasing the program break has the effect of allocating memory
 * to the process;
 * decreasing the break deallocates memory
 *
 * Here, we need to write a simple program that extends the program break
 * by 1 byte, in order to store the char H in it;
 * we have to try to print the address of the program break before extending it;
 * After extending the address, we print the char stored there
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */

int main(void)
{
	void *p1, *p2;

	p1 = sbrk(0);
	if (p1 == (void *)-1)
	{
		perror(NULL);
		return (EXIT_FAILURE);
	}
	printf("Starting break is %p\n", p1);

	p2 = sbrk(1);
	if (p2 == (void *)-1)
	{
		perror(NULL);
		return (EXIT_FAILURE);
	}
	p2 = sbrk(0);
	printf("Break after extension is %p\n", p2);

	*((char *)p1) = 'H';
	printf("Address of our char is %p\n", p1);
	printf("Value at this address is '%c'\n", *((char *)p1));

	return (EXIT_SUCCESS);
}
