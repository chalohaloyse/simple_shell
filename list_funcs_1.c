#include "shell.h"

/**
 * add_node_end - adds a new node at the end of a linked list
 * @head: double pointer to the env_t list
 * @str: string to put in the new node
 *
 * Description: allocate memory for a node, and check if it failed
 * Copy str into the node, set next node to NULL
 * If list is empty, set head to new node and return it
 * Traverse the list
 * Set the next element in the list to new, return it
 *
 * Return: address of the new element, or NULL if it failed
 */
env_t *add_node_end(env_t **head, char *str)
{
	env_t *new = NULL;
	env_t *temp = *head;

	new = malloc(sizeof(env_t));
	if (!new)
		return (NULL);

	new->str = _strdup(str);
	new->next = NULL;

	if (*head == NULL)
	{
		*head = new;
		return (new);
	}

	while (temp->next)
		temp = temp->next;

	temp->next = new;

	return (new);
}

/**
 * delete_node_at_index - deletes a node in a linked list at a certain index
 * @head: pointer to the first element in the list
 * @index: index of the node to delete
 *
 * Description: If the list is empty, return NULL
 * If we want to delete the first node,
 * Set the head to point to the next, and free the node
 * Traverse the list, at the end set the current node to
 * point to two nodes after it, free the next node and free its string
 *
 * Return: 1 (Success), or -1 (Fail)
 */
int delete_node_at_index(env_t **head, unsigned int index)
{
	env_t *temp = *head;
	env_t *current = NULL;
	unsigned int i = 0;

	if (*head == NULL)
		return (-1);

	if (index == 0)
	{
		*head = (*head)->next;
		free(temp->str);
		free(temp);
		return (1);
	}

	while (i < index - 1)
	{
		if (!temp || !(temp->next))
			return (-1);
		temp = temp->next;
		i++;
	}

	current = temp->next;
	temp->next = current->next;
	free(current->str);
	free(current);

	return (1);
}

/**
 * add_node_at_index - adds a new node in a linked list at a given index
 * @head: double pointer to the en_t list
 * @str: string to put in the new node
 * @idx: index where to insert the node
 *
 * Description: Allocate memory for a new node, check if it failed
 * If we want to add the node at the beginning, add it
 * Else traverse the list until the index, and add the new node
 *
 * Return: 0 on success, -1 on failure
 */
int add_node_at_index(env_t **head, char *str, int idx)
{
	int i;
	env_t *new = NULL;
	env_t *temp = *head;

	new = malloc(sizeof(env_t));
	if (!new || !head)
		return (-1);

	new->str = _strdup(str);
	new->next = NULL;

	if (idx == 0)
	{
		new->next = *head;
		*head = new;
		return (0);
	}

	for (i = 0; temp && i < idx; i++)
	{
		if (i == idx - 1)
		{
			new->next = temp->next;
			temp->next = new;
			return (0);
		}
		else
			temp = temp->next;
	}

	return (-1);
}

/**
 * find_index_list - finds the index of a given element in a list
 * @head: pointer to the env_t list
 * @name: string of the node to find
 *
 * Description: Traverse the list,
 * For each node, compare its string with name
 * If it matches, return the index of teh node
 *
 * Return: index of the node, or 0 if the node is not found
 */
int find_index_list(env_t *head, char *name)
{
	int index = 0;
	int c = 0;

	while (head)
	{
		c = _strncmp(head->str, name, _strlen(name));
		if (c == 0)
			return (index);
		index++;
		head = head->next;
	}

	return (0);
}
