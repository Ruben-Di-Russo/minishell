#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == s[i])
		return ((char *)&s[i]);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;

	if (!s1 || !set)
		return (0);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i && ft_strchr(set, s1[i]))
		i--;
	return (ft_substr(s1, 0, i + 1));
}

char **cmd_parser(char *line)
{
    char *tmp;
    char **cmd;
    int op;
    int x;
    int y;
    
    op = 1;
    x = 0;
    while(line[x])
    {
        if (line[x] == '|')
            op++;
        x++;
    }
    cmd = malloc(sizeof (char*) * (op + 1));
    y = 0;
    x = 0;
    op = 0;
    tmp = malloc(ft_strlen(line));
    while(line[x])
    {
        if (line[x] == '|')
        {
            tmp[y] = '\0';
            cmd[op] = ft_strdup(ft_strtrim(tmp, " "));
            op++;
            x++;
            y = 0;
            continue;
        }
        tmp[y] = line[x];
        y++;
        x++;
    }
    tmp[y] = '\0';
    cmd[op] = ft_strdup(ft_strtrim(tmp, " "));
    cmd[op + 1] = 0;
    return(cmd);
}

int main(void)
{
    char **cmd;
    char *line;
    //line = "          ls     |      grep -e test                    |      wc -l ";
    /*
    bash-3.2$ echo "    'ls ls '  ' '"   " ' llllll ' "
    'ls ls '  ' '  ' llllll ' 

    */
    line = "ls \"philo\" | grep -e time | wc -l | echo \"    'ls ls '  ' '\"   \" ' llllll ' \"";
    cmd = cmd_parser(line);
    ft_argv_print(cmd);
}