#include "main.h"


/**
 * sigintHandler - Entry point(CTRL + C)
 * @sig_num: signal numberadasdasd
 *
 *
 * Return: the length of a string.
 */
void sigintHandler(int sig_num)
{
	(void)sig_num;
	write(STDOUT_FILENO, "\n", 1);
	signal(SIGINT, sigintHandler);
}
