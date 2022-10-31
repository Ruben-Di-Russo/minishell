#include "minishell.h"


int single_right(t_cmd *config){
    
    printf("cmd : %s \n", config->cmd_line[config->last_cmd_position + 1]);
    return(1);
}