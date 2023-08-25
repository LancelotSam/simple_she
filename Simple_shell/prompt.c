#include "shell.h"
/**
 * prompt-this is the main function
 *
 * It prints my shell prompt
 *
 * Return: void
 */
void prompt()
{
	const char prompt[] = "(MYShell) $ ";
	char *lineptr = NULL;

	while (1) 
	{
		write(STDOUT_FILENO, prompt, _strlen(prompt));

		ssize_t read_chars = getline(&lineptr, &buff_size, stdin);

		if (read_chars == -1 || read_chars == EOF) {
			perror("Nothing was entered");
			continue;
		}
		if (read_chars == 1) {
			perror("Not a cmd");
			continue;
		}
	}
}
