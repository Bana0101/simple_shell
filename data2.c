#include "main.h"

/**
 * set_his_file - a function that got the history file
 * @info: file info
 * Return: pointer with a history
 */

char *set_his_file(info_t *info)
{
	char *buf, *dir;

	dir = val_env(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * wr_hist - a function use write function
 * @info: file info
 * Return: integer
 */
int wr_hist(info_t *info)
{
	char *filename = set_his_file(info);
	list_t *node = NULL;
	ssize_t fd;

	if (!filename)
		return (-1);
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		puts_fd(node->str, fd);
		set_fd('\n', fd);
	}
	set_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * rd_hist - a function use reads for get history
 * @info: file info
 * Return: histcount on success, 0 otherwise
 */

int rd_hist(info_t *info)
{
	ssize_t fd, rdlen, fsize = 0;
	char *buf = NULL, *filename = set_his_file(info);
	struct stat st;
	int i, last = 0, linecount = 0;

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			set_hist_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		set_hist_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		rm_node_idx(&(info->history), 0);
	re_num_hist(info);
	return (info->histcount);
}

/**
 * set_hist_list - a function that set an entry to a history list
 * @info: file info
 * @buf: the buf
 * @linecount: an integer
 * Return: integer
 */
int set_hist_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_nd_in__end(&node, buf, linecount);
	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * re_num_hist - change the number of history list
 * @info: file info
 * Return: integer
 */
int re_num_hist(info_t *info)
{
	int i = 0;
	list_t *node = info->history;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
