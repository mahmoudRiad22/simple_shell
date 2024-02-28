#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define USE_GETLINE 0
#define USE_STRTOK 0

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} information_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(information_t *);
} BuildIn_t;




int loophsh(char **);
int hsh(information_t *, char **);
int _FindBuildIn_(information_t *);
void _Find_cmd_(information_t *);
void _Fork_cmd_(information_t *);
void _Errorputs_(char *); /*done*/
int _Error_putchar_(char);
int _PutFD_(char c, int fd);
int _PutsFD_(char *str, int fd);
int _strlen_(char *);
int _strCMP_(char *, char *);
char *_StartWith_(const char *, const char *);
char *_StrCat_(char *, char *);
int _Is_CMD_(information_t *, char *);
char *_chars_dup_(char *, int, int);
char *_FindPath_(information_t *, char *, char *);
char *_StrCpy_(char *, char *);
char *_StrDup_(const char *);
void _puts(char *);
int _putchar(char);
char *_StrnCpy_(char *, char *, int);
char *_StrnCat_(char *, char *, int);
char *_StrChar_(char *, char);
char **strtow(char *, char *);
char **strtow2(char *, char);
char *_MemorySet_(char *, char, unsigned int);
void _FFree_(char **);
void *_Realloc_(void *, unsigned int, unsigned int);
int _BufferFree_(void **);
int Interactive_Mode(information_t *);
int _Is_delimeter_(char, char *);
int _Is_Alpha_(int);
int _AtoI_(char *);
int _ErrAtoI_(char *);
void _PrintError_(information_t *, char *);
int _PrintInt_(int, int);
char *_ConvertNumber_(long int, int, int);
void _RemoveComments_(char *);
int _Exit_(information_t *);
int _CD_(information_t *);
int _Help_(information_t *);
int _History_(information_t *);
int _Alias_(information_t *);
ssize_t _GetInput_(information_t *);
int _GetLine_(information_t *, char **, size_t *);
void _signIn_(int);
void _ClearInfo_(information_t *);
void _SetInfo_(information_t *, char **);
void _FreeInfo_(information_t *, int);
char *_GetEnv_(information_t *, const char *);
int _Env_(information_t *);
int _SetEnv_(information_t *);
int _UnSetEnv_(information_t *);
int Double_EnvList(information_t *);
char **_Get_Environ_(information_t *);
int _unsetenv_(information_t *, char *);
int _setenv_(information_t *, char *, char *);
char *_GetHistoryFile_(information_t *info);
int _WriteHistory_(information_t *info);
int _ReadHistory_(information_t *info);
int _BuildHistory_L_(information_t *info, char *buf, int linecount);
int _ReOrderH_(information_t *info);
list_t *_Add_Node_(list_t **, const char *, int);
list_t *_AddNodeAtEnd_(list_t **, const char *, int);
size_t _PrintListStrings_(const list_t *);
int _DelNodeAtIndex_(list_t **, unsigned int);
void _FreeList_(list_t **);
size_t _ListLen_(const list_t *);
char **_ListToString_(list_t *);
size_t _PrintList_(const list_t *);
list_t *_NodeStartWith_(list_t *, char *, char);
ssize_t _GetNodeIndex_(list_t *, list_t *);
int _Is_Chain_(information_t *, char *, size_t *);
void _CheckChain_(information_t *, char *, size_t *, size_t, size_t);
int _Replace_A_(information_t *);
int _Repalce_V_(information_t *);
int _Replace_S_(char **, char *);
int _UnsetAlias_(information_t *info, char *str);
int _SetAlias_(information_t *info, char *str);
int _PrintAlias_(list_t *node);
ssize_t _ReadBuff_(information_t *info, char *buf, size_t *i);
#endif
