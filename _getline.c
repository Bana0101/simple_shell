#include "main.h"

void sg_handler(__attribute__((unused))int sig_num);

/**
 * set_a_buf - put buf
 * @info: file info
 * @buf: the buf
 * @len: the length
 * Return: a number
 */

ssize_t set_a_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sg_handler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = my_getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			rm_comments(*buf);
			set_hist_list(info, *buf, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * set_buf_input - a function that set a buf from std
 * @info: file info
 * Return: a number
 */

ssize_t set_buf_input(info_t *info)
{
	char **buf_p = &(info->arg), *p;
	static char *buf;
	ssize_t r = 0;
	static size_t i, j, len;

	_putchar(BUF_FLUSH);
	r = set_a_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;
		_cont_check(info, buf, &j, i, len);
		while (j < len)
		{
			if (check_sep_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = p;
		return (_strlen(p));
	}
	*buf_p = buf;
	return (r);
}

/**
 * rd_input_buf - a function that read the buf
 * @info: file info
 * @buf: the buf
 * @i: an integer
 * Return: integer
 */

ssize_t rd_input_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * my_getline - a function do the same as getline function
 * @info: file info
 * @ptr: a pointer
 * @length: the length
 * Return: integer
 */
int my_getline(info_t *info, char **ptr, size_t *length)
{
	size_t k;
	static char buf[READ_BUF_SIZE];
	char *p = NULL, *new_p = NULL, *c;
	ssize_t r = 0, s = 0;
	static size_t i, len;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;
	r = rd_input_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = new_allocat(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);
	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);
	s += k - i;
	i = k;
	p = new_p;
	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sg_handler - display a new line if the input was ctrl-C
 * @sig_num: unused variable
 * Return: void
 */
void sg_handler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
