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
		dup2(fd[1], STDOUT_FILENO);//STDOUT_FILENO 1
		execve(ft_pathfinder(config->cmd_line[i], config->envp), args_build(config, i), config->envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);//STDIN 0
		waitpid(pid, NULL, 0);
	}
    return (1);
}
int pipe_execute(t_cmd *config)
{
    int i;
    pid_t   pid;

    i = 0;
    while (i < config->npipe){
        ft_child_process(config, i);
        i++;
    }
    dup2(config->stdout_clone, STDOUT_FILENO);
    pid = fork();
    if (pid == -1)
        return (-1);
    if (pid == 0)
        execve(ft_pathfinder(config->cmd_line[i], config->envp), args_build(config, i), config->envp);
    else
        wait(NULL);
    config->npipe = 0;
	config->last_cmd_position = i;
    dup2(config->stdin_clone, STDIN_FILENO);

	if(config->red > 0){
		printf("red dec : %d \n", config->red);
		printf("last  : %d \n", config->last_cmd_position);
		return(single_right(config));
	}

    return (1);
}