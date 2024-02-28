#include "shell.h"

/**
 *_Is_Alpha_ - checks for alphabetic character
 *@_char: The character to input
 *Return: 1 if char is alphabetic, 0 else
 */
int _Is_Alpha_(int _char)
{
	if ((_char >= 'a' && _char <= 'z') || (_char >= 'A' && _char <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _Is_delimeter_ - checks if character is a delimeter
 * @ch: the char to check
 * @delimeter: the delimeter string
 * Return: 1 if true, 0 if false
 */
int _Is_delimeter_(char ch, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == ch)
			return (1);
	return (0);
}

/**
 * _Is_CMD_ - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int _Is_CMD_(information_t *info, char *path)
{
	struct stat _stat_;

	(void)info;
	if (!path || stat(path, &_stat_))
		return (0);

	if (_stat_.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _Is_Chain_ - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buffer: the char buffer
 * @add: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int _Is_Chain_(information_t *info, char *buffer, size_t *add)
{
	size_t copy = *add;

	if (buffer[copy] == '|' && buffer[copy + 1] == '|')
	{
		buffer[copy] = 0;
		copy++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buffer[copy] == '&' && buffer[copy + 1] == '&')
	{
		buffer[copy] = 0;
		copy++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buffer[copy] == ';')
	{
		buffer[copy] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*add = copy;
	return (1);
}


