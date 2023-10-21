#include "main.h"

/**
 * builtin_handler - handles all the builtin commands
 *
 * @mode_args: pointer to a struct
 *
 * Return: void
 */
int builtin_handler(m_args *mode_args)
{
	int i = 0;

	/*TODO: handle `type` built in */
	builtin_t builtins[] = {
		{"exit", exit_builtin},
		{"cd", change_directory},
		{"env", env_builtin},
		{"setenv", setenv_builtin},
		{"unsetenv", unsetenv_builtin},
		{"alias", alias_builtin},
		{NULL, NULL}
	};

	while (builtins[i].cmd)
	{
		if (!_strcmp((char *)builtins[i].cmd,
					(char *)(mode_args->tokens)[0]))
		{
			builtins[i].builtin(mode_args);
			return (0);
		}
		i++;
	}
	return (1);
}

