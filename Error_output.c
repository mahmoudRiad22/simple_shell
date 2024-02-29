#include "shell.h"

/**
 * _PrintError_ - prints an error message
 *
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 *
 *  Return: 0 if no string, converted number otherwise, -1 on error
 */
void _PrintError_(information_t *info, char *estr)
{
	_Errorputs_(info->fname);
	_Errorputs_(": ");

	_PrintInt_(info->line_count, STDERR_FILENO);
	_Errorputs_(": ");

	_Errorputs_(info->argv[0]);
	_Errorputs_(": ");

	_Errorputs_(estr);
}

/**
 *_Errorputs_ - prints an input string
 *
 * @string: the string to be printed
 *
 * Return: Nothing
 */
void _Errorputs_(char *string)
{
	int counter = 0;

	if (!string)
		return;
	while (string[counter] != '\0')
	{
		_Error_putchar_(string[counter]);
		counter++;
	}
}

/**
 * _Error_putchar_ - writes the character c to stderr
 *
 * @chr: The character to print
 *
 * Return: On success 1, -1 On error and errno is set appropriately.
 */
int _Error_putchar_(char chr)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (chr == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (chr != BUF_FLUSH)
		buffer[i++] = chr;
	return (1);
}


/**
 * _PutFD_ - writes the character c to given fd
 *
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _PutFD_(char c, int fd)
{
	static char buf[WRITE_BUF_SIZE];
	static int i;

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}


/**
 * _ErrAtoI_ - converts an Error string to an integer
 *
 * @s: the string to be converted
 *
 * Return: 0 if no numbers in string, -1 on error, converted number otherwise
 *
 */
int _ErrAtoI_(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;

	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

