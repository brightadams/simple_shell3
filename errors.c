#include "shell.h"

/**
 * _eputs - Prints a string to standard error.
 * @str: The string to print.
 *
 * Return: Nothing.
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - Writes a character to standard error.
 * @c: The character to write.
 *
 * Return: On success 1.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int idx;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || idx >= WRITE_BUF_SIZE)
	{
		write(2, buf, idx);
		idx = 0;
	}
	if (c != BUF_FLUSH)
		buf[idx++] = c;
	return (1);
}

/**
 * _putfd - Writes a character to a given file descriptor.
 * @c: The character to write.
 * @fd: The file descriptor to write to.
 *
 * Return: On success 1.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int idx;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || idx >= WRITE_BUF_SIZE)
	{
		write(fd, buf, idx);
		idx = 0;
	}
	if (c != BUF_FLUSH)
		buf[idx++] = c;
	return (1);
}

/**
 * _putsfd - Prints a string to a given file descriptor.
 * @str: The string to print.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}

