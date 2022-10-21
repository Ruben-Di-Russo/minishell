#include "demo.h"
/*
ls
ls -l
ls -l | wc -l
ls -l | wc -l >> test.txt
ls -l | grep -s test | wc -l
echo aaa > file.txt
echo "hello"
echo hello

detect operator 
1 pipe
2 red

*/
int operator_detector(char *cmd, char *operator){
    int i;
    i = 0;
    while(cmd[i]){
        if(operator[0] && operator[1]){
            if(cmd[i] == operator[0] && cmd[i + 1] == operator[1]){
            return (1);
            }          
        }
        else{
            if(cmd[i] == operator[0]){
                if(cmd[i + 1] == operator[0]){
                    return(0);
                }
                else {
                return (1);
                }
            }
        }
        i++;
    }
    return (0);
}
char	*ft_strip(char **s)
{
	if (*s == NULL)
		return (NULL);
	while (**s == ' ')
		(*s)++;
	while ((*s)[ft_strlen(*s) - 1] == ' ')
		(*s)[ft_strlen(*s) - 1] = '\0';
	return (*s);
}
int cmd_parser(t_config *config){
    char **cmd;
    char **tmp;
    int i;
    int j;
    int cmd_counter;
    int args_counter;
    int counter;
    j = 0;
    i = 0;
    counter = 0;
    cmd_counter = 0;
    args_counter = 0;
    //char *test;
    if(operator_detector(config->line, "|")){
        printf("pip here \n");
        cmd = ft_split(config->line,(char)PIPE_DELM);
        //ft_argv_print(cmd);
        while(cmd[i]){
            //printf("valcmd : %s \n", cmd[i]);
            tmp = ft_split(cmd[i],(char)SPACE_DELM);
            cmd_counter += ft_strlen(tmp[0]);
            args_counter += ft_strlen(tmp[1]);
            config->cmd = malloc(sizeof(char *) * cmd_counter + 1);
            config->args = malloc(sizeof(char *) * args_counter + 1);
            while(tmp[j]){
                if(j % 2 == 0){
                    printf("cmd id %d : %s \n", counter, tmp[j]);
                    config->cmd[counter] = tmp[j];
                    counter++;
                }
                else{
                    printf("args id %d : %s \n", counter, tmp[j]);
                    config->args[counter] = tmp[j];
                    counter++;
                }
                j++;
            }
            i++;
            tmp = 0;
            j = 0;
        }
         //printf("size of cmd %d and ars %d \n", cmd_counter, args_counter);
        //ft_argv_print(config->cmd);
        printf("val : %s \n", config->cmd[1]);
    }
    else if(operator_detector(config->line, ">")){
        printf("single > here \n");
    }
    else{
        printf("simple cmd");
    }

return(0);
}


int main(void){
    t_config config;
    //config.line = "ls -l | grep -s test | wc -l > file.txt";
    config.line = "ls -l | wc -l | grep simoo";
    //config.line = "ls -l ";
    //config.cmd = ft_split(config.line, (char)SPACE_DELM);
    //config.tmp1 = ft_split(config.line, (char)PIPE_DELM);
    //printf("val : %s \n", config.tmp1);
    //ft_argv_print(config.tmp1);
    //printf("val : %s \n", config.tmp1[0]);
    cmd_parser(&config);
    //ft_argv_print(config.cmd);
    /*
    char *ex = "ls -l | grep -s test | wc -l > file.txt";// ls -l wc -l 
    printf("val op %d \n", operator_detector(ex, "<"));
    */
    return (0);
}