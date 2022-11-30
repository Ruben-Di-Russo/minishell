#include "minishell.h"

char	*read_line(t_cmd *config)
{
	char *line;
	line = readline(config->banner);
	if (!line[0])
	{
		while (!line[0])
			line = readline(config->banner);
	}
	else
		add_history(line);
	return (line);
}

void shell_loop(t_cmd *config)
{
	int status;
	status = 1;

	while (1)
	{
		config->line = read_line(config);
		cmd_parser(config, config->line);
		cmd_fill(config);
		status = cmd_prepare(config);
		ft_clean(config);
	}
}

char **args_build(t_cmd *config, int i)
{
	int x;

	x = 0;
	config->arg_build = malloc(sizeof(char *) * 100);
	config->arg_build[x] = ft_strdup(config->cmd_line[i]);
	x++;
	if (config->cmd_args[i])
	{
		config->arg_build[x] = ft_strdup(config->cmd_args[i]);
		x++;
	}
	if (config->cmd_value[i])
	{
		config->arg_build[x] = ft_strdup(config->cmd_value[i]);
		x++;
	}
	config->arg_build[x] = NULL;
	// printf("%s %s %s %s \n",now [x - 3] ,now[x - 2], now[x - 1], now[x]);
	return (config->arg_build);
}

int cmd_single(t_cmd *config)
{

	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (ft_check(config))
		{
			printf("error exec.\n");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		wait(NULL);
	}

	return 1;
}

int cmd_execute(t_cmd *config)
{

	if (config->npipe > 0)
	{
		if (config->red > 0)
		{
			printf("red mode on pip  \n");
			if (config->red == 1) // single >
			{
				// printf("ciao %d \n", single_right(config));
				return (single_right(config));
			}
			if (config->red == 2) // single >>
				return (double_right(config));
			if (config->red == 3) // single <
				return (single_left(config));
			if (config->red == 4) // single <<
				return (double_left(config));
		}
		else
		{
			printf("pipe mode \n");
			return (pipe_execute(config));
		}
	}
	else
	{
		if (config->red > 0)
		{
			printf("red mode on single\n");
			if (config->red == 1) // single >
			{
				return (single_right(config));
			}
			if (config->red == 2) // single >>
			{
				return (double_right(config));
			}
			if (config->red == 3) // single <
				return (single_left(config));
			if (config->red == 4) // single <<
				return (double_left(config));
		}
		else
		{
			printf("single mode \n");
			return (cmd_single(config));
		}
	}

	return (0);
}

int cmd_prepare(t_cmd *config)
{
	int i;
	i = 0;

	if (config->cmd_line[0] == NULL)
	{
		return 1;
	}

	while (i < config->builtin_len)
	{
		if (ft_strcmp(config->cmd_line[0], config->builtin_cmd[i]) == 0)
		{
			return (builtin_func(config->builtin_cmd[i], &config->cmd_args[0], config));
		}
		i++;
	}
	return cmd_execute(config);
}
char **ft_set_envp(char **envp)
{
	char **env_copy;
	int i;

	i = 0;
	env_copy = malloc((ft_matrix_len(envp) + 2) * 8);
	while(envp[i])
	{
		env_copy[i] = ft_strdup(envp[i]);
		i++;
	}
	env_copy[i] = 0;

	return (env_copy);
}
void shell_init(t_cmd *config, char **envp)
{

	config->envp = ft_set_envp(envp);
	config->npipe = 0;
	config->builtin_cmd = builtin_str();
	config->builtin_len = len_num_builtins(config->builtin_cmd);
	config->banner = ft_strcat(getenv("USER"), "@minishell>");
	config->stdout_clone = dup(STDOUT_FILENO);
	config->stdin_clone = dup(STDIN_FILENO);
	config->operator= operator();
	config->index_q = quote_index();
	config->red = 0;
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_cmd config;
	// t_cmd config;
	shell_init(&config, envp);
	shell_loop(&config);
	return (1);
}