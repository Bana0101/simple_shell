#include "main.h"

/**
 * _strlen - determine the lenght of a string
 * @str: the string
 * Return: integer
 */
int _strlen(char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str++)
		i++;
	return (i);
}

/**
 * _strcmp - a function that compare two strings.
 * @s1: the string
 * @s2: the string to be compared
 * Return: integer
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * check_if_start - a function that check if arg2 start with arg1
 * @str_searched: to check
 * @str_source: the string to find arg1
 * Return: string
 */
char *check_if_start(const char *str_searched, const char *str_source)
{
	while (*str_source)
		if (*str_source++ != *str_searched++)
			return (NULL);
	return ((char *)str_searched);
}

/**
 * _strcat - function that concatenates two strings
 * @dest: the destination string
 * @src: the source string
 * Return: string
 */

char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
