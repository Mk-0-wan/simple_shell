#include "main.h"

/**
 * _unsetenv - deletes the variable name from the environment.
 * @name: environ name
 *
 * Return: 0 on success
 * -1 on failure
 */
int _unsetenv(const char *name)
{
	int i = 0, j = 0, ignore;
	char **cpy;
	env_config env = {0, 0, name};

	ignore = set_envconfig(&env);

	if (ignore)/*TODO: handle errno here */
		return (-1);

	cpy = malloc( sizeof(environ) * env.len);//{"k1", "k2", 0}
	for (j = 0; environ[i]; i++)
		if (i != env.idx)
			cpy[j++] = _strdup(environ[i]);
	cpy[j] = 0;
	environ = cpy;

	return (0);
}
