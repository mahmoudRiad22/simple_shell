#include "shell.h"


/**
 * _strlen_ - returns the length of a string
 *
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen_(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _StrCat_ - concatenates two strings
 *
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_StrCat_(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 * _StrCpy_ - copies a string
 *
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_StrCpy_(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _StrDup_ - duplicates a string
 *
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_StrDup_(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _strCMP_ - performs comparison on two strangs.
 *
 * @string1: the first strang
 * @string2: the second strang
 *
 * Return:	-ev if string1 < string2,
 *		+ev if string1 > string2,
 *		0 if string1 == string2
 */
int _strCMP_(char *string1, char *string2)
{
	while (*string1 && *string2)
	{
		if (*string1 != *string2)
			return (*string1 - *string2);
		string1++;
		string2++;
	}
	if (*string1 == *string2)
		return (0);
	else
		return (*string1 < *string2 ? -1 : 1);
}

