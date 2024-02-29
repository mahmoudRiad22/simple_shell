#include "shell.h"

/**
 * _Get_Environ_ - return the new environ after change occurs
 *
 * @info: information struct
 *
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
 * _setenv_ - hanf=dle the env variablels by updating it if necessary
 *
 * @info: information struct
 * @env_var: the string env env_var property
 * @env_value: the string env env_var env_value
 *
 *  Return: Always 0
 */
int _setenv_(information_t *info, char *env_var, char *env_value)
{
	list_t *node;
	char *p;
	char *buffer = NULL;

	if (!env_var || !env_value)
		return (0);

	buffer = malloc(_strlen_(env_var) + _strlen_(env_value) + 2);

	if (!buffer)
		return (1);

	_StrCpy_(buffer, env_var);
	_StrCat_(buffer, "=");
	_StrCat_(buffer, env_value);

	node = info->env;
	while (node)
	{
		p = _StartWith_(node->str, env_var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}

	_AddNodeAtEnd_(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}

/**
 * _unsetenv_ - Remove an environment variable
 *
 * @info: information struct
 * @env_var: the string env env_var property
 *
 *  Return: 1 on delete, 0 otherwise
 */
int _unsetenv_(information_t *info, char *env_var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *ptr;

	if (!node || !env_var)
		return (0);

	while (node)
	{
		ptr = _StartWith_(node->str, env_var);
		if (ptr && *ptr == '=')
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
 *
 * @info: information struct
 *
 *  Return: Always 0
 */
int _UnSetEnv_(information_t *info)
{
	int counter;

	if (info->argc == 1)
	{
		_Errorputs_("Too few arguements.\n");
		return (1);
	}

	for (counter = 1; counter <= info->argc; counter++)
		_unsetenv_(info, info->argv[counter]);

	return (0);
}

/**
 * Double_EnvList - populates env linked list
 *
 * @info: information struct
 *
 * Return: Always 0
 */
int Double_EnvList(information_t *info)
{
	list_t *node = NULL;
	size_t counter;

	for (counter = 0; environ[counter]; counter++)
		_AddNodeAtEnd_(&node, environ[counter], 0);

	info->env = node;

	return (0);
}

