#include "main.h"

/**
 * expansion_handler - handles variable replacement
 * @mode_args: struct (read main.h)
 *
 * Return: array of string represent arguments to `execve` syscall
 */
char **expansion_handler(m_args *mode_args)
{
	int i, j = 0;
	char *str;

	mode_args->args[0] = mode_args->tokens[0];
	for (i = 1; mode_args->tokens[i]; i++)
	{
		str = mode_args->tokens[i];

		/* escape 1st back-slash */
		if (str[0] == '\\')
			str++;
		if (str[0] == '\\' || !str[1])
		{
			mode_args->args[i] = str;
			continue;
		}
		switch (str[1])
		{
			case '$':
				mode_args->args[i] = utoa(mode_args->ppid);
				break;
			case '?':
				mode_args->args[i] = utoa(mode_args->_errno);
				break;
			default:
				mode_args->args[i] = str;
				if (str[0] == '$')
					mode_args->args[i] = _getenv(str + 1);
				/* Replace previous NULL values */
				if (str[0] != '$' && !mode_args->args[++j])
					mode_args->args[j] = str;
		}
	}
	mode_args->args[i] = 0;

	return (mode_args->args);
}

/**
 * _is_replacement - check if there's any variable replacement
 * @mode_args: struct (read main.h)
 *
 * Return: 1 if there's replacement, 0 otherwise
 */
int _is_replacement(m_args *mode_args)
{
	int i = 1,
	is_replaced = !_strcmp(mode_args->tokens[0], "echo") && mode_args->tokens[1];
	char *is_expanded = 0;

	for (; is_replaced && mode_args->tokens[i]; i++)
	{
		is_expanded = _strpbrk(mode_args->tokens[i], "$");

		if (is_expanded)
			return (1);
	}

	return (is_replaced && is_expanded);
}
