#include "shell.h"

/**
 * _Get_Environ_ - returns the string array copy of our environ
 * 
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **_Get_Environ_(information_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = _ListToString_(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}


/**
 * _setenv_ - Initialize a new environment variable,
 *             or modify an existing one
 * 
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv_(information_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen_(var) + _strlen_(value) + 2);
	if (!buf)
		return (1);
	_StrCpy_(buf, var);
	_StrCat_(buf, "=");
	_StrCat_(buf, value);
	node = info->env;
	while (node)
	{
		p = _StartWith_(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	_AddNodeAtEnd_(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}



/**
 * _unsetenv_ - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv_(information_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = _StartWith_(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = _DelNodeAtIndex_(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}



/**
 * _UnSetEnv_ - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _UnSetEnv_(information_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_Errorputs_("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv_(info, info->argv[i]);

	return (0);
}


/**
 * Double_EnvList - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int Double_EnvList(information_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		_AddNodeAtEnd_(&node, environ[i], 0);
	info->env = node;
	return (0);
}
