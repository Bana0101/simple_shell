#include "main.h"

/**
 * p_error - print an error message
 * @info: file info
 * @estr: second arguments
 * Return: integer
 */

void p_error(info_t *info, char *estr)
{
	p_puts(info->fname);
	p_puts(": ");
	print_d(info->line_count, STDERR_FILENO);
	p_puts(": ");
	p_puts(info->argv[0]);
	p_puts(": ");
	p_puts(estr);
}

/**
 * print_d - print integer
 * @input: the input
 * @fd: file descreptor
 * Return: integer
 */

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = std_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;
	return (count);
}

/**
 * **ignore_separators - a function that concat ignored separator
 * @str: the whole string
 * @d: the separator
 * Return: string
 */

char **ignore_separators(char *str, char *d)
{
	char **s;
	int i, j, k, m, counter = 0;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!_check_separators(str[i], d) &&
				(_check_separators(str[i + 1], d) || !str[i + 1]))
			counter++;

	if (counter == 0)
		return (NULL);
	s = malloc((1 + counter) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < counter; j++)
	{
		while (_check_separators(str[i], d))
			i++;
		k = 0;
		while (!_check_separators(str[i + k], d) && str[i + k])
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
 * convert_number - converter function
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rm_comments - a function that remove comments
 * @buf: a buffer to modify
 * Return: 0;
 */

void rm_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
