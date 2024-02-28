#include "shell.h"

/**
 * _CD_ - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _CD_(information_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _GetEnv_(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _GetEnv_(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strCMP_(info->argv[1], "-") == 0)
	{
		if (!_GetEnv_(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_GetEnv_(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _GetEnv_(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		_PrintError_(info, "can't cd to ");
		_Errorputs_(info->argv[1]), _Error_putchar_('\n');
	}
	else
	{
		_setenv_(info, "OLDPWD", _GetEnv_(info, "PWD="));
		_setenv_(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}


/**
 * _FindBuildIn_ - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int _FindBuildIn_(information_t *info)
{
	int i, built_in_ret = -1;
	BuildIn_t builtintbl[] = {
		{"exit", _Exit_},
		{"env", _Env_},
		{"help", _Help_},
		{"history", _History_},
		{"setenv", _SetEnv_},
		{"unsetenv", _UnSetEnv_},
		{"cd", _CD_},
		{"alias", _Alias_},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strCMP_(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}


/**
 * _Find_cmd_ - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void _Find_cmd_(information_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!_Is_delimeter_(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = _FindPath_(info, _GetEnv_(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		_Fork_cmd_(info);
	}
	else
	{
		if ((Interactive_Mode(info) || _GetEnv_(info, "PATH=")
			|| info->argv[0][0] == '/') && _Is_CMD_(info, info->argv[0]))
			_Fork_cmd_(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			_PrintError_(info, "not found\n");
		}
	}
}



/**
 * _Fork_cmd_ - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void _Fork_cmd_(information_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, _Get_Environ_(info)) == -1)
		{
			_FreeInfo_(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				_PrintError_(info, "Permission denied\n");
		}
	}
}




