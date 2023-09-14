#include "shell.h"

/**
 * arr_to_list - transforms the environ variable into a linked list
 * @head: double pointer to the env_t list to fill
 * @env: array of strings containing the environment variables
 *
 * Description: Free the list if it exists
 * Loop through the array and add a node for each string
 *
 * Return: Number of nodes in the list
 */
int arr_to_list(env_t **head, char **env)
{
	int i = 0;

	if (head)
		free_list(head);

	while (env[i])
	{
		add_node_end(head, env[i]);
		i++;
	}
	return (i);
}

/**
 * list_to_arr - transforms a linked list in an array of strings
 * @head: pointer to the env_t list
 *
 * Description: If the list doesn't exist, return NULL
 * Allocate memory for the array, check if it failed
 * Traverse the list, allocate memory for each string
 * Fill each string with the string from the node
 * Set last element of the array to NULL
 * Return the array
 *
 * Return: address of the array, or NULL if it failed
 */
char **list_to_arr(env_t *head)
{
	env_t *temp = head;
	char **arr = NULL, *s = NULL;
	size_t size = 0;
	int i;

	size = list_len(head);

	if (!head || !size)
		return (NULL);

	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		return (NULL);

	for (i = 0; temp; temp = temp->next, i++)
	{
		s = malloc(sizeof(char) * (_strlen(temp->str) + 1));
		if (!s)
		{
			free_everything(arr);
			return (NULL);
		}
		s = _strcpy(s, temp->str);
		arr[i] = s;
	}
	arr[i] = NULL;

	return (arr);
}

/**
 * print_list - prints all the nodes of a linked list
 * @h: pointer to the list_t list to print
 *
 * Return: the number of nodes printed
 */
size_t print_list(env_t *h)
{
	size_t s = 0;

	while (h)
	{
		if (!h->str)
			_puts("(nil)");
		else
			_puts(h->str);
		h = h->next;
		s++;
	}

	return (s);
}

/**
 * free_list - frees all the nodes of a linked list
 * @head: list_t list to be freed
 */
void free_list(env_t **head)
{
	env_t *temp = NULL;

	if (head == NULL)
		return;

	while (*head)
	{
		temp = (*head)->next;
		free((*head)->str);
		free(*head);
		*head = temp;
	}

	*head = NULL;
}

/**
 * list_len - returns the number of elements in a linked list
 * @h: pointer to the env_t list
 *
 * Return: number of elements in h
 */
size_t list_len(const env_t *h)
{
	size_t n = 0;

	while (h)
	{
		n++;
		h = h->next;
	}
	return (n);
}
