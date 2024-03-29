#include "shell.h"


/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 *
 * @w: the input string
 * @d: the delimeter string
 *
 * Return: a pointer to array_strings, or NULL otherwise
 */

char **strtow(char *w, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (w == NULL || w[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; w[i] != '\0'; i++)
		if (!_Is_delimeter_(w[i], d) && (_Is_delimeter_(w[i + 1], d) || !w[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (_Is_delimeter_(w[i], d))
			i++;
		k = 0;
		while (!_Is_delimeter_(w[i + k], d) && w[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = w[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}


