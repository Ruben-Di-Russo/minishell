#include "minishell.h"

char *find_dollar(char *line, int time, t_cmd *config)
{
    char **tmp;
    int try;
    int x;

    tmp = ft_split(line, ' ');
    try = 0;
    x = 0;
    while(tmp[x])
    {
        // printf("split : %s \n", tmp[x]);
        if(ft_strchr(tmp[x], '$'))
            tmp[x] = ft_strchr(tmp[x], '$');
        tmp[x] = ft_strtrim(tmp[x], "\", \'");
        config->jump = ft_strlen(tmp[x]);
        if (tmp[x][0] == '$')
        {
            if (try == time)
            {
                free_matrix(tmp);
                return(tmp[x]);
            }
            try++;
        }
        x++;
    }
    return(NULL);
}

char *find_envp(t_cmd *config, char *tmp)
{
    char *dollaro;
    char **dollarofinito;
    int x;

    x = 0;
    while(config->envp[x])
    {
        if(ft_strncmp(config->envp[x], tmp, ft_strlen(tmp)) == 0)
        {
            dollarofinito = ft_split(config->envp[x], '=');
            dollaro = ft_strdup(dollarofinito[1]);
            free_matrix(dollarofinito);
            free(tmp);
            return(dollaro);
        }
        x++;
    }
    return(dollaro);
}

char *dollar(t_cmd *config, char *line, int time)
{
    char *tmp;
    int x;

    x = 0;
    tmp = find_dollar(line, time, config);
    if(!tmp)
        return(NULL);
    tmp = ft_strtrim(tmp, "$");
    while(tmp[x] != '\0')
    {
        if (!(tmp[x] >= 65 && tmp[x] <= 90))
            return(NULL);
        x++;
    }
    tmp = find_envp(config, tmp);
    if(!tmp)
        return(NULL);
    return(tmp);
}