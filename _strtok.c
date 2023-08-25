#include "shell.h"
/**
 * _strncpy-this is the main function
 *
 * It copies a string
 * @dest:this is the destination
 * @src:this is the source string
 * @n:the number of characters to be copied from src
 * Return: copied chars
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
	size_t i = 0;

	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}

	return (dest);
}
/**
 * _strchr-this is the main function
 *
 * it checks for characters in a string
 * @str:the str to be checked
 * @c:the character to be checked
 * Return: string character found
 */
const char *_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == c)
		{
			return (str);
		}
		str++;
	}
	return (NULL);
}
/**
 * _strtok-this is the main function
 *
 *  it tokenizes a string
 *  @str:str input to be tokenized
 *  @delim:the delimiter to be used
 *  Return: pointer to the position of the last token
 */
const char *_strtok(const char *str, const char *delim)
{
	static const char *last_token = NULL;
	const char *current_token = NULL;
	size_t token_length;
	char *token_copy;

	if (str != NULL)
		last_token = str;
	else
		if (last_token == NULL)
			return (NULL);
	str = last_token;
	/*skip leading delims*/
	while (*str && _strchr(delim, *str))
	{
		str++;
	}
	if (*str == '\0')
	{
		last_token = NULL;
		return (NULL);
	}
	current_token = str;
	while (*str && !_strchr(delim, *str))
	{ /*check end of current tok*/
		str++;
	}
	token_length = str - current_token;

	last_token = str + 1;

	token_copy = malloc(token_length + 1);

	if (token_copy == NULL)
		return (NULL);
	_strncpy(token_copy, current_token, token_length);
	token_copy[token_length] = '\0';

	return (token_copy);
}

