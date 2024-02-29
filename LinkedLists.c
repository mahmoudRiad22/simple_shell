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
 *
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *_NodeStartWith_(list_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = _StartWith_(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * _Add_Node_ - adds a node to the start of the list
 * @head_node: address of pointer to head_node node
 * @string: string field of node
 * @index_h: node index used by history
 *
 * Return: size of list
 */
list_t *_Add_Node_(list_t **head_node, const char *string, int index_h)
{
	list_t *new_head;

	if (!head_node)
		return (NULL);

	new_head = malloc(sizeof(list_t));

	if (!new_head)
		return (NULL);

	_MemorySet_((void *)new_head, 0, sizeof(list_t));
	new_head->index_h = index_h;

	if (string)
	{
		new_head->string = _StrDup_(string);
		if (!new_head->string)
		{
			free(new_head);
			return (NULL);
		}
	}

	new_head->next = *head_node;
	*head_node = new_head;

	return (new_head);
}

/**
 * _AddNodeAtEnd_ - adds a node to the end of the list
 *
 * @head_node: address of pointer to head_node node
 * @string: string field of node
 * @node_index: node index used by history
 *
 * Return: size of list
 */
list_t *_AddNodeAtEnd_(list_t **head_node, const char *string, int node_index)
{
	list_t *current_node, *new_node;

	if (!head_node)
		return (NULL);

	current_node = *head_node;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_MemorySet_((void *)new_node, 0, sizeof(list_t));
	new_node->node_index = node_index;
	if (string)
	{
		new_node->string = _StrDup_(string);
		if (!new_node->string)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (current_node)
	{
		while (current_node->next)
			current_node = current_node->next;
		current_node->next = new_node;
	}
	else
		*head_node = new_node;
	return (new_node);
}


