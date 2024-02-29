#include "shell.h"

/**
 * input_buf - add commands to buffer
 *
 * @info: parameter struct
 * @buffer: address of buffer
 * @buffer_len: address of buffer_len var
 *
 * Return: bytes read
 */
ssize_t input_buf(information_t *info, char **buffer, size_t *buffer_len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*buffer_len)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, _signIn_);
#if USE_GETLINE
		r = getline(buffer, &len_p, stdin);
#else
		r = _GetLine_(info, buffer, &len_p);
#endif
		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0';
				r--;
			}

			info->linecount_flag = 1;

			_RemoveComments_(*buffer);
			_BuildHistory_L_(info, *buffer, info->histcount++);

			*buffer_len = r;
			info->cmd_buf = buffer;
		}
	}
	return (r);
}



/**
 * _GetInput_ - gets a line minus the newline
 *
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t _GetInput_(information_t *info)
{
	ssize_t r = 0;
	static size_t i, j, len;
	char **buf_p = &(info->arg), *ptr;
	static char *buffer;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buffer, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		ptr = buffer + i;

		_CheckChain_(info, buffer, &j, i, len);
		while (j < len)
		{
			if (_Is_Chain_(info, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = ptr;
		return (_strlen_(ptr));
	}

	*buf_p = buffer;
	return (r);
}


/**
 * _GetLine_ - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _GetLine_(information_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *ptr = NULL, *new_ptr = NULL, *c;

	ptr = *ptr;
	if (ptr && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = _ReadBuff_(info, buffer, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _StrChar_(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_ptr = _Realloc_(ptr, s, s ? s + k : k + 1);
	if (!new_ptr) /* MALLOC FAILURE! */
		return (ptr ? free(ptr), -1 : -1);

	if (s)
		_StrnCat_(new_ptr, buffer + i, k - i);
	else
		_StrnCpy_(new_ptr, buffer + i, k - i + 1);

	s += k - i;
	i = k;
	ptr = new_ptr;

	if (length)
		*length = s;
	*ptr = ptr;
	return (s);
}


/**
 * _ReadBuff_ - reads a buffer
 * @info: information struct
 * @buf: buffer
 * @i: size
 *
 * Return: bytes read
 */
ssize_t _ReadBuff_(information_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);

	r = read(info->readfd, buf, READ_BUF_SIZE);

	if (r >= 0)
		*i = r;

	return (r);
}



