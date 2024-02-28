#include "SHELL.h"
/**
 * interactive_mode - return 1 if shell is in interactive mode
 *
 * @info: adress struct
 *
 * Return: 1 if interactive mode is on, 0 if not
 *
 */

int interactive_mode(information_t *info)
{
	int x;

	x = isatty(STDIN_FILENO) && info->readfd <= 2;
	return (x);
}

/**
 * Is_Delim - a function to check if the char is a delimeter or not
 *
 * @c: the char to be checked
 * @delim: the delimeter string
 *
 * Return: 1 if true, 0 if false
 *
 */
int Is_Delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
			return (1);
	}
	return (0);
}

/**
 * Is_alpha - a function to check if a char is in the alphabet or not
 *
 * @c: the char to be checked
 *
 * Return: 1 if true, 0 if flase
 *
 */
int Is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _AtoI - a fucntion to convert a string to an integer
 *
 * @arr: the string
 *
 * Return: 0 if string has no numbers, otherwie the converted number
 *
 */

int _AtoI(char *arr)
{
	int i, sign = 1, flag = 0, out;
	unsigned int result = 0;

	for (i = 0; arr[i] != '\0' && flag != 2; i++)
	{
		if (arr[i] == '-')
			sign *= -1;

		if (arr[i] >= '0' && arr[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (arr[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		out = -result;
	else
		out = result;

	return (out);
}

