#include <stdio.h>
#include "shell.h"

/**
 * _strcmp2 - compares two strings
 * @s1: string 1 to be compared to string 2
 * @s2: string 2 to be compared to string 1
 * Return: integer < 0 if string 1 first unmatched character ASCII value is
 * less than string 2; integer > 0 if first unmatched character ASCII value
 * is greater; 0 if strings are equal
 */
int _strcmp2(const char *s1, const char *s2)
{
	int i, result;

	for (i = 0; s1[i] != '\0' || s2[i] != '\0'; i++)
	{
		result = s1[i] - s2[i];
		if (result == 0)
			continue;
		else
			break;
	}
	if (s1[i] == '\0' || s2[i] != '\0')
		result = s1[i] - s2[i];

	return (result);
}

/**
 * _atoi - convert a string to an integer
 * @s: string to be converted
 * Return: integer
 */
int _atoi(char *s)
{
	int i, sign;
	unsigned int num;

	num = i = 0;
	sign = 1;
	while ((s[i] < '0' || s[i] > '9') && s[i] != '\0')
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	for (; s[i] != '\0' && s[i] >= '0' && s[i] <= '9'; i++)
	{
		num = num * 10 + (s[i] - '0');
	}
	num *= sign;
	return (num);
}

/**
 * _getenv - get an environmental variable
 * @name: name of env var
 * @env: list of env var
 * Return: pointer to env var
 */
char *_getenv(const char *name, char **env)
{
	int i, j;
	int res, len;

	i = j = 0;
	while (env[i] != NULL)
	{
		res = _strcmp(name, (const char *)env[i]);
		if (res == 1)
		{
			len = _strlen(env[i]);
			while (env[i][j] != '=')
				j += 1;
			len -= j;
			return (env[i] + j + 1);
		}
		i++;
	}
	return (NULL);
}

/**
 * _memcpy - copies memory area
 * @dest: address of memory to be filled
 * @src: constant byte to be filled
 * @n: number of bytes to be copied from src to dest
 * Return: address of pointer to dest
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
{
		dest[i] = src[i];
}
	return (dest);
}

/**
 * str_concat - concatenates two strings to newly allocated space in memory
 * @s1: string1
 * @s2: string 2 to appended to string1
 * Return: pointer to the concatenated string; NULL otherwise
 */
char *str_concat(char *s1, char *s2)
{
	char *concat_str;
	int i, j;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";
	for (i = 0; s1[i] != '\0'; i++)
		;
	for (j = 0; s2[j] != '\0'; j++)
		;
	concat_str = malloc((sizeof(char) * i) + (sizeof(char) * j) + 1);
	if (concat_str == NULL)
		exit(0);
	for (i = 0; s1[i] != '\0'; i++)
		concat_str[i] = s1[i];
	for (j = 0; s2[j] != '\0'; j++)
		concat_str[i + j] = s2[j];
	concat_str[i + j] = '\0';
	return (concat_str);
}
