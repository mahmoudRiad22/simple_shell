#include "shell.h"


/**
 *_AtoI_ - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */
int _AtoI_(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}


/**
 * _PrintInt_ - function prints an integer
 * @input: the input
 * @file_des: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int _PrintInt_(int input, int file_des)
{
	int (*_putchar_)(char) = _putchar;
	int i, counter = 0;
	unsigned int num_value, current;

	if (file_des == STDERR_FILENO)
		_putchar_ = _Error_putchar_;
	if (input < 0)
	{
		num_value = -input;
		_putchar_('-');
		counter++;
	}
	else
		num_value = input;
	current = num_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (num_value / i)
		{
			_putchar_('0' + current / i);
			counter++;
		}
		current %= i;
	}
	_putchar_('0' + current);
	counter++;

	return (counter);
}



/**
 * _ConvertNumber_ - converter function, a clone of itoa
 * @number: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *_ConvertNumber_(long int number, int base, int flags)
{
	static char *Array;
	static char Buffer[50];
	char minus_sign = 0;
	char *ptr;
	unsigned long num = number;

	if (!(flags & CONVERT_UNSIGNED) && number < 0)
	{
		num = -number;
		minus_sign = '-';

	}
	Array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &Buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = Array[num % base];
		num /= base;
	} while (num != 0);

	if (minus_sign)
		*--ptr = minus_sign;
	return (ptr);
}


/**
 * _chars_dup_ - replicate characters
 * 
 * @strpath: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *_chars_dup_(char *strpath, int start, int stop)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (strpath[i] != ':')
			buffer[k++] = strpath[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * _StartWith_ - checks if needle starts with haystack
 * 
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *_StartWith_(const char *haystack, const char *needle)
{
	while (*needle)

		if (*needle++ != *haystack++)
			return (NULL);
	
	return ((char *)haystack);
}





