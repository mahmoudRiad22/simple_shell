#include "shell.h"

/**
 * _ListLen_ - determines length of linked list
 *
 * @node: pointer to first node
 *
 * Return: size of list
 */
size_t _ListLen_(const list_t *node)
{
	size_t i = 0;

	while (node)
	{
		node = node->next;
		i++;
	}

	return (i);
}

/**
 * _PrintList_ - prints all elements of a list_t linked list
 *
 * @node: pointer to first node
 *
 * Return: size of list
 */
size_t _PrintList_(const list_t *node)
{
	size_t i = 0;

	while (node)
	{
		_puts(_ConvertNumber_(node->num, 10, 0));

		_putchar(':');
		_putchar(' ');

		_puts(node->str ? node->str : "(nil)");
		_puts("\n");

		node = node->next;
		i++;
	}

	return (i);
}

/**
 * _NodeStartWith_ - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *_NodeStartWith_(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = _StartWith_(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}



/**
 * _Add_Node_ - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *_Add_Node_(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_MemorySet_((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _StrDup_(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}




/**
 * _AddNodeAtEnd_ - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *_AddNodeAtEnd_(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_MemorySet_((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _StrDup_(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}






