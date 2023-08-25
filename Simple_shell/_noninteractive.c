#include "shell.h"
/**
 * _noninteractive-this is the main function
 *
 * It receives arguments from command line
 * @name:the name of the program
 * Return:void
 */
void _noninteractive(char *name)
{
	char **args;
	char *line;
	char *prompt = "(MyShell) $ ";

	while (1)
	{
		write(STDOUT_FILENO, prompt, _strlen(prompt));

		ssize_t chars_read = _getline(&line, NULL, stdin);
	       if (chars_read > 0)
	       {
		       args = _parse_input(lineptr);
	       }
	       else if (cars_read == 0)
	       {
		       perror("no characters read");
	       }
	       else
	       {
		       perror("Error reading input");
	       }







	       free(line);
