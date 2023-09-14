#include "shell.h"

/**
 * print_error - prints a custom error message
 * @i: index of the command in history
 * @s: name of the program
 * @argv: array of arguments from the command line
 *
 * Description: Concatenate strings to format the error message
 * Free previous concatenation at every new string
 * When the string is completed, write message to standard error
 */
void print_error(int *i, char *s, char **argv)
{
	char *buf1 = NULL, *buf2 = NULL, *buf3 = NULL, *buf4 = NULL, *buf5 = NULL;
	char *number = NULL;

	number = convert(*i, 10);

	buf1 = str_concat(s, ": ");
	buf2 = str_concat(buf1, number);
	free(buf1);
	buf3 = str_concat(buf2, ": ");
	free(buf2);
	buf4 = str_concat(buf3, argv[0]);
	free(buf3);
	buf5 = str_concat(buf4, ": not found\n");
	free(buf4);
	write(2, buf5, _strlen(buf5));
	free(buf5);
}

/**
 * print_error_env - prints a custom error message for env builtin
 * @argv: array of arguments from the command line
 * Description: Concatenate strings to format the error message
 * Free previous concatenation at every new string
 * When the string is completed, write message to standard error
 */
void print_error_env(char **argv)
{
	char *buf1 = NULL, *buf2 = NULL, *buf3 = NULL;

	buf1 = str_concat(argv[0], ": ");
	buf2 = str_concat(buf1, argv[1]);
	free(buf1);
	buf3 = str_concat(buf2, ": No such file or directory\n");
	free(buf2);
	write(2, buf3, _strlen(buf3));
	free(buf3);
}

/**
 * print_error_exit - prints a custom error message for exit builtin
 * @i: index of the command in history
 * @s: name of the program
 * @argv: array of arguments from the command line
 * Description: Concatenate strings to format the error message
 * Free previous concatenation at every new string
 * When the string is completed, write message to standard error
 */
void print_error_exit(int *i, char *s, char **argv)
{
	char *buf1 = NULL, *buf2 = NULL, *buf3 = NULL;
	char *buf4 = NULL, *buf5 = NULL, *buf6 = NULL, *buf7 = NULL;
	char *number = NULL;

	number = convert(*i, 10);

	buf1 = str_concat(s, ": ");

	buf2 = str_concat(buf1, number);
	free(buf1);
	buf3 = str_concat(buf2, ": ");
	free(buf2);
	buf4 = str_concat(buf3, argv[0]);
	free(buf3);
	buf5 = str_concat(buf4, ": Illegal number: ");
	free(buf4);
	buf6 = str_concat(buf5, argv[1]);
	free(buf5);
	buf7 = str_concat(buf6, "\n");
	free(buf6);
	write(2, buf7, _strlen(buf7));
	free(buf7);
}

/**
 * print_error_main - prints a custom error message for main
 * @av: array of arguments passed to main
 * Description: Concatenate strings to format the error message
 * Free previous concatenation at every new string
 * When the string is completed, write message to standard error
 */
void print_error_main(char **av)
{
	char *buf1 = NULL, *buf2 = NULL, *buf3 = NULL;

	buf1 = str_concat(av[0], ": 0: Can't open ");
	buf2 = str_concat(buf1, av[1]);
	free(buf1);
	buf3 = str_concat(buf2, "\n");
	free(buf2);
	write(2, buf3, _strlen(buf3));
	free(buf3);
}

/**
 * print_error_cd - prints a custom error message for cd
 * @i: index of the command in history
 * @s: name of the program
 * @argv: array of arguments from the command line
 * Description: Concatenate strings to format the error message
 * Free previous concatenation at every new string
 * When the string is completed, write message to standard error
 */
void print_error_cd(int *i, char *s, char **argv)
{
	char *buf1 = NULL, *buf2 = NULL, *buf3 = NULL, *buf4 = NULL;
	char *buf5 = NULL, *buf6 = NULL;
	char *number = NULL;

	number = convert(*i, 10);

	buf1 = str_concat(s, ": ");
	buf2 = str_concat(buf1, number);
	free(buf1);
	buf3 = str_concat(buf2, ": ");
	free(buf2);
	buf4 = str_concat(buf3, argv[0]);
	free(buf3);
	buf5 = str_concat(buf4, ": can't cd to ");
	free(buf4);
	buf6 = str_concat(buf5, argv[1]);
	free(buf5);
	write(2, buf6, _strlen(buf6));
	free(buf6);
}
