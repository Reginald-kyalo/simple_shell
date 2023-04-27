#include "shell.h"

/**
 * shell_exit - exits the shells
 * @args: array of arguments
 * @env: array of env vars
 * Return: success: 1
 */
int shell_exit(char **args, char **env)
{
	int status;
	(void)env;

	status = 0;
	if (args[1])
		status = _atoi(args[1]);
	free_array(args);
	exit(status);
}
/**
 * shell_built - checks for built-in commands and execute them
 * @args: array of arguments
 * @env: array of env vars
 * Return: success: 1
 */
int shell_built(char **args, char **env)
{
	built_t b_ins[] = {
		{"env", shell_env},
		{"exit", shell_exit},
		{NULL, NULL}
	};
	int i;

	if (args[0] == NULL)
		return (0);
	for (i = 0; i < 2; i++)
	{
		if (_strcmp2(args[0], b_ins[i].cmd) == 0)
		{
		return (b_ins[i].f(args, env));
			break;
		}
	}
	return (0);
}
