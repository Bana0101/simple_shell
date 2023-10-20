#include "main.h"

/**
 * set_const_byte - a function that set a char
 * @str: the pointer
 * @c: the char to put in the pointer
 * @n: integer
 * Return: the string
 */
char *set_const_byte(char *str, char c, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		str[i] = c;
	return (str);
}

/**
 * **ignore_separators2 - a function do the same
 * @str: the string
 * @d: the separator
 * Return: a string
 */
char **ignore_separators2(char *str, char d)
{
	int i, j, k, m, counter = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
				    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			counter++;
	if (counter == 0)
		return (NULL);
	s = malloc((1 + counter) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < counter; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
/**
 * free_and_null - a function that frees allocation
 * @pointer: a pointer
 * Return: integer
 */
int free_and_null(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}

/**
 * matrix_to_free - function that free double pointer
 * @matrix: the matrix
 */
void matrix_to_free(char **matrix)
{
	char **a = matrix;

	if (!matrix)
		return;
	while (*matrix)
		free(*matrix++);
	free(a);
}

/**
 * new_allocat - a functin that reallocate the memory
 * @str: pointer
 * @old_ssize: integer
 * @new_ssize: integer
 * Return: pointer
 */

void *new_allocat(void *str, unsigned int old_ssize, unsigned int new_ssize)
{
	char *p;

	if (!str)
		return (malloc(new_ssize));
	if (!new_ssize)
		return (free(str), NULL);
	if (new_ssize == old_ssize)
		return (str);

	p = malloc(new_ssize);
	if (!p)
		return (NULL);
	old_ssize = old_ssize < new_ssize ? old_ssize : new_ssize;
	while (old_ssize--)
		p[old_ssize] = ((char *)str)[old_ssize];
	free(str);
	return (p);
}
