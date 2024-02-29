#include "shell.h"

/**
 * _Exit_ - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _Exit_(information_t *info)
{
	int Exit_Check;

	if (info->argv[1])
	{
		Exit_Check = _ErrAtoI_(info->argv[1]);

		if (Exit_Check == -1)
		{
			info->status = 2;
			_PrintError_(info, "Illegal number: ");
			_Errorputs_(info->argv[1]);
			_Error_putchar_('\n');
			return (1);
		}

		info->err_num = _ErrAtoI_(info->argv[1]);

		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _Help_ - activate the help function
 *
 * @info: informatio struct
 *
 *  Return: Always 0
 */
int _Help_(information_t *info)
{
	char **arg_array;

	arg_array = info->argv;

	_puts("help started ... help ended :) \n");
	if (0)
		_puts(*arg_array);
	return (0);
}


/**
 * _History_ - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: informatio struct
 *
 *  Return: Always 0
 */
int _History_(information_t *info)
{
	_PrintList_(info->history);
	return (0);
}
