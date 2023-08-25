#include "shell.h"
/**
 * env-this is the main function
 *
 * It prints the environment of the system
 * @args:the list of arguments received
 * Return: 0 if successful
 */
int env(char **args)
{
	int count = 0;

	args = environ;

	while (args[count])
	{
		write(STDOUT_FILENO, environ[count], _strlen(environ[count]));
		write(STDOUT_FILENO, "\n", 1);
		count++;
	}
	return (0);
}

