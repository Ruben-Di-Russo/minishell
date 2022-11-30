#include "minishell.h"

char *quote_index(void)
{
    char *op;
    op = malloc(sizeof(char) * 2 + 1);
    op[0] = '\"';
    op[1] = '\'';
    op[2] = '\0';
    return (op);
}

int double_quote(t_cmd *config, char *line, int pos)
{
    int i;
    int n;
    int t;
    int space;
    int d;
    int time;
    char *copy;
    char *dollaro;

    i = 0;
    n = 0;
    t = 0;
    time = 0;
    space = 0;
    // copy = malloc(ft_strlen(line) * 4);
    copy = malloc(1000);

    while (line[i])
    {
        if (line[i] == '$')
        {
            d = 0;
            dollaro = dollar(config, line, time);
            while(dollaro && dollaro[d])
            {
                copy[t] = dollaro[d];
                t++;
                d++;
            }
            i += config->jump;
            if (!dollaro)
                space = 1;
            continue;
        }
        if (line[i] == config->index_q[0])
        {
            i++;
            n++;
            continue;
        }
        if ((n % 2) == 0 && ft_isalpha(line[i]) == 1)
            space = 0;
        else if ((n % 2) == 0 && space == 0)
            space++;
        else if ((n % 2) == 0 && space != 0)
        {
            space++;
            i++;
            continue;
        }
        copy[t] = line[i];
        i++;
        t++;
    }
    copy[t + 1] = '\0';
    if ((n % 2) != 0)
        return (0);
    config->cmd_value[pos] = ft_strdup(copy);
    return (1);
}

int single_quote(t_cmd *config, char *line, int pos)
{
    int i;
    int n;
    int t;
    int space;
    char *copy;

    i = 0;
    n = 0;
    t = 0;
    space = 0;
    copy = malloc(ft_strlen(line) * 4);
    while (line[i])
    {
        if (line[i] == config->index_q[1])
        {
            i++;
            n++;
            continue;
        }
        if ((n % 2) == 0 && ft_isalpha(line[i]) == 1)
        {
            space = 0;
            copy[t] = line[i];
            i++;
            t++;
            continue;
        }
        if ((n % 2) == 0 && space == 0)
        {
            space++;
                copy[t] = line[i];
                i++;
                t++;
                continue;
            }
            if ((n % 2) == 0 && space != 0)
            {
                space++;
                i++;
                continue;
            }
            copy[t] = line[i];
            i++;
            t++;
    }
    copy[i] = '\0';
    if ((n % 2) != 0)
        return (0);
    config->cmd_value[pos] = ft_strdup(copy);
    return (1);
}

char *dollar(t_cmd *config, char *line, int time)
{
    char **tmp;
    char *dollaro;
    char **dollarofinito;
    int pos;
    int x;
    int try;

    x = 0;
    try = 0;
    tmp = ft_split(line, ' ');
    while(tmp[x])
    {
        tmp[x] = ft_strtrim(tmp[x], "\"");
        if (tmp[x][0] == '$')
        {
            if (try == time)
                break;
            try++;
        }
        x++;
    }
    config->jump = ft_strlen(tmp[x]);
    tmp[x] = ft_strtrim(tmp[x], "$");
    pos = 0;
    while(tmp[x][pos] != '\0')
    {
        if (!(tmp[0][pos] >= 65) && !(tmp[0][pos] <= 90))
            return(0);
        pos++;
    }
    pos = 0;
    while(config->envp[pos])
    {
        if(ft_strncmp(config->envp[pos], tmp[x], ft_strlen(tmp[x])) == 0)
        {
            dollaro = malloc(ft_strlen(config->envp[pos]) * (sizeof (char)));
            dollarofinito = ft_split(config->envp[pos], '=');
            dollaro = dollarofinito[1];
        }
        pos++;
    }
    return(dollaro);
}

int no_quote(t_cmd *config, char *line, int pos)
{
    int i;
    int d;
    int space;
    int t;
    int time;
    char *copy;
    char *dollaro;

    copy = malloc(1000);
    i = 0;
    time = 0;
    d = 0;
    space = 0;
    t = 0;
    while (line[i])
    {
        if (line[i] == '$')
        {
            dollaro = dollar(config, line, time);
            while(dollaro && dollaro[d])
            {
                copy[t] = dollaro[d];
                t++;
                d++;
            }
            i += config->jump;
            time++;
            if (!dollaro)
                space = 1;
            continue;
        }
        if (space == 0 && ft_isdigit(line[i]))
            space++;
        else if (space != 0 && ft_isdigit(line[i]))
        {
            space++;
            i++;
            continue;
        }
        copy[t] = line[i];
        i++;
        t++;
    }
    copy[t + 1] = '\0';
    config->cmd_value[pos] = ft_strdup(copy);
    return (1);
}

int check_quotes(t_cmd *config, char *line, int pos)
{
    size_t i;

    i = 0;
    while(line[i])
    {
        if (line[i] == config->index_q[0])
        {
            double_quote(config, line, pos);
            return(1);
        }
        else if (line[i] == config->index_q[1])
        {
            single_quote(config, line, pos);
            return(1);
        }
        i++;
    }
    no_quote(config, line, pos);
    return(1);
}