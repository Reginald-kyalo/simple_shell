#include "shell.h"

/**
 * main - Entry point
 * @argc: argument count
 * @argv: list of arguments
 * @env: list of env vars
 * Return: Always 0 (Success)
 */

int main(int argc, char *argv[], char **env)
{
	char *ptr = NULL;
	char **string = NULL;
	int status;
	pid_t parent;
	(void)argc;

	while (1)
	{
		ptr = NULL;
		signal(SIGINT, signal_handler);
		if (prompt(&ptr) == -1)
			continue;
		string = strtow(ptr);
		if (!string)
		{
			free_cpt(99, 1, ptr);
			continue;
		}
		free_cpt(99, 1, ptr);
		if (shell_built(string, env))
			continue;
		parent = fork();
		if (parent == 0)
		{
			check_path(string, env);
			if (execve(string[0], string, NULL) == -1)
			{
				perror(*argv);
				free_array(string);
				exit(0);
			}
		}
		else
		{
			free_array(string);
			if (!wait(&status))
				break;
		}
	}
	return (0);
}
/**
 * prompt - prompts the user for commands
 * @ptr: ptr will hold the string of commands
 * Return: 1 for success
 */

int prompt(char **ptr)
{
	size_t size = 0;
	int len;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "Fuji$ ", 6);
	len = getline(ptr, &size, stdin);
	if (len == EOF)
		free_cpt(-1, 1, *ptr);
	(*ptr)[len - 1] = '\0';
	if (*(*ptr) == '\0' || (*(*ptr) == '.' && (*ptr)[1] == '\0'))
	{
		free_cpt(99, 1, *ptr);
		return (-1);
	}
	else
		return (1);
}

/**
 * signal_handler - reprints prompt when signal ctrl+C is captured
 * @signo: signal number
 */
void signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		write(STDOUT_FILENO, "$ ", 2);
	}
}
