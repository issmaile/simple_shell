#include "main.h"

/**
 * _freeargs - frees the args
 * @args: tokenazied arg
 *
 * Return:void
 */
void  _freeargs(char **args)
{
	int index;
	int len = 0;

	while (args[len] != NULL)
		len++;

	for (index = 0; index <= len; index++)
	{
		free(args[index]);
	}
}

/**
 * _freeenv - frees environ
 *
 * Return:void
 */
void _freeenv(void)
{
	int index;

	for (index = 0; environ[index] != NULL; index++)
	{
		free(environ[index]);
	}
	free(environ);
}

/**
 * _freepath - frees path
 * @path: fress path
 *
 * Return:void
 */
void _freepath(linked_path *path)
{
	linked_path *temp;

	while (temp != NULL)
	{
		temp = path->next;
		free(path->dir);
		free(path);
		path = temp;
	}
}
