#include <stdio.h>
#include <stdlib.h>
/**
 * my_getline-this is the main function
 * 
 * it gets the input from std
 * @lineptr:ptr to a ptr to the memory location of storing input
 * @n:the size of the memory location
 * @stream:input
 * Return: ssize_t characters read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t buffer_size = *n
	ssize_t read_chars;
	int current_position = 0;

	if (*lineptr == NULL || n == NULL || stream = NULL)
	{
		perror("invalid parameters");
		return (-1);
	}
	//n(size of buffer) has no correlation with memory allocation
	if (*lineptr == NULL)
	{
		buffer_size = 128; //allocate initial size to be filled with memory
		*lineptr = malloc(sizeof(char) * buffer_size);
		if (*lineptr == NULL)
		{
			perror("memory allocation failed");
			return (NULL);
		}
	}
	//now get characters from lineptr
	read_chars = fgetc(stream);//read a single character from filestream
	while (read_chars != EOF)
	{
		if (current_position >= buffer_size - 1)
		{
			buffer_size *= 2;//increase sizeof buffer
			char *new_buff;
			//realloc takes two arguments
			new_buff = realloc(*lineptr, sizeof(char) * buffer_size);
			if(new_buff == NULL)
			{
				perror("Mem reallocation failed");
				return (NULL);
			}
			*lineptr = new_buff;
		}
		//traverse through lineptr
		(*lineptr)[current_position++] = (char)read_chars;

		if (read_chars == '\n') {
			break;
		}

		read_chars = fgetc(stream);//next character

	}
	(*lineptr[current_position]) = '\0';
	if (current_position == 0 && read_chars == EOF)
	{
		perror("no chars read");
		return (-1);
	}
	//free(new_buff)-will be used to free line whne the function is called
	*n = buffer_size;//updates buffer to current size
	return (current_position);
}

