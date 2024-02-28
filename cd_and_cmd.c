#include "shell.h"

/**
 * _CD_ - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _CD_(information_t *info)
{
	char *cwd, *dirctory, Buffer[1024];
	int ch_dir_return;

	cwd = getcwd(Buffer, 1024);
	if (!cwd)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dirctory = _GetEnv_(info, "HOME=");
		if (!dirctory)
			ch_dir_return = /* TODO: what should this be? */
				chdir((dirctory = _GetEnv_(info, "PWD=")) ? dirctory : "/");
		else
			ch_dir_return = chdir(dirctory);
	}
	else if (_strCMP_(info->argv[1], "-") == 0)
	{
		if (!_GetEnv_(info, "OLDPWD="))
		{
			_puts(cwd);
			_putchar('\n');
			return (1);
		}
		_puts(_GetEnv_(info, "OLDPWD=")), _putchar('\n');
		ch_dir_return = /* TODO: what should this be? */
			chdir((dirctory = _GetEnv_(info, "OLDPWD=")) ? dirctory : "/");
	}
	else
		ch_dir_return = chdir(info->argv[1]);
	if (ch_dir_return == -1)
	{
		_PrintError_(info, "can't cd to ");
		_Errorputs_(info->argv[1]), _Error_putchar_('\n');
	}
	else
	{
		_setenv_(info, "OLDPWD", _GetEnv_(info, "PWD="));
		_setenv_(info, "PWD", getcwd(Buffer, 1024));
	}
	return (0);
}


/**
 * _FindBuildIn_ - search for a builtin command
 * 
 * @info: the parameter & return info struct
 *
 * Return: 1 if  found but not successful, -1 if  not found,
 *			0 if  executed successfully, -2 if signals exit()
 */
int _FindBuildIn_(information_t *info)
{
	int i, return_value = -1;
	BuildIn_t buildInTable[] = {
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

	for (i = 0; buildInTable[i].type; i++)
    {
		if (_strCMP_(info->argv[0], buildInTable[i].type) == 0)
		{
			info->line_count++;
			return_value = buildInTable[i].func(info);
			break;
		}
    }
	return (return_value);
}


/**
 * _Find_cmd_ - finds a command in PATH
 * 
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void _Find_cmd_(information_t *info)
{
	char *path = NULL;
	int i, j;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, j = 0; info->arg[i]; i++)
		if (!_Is_delimeter_(info->arg[i], " \t\n"))
			j++;
	if (!j)
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
 * _Fork_cmd_ - forks an exec thread to run cmd
 * 
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void _Fork_cmd_(information_t *info)
{
	pid_t pid_child;

	pid_child = fork();
	if (pid_child == -1)
	{
		perror("Error:");
		return;
	}
	if (pid_child == 0)
	{
		if (execve(info->path, info->argv, _Get_Environ_(info)) == -1)
		{
			_FreeInfo_(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
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




