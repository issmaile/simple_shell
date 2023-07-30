#include "header.h"

/**
 * _memset - fills memory with a constant byte
 *@ptr: the pointer to the memory area
 *@byt: the byte to fill *s with
 *@amount: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *ptr, char byt, unsigned int amount)
{
	unsigned int i;

	for (i = 0; i < amount; i++)
		ptr[i] = byt;
	return (ptr);
}

/**
 * tfree - frees a string of strings
 *@pp: string of strings
 */
void tfree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 *@ptr: pointer to previous malloc'ated block
 *@old_size: byte size of previous block
 *@new_size: byte size of new block
 *Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
