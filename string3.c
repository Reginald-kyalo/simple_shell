#include "shell.h"

/**
* strtow - splits a string into words
* @str: a pointer to the string
* Return: a pointer to an array
*/

char **strtow(char *str)
{
	char **words;
	int count;

	count = word_count(str);
	if (count <= 0)
		return (NULL);

	words = malloc(sizeof(char *) * (count + 1));
	if (!words)
		return (NULL);
	get_word(words, str);


	return (words);
}

/**
* cpy_str - clips a word from the string
* @end: the end of the word
* @s: the string to clip the word from
* @word_box: the array to store the word in
*/
void cpy_str(int end, char *s, char **word_box)
{
	int i;

	(*word_box) = malloc(sizeof(char) * end + 1);
	if (!(*word_box))
	{
		perror("Error: malloc\n");
		free(word_box);
		exit(0);
	}

	for (i = 0; i < end; i += 1)
		(*word_box)[i] = s[i];
	(*word_box)[i] = '\0';
}

/**
* word_count - counts the number of words in a string
* @str: a pointer to the string
* Return: the number of words in a string
*/

int word_count(char *str)
{
	unsigned int count, i;
	int found;

	if (str == NULL || *str == '\0')
		return (-1);

	found = i = count = 0;

	if (str[1] == '\0' && *str == ' ')
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i + 1] == '\0')
		{
			if (str[i] != ' ')
				found = 1;
			if (found)
			{
				count += 1;
				found = 0;
			}
			i += 1;
			continue;
		}
		else
			found = 1;
		i += 1;
	}
	return (count);
}
/**
* get_word - get a word from a string to copy
* @words: an array of words
* @str: a pointer to the string
* Return: the array of words
*/
void get_word(char **words, char *str)
{
	int i, start, found, count;

	count = i = start = found = 0;

	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i + 1] == '\0')
		{
			if (str[i] != ' ')
			{
				i += 1;
				found = 1;
			}
			if (found)
			{
				cpy_str(i - start, str + start, words + count);
				if (!(words + count))
					exit(0);
				count += 1;
				start = i + 1;
				found = 0;
			}
				if (str[i] == '\0')
					continue;
			i += 1;
			start += 1;
			continue;
		}
		else
		{
			if (!found)
				start = i;
			found = 1;
		}
		i += 1;
	}
	words[count] = NULL;
}
