#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - unsets an alias with the given name
 * @info: parameter struct
 * @alias_name: the name of the alias to unset
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *alias_name)
{
	char *equals_ptr, equals_char;
	int ret;

	equals_ptr = _strchr(alias_name, '=');
	if (!equals_ptr)
		return (1);
	equals_char = *equals_ptr;
	*equals_ptr = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, alias_name, -1)));
	*equals_ptr = equals_char;
	return (ret);
}

/**
 * set_alias - sets an alias with the given name and value
 * @info: parameter struct
 * @alias_string: the string representing the alias to set
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *alias_string)
{
	char *equals_ptr;

	equals_ptr = _strchr(alias_string, '=');
	if (!equals_ptr)
		return (1);
	if (!*++equals_ptr)
		return (unset_alias(info, alias_string));

	unset_alias(info, alias_string);
	return (add_node_end(&(info->alias), alias_string, 0) == NULL);
}

/**
 * print_alias - prints an alias with the given name and value
 * @alias_node: the alias node to print
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *alias_node)
{
	char *equals_ptr = NULL, *alias_name = NULL;

	if (alias_node)
	{
		equals_ptr = _strchr(alias_node->str, '=');
		for (alias_name = alias_node->str; alias_name <= equals_ptr; alias_name++)
			_putchar(*alias_name);
		_putchar('\'');
		_puts(equals_ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *equals_ptr = NULL;
	list_t *alias_node = NULL;

	if (info->argc == 1)
	{
		alias_node = info->alias;
		while (alias_node)
		{
			print_alias(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		equals_ptr = _strchr(info->argv[i], '=');
		if (equals_ptr)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

