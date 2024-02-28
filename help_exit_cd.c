#include "SHELL.h"

/**
 *
 */
int _Help_(information_t *info)
{
	char **array;

	array = info->argv;
	_puts("Help function works\n");

	if (0)
		_puts(*array);

	return (0);
}

/**
 *
 */

int _exit_(information_t *info)
{
	int out;

	if (info->argv[1])
	{
		out = 
	}
}
