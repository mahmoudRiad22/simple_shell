#include "shell.h"

/**
 * _signIn_ - blocks ctrl-C
 *
 * @sig_num: the signal number
 *
 * Return: void
 */
void _signIn_(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}



/**
 * _CheckChain_ - checks if we continue chains or not
 *
 * @info: information struct
 * @B: the char B
 * @p: address of current position in buf
 * @i: starting position in buf
 * @l: length of buf
 *
 * Return: Void
 */
void _CheckChain_(information_t *info, char *B, size_t *p, size_t i, size_t l)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			B[i] = 0;
			j = l;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			B[i] = 0;
			j = l;
		}
	}

	*p = j;
}



/**
 * _FindPath_ - finds this cmd in the PATH string
 *
 * @info: information struct
 * @PATH: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *_FindPath_(information_t *info, char *PATH, char *cmd)
{
	int counter = 0, currentPosition = 0;
	char *path;

	if (!PATH)
		return (NULL);
	if ((_strlen_(cmd) > 2) && _StartWith_(cmd, "./"))
	{
		if (_Is_CMD_(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!PATH[counter] || PATH[counter] == ':')
		{
			path = _chars_dup_(PATH, currentPosition, counter);
			if (!*path)
				_StrCat_(path, cmd);
			else
			{
				_StrCat_(path, "/");
				_StrCat_(path, cmd);
			}
			if (_Is_CMD_(info, path))
				return (path);
			if (!PATH[counter])
				break;
			currentPosition = counter;
		}
		counter++;
	}
	return (NULL);
}


/**
 *_PutsFD_ - prints an input string
 *
 * @str: the string to be printed
 * @file_desc: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _PutsFD_(char *str, int file_desc)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _PutFD_(*str++, file_desc);
	}
	return (i);
}



/**
 * _RemoveComments_ - function replaces first instance of '#' with '\0'
 * @buffer: address of the string to modify
 *
 * Return: Always 0;
 */
void _RemoveComments_(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
}








