#include "main.h"

/**
 * set_env_all - a function that copy env
 * @info: file info
 * Return: array
 */

char **set_env_all(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = str_the_list(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * un_set_env - a function that delete env
 * @info: file info
 * @var: the string
 * Return: integer
 */

int un_set_env(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);
	while (node)
	{
		p = check_if_start(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = rm_node_idx(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * init_env - Init an env
 * @info: file info
 * @var: the string
 * @value: the var value
 * Return: integer
 */

int init_env(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);
	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = check_if_start(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_nd_in__end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
