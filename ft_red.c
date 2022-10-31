#include "minishell.h"


int single_right(t_cmd *config){
    if(config->npipe > 0)
        config->last_cmd_position += 1;

    printf("cmd : %s \n", config->cmd_line[config->last_cmd_position]);
    return(1);
}