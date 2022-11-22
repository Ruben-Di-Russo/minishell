#include "minishell.h"

int builtin_exec(t_cmd *config)
{
    char **test;
    int i;

    i = 0;
    test = malloc(sizeof(char *) * 1024);
    test[i] = ft_strdup("builtin");
    i++;
    if (ft_strcmp(config->cmd_line[0], "echo") == 0){
        //printf("sono simoecho\n");
        test[i]=ft_strdup(config->cmd_line[0]);
        i++;
        if(config->cmd_args[0])
        {
        test[i] = ft_strdup(config->cmd_args[0]);
        i++;
        }
        if(config->cmd_value[0])
        {
        test[i] = ft_strdup(config->cmd_value[0]);
        i++;
        }
        config->arg_build[0] = NULL;
    }
    return(1);
}