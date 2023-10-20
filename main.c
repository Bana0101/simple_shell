#include "main.h"

/**
 * main - the entry point
 * @ac: the number of arguments
 * @av: the arguments
 * Return: 0
 */

int main(int ac, char **av)
{
	int fd = 2;
	info_t info[] = { INFO_INIT };

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				p_puts(av[0]);
				p_puts(": 0: Can't open ");
				p_puts(av[1]);
				std_putchar('\n');
				std_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	exec_f(info, av);
	return (EXIT_SUCCESS);
}
