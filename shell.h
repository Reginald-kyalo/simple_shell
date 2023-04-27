#ifndef _SHELL_H_
#define _SHELL_H_

/*
 * File: shell.h
 * Auth: Reginald Kyalo
 */

#define MAX_IN 512
#define MAX_ARGS 64

extern char **environ;

void type_prompt(void);
char **read_commands(char *input);
int execute(char **args);
int handle_builtin(char **args);

int _strcspn(const char *str, const char *discard);
char *_strtok(char *str, const char *delim);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strlen(const char *str);
int _strncmp(const char *s1, const char *s2, int n);

char *_getenv(const char *name);

#endif /* _SHELL_H_ */


