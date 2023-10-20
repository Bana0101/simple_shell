#include "main.h"

/**
 * len_list - the length of the list
 * @lis: a pointer
 * Return: the length
 */
size_t len_list(const list_t *lis)
{
	size_t i = 0;

	while (lis)
	{
		lis = lis->next;
		i++;
	}
	return (i);
}

/**
 * str_the_list - get the list
 * @head: a pointer
 * Return: the string
 */
char **str_the_list(list_t *head)
{
	list_t *node = head;
	size_t i = len_list(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - display the list
 * @lis: pointer
 * Return: the length
 */
size_t print_list(const list_t *lis)
{
	size_t i = 0;

	while (lis)
	{
		_puts(convert_number(lis->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(lis->str ? lis->str : "(nil)");
		_puts("\n");
		lis = lis->next;
		i++;
	}
	return (i);
}

/**
 * begin_node - get node that begin with  pref
 * @node: pointer
 * @pref: for comparing
 * @c: a char
 * Return: null or the node
 */
list_t *begin_node(list_t *node, char *pref, char c)
{
	char *p = NULL;

	while (node)
	{
		p = check_if_start(node->str, pref);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_idx_node - count and find the idx
 * @head: a pointer
 * @node: another pointer
 * Return: integer
 */

ssize_t set_idx_node(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
