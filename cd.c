#include "shell.h"
/**
 * _cd-this is the main function
 *
 * It changes the directory
 * @args:the list of commands
 * Return: 0 i succefful, -1 if unsuccessful
 */
int _cd(char **args)
{
	if (args[1] == NULL)
	{
		perror("Expected arguments to cd: \"cd\"\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("Error chnaging current directory");
			return (-1);
		}
	}
	return (0);
}
