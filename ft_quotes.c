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
    copy = malloc(ft_strlen(line) * 4);
    // copy = malloc(1000);

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
            time++;
            i += config->jump;
            free(dollaro);
            space = 0;
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
        if ((n % 2) == 0 && ft_isprint(line[i]) == 1)
            space = 0;
        else if ((n % 2) == 0 && space == 0)
        {
            copy[t] = line[i];
            space++;
            i++;
            t++;
            continue;
        }
        else if ((n % 2) == 0 && space != 0)
        {
            space++;
            i++;
            continue;
        }
        copy[t] = line[i];
        space = 0;
        i++;
        t++;
    }
    copy[t] = '\0';
    if ((n % 2) != 0)
        return (0);
    config->cmd_value[pos] = ft_strdup(copy);
    free(copy);
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
        space = 0;
        copy[t] = line[i];
        i++;
        t++;
    }
    copy[i] = '\0';
    if ((n % 2) != 0)
        return (0);
    config->cmd_value[pos] = ft_strdup(copy);
    free(copy);
    return (1);
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
    // printf("lunghezza : %zu\n", ft_strlen(line));
    // printf("line : %s \n", line);
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
            if (!dollaro)
                space = 1;
            i += config->jump;
            time++;
            space = 0;
            free(dollaro);
            // printf("dollaro : %s \n", copy);
            continue;
        }
        if (space == 0 && ft_isprint(line[i]) == 0)
        {
            copy[t] = line[i];
            space++;
            i++;
            t++;
            continue;
        }
        if (space != 0 && ft_isprint(line[i]) == 0)
        {
            space++;
            i++;
            continue;
        }
        copy[t] = line[i];
        // space = 0;
        // printf("giro : %d \n", i);
        i++;
        t++;
    }
    copy[t] = '\0';
    // free(line);
    // printf("copia : %s \n", copy);
    // printf("giro : %d \n", i);
    config->cmd_value[pos] = ft_strdup(copy);
    free(copy);
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
            free(line);
            return(1);
        }
        else if (line[i] == config->index_q[1])
        {
            single_quote(config, line, pos);
            free(line);
            return(1);
        }
        i++;
    }
    no_quote(config, line, pos);
    free(line);
    return(1);
}