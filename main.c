#include "shell.h"

/**
* exec - handles execution of commands
* @input: array of arguments from standard input
* @s: name of the program
* @i: index of error
* @head: linked list containing environment
*
* Description: make child process
* If forking failed, print error, free, and exit
* If forking is successful,
* Transform the environ linked list in an array, for execve
* Check if the PATH has been modified
* If command can be run on its own without PATH,
* Execute command with execve
* Set variable "exe" to resulting full command from path_finder
* If exe returned NULL but the command is a local executable,
* Execute input. If execve fails, print error, free, and return
* Else if exe did not return NULL,
* Execute exe. If execve failed, print error, free all, exit
* In the meantime, make the parent process wait
* Free the input and the environ array
*
* Return: return to main loop with 1 on success, or 0 on failure
*/
int exec(char **input, char *s, int *i, env_t **head)
{
	struct stat filestat;
	int status = 0;
	char *exe = NULL, **env = NULL;
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		print_error(i, s, input);
		free_everything(input);
		exit(EXIT_SUCCESS);
	}
	if (child_pid == 0)
	{
		env = list_to_arr(*head);
		if (get_env_val("PATH=", env)[0] != '/')
			execve(input[0], input, env);
		exe = path_finder(input, env);
		if (!exe && !stat(input[0], &filestat))
		{
			if (execve(input[0], input, env) == -1)
			{
				print_error(i, s, input);
				free_everything(input), free_everything(env);
				return (0);
			}
			free_everything(input);
			free_everything(env);
		}
		if (execve(exe, input, env) == -1)
		{
			print_error(i, s, input);
			free(exe), free_everything(input), free_everything(env);
			exit(EXIT_SUCCESS);
		}
	}
	else
		wait(&status);
	free_everything(input), free_everything(env);
	return (1);
}

/**
 * main - simple command-line argument interpreter
 * prints a prompt and waits for the user to input a command,
 * then creates a child process in which it exececutes the command
 * @ac: number of arguments
 * @av: array of arguments
 *
 * Description: If an argument is passed to main, print error, exit
 * Call to signal to not exit on Ctrl+C
 * Store the environ variable into a linked list
 * Enter the "infinite" loop of the shell
 * If this shell is running from a terminal, print prompt
 * Read from standard input into variable "line"
 * If getline failed, or if non-interactive mode
 * Print a newline and break
 * Increment count of calls to the shell
 * If just enter is pressed, restart shell loop
 * Call to parse_line: replace newline with null byte to remove it
 * Break up input line into array of tokens
 * Check if first token is a builtin
 * If exec returns 0, break out of the loop
 * Free input and linked list, return
 *
 * Return: always 0, for success
 */
int main(int ac, char *av[])
{
	size_t len = 0;
	int cmd_count = 0, get;
	char **input = NULL, *line = NULL, *prog_name = av[0];
	env_t *head = NULL;

	if (ac != 1)
	{
		print_error_main(av);
		exit(127);
	}
	signal(SIGINT, sigint_handler);
	arr_to_list(&head, environ);
	while (1)
	{
		if (isatty(STDIN_FILENO) != 0 && isatty(STDOUT_FILENO) != 0)
			print_prompt();
		get = getline(&line, &len, stdin);
		if (get < 0)
		{
			if (isatty(STDIN_FILENO) != 0 && isatty(STDOUT_FILENO) != 0)
				_putchar('\n');
			break;
		}
		cmd_count++;
		if (_strcmp(line, "\n") == 0)
			continue;
		input = parse_line(line, get);
		if (!input)
			continue;
		if (is_builtin(line, input, prog_name, &cmd_count, &head))
		{
			free_everything(input);
			continue;
		}
		if (!exec(input, prog_name, &cmd_count, &head))
			break;
	}
	free_list(&head), free(line);
	return (0);
}
