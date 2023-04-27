#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * type_prompt - types prompt on screen
 *
 * Return: nothing
 */
void type_prompt(void)
{
	char *prompt = "$ ";

	write(STDOUT_FILENO, prompt, _strlen(prompt));
	fflush(stdout);
}

/**
 * read_commands - reads commands and parses it to execution
 * @input: array containing line of commands
 *
 * Return: pointer to array containing individual commands
 *	0 on failure
 */
char **read_commands(char *input)
{
	char **args;
	int i = 0;
	ssize_t nread;

	args = malloc(sizeof(char *) * MAX_ARGS);
	if (args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	nread = read(STDIN_FILENO, input, MAX_IN);
	if (nread < 0)
	{
		perror("read");
		free(args);
		exit(EXIT_FAILURE);
	}
	else if (nread == 0)
	{
		args[0] = NULL;
		return (args);
	}
	else if (nread > MAX_IN)
	{
		free(args);
		return (0);
	}
	input[_strcspn(input, "\n")] = '\0';
	args[i] = _strtok(input, " ");
	while (args[i] != NULL)
	{
		i++;
		args[i] = _strtok(NULL, " ");
	}
	args[i] = NULL;
	return (args);
}

/**
 * execute - executes commands
 *	saved in bin directory
 * @args: commands to be executed
 *
 * Return: 1 failure
 */
int execute(char **args)
{
	pid_t pid =  fork();
	int status;

	if (pid < 0)
	{
		perror("fork");
		free(args);
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			free(args);
			return (1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	free(args);
	return (0);
}

/**
 * handle_builtin - executes builtin shell commands
 * @args: commands to execute
 *
 * Return: 0 on success,
 *	1 if command not found or failure
 */
int handle_builtin(char **args)
{
	int exit_status;

	if ((_strcmp(args[0], "exit")) == 0)
	{
		if (args[1] == NULL)
		{
			free(args);
			exit(0);
		}
		else if (args[1] != NULL)
		{
			exit_status = atoi(args[1]);
			free(args);
			exit(exit_status);
		}
	}
	else if ((_strcmp(args[0], "env")) == 0 && args[1] == NULL)
	{
		int i = 0;
		char *p;

		while (environ[i] != NULL)
		{
			p = environ[i];
			while (*p != '\0')
			{
				putchar(*p);
				p++;
			}
			putchar('\n');
			i++;
		}
		free(args);
		return (0);
	}
	else
	{
		return (1);
	}
	return (1);
}

/**
 * main - runs simple shell
 * @argc: number of command line arguments
 * @argv: stores command line arguments
 *
 * Return: 0 always
 */
int main(int argc, char **argv)
{
	char input[MAX_IN];
	char **commands = NULL;
	char *message = NULL;

	while (1)
	{
		type_prompt();
		commands = read_commands(input);
		if (handle_builtin(commands) == 1)
		{
			if (execute(commands) == 1 && argc == 1)
			{
				message = argv[0];
				perror(message);
			}
		}
	}
	return (0);
}
