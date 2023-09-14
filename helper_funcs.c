#include "shell.h"

/**
 * sigint_handler - doesn't exit in case of Ctrl-C
 * @sig: required for signal function to run properly
 *
 * Description: ignore sig, print newline, print the prompt
 * Call to fflush discards the Ctrl-C
 */
void sigint_handler(int sig)
{
	(void)sig;
	 _putchar('\n');
	 print_prompt();
	 fflush(stdout);
}

/**
 * free_everything - frees arrays of strings
 * @args: array of strings to free
 */
void free_everything(char **args)
{
	int i;

	if (!args)
		return;

	for (i = 0; args[i]; i++)
		free(args[i]);

	free(args);
}

/**
* parse_line - handle newline character if found, and parses the input line
* @line: line read from stdin
* @get: size of line returned from getline
*
* Return: parsed line
*/
char **parse_line(char *line, int get)
{
	char **input = NULL;

	if (line[get - 1] == '\n')
		line[get - 1] = '\0';
	input = _strtok(line, ' ');

	return (input);
}
