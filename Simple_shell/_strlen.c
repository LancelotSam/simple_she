#include "shell.h"
/**
 * _strlen-this is the main function
 *
 * It calculates the length of a string
 * @str:the str whose len is to be determined
 * Return: int length(index)
 */
int _strlen(const char *str)
{
	int i = 0;

	if (*str = '\0')
	{
		return (0);
	}
	while (str[i])
	{
		i++;
	}
	return (i);
}
