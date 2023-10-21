#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ;

#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define USE_GETLINE 0
#define USE_STRTOK 0
#define CONVERT_UNSIGNED	2
#define CONVERT_LOWERCASE	1
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096


/**
 * struct liststr - a list
 * @num: arguments
 * @str: pointer
 * @next: points to the next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo -  a function,
 * @argv: tokenize the argv
 * @arg: the arguments (command line)
 * @argc: the number of arguments
 * @line_count: the number line err
 * @err_num: for exit
 * @path: the whole cmd (with path)
 * @fname: the file name of the programm
 * @environ: the environ
 * @history: the data node
 * @linecount_flag: an integer
 * @env: a pointer that get the environ
 * @alias: the alias
 * @status: to restore the return the last status
 * @cmd_buf: integer
 * @env_changed: in the case that the environ change
 * @cmd_buf_type: the type of the command line
 * @readfd: the file descriptor
 * @histcount: the data of the line count
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - list
 * @type: the type
 * @func: the function to return
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

void exec_f(info_t *, char **);
int find_bcmd(info_t *);
void _get_the_command(info_t *);
void fork_with_command(info_t *);
int exec_function(info_t *, char **);
char *find_path(info_t *, char *, char *);
char *_strcat(char *, char *);
int loophsh(char **);
void p_puts(char *);
int std_putchar(char);
char *_strchr(char *, char);
int set_fd(char, int);
int puts_fd(char *, int);
int _strlen(char *);
int _strcmp(char *, char *);
char *check_if_start(const char *, const char *);
char *_strdup(const char *);
int _putchar(char);
void _puts(char *);
char **ignore_separators(char *, char *);
char *_strncpy(char *, char *, int);
char **ignore_separators2(char *, char);
char *set_const_byte(char *, char, unsigned int);
char *_strncat(char *, char *, int);
void matrix_to_free(char **);
void *new_allocat(void *, unsigned int, unsigned int);
int free_and_null(void **);
int interactive(info_t *);
int _check_separators(char, char *);
int _isalpha(int);
int _atoi(char *);
int rev_atoi(char *);
void p_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void rm_comments(char *);
char *_strcpy(char *, char *);
int exec_exit(info_t *);
int exec_cd(info_t *);
int exec_help(info_t *);
int with_alias(info_t *info, char *str);
int display_alias(list_t *node);
int exec_his(info_t *);
int exec_alias(info_t *);
ssize_t set_buf_input(info_t *);
int my_getline(info_t *, char **, size_t *);
void clr_data(info_t *);
int check_command(info_t *, char *);
void put_data(info_t *, char **);
void rm_data(info_t *, int);
char *val_env(info_t *, const char *);
int exec_env(info_t *);
int exec_set_env(info_t *);
int exec_un_env(info_t *);
int linked_env_list(info_t *);
char **set_env_all(info_t *);
int un_set_env(info_t *, char *);
int init_env(info_t *, char *, char *);
int wr_hist(info_t *info);
int rd_hist(info_t *info);
int set_hist_list(info_t *info, char *buf, int linecount);
int re_num_hist(info_t *info);
list_t *add_nd_in_(list_t **, const char *, int);
list_t *add_nd_in__end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int rm_node_idx(list_t **, unsigned int);
void list_to_free(list_t **);
size_t len_list(const list_t *);
char **str_the_list(list_t *);
size_t print_list(const list_t *);
list_t *begin_node(list_t *, char *, char);
ssize_t set_idx_node(list_t *, list_t *);
int check_sep_chain(info_t *, char *, size_t *);
void _cont_check(info_t *, char *, size_t *, size_t, size_t);
int puts_toalias(info_t *);
int puts_tovars(info_t *);
int puts_tostring(char **, char *);

#endif
