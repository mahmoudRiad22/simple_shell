#include "shell.h"

/**
 * _Replace_S_ - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _Replace_S_(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}


/**
 * _Repalce_V_ - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _Repalce_V_(information_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strCMP_(info->argv[i], "$?"))
		{
			_Replace_S_(&(info->argv[i]),
				_StrDup_(_ConvertNumber_(info->status, 10, 0)));
			continue;
		}
		if (!_strCMP_(info->argv[i], "$$"))
		{
			_Replace_S_(&(info->argv[i]),
				_StrDup_(_ConvertNumber_(getpid(), 10, 0)));
			continue;
		}
		node = _NodeStartWith_(info->env, &info->argv[i][1], '=');
		if (node)
		{
			_Replace_S_(&(info->argv[i]),
				_StrDup_(_StrChar_(node->str, '=') + 1));
			continue;
		}
		_Replace_S_(&info->argv[i], _StrDup_(""));

	}
	return (0);
}

/**
 * _Replace_A_ - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _Replace_A_(information_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = _NodeStartWith_(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _StrChar_(node->str, '=');
		if (!p)
			return (0);
		p = _StrDup_(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

