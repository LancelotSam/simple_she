#include "shell.h"
/**
 * _strdup-this is the main function
 *
 * It duplicates a string
 * @src: the string to be duplicated
 * Return: duplicated string char
 */
char *_strdup(const char *src)
{
	int len = 0;
	char *str;
	char *p;

	if (src == NULL)
		return (NULL);
	while (src[len])
	{
		len++;
	}
	/*allocate memory to store duplice*/
	str = malloc(len + 1);

	if (str == NULL)
	{
		perror("mem allocation failed");
		return (NULL);
	}
	/*since you cannot manipulate str, assign it to a pointer*/
	p = str;
	/*copy src to str*/
	while (*src)
	{
		*p++ = *src++;
	}
	*p = '\0';

	return (str);
}

/**
 * _strcpy-this is the main function
 *
 * It copies a string from src to dest
 * @dest:where str is to be copied into
 * @src: source of str
 * Return: destination string with new str
 */
char *_strcpy(char *dest, const char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}

/**
 * _strlen-this is the main function
 *
 * It calculates the length of a string
 * @str: string whose length is to be determined
 * Return: integer length
 */
int _strlen(const char *str)
{
	int index = 0;

	if (*str == '\0')
		return (0);
	while (str[index])
	{
		index++;
	}

	return (index);
}

/**
 * _strcmp-this is the main function
 *
 * It compares two strings
 * @s1: this is the first string
 * @s2:this is the second string
 * @n:number of characters to compare
 * Return: -1 if s1 < s2, 1 if s1 > s2, & 0 if s1 == s2
 */
int _strcmp(const char *s1, const char *s2, size_t n)
{
	size_t i = 0;

	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if (s1[i] < s2[i])
			return (-1);
		else if (s1[i] > s2[i])
			return (1);
		i++;
	}
	return (0);
}

/**
 * _strcat-this is the main function
 *
 * It concatenates two strings
 * @dest:this is the destination str
 * @src:tis is the source str
 * Return: a concatenated str
 */
char *_strcat(char *dest, const char *src)
{
	int dest_len = 0, i = 0, TOTAL_LEN = 64;

	while (dest[dest_len] != '\0')
	{
		dest_len++;
	}

	while (src[i] != '\0' && i < TOTAL_LEN - dest_len)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';

	return (dest);
}
