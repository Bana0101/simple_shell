#include "main.h"

/**
 * exec_alias - alias function
 * @info: file info
 * Return: 0
*/
int exec_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			display_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			with_alias(info, info->argv[i]);
		else
			display_alias(begin_node(info->alias, info->argv[i], '='));
	}
	return (0);
}

/**
 * p_puts - prints a string
 * @str: the string to be printed
 * Return: Nothing
 */

void p_puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		std_putchar(str[i]);
		i++;
	}
}

/**
 * std_putchar - set a char to stderr
 * @c: The character
 * Return: 1 or 0.
 */

int std_putchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int i;

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * set_fd - put c to file desc
 * @c: char
 * @fd: the file
 * Return: 1 or 0.
 */

int set_fd(char c, int fd)
{
	static char buf[WRITE_BUF_SIZE];
	static int i;

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * puts_fd - prints an input string
 * @str: the string to be printed
 * @fd: the file
 * Return: the number of chars
 */

int puts_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
		i += set_fd(*str++, fd);
	return (i);
}
