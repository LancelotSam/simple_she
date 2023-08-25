#include "shell.h"
/**
 * _parse_input-this is the main function
 *
 * It parses the input from lineptr
 * @lineptr:pointer containing the user input
 * Return: char arguments input
 */
char **_parse_input(char *lineptr)
{
	const char delimiter[] = " ,;:-|";
	int args_index = 0;
	char *token;
	char **args_input;

	args_input = malloc(sizeof(char *) * (MAX_ARGS + 1));

	if (args_input == NULL)
		return (NULL);
	token = strtok(lineptr, delimiter);
	while (token != NULL && args_index < MAX_ARGS - 1)
	{
		if (_strlen(token) >= MAX_LEN)
		{
			perror("Argument too long\n");
			break;
		}
		args_input[args_index++] = _strdup(token);
		token = strtok(NULL, delimiter);
	}
	args_input[args_index] = '\0';

	return (args_input);
}
/**
 * **get_path-this is the main function
 *
 * it gets the path
 * Return: character path tokens
 */
char **get_path()
{

	char *main_path = getenv("PATH");
	int i = 0, j = 0;

	char *path_cpy = _strdup(main_path);
	char *dir;
	char **path_tokens = malloc(sizeof(char *) * (MAX_ARGS + 1));

	if (main_path == NULL)
	{
		perror("Path does not exist");
		return (NULL);
	}
	if (path_tokens == NULL)
	{
		perror("Mem allocatin failed");
		return (NULL);
	}

	dir = strtok(path_cpy, ":");
	while (dir != NULL && i < MAX_PATHS - 1)
	{
		path_tokens[i] = _strdup(dir);
		if (path_tokens[i] == NULL)
		{
			perror("Error duplicating tokens");
			for (; j < i; j++)
			{
				free(path_tokens[j]);
			}
			free(path_tokens);
			free(path_cpy);

			return (NULL);
		}
		dir = strtok(NULL, ":");
		i++;
	}
	path_tokens[i] = '\0';

	free(path_cpy);

	return (path_tokens);
}
/**
 * _parse_path-this is the main function
 *
 * It parse steh gotten pat
 * @path_tokens: tokenized path
 * @args_input: arguments input
 * @full_path: the total length of path
 * Return:void
 */
void _parse_path(char **path_tokens, char **args_input, char full_path[][MAX_LEN])
{
	int ind = 0, path_len;

	for (; path_tokens[ind] != NULL; ind++)
	{
		path_len = _strlen(path_tokens[ind]);
		if (path_len + _strlen(args_input[0]) + 1 >= MAX_LEN)
		{
			perror("Path too long, increase buffer\n");
			return;
		}
		 printf("Evaluating path_tokens[%d]: %s\n", ind, path_tokens[ind]);
		/*check if command starts with / */
		if (args_input[0][0] == '/')
		{
			_strncpy(full_path[ind], args_input[0], MAX_LEN);
		}
		else
		{
			printf("Constructing path using %s and %s\n", path_tokens[ind], args_input[0]);
			snprintf(full_path[ind], MAX_LEN, "%s/%s", path_tokens[ind], args_input[0]);
			/*_strcpy(full_path[ind], path_tokens[ind]);
			_strcat(full_path[ind], "/");
			_strcat(full_path[ind], args_input[0]);*/
		}
	}
}
/**
 * prompt-this is the main function
 *
 * It writes a prompt for user
 *
 * Return:void
 */
/*void prompt(char **lineptr)
{
	const char prompt[] = "(MYShell) $ ";
	size_t buff_size = 0;
	ssize_t read_chars;

	write(STDOUT_FILENO, prompt, _strlen(prompt));

	read_chars = getline(lineptr, &buff_size, stdin);
	if (read_chars == -1) {
		perror("Nothing was entered");
		free(*lineptr);
		*lineptr = NULL;
		return;
	}
	if (read_chars == EOF) {
                free(*lineptr);
                *lineptr = NULL;
                return;
        }
	if (read_chars == 1) {
		perror("Not a cmd");
		free(*lineptr);
		*lineptr = NULL;
		return;
	}

}*/
void prompt(char **lineptr)
{
    const char prompt[] = "(MYShell) $ ";
    size_t buff_size = 0;
    ssize_t read_chars;

    write(STDOUT_FILENO, prompt, _strlen(prompt));

    read_chars = getline(lineptr, &buff_size, stdin);
    if (read_chars == -1 || read_chars == EOF) {
       /* perror("Error reading input");*/
        free(*lineptr);
        *lineptr = NULL;
        return;
    }
/*    if (read_chars == EOF) {
        free(*lineptr);
        *lineptr = NULL;
        return;
    }*/
    if (read_chars == 1 && (*lineptr)[0] == '\n') {
        /* Empty line, nothing was entered*/
        free(*lineptr);
        *lineptr = NULL;
        return;
    }
}


/**
 * my_shell-this is the main function
 *
 * It is a custom simple shell
 * Return: void
 */
void my_shell()
{
	char *lineptr = NULL;
	pid_t PID;
	int i, command_found, exit_status;
	char **args_input;
	char **path_tokens;

	while (1)
	{
		prompt(&lineptr);

		if (lineptr == NULL) {
			break;  /* End of file (Ctrl+D)*/
		}

		/* Remove the newline character */
		if (lineptr[_strlen(lineptr) - 1] == '\n') {
			lineptr[_strlen(lineptr) - 1] = '\0';
		}

		args_input = _parse_input(lineptr);

		if (_strcmp2(args_input[0], "env") == 0)
		{
			env(args_input);
		}
		if (_strcmp2(args_input[0], "exit") == 0)
		{
			exit_status = my_exit(args_input);
			exit(exit_status);
		}

		path_tokens = get_path();

		if (path_tokens == NULL)
		{
			free(args_input);
			continue;  /* for next iteration*/
		}

		command_found = 0;
		for (i = 0; path_tokens[i] != NULL; i++)
		{
			char full_path[MAX_LEN];
			snprintf(full_path, MAX_LEN, "%s/%s", path_tokens[i], args_input[0]);

			if (access(full_path, F_OK | X_OK) == 0)
			{
				command_found = 1;
				PID = fork();
				if (PID == 0)
				{
					execve(full_path, args_input, NULL);
					perror("execve"); /* if execve fails*/

					/* Exit the child process on error*/
					/*exit(EXIT_FAILURE);*/
				}
				else if (PID == -1)
				{
					perror("fork");
					break;
				}
				else
				{
					wait(NULL); /* Wait for the child to complete*/
					break;  /*since command was found and executed, break loop*/
				}
			}
		}

		if (!command_found)
		{
			fprintf(stderr, "Command not found: %s\n", args_input[0]);
		}

		free(args_input);
		for (i = 0; path_tokens[i] != NULL; i++)
		{
			free(path_tokens[i]);
		}
		free(path_tokens);
	}

	free(lineptr);
}
