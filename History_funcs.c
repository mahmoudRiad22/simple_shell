#include "shell.h"

/**
 * _GetHistoryFile_ - gets the history file
 *
 * @info: parameter struct
 *
 * Return: allocated string containg history_file
 */

char *_GetHistoryFile_(information_t *info)
{
	char *buffer, *directory;

	directory = _GetEnv_(info, "HOME=");
	if (!directory)
		return (NULL);

buffer =
	malloc(sizeof(char) * (_strlen_(directory) + _strlen_(HIST_FILE) + 2));

	if (!buffer)
		return (NULL);

	buffer[0] = 0;
	_StrCpy_(buffer, directory);
	_StrCat_(buffer, "/");
	_StrCat_(buffer, HIST_FILE);

	return (buffer);
}


/**
 * _WriteHistory_ - creates a history file or append if already exists
 *
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int _WriteHistory_(information_t *info)
{
	ssize_t file_desc;
	char *FileName = _GetHistoryFile_(info);
	list_t *node = NULL;

	if (!FileName)
		return (-1);

	file_desc = open(FileName, O_CREAT | O_TRUNC | O_RDWR, 0644);

	free(FileName);

	if (file_desc == -1)
		return (-1);

	for (node = info->history; node; node = node->next)
	{
		_PutsFD_(node->str, file_desc);
		_PutFD_('\n', file_desc);
	}

	_PutFD_(BUF_FLUSH, file_desc);
	close(file_desc);

	return (1);
}


/**
 * _ReadHistory_ - reads history from file
 *
 * @info: information struct
 *
 * Return: histcount on success, 0 otherwise
 */
int _ReadHistory_(information_t *info)
{
	int counter, LastLine = 0, LineCounter = 0;
	char *buffer = NULL, *filename = _GetHistoryFile_(info);
	ssize_t file_desc, readlen, file_size = 0;
	struct stat st;

	if (!filename)
		return (0);
	file_desc = open(filename, O_RDONLY);
	free(filename);
	if (file_desc == -1)
		return (0);
	if (!fstat(file_desc, &st))
		file_size = st.st_size;
	if (file_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);
	readlen = read(file_desc, buffer, file_size);
	buffer[file_size] = 0;
	if (readlen <= 0)
		return (free(buffer), 0);
	close(file_desc);
	for (counter = 0; counter < file_size; counter++)
		if (buffer[counter] == '\n')
		{
			buffer[counter] = 0;
			_BuildHistory_L_(info, buffer + LastLine, LineCounter++);
			LastLine = counter + 1;
		}
	if (LastLine != counter)
		_BuildHistory_L_(info, buffer + LastLine, LineCounter++);
	free(buffer);
	info->histcount = LineCounter;
	while (info->histcount-- >= HIST_MAX)
		_DelNodeAtIndex_(&(info->history), 0);
	_ReOrderH_(info);
	return (info->histcount);
}



/**
 * _BuildHistory_L_ - adds entry to a history linked list
 *
 * @info: information struct
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int _BuildHistory_L_(information_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	_AddNodeAtEnd_(&node, buf, linecount);

	if (!info->history)
		info->history = node;

	return (0);
}



/**
 * _ReOrderH_ - renumbers the history linked list after changes
 *
 * @info: information struct
 *
 * Return: the new histcount
 */
int _ReOrderH_(information_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return (info->histcount = i);
}



