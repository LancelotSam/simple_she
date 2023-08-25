#include "shell.h"
/**
 * _strcmp2-this is the main function
 *
 * it compares two strings
 * @s1: the first string
 * @s2: the second string
 * Return: 0 if str equal, -1 if s1<s2, 1 if s1>s2
 */
int _strcmp2(const char *s1, const char *s2)
{
	size_t i = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
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
 * _atoi-this is the main function
 *
 * It converts a str to int
 * @str:the string to be converted
 * Return: integer of converted string
 */
int _atoi(const char *str)
{
	int i = 0, reslt = 0;

	/**
	*	  if (str[i] == '-')
	*	{
	*	sign = -1;
	*	i++;
	*	}
	*	else if (str[i] == '+')
	*	{
	*	sign = 1;
	*	i++;
	*	}
		*/
	for (; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			/*iteratig t right means shifting digits to left*/
			/*this multiplies the number by 10 (base 10)*/
			/*str[i] - '\0', subtracts ascii val of 0,i.e 48*/
			reslt = reslt * 10 + str[i] - '0';
		}
	}
	return (reslt);
}
/**
 * my_exit-this is the main function
 *
 * It exits with an integer status
 * @args:the expected exit argument to cmd line
 * Return: int exit status
 */
int my_exit(char *args[])
{
	if (args[1])
	{
		return (_atoi(args[1]));
	}
	else
	{
		return (0);
	}
}
