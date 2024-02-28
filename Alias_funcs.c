#include "shell.h"


/**
 * _Alias_ - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _Alias_(information_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

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
	for (i = 1; info->argv[i]; i++)
	{
		p = _StrChar_(info->argv[i], '=');
		if (p)
			_SetAlias_(info, info->argv[i]);
		else
			_PrintAlias_(_NodeStartWith_(info->alias, info->argv[i], '='));
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
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _StrChar_(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}


/**
 * _SetAlias_ - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _SetAlias_(information_t *info, char *str)
{
	char *p;

	p = _StrChar_(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (_UnsetAlias_(info, str));

	_UnsetAlias_(info, str);
	return (_AddNodeAtEnd_(&(info->alias), str, 0) == NULL);
}



/**
 * _UnsetAlias_ - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _UnsetAlias_(information_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _StrChar_(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = _DelNodeAtIndex_(&(info->alias),
		_GetNodeIndex_(info->alias, _NodeStartWith_(info->alias, str, -1)));
	*p = c;
	return (ret);
}




