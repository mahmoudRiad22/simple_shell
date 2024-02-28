#include "shell.h"

/**
 * main - entry point
 * @argc: arg count
 * @argv: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	information_t info[] = { INFO_INIT };
	int file_d = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (file_d)
		: "r" (file_d));

	if (argc == 2)
	{
		file_d = open(argv[1], O_RDONLY);
		if (file_d == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_Errorputs_(argv[0]);
				_Errorputs_(": 0: Can't open ");
				_Errorputs_(argv[1]);
				_Error_putchar_('\n');
				_Error_putchar_(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = file_d;
	}
	Double_EnvList(info);
	_ReadHistory_(info);
	hsh(info, argv);
	return (EXIT_SUCCESS);
}
