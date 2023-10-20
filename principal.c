#include "main.h"

/**
 * exec_f - the principal function
 * @info: file info
 * @av: the arguments
 * Return: void
 */

void exec_f(info_t *info, char **av)
{
	linked_env_list(info);
	rd_hist(info);
	exec_function(info, av);
}
/**
 * exec_function - the exec function
 * @info: file info
 * @av: the matrix
 * Return: integer
 */
int exec_function(info_t *info, char **av)
{
	int set_ret_built = 0;
	ssize_t r = 0;

	while (r != -1 && set_ret_built != -2)
	{
		clr_data(info);
		if (interactive(info))
			_puts("$ ");
		std_putchar(BUF_FLUSH);
		r = set_buf_input(info);
		if (r != -1)
		{
			put_data(info, av);
			set_ret_built = find_bcmd(info);
			if (set_ret_built == -1)
				_get_the_command(info);
		}
		else if (interactive(info))
			_putchar('\n');
		rm_data(info, 0);
	}
	wr_hist(info);
	rm_data(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (set_ret_built == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (set_ret_built);
}

/**
 * find_bcmd -  a function that finds a cmd
 * @info: file info
 * Return: integer
 */
int find_bcmd(info_t *info)
{
	int i, built_in_ret = -1;

	builtin_table builtintbl[] = {
		{"exit", exec_exit},
		{"env", exec_env},
		{"help", exec_help},
		{"history", exec_his},
		{"setenv", exec_set_env},
		{"unsetenv", exec_un_env},
		{"cd", exec_cd},
		{"alias", exec_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * _get_the_command - finds a command in PATH
 * @info: file info
 * Return: void
 */

void _get_the_command(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!_check_separators(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;
	path = find_path(info, val_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_with_command(info);
	}
	else
	{
		if ((interactive(info) || val_env(info, "PATH=")
					|| info->argv[0][0] == '/') && check_command(info, info->argv[0]))
			fork_with_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			p_error(info, "not found\n");
		}
	}
}

/**
 * fork_with_command - execute with fork
 * @info: file info
 * Return: void
 */
void fork_with_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, set_env_all(info)) == -1)
		{
			rm_data(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				p_error(info, "Permission denied\n");
		}
	}
}
