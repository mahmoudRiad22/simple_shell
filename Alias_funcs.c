#include "shell.h"


/**
 * _Alias_ - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _Alias_(information_t *info)
{
	list_t *node = NULL;
    char *p = NULL;
	int index = 0;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			_PrintAlias_(node);
			node = node->next;
		}
		return (0);
	}

	for (index = 1; info->argv[index]; index++)
	{
		p = _StrChar_(info->argv[index], '=');
		if (p)
			_SetAlias_(info, info->argv[index]);
		else
			_PrintAlias_(_NodeStartWith_(info->alias, info->argv[index], '='));
	}

	return (0);
}

/**
 * _PrintAlias_ - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int _PrintAlias_(list_t *node)
{
	char *address = NULL, *current = NULL;

	if (node)
	{
		address = _StrChar_(node->str, '=');

		for (current = node->str; current <= address; current++)
			_putchar(*current);
		
        _putchar('\'');
		_puts(address + 1);
		_puts("'\n");
		return (0);
	}
    
	return (1);
}

/**
 * _SetAlias_ - sets alias to string
 * @info: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _SetAlias_(information_t *info, char *string)
{
	char *pointer;

	pointer = _StrChar_(string, '=');

	if (!pointer)
		return (1);
	
    if (!*++pointer)
		return (_UnsetAlias_(info, string));

	_UnsetAlias_(info, string);
	
    return (_AddNodeAtEnd_(&(info->alias), string, 0) == NULL);
}


/**
 * _UnsetAlias_ - sets alias to string
 * @info: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _UnsetAlias_(information_t *info, char *string)
{
	char *p, c;
	int ret;

	p = _StrChar_(string, '=');

	if (!p)
		return (1);
	c = *p;
	*p = 0;
	
    ret = _DelNodeAtIndex_(&(info->alias),
		_GetNodeIndex_(info->alias, _NodeStartWith_(info->alias, string, -1)));
	*p = c;
	return (ret);
}




