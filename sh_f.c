#include "main.h"

/**
 * main - simple shell
 * @ac: arguments count
 * @av: arguments vector
 * @env: enviroment variables
 *
 * Return: 0 as exit status
 */
int main(__attribute__((unused))int ac, char **av, char **env)
{
	ssize_t bytes;
	size_t n = 0;
	ui cmd_count = 0;
	char *line = 0;
	char **tokens = 0;
	char *path = 0;
	list_t *list_path = path_list();
	m_args mode_args;

	while (-1)
	{
		if (isatty(STDIN_FILENO))
			printf("($) ");
		bytes = getline(&line, &n, stdin);
		if (bytes == -1)
		{
			free_buf(0, &line, 0);
			free_list(list_path);
			exit(1);
		}
		line[bytes - 1] = 0;
		cmd_count++;
		tokens = tokenize_line(line);
		if (!_strcmp(tokens[0], "exit"))
		{
			free_list(list_path);
			free_buf(0, &line, 0);
			free_buf(&tokens, 0, 1);
			exit(0);
		}
		path = _which(tokens[0], list_path);
		mode_args.tokens = &tokens;
		mode_args.env = &env;
		mode_args.av = av;
		mode_args.path = &path;
		mode_args.line = &line;
		mode_args.cmd_count = &cmd_count;
		mode_args.list_path = &list_path;
		mode(STDIN_FILENO)(&mode_args);
	}
	return (0);
}

