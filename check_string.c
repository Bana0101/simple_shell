#include "main.h"

/**
 * check_sep_chain - function check if its chain of separator
 * @info: file info
 * @buf: a buf
 * @p: pointer
 * Return: integer
 */
int check_sep_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * _cont_check - function check chain
 * @info: file info
 * @buf: a buf
 * @p: pointer
 * @i: the beginning
 * @len: the length
 * Return: Void
 */

void _cont_check(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * puts_toalias - a function that puts an aliases in the string
 * @info: file info
 * Return: integer
 */

int puts_toalias(info_t *info)
{
	char *p;
	int i;
	list_t *node;

	for (i = 0; i < 10; i++)
	{
		node = begin_node(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * puts_tovars - a function that puts the vars in the string
 * @info: file info
 * Return: integer
 */
int puts_tovars(info_t *info)
{
	list_t *node;
	int i = 0;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			puts_tostring(&(info->argv[i]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			puts_tostring(&(info->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = begin_node(info->env, &info->argv[i][1], '=');
		if (node)
		{
			puts_tostring(&(info->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		puts_tostring(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * puts_tostring - a function that puts a string
 * @old: first string
 * @new: the string to set
 * Return: integer
 */
int puts_tostring(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
