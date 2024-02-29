#include "shell.h"

/**
 * _GetEnv_ - gets the value of an environ variable
 *
 * @info: information struct
 * @env_name: env_name
 *
 * Return: the value
 */
char *_GetEnv_(information_t *info, const char *env_name)
{
	list_t *node = info->env;
	char *ptr;

	for (; node;)
	{
		ptr = _StartWith_(node->str, env_name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}


/**
 * _SetEnv_ - Initialize a new envi_var, or modify an existing one
 *
 * @info: information struct
 *
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
 *
 * @info: information struct
 *
 * Return: Always 0
 */
int _Env_(information_t *info)
{
	_PrintListStrings_(info->env);
	return (0);
}


