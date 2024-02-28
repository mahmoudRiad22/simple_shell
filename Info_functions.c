#include "shell.h"

/**
 * _SetInfo_ - initializes information_t struct
 * @info: struct address
 * @av: argument vector
 */
void _SetInfo_(information_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
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
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		_Replace_A_(info);
		_Repalce_V_(info);
	}
}

/**
 * _ClearInfo_ - initializes information_t struct
 * @info: struct address
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
 * @info: struct address
 * @all: true if freeing all fields
 */
void _FreeInfo_(information_t *info, int all)
{
	_FFree_(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
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
