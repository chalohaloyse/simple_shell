#include "shell.h"

/**
* get_env_val - gets the value of a environment variable
* @name: env key to check
* @env: array of strings containing environment copy
*
* Description: loop through strings in env
* If name compares with the name of the variable,
* Return the rest of the string
*
* Return: value of name in env
*/

char *get_env_val(char *name, char **env)
{
	int i;

	for (i = 0; env[i]; i++)
		if (_strncmp(env[i], name, _strlen(name)) == 0)
			return (env[i] + _strlen(name));
	return (NULL);
}

/**
* get_env - transform the PATH string in an array of strings
* @name: key (key=value) to select in env
* @env: array of strings containing the environment copy
*
* Description: loop through strings in env
* Parse each env string by the '=' delim
* Compare the given key with name (env[0])
* If it compares, parse the result by ':'
* Return resulting array of strings
*
* Return: value at key, in the form of an array of strings
*/
char **get_env(char *name, char **env)
{
	char **value = NULL, **path = NULL;
	int i;

	for (i = 0; env[i]; i++)
	{
		path = _strtok(env[i], '=');
		if (_strcmp(name, path[0]) == 0)
		{
			value = _strtok(path[1], ':');
			free_everything(path);
			return (value);
		}
		else
			free_everything(path);
	}
	free_everything(path);
	free_everything(value);
	return (NULL);
}
/**
* path_finder - connect directories in PATH with input command
* to check if executable
* @s: input, in form array of strings
* @env: array of strings containing the environment copy
*
* Description: call get_env to get value at PATH, save into path_value
* If it failed, free and return NULL
* Loop through strings in path_value
* Concatenate the directory in PATH with a '/' and the command
* If the result is executable, free variables and return result string
* If not, free variables and go to the next directory in the path
* If the command was not found in the PATH, return NULL
*
* Return: concatenated string on success, NULL on failure
*/
char *path_finder(char **s, char **env)
{
	int i;
	char *dir = NULL;
	char *prog = NULL;
	char **path_value = NULL;

	path_value = get_env("PATH", env);
	if (!path_value)
	{
		free_everything(path_value);
		return (NULL);
	}

	for (i = 0; path_value[i]; i++)
	{
		dir = str_concat(path_value[i], "/");
		prog = str_concat(dir, s[0]);

		if (access(prog, X_OK) == 0)
		{
			free_everything(path_value);
			free(dir);
			return (prog);
		}
		free(dir);
		free(prog);
	}
	free_everything(path_value);
	return (NULL);
}
