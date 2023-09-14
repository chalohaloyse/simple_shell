#include "shell.h"

/**
 * _atoi - converts a string to an integer
 * @s: string to be converted
 *
 * Description: if the first character is a '+',
 * Go to next character
 * Loop through the string while the flag is 0
 * If the first character is '-'
 * Return -1 because we don't want negative values
 * If the current character is a digit, convert it into a digit
 * Store it into the integer
 * If the next character is a letter, breakout of the loop
 * If the result number is superior to INT_MAX or is negative
 * Return -1 for error
 * Else return the number
 *
 * Return: the int converted from the string
 */
long int _atoi(char *s)
{
	int i, len, f, digit;
	long int n;

	i = 0;
	n = 0;
	len = _strlen(s);
	f = 0;
	digit = 0;

	if (s[i] == '+')
		i++;

	while (i < len && f == 0)
	{
		if (s[i] == '-')
			return (-1);

		if (s[i] >= '0' && s[i] <= '9')
		{
			digit = s[i] - '0';
			n = n * 10 + digit;
			f = 1;
			if (s[i + 1] < '0' || s[i + 1] > '9')
				break;
			f = 0;
		}
		i++;
	}

	if (f == 0)
		return (0);

	if (n > INT_MAX || n < 0)
		return (-1);

	return (n);
}

/**
 * convert - converts number and base into string
 * @num: input number
 * @base: input base
 *
 * Description: Create a static buffer of 50 chars
 * And a static string of digits
 * Go from the end of the buffer and loop until num reaches 0
 * Current number is the member of rep at index num % base
 * Divide num by base
 *
 * Return: result string
 */
char *convert(int num, int base)
{
	static char *rep = "0123456789";
	static char buffer[50];
	char *ptr = NULL;

	ptr = &buffer[49];
	*ptr = '\0';
	do {
		*--ptr = rep[num % base];
		num /= base;
	} while (num != 0);

	return (ptr);
}
