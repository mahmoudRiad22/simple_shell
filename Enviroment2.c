#include "shell.h"

/**
 * _GetEnv_ - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_GetEnv_(information_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = _StartWith_(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}


/**
 * _SetEnv_ - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _SetEnv_(information_t *info)
{
	if (info->argc != 3)
	{
		_Errorputs_("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv_(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _Env_ - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _Env_(information_t *info)
{
	_PrintListStrings_(info->env);
	return (0);
}

