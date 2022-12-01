#include "minishell.h"


int single_right(t_cmd *config){
    int fd;
    //printf("file : %s \n", config->cmd_line[config->num_cmd - 1 ]);
    fd = open(config->cmd_line[config->num_cmd - 1 ], O_CREAT | O_TRUNC | O_WRONLY, 0777);
    if(config->npipe > 0){
        return(red_pipe_execute(fd, config));
    }
    dup2(fd, STDOUT_FILENO);
    cmd_single(config);
    close(fd);
    dup2(config->stdout_clone, STDOUT_FILENO);
    return(1);
}

int double_right(t_cmd *config){
    int fd;
    pid_t   pid;

    fd = open(config->cmd_line[config->num_cmd - 1 ], O_CREAT | O_APPEND | O_WRONLY, 0777);
    if(config->npipe > 0){
        return(red_pipe_execute(fd, config));
    }
    pid = fork();    
    if (pid == -1)
        return (0);
    dup2(fd, STDOUT_FILENO);
    if (pid == 0)
        execve(ft_pathfinder(config->cmd_line[0], config->envp), args_build(config, 0), config->envp);
    else
        wait(NULL);
    //close(fd);
    dup2(config->stdout_clone, STDOUT_FILENO);
    return(1);
}

int single_left(t_cmd *config){
    int fd;
    fd = open(config->cmd_line[config->num_cmd - 1 ], O_RDONLY);
    dup2(fd, STDIN_FILENO);
    cmd_single(config);
    close(fd);
    dup2(config->stdin_clone, STDIN_FILENO);    
    return(1);
}

int double_left(t_cmd *config){
    int fd;
    int st;
    char *delimiter;
    char *lines;
    st = 1;
    delimiter = config->cmd_line[config->num_cmd - 1 ];
    fd = open(".tmp", O_CREAT | O_TRUNC | O_WRONLY, 0777);
    while( st )  {
        lines = readline(">");
        if(ft_strcmp(lines, delimiter) == 0){
            st = 0;
            break;
        }
        ft_putstr_fd(lines, fd);
        ft_putchar_fd('\n', fd);

    }
    close(fd);
    fd = open(".tmp", O_RDONLY);
    dup2(fd, STDIN_FILENO);
    cmd_single(config);
    close(fd);
    dup2(config->stdin_clone, STDIN_FILENO);
    return(1);
}