#include "minishell.h"

int xpipe_execute(t_cmd *config)
{
    int i;
    
    int ch[2];
    pid_t child1;
    pid_t child2;
    
    i = 0;
    /*
    printf("val  %s\n", config->cmd_line[0]);
    printf("val  %s\n", config->cmd_line[1]);
    printf("val  %s\n", config->cmd_line[2]);
    ft_argv_print(args_build(config, 0), "cc : ");
    ft_argv_print(args_build(config, 1), "cc : ");
    ft_argv_print(args_build(config, 2), "cc : ");
    */
    
    while (i <= config->npipe)
    {
        /*
        printf("id %d val  %s\n", i, config->cmd_line[i]);
        ft_argv_print(args_build(config, i), "cc : ");
        */

        pipe(ch);
        config->stdout_clone = dup(STDOUT_FILENO);
        config->stdin_clone = dup(STDIN_FILENO);
        child1 = fork();
        if (child1 == 0)
        {
            dup2(ch[1], STDOUT_FILENO);
            close(ch[0]);
            close(ch[1]);
            if (execve(ft_pathfinder(config->cmd_line[i], config->envp), args_build(config, i), config->envp))
                printf("error exec pipe 1.\n");
            //exit(0);
        }
        else
        {
            // close(ch[0]);
            // close(ch[1]);
            wait(NULL);
        }

        child2 = fork();
        if (child2 == 0)
        {
            dup2(ch[0], STDIN_FILENO);
            close(ch[1]);
            close(ch[0]);
            if (execve(ft_pathfinder(config->cmd_line[i + 1], config->envp), args_build(config, i + 1), config->envp))
                printf("error exec pipe 2.\n");
            //exit(0);
        }

        else
        {
            // close(ch[0]);
            // close(ch[1]);
            wait(NULL);
        }

        dup2(config->stdout_clone, STDOUT_FILENO);
        close(config->stdout_clone);

        dup2(config->stdin_clone, STDIN_FILENO);
        close(config->stdin_clone);
        
        i++;
    }
    config->npipe = 0;
    printf("pipe finishhhhhhh");
    // sleep(10);
    return (1);
}
