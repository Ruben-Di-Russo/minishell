#include "minishell.h"

int	ft_child_process(t_cmd *config, int i)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (0);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		execve(ft_pathfinder(config->cmd_line[i], config->envp), args_build(config, i), config->envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		waitpid(pid, NULL, 0);
	}
    i++;
    return (0);
}
int pipe_execute(t_cmd *config)
{
    int i;

    i= 0;
    while (i < config->npipe)
        ft_child_process(argv[i++], i);
    dup2(fileout, STDOUT_FILENO);
    ft_exec(argv[argc - 2], envp);
    return (0);
}