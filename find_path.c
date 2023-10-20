#include "main.h"

/**
 * check_command - a function that check if its execute
 * @info: file info
 * @path: the path
 * Return: integer
 */
int check_command(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * c_duplication - a function that duplicate char
 * @pathstr: the whole PATH
 * @start: the beginning
 * @stop: the end
 * Return: string
 */
char *c_duplication(char *pathstr, int start, int stop)
{
	int i = 0, k = 0;
	static char buf[1024];

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - a function that find the path
 * @info: file info
 * @pathstr: getenv("PATH")
 * @cmd: the command line
 * Return: the cmd with the path
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && check_if_start(cmd, "./"))
	{
		if (check_command(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = c_duplication(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (check_command(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
