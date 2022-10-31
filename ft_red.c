#include "minishell.h"


int single_right(t_cmd *config){
    int fd;
    printf("file : %s \n", config->cmd_line[config->num_cmd - 1 ]);
    fd = open(config->cmd_line[config->num_cmd - 1 ], O_CREAT | O_TRUNC | O_WRONLY, 0777);
    if(config->npipe > 0){
        red_pipe_execute(fd, config);
        return (1);
    }



    close(fd); 
    return(1);
}