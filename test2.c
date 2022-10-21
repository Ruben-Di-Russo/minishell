#include "minishell.h"

void open_pipe(int pipes[], int no_pipes)
{
	int i;
	
	i = -1;
	while (++i < no_pipes)
		pipe(pipes + i * 2);
}

void ft_exec_pipe(char *cmd, int nb_pipe)
{
	int 	i;
	int		j;
	int 	pipes[2 * nb_pipe];
	int 	status;
	pid_t	pid;
	
	i = 0;
	j = nb_pipe + 1;
	open_pipe(pipes, nb_pipe);
	while (cmds[i])
	{
		pid = fork();
		if (pid == 0)
		{
			if (non è l ultimo comando)
				dup2(pipes[i + 1], STDOUT_FILENO);
			if (non è il primo comando)
				dup2(pipes[i - 2], STDIN_FILENO);
			close_pipe(pipes, nb_pipe);
			ft_exec_cmd_fork(cmds[i]);
		}
		i += 2;
		shell->token++;
		shell->operator++;
	}
	close_pipe(pipes, nb_pipe);
	while (i-- > 0)
        waitpid(-1, &status, 0);
	shell->exitstatus = WEXITSTATUS(status);
}