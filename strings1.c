#include <stdio.h>
#include "shell.h"

/**
 * _strcspn - checks index of desired character
 * @str: string to be checked
 * @discard: character to be searched
 *
 * Return: index of character being searched for or
 *	length of string if character is not found
 */
int _strcspn(const char *str, const char *discard)
{
	int i, j;

	for (i = 0; str[i]; i++)
	{
		for (j = 0; discard[j]; j++)
		{
			if (str[i] == discard[j])
				return (i);
		}
	}
	return (i);
}

/**
 * _strtok - splits a line into seperate words(tokens) by
 *	replacing specified character with '\0'
 * @str: string to be tokenized
 * @delim: specified character
 *
 * Return: pointer to tokenized string
 *	NULL on error or end of string is reached
 */
char *_strtok(char *str, const char *delim)
{
	static char *last_str;
	char *token;
	const char *d = delim;

	if (str != NULL)
		last_str = str;

	if (last_str == NULL || *last_str == '\0')
		return (NULL);

	token = last_str;
	while (*last_str != '\0')
	{
		while (*d != '\0')
		{
			if (*last_str == *delim)
			{
				last_str = '\0';
				last_str++;
				return (token);
			}
			d++;
		}
		last_str++;
	}
	return (token);
}

/**
 * _strncmp - compares s1 and s2 if similar or not
 *	upto n characters
 * @s1: to be compared with s2
 * @s2: participates in comparison too
 * @n: number of characters to be compared
 *
 * Return: if s1 > s2; positive difference of s1 and s2
 *	if s1 < s2; negative difference of s1 and s2
 *	if s1 == s2; 0
 */
int _strncmp(const char *s1, const char *s2, int n)
{
	int i = 0;

	while ((*s1 && *s2) && (*s1 == *s2) && i < n)
	{
		s1++;
		s2++;
		i++;
	}
	return (*s1 - *s2);
}

/**
 * _strcmp - compares s1 and s2 if similar or not
 * @s1: to be compared with s2
 * @s2: participates in comparison too
 *
 * Return: if s1 > s2; positive difference of s1 and s2
 *      if s1 < s2; negative difference of s1 and s2
 *      if s1 == s2; 0
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (*s1 && *s2)
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
		i++;
	}
	return (0);
}

/**
 * _strlen - finds length of string
 * @s: string to be "measured"
 *
 * Return: number of characters counted plus null byte
 *	0 if no counting has occured
 */
int _strlen(const char *s)
{
	int i = 0;

	while (*s)
	{
		s++;
		i++;
	}
	return (i);
}
