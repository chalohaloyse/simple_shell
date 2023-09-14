#include "shell.h"

/**
* _strdup - allocate memory for a string to duplicate
* @str: string to duplicate
*
* Return: new string on success, NULL on failure
*/

char *_strdup(char *str)
{
	char *dup = NULL;
	int c, i = 0;

	if (!str)
		return (NULL);

	while (str[i])
		i++;

	dup = malloc(sizeof(char) * i + 1);

	if (!dup)
		return (NULL);

	for (c = 0; c < i; c++)
		dup[c] = str[c];

	dup[c] = '\0';

	return (dup);
}

/**
 * str_concat - concatenates two strings,
 * and allocate memory for the result string
 * @s1: string to concatenate
 * @s2: other string to concatenate
 *
 * Return: pointer to the string created on success, or NULL on failure
 */
char *str_concat(char *s1, char *s2)
{
	char *s3 = NULL;
	unsigned int i = 0, j = 0, len1 = 0, len2 = 0;

	len1 = _strlen(s1);
	len2 = _strlen(s2);

	s3 = malloc(sizeof(char) * (len1 + len2 + 1));
	if (s3 == NULL)
		return (NULL);

	i = 0;
	j = 0;

	if (s1)
	{
		while (i < len1)
		{
			s3[i] = s1[i];
			i++;
		}
	}

	if (s2)
	{
		while (i < (len1 + len2))
		{
			s3[i] = s2[j];
			i++;
			j++;
		}
	}
	s3[i] = '\0';

	return (s3);
}

/**
 * _strcmp - compares two strings
 * @s1: first string to compare
 * @s2: second string to compare
 *
 * Return: less than 0 if s1 is less than s2, 0 if they're equal,
 * more than 0 if s1 is greater than s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
		{
			return (0);
		}
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
* _strncmp - compare strings up to n bytes
* @s1: string to compare against
* @s2: string to compare from
* @n: number of bytes to compare
*
* Return: 0 if the strings are different, non-zero if they are the same
*/
int _strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int i = 0;

	while (*s1 == *s2 && i < n)
	{
		if (*s1 == '\0')
		{
			return (0);
		}
		s1++;
		s2++;
		i++;
	}
	return (i != n);
}
