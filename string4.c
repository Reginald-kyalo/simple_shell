#include "shell.h"

/**
 * check_path - check if command is in the path directories
 * @string: an array of strings
 * @env: an array of env vars
 * Return: pointer to the linked list
 */
void check_path(char **string, char **env)
{
	char *str1, *str2, *path;
	int i, start, last;

	str1 = str_concat("/", string[0]);
	path = _getenv("PATH", env);
	if (path == NULL)
	{
		free(str1);
		exit(0);
	}
	start = i = last = 0;
	while (path[i])
	{
		if (path[i] == ':' || path[i + 1] == '\0')
		{
			if (path[i + 1] == '\0')
			{
				i += 1;
				last = 1;
			}
			else
				path[i] = '\0';
			str2 = str_concat(path + start, str1);
			if (access(str2, F_OK) == 0)
			{
				free(string[0]);
				string[0] = str2;
				free(str1);
				return;
			}
			free(str2);
			if (last)
				break;
			path[i] = ':';
			start = i + 1;
		}
		i += 1;
	}
	free(str1);
}


/**
* error_exit - prints out an error and exits
* @argv: arguments
* @status: exits with this status
*/

void error_exit(char *argv, int status)
{
	(void)status;
	perror(argv);
	exit(0);
}


/**
* free_cptrn - frees n amounts of strings
* @status: the status to exit with
* @n: the number of strings to free
*/
void free_cptrn(int status, const unsigned int n, ...)
{
	unsigned int i;
	va_list args;
	char *ptr;

	va_start(args, n);


	for (i = 0; i < n; i += 1)
	{
		ptr = va_arg(args, char *);
		free(ptr);
	}

	va_end(args);
	if (status == 99)
		return;
	exit(0);
}

/**
* free_array - frees an array of char pointers
* @array: a pointer to the array of chars
*/
void free_array(char **array)
{
	int i;

	if (!array)
		exit(0);
	i = 0;

	while (array[i])
	{
		free(array[i]);
		i += 1;
	}
	free(array);
}

/**
 * shell_env - prints environmental variable
 * @args: array of arguments
 * @env: array of env vars
 * Return: success: 1
 */
int shell_env(char **args, char **env)
{
	int i, len;

	i = 0;
	while (env[i] != NULL)
	{
		len = _strlen(env[i]);
		write(STDOUT_FILENO, env[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	free_array(args);
	return (1);
}
