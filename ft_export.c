#include "minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

int ft_ciack(char *tmp)
{
    int x;

    x = 0;
    while(tmp[x] != '=' && tmp[x])
    {
        if(!ft_isalpha(tmp[x]) && !ft_isdigit(tmp[x]))
            return(1);
        x++;
    }
    return(0);
}

int ft_matrix_len(char **mtx)
{
    int i;

    i = 0;
    while(mtx[i])
    {
        i++;
    }
    return(i);
}

char **ft_append(t_cmd *config, char *line)
{
    char **env_copy;
    int i;

    i = 0;
    env_copy = malloc((ft_matrix_len(config->envp) + 2) * 8);
    while(config->envp[i])
    {
        env_copy[i] = ft_strdup(config->envp[i]);
        i++;
    }
    env_copy[i] = line;
    env_copy[i + 1] = 0;

    ft_free_matrix(config->envp);
    return (env_copy);
}

int ft_export(char **args, t_cmd *config)
{
    char **tmp;
    int status;
    int i;

    tmp = ft_split(config->cmd_parser[0], ' ');
    i = 1;
    status = 0;
    while(tmp[i]){
        if(!ft_isdigit(tmp[i][0]) && !ft_ciack(tmp[i]))
            config->envp = ft_append(config , tmp[i]);
        else 
            status = 1;
        i++;
    }
    if (status)
        printf("errore");
    free(tmp[0]);
    return(status);
}

void ft_checkunset(t_cmd *config, char *str)
{
    int i;

    i = -1;
    while(config->envp[++i])
    {
        if(ft_strncmp(config->envp[i], str, ft_strlen(str)) == 0){
            free(config->envp[i]);
            while(config->envp[i + 1]){
                config->envp[i] = config->envp[i+1];
                i++;
            }
            config->envp[i] = 0;
        }
    }
}

int ft_unset(char **args, t_cmd *config)
{
    char **tmp;
    int status;
    int i;

    tmp = ft_split(config->cmd_parser[0], ' ');
    i = 1;
    status = 0;
    while(tmp[i]){
        if(!ft_isdigit(tmp[i][0]) && !ft_ciack(tmp[i]))
            ft_checkunset(config , tmp[i]);
        else 
            status = 1;
        i++;
    }
    if (status)
        printf("errore");
    free_matrix(tmp);
    return(status);
}
