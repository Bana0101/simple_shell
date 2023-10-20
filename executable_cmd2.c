#include "main.h"
/**
 * exec_his - the history list
 * @info: file information
 * Return: integer
*/
int exec_his(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * un_alias - set alias to a string
 * @info: file info
 * @str: the string alias
 * Return: 0 or 1
*/

int un_alias(info_t *info, char *str)
{
	int ret;
	char *p, c;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = rm_node_idx(&(info->alias),
		set_idx_node(info->alias, begin_node(info->alias, str, -1)));
	*p = c;
	return (ret);
}
/**
 * display_alias - a function tha print an alias string
 * @node: the node
 * Return: integer
*/

int display_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * with_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
*/

int with_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (un_alias(info, str));
	un_alias(info, str);
	return (add_nd_in__end(&(info->alias), str, 0) == NULL);
}
