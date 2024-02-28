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
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _StrChar_(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(_NodeStartWith_(info->alias, info->argv[i], '='));
	}

	return (0);
}


/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
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
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(information_t *info, char *str)
{
	char *p;

	p = _StrChar_(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (_AddNodeAtEnd_(&(info->alias), str, 0) == NULL);
}



/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(information_t *info, char *str)
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



