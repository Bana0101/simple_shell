#include "main.h"

/**
 * clr_data - clear info_t
 * @info: file info
 * Return: void
 */

void clr_data(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * put_data - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void put_data(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = ignore_separators(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		puts_toalias(info);
		puts_tovars(info);
	}
}

/**
 * rm_data - frees the struct
 * @info: file info
 * @all: true if freeing all fields
 */
void rm_data(info_t *info, int all)
{
	matrix_to_free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			list_to_free(&(info->env));
		if (info->history)
			list_to_free(&(info->history));
		if (info->alias)
			list_to_free(&(info->alias));
		matrix_to_free(info->environ);
			info->environ = NULL;
		free_and_null((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
