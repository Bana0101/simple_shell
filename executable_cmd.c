#include "main.h"

/**
 * _check_separators - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int _check_separators(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * exec_exit - for exits
 * @info: file information
 * Return: integer
*/

int exec_exit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = rev_atoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			p_error(info, "Illegal number: ");
			p_puts(info->argv[1]);
			std_putchar('\n');
			return (1);
		}
		info->err_num = rev_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
/**
 * exec_env - a function to print the environment
 * @info: file info
 * Return: 0
*/

int exec_env(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * exec_help - changes directory of the process
 * @info: file info
 * Return: 0
*/
int exec_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

/**
 * exec_cd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
*/
int exec_cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = val_env(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = val_env(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!val_env(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(val_env(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = val_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		p_error(info, "can't cd to ");
		p_puts(info->argv[1]), std_putchar('\n');
	}
	else
	{
		init_env(info, "OLDPWD", val_env(info, "PWD="));
		init_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
