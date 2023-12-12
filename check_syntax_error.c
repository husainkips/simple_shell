#include "header.h"

#define REPEAT_THRESHOLD 1

/**
 * count_repeated_char - Counts the repetitions of a char
 * @input: Input string
 * @i: Index
 *
 * Return: Repetitions
 */
int count_repeated_char(char *input, int i)
{
	if (*(input - 1) == *input)
	return (count_repeated_char(input - 1, i + 1));

	return (i);
}

/**
 * find_syntax_error - Finds syntax errors in separators
 * @input: Input string
 * @i: Index
 * @last: Last char read
 *
 * Return: Index of error. 0 when there are no errors
 */
int find_syntax_error(char *input, int i, char last)
{
	int count = 0;

	if (*input == '\0')
	return (0);

	if (*input == ' ' || *input == '\t')
	return (find_syntax_error(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
		return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
		return (i);

		if (last == '|')
		{
			count = count_repeated_char(input, 0);
			if (count == 0 || count > REPEAT_THRESHOLD)
			return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
		return (i);

		if (last == '&')
		{
			count = count_repeated_char(input, 0);
			if (count == 0 || count > REPEAT_THRESHOLD)
			return (i);
		}
	}

	return (find_syntax_error(input + 1, i + 1, *input));
}

/**
 * find_first_char - Finds index of the first non-space character
 * @input: Input string
 * @i: Index
 *
 * Return: -1 if there is an error. 0 otherwise
 */
int find_first_char(char *input, int *i)
{
	for (*i = 0; input[*i]; (*i)++)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
		return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error_message - Prints syntax error message
 * @datash: Data structure
 * @input: Input string
 * @i: Index of the error
 * @bool: To control error message
 *
 * Return: No return
 */
void print_syntax_error_message(data_shell *datash,
char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	switch (input[i])
	{
	case ';':
		msg = (bool == 0) ? (input[i + 1] == ';' ? ";;" : ";") :
		(input[i - 1] == ';' ? ";;" : ";");
		break;
	case '|':
		msg = (input[i + 1] == '|') ? "||" : "|";
		break;
	case '&':
		msg = (input[i + 1] == '&') ? "&&" : "&";
		break;
	default:
		msg = "";
	}

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = aux_itoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(counter) +
	_strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == NULL)
	{
		free(counter);
		return;
	}

	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * check_syntax_error - Intermediate function to find and print a syntax error
 * @datash: Data structure
 * @input: Input string
 *
 * Return: 1 if there is an error. 0 otherwise
 */
int check_syntax_error(data_shell *datash, char *input)
{
	int begin = 0;
	int first_char_result = 0;
	int i = 0;

	first_char_result = find_first_char(input, &begin);
	if (first_char_result == -1)
	{
		print_syntax_error_message(datash, input, begin, 0);
		return (1);
	}

	i = find_syntax_error(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		print_syntax_error_message(datash, input, begin + i, 1);
		return (1);
	}

	return (0);
}
