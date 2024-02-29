#include "shell.h"

/**
 * _SetInfo_ - initializes information_t struct
 *
 * @info: struct address
 * @argv: argument vector
 */
void _SetInfo_(information_t *info, char **argv)
{
	int counter = 0;

	info->fname = argv[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");

		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _StrDup_(info->arg);
				info->argv[1] = NULL;
			}
		}

		for (counter = 0; info->argv && info->argv[counter]; counter++)
			;

		info->argc = counter;

		_Replace_A_(info);
		_Repalce_V_(info);
	}
}


/**
 * _ClearInfo_ - clear all information saved
 *
 * @info: struct address
 *
 * Return: void
 */
void _ClearInfo_(information_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}



/**
 * _FreeInfo_ - frees information_t struct fields
 *
 * @info: struct address
 * @free_all: true if freeing all fields
 *
 * Return: void
 */
void _FreeInfo_(information_t *info, int free_all)
{
	_FFree_(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (free_all)
	{
		if (!info->cmd_buf)
			free(info->arg);

		if (info->env)
			_FreeList_(&(info->env));

		if (info->history)
			_FreeList_(&(info->history));

		if (info->alias)
			_FreeList_(&(info->alias));

		_FFree_(info->environ);
		info->environ = NULL;
		_BufferFree_((void **)info->cmd_buf);

		if (info->readfd > 2)
			close(info->readfd);

		_putchar(BUF_FLUSH);
	}
}

