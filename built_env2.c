#include "main.h"

/**
 * val_env - a function that get the environment
 * @info: file info
 * @name: the name of the var
 * Return: pointer
*/
char *val_env(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = check_if_start(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}
/**
 * rev_atoi - transforme a string to an integer
 * @s: the converted string
 * Return: integer
 */

int rev_atoi(char *s)
{
	unsigned long int result = 0;
	int i = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * exec_set_env - a new environment set
 * @info: file info
 *  Return: integer
*/

int exec_set_env(info_t *info)
{
	if (info->argc != 3)
	{
		p_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (init_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * exec_un_env - delete an environment
 * @info: file info
 * Return: 0
*/

int exec_un_env(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		p_puts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		un_set_env(info, info->argv[i]);

	return (0);
}

/**
 * linked_env_list - an env linked list
 * @info: file info
 * Return: 0
*/
int linked_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_nd_in__end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
