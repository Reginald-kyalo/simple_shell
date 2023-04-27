#include <stdio.h>
#include "shell.h"

/**
 * _strchr - searches for a character
 * @s: to be searched from
 * @c: to be searched for
 *
 * Return: on success pointer to 1st occurence of character,
 *	null on failure
 */

char *_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}

/**
 * _getenv - returns pointer to value of a key(name)
 * @name: variable to be searched for
 *
 * Return: pointer to value if found
 *	NULL if not found;
 */

char *_getenv(const char *name)
{
	int i = 0;
	char *value = NULL;

	while (environ[i] != NULL)
	{
		if ((_strncmp(name, environ[i], _strlen(name))) == 0)
		{
			value = _strchr(environ[i], '=') + 1;
			break;
		}
		i++;
	}
	return (value);
}

