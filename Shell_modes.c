#include "shell.h"


/**
 * Interactive_Mode - returns true if shell is interactive mode
 *
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int Interactive_Mode(information_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(information_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		_ClearInfo_(info);
		if (Interactive_Mode(info))
			_puts("$ ");
		_Error_putchar_(BUF_FLUSH);
		r = _GetInput_(info);

		if (r != -1)
		{
			_SetInfo_(info, av);
			builtin_ret = _FindBuildIn_(info);
			if (builtin_ret == -1)
				_Find_cmd_(info);
		}
		else if (Interactive_Mode(info))
			_putchar('\n');
		_FreeInfo_(info, 0);
	}

	_WriteHistory_(info);
	_FreeInfo_(info, 1);

	if (!Interactive_Mode(info) && info->status)
		exit(info->status);

	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}



