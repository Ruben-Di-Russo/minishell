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

int echo_fill(t_cmd *t_cmd, char *line, int i)
{
    int count;
    char *e;
    char *value;
    value = "-n";
    e = "echo";
    count = 0;
    while(line[0] != ' ')
    {
        line++;
    }
    line++;
    t_cmd->cmd_line[i] = ft_strdup(e);
    if (line[count] == '-')
    {
        line++;
        line++;
        line++;
        while(line[count] == ' '){
            line++;
        }
        t_cmd->cmd_args[i] = ft_strdup(value);
    }
    else
    {
        t_cmd->cmd_args[i] = NULL;
    }
    t_cmd->cmd_value[i] = ft_strdup(line);
    //line++;
    return(1);
}

char **cmd_parser(t_cmd *razzo, char *line)
{
    char *tmp;
    int x;
    int y;
    
    razzo->num_cmd = 1;
    x = 0;
    while(line[x])
    {
        if (line[x] == '|')
            razzo->num_cmd++;
        x++;
    }
    razzo->cmd_parser = malloc(sizeof (char*) * (razzo->num_cmd + 1));
    y = 0;
    x = 0;
    razzo->num_cmd = 0;
    tmp = malloc(ft_strlen(line));
    while(line[x])
    {
        if (line[x] == '|')
        {
            tmp[y] = '\0';
            razzo->cmd_parser[razzo->num_cmd] = ft_strdup(ft_strtrim(tmp, " "));
            razzo->num_cmd++;
            x++;
            y = 0;
            continue;
        }
        tmp[y] = line[x];
        y++;
        x++;
    }
    tmp[y] = '\0';
    razzo->cmd_parser[razzo->num_cmd] = ft_strdup(ft_strtrim(tmp, " "));
    razzo->cmd_parser[razzo->num_cmd + 1] = 0;
    razzo->num_cmd++;
    return(razzo->cmd_parser);
}

void cmd_fill(t_cmd *tcmd ,char **cmd){
(void)cmd;
(void)tcmd;
char *tmp;
char **tmp2;
int i;
int x;
int y;

y = 0;
x = 0;
i = 0;
tcmd->cmd_line = malloc(100);
tcmd->cmd_args = malloc(100);
tcmd->cmd_value = malloc(100);

while(tcmd->cmd_parser[i])
{
    tmp = ft_strdup(tcmd->cmd_parser[i]);
    if(tmp[0] == 'e' && tmp[1] == 'c')
    {
        echo_fill(tcmd, tmp, i);
        i++;
        continue;
    }
    tmp2 = ft_split(tmp, ' ');
    // printf("tmp2 : %s\n", tmp2[2]);
    tcmd->cmd_line[i] = ft_strdup(tmp2[0]);
    if(tmp2[1]){
        tcmd->cmd_args[i] = ft_strdup(tmp2[1]);
    }
    if(tmp2[2]){
        // printf("tmp : %s\n", tmp2[2]);
        tcmd->cmd_value[i] = ft_strdup(tmp2[2]);
    }
    i++;
}
    ft_argv_print(tcmd->cmd_line);
    ft_argv_print(tcmd->cmd_args);
    printf("cmd:%s \n", tcmd->cmd_args[3]);
    printf("val:%s \n", tcmd->cmd_value[0]);
    printf("val:%s \n", tcmd->cmd_value[1]);
    printf("val:%s \n", tcmd->cmd_value[2]);
    printf("val:%s \n", tcmd->cmd_value[3]);
//tmp = ft_split(cmd, ' ');
//ft_argv_print(tmp);

}
void exe(int arc, char **argv, char **envp){
    (void)arc;
    (void)argv;
    char *args[2];
    char *cmd[2];
    //args[0] = "/bin/ls";
    cmd[0] = "/bin/ls";
    args[0] = "-l";
    args[1] = NULL;

    char *argss[3];
    //argss[0] = "/usr/bin/wc";
    cmd[1] = "/usr/bin/grep";
    argss[0] = "-i";
    argss[1] = "test";
    argss[2] = NULL;
    if (execve(cmd[0], args, envp))
        printf("error exec pipe 1.\n");

}
int main(int arc, char **argv, char **envp)
{
    (void)arc;
    (void)argv;
    (void)envp;
    t_cmd config;
    char **cmd;
    char *line;
    //line = "          ls     |      grep -e test                    |      wc -l ";
    /*
    bash-3.2$ echo "    'ls ls '  ' '"   " ' llllll ' "
    'ls ls '  ' '  ' llllll ' 

    */
    //line = "ls \"philo\" | grep -e time | wc -l | echo \"    'ls ls '  ' '\"   \" ' llllll ' \"";
    line = "cd dir | ls -l | id -d            culo | echo -n     'ciao'        ";
    // line = "echo 'ciao'";
    
    cmd = cmd_parser(&config, line);
    //exe(arc, argv, envp);
    // ft_argv_print(cmd);
    cmd_fill(&config, cmd);
}