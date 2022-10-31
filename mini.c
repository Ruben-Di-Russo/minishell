#include "minishell.h"


char *read_line(t_cmd *config)
{
  char *line;
  line = readline(config->banner);
  if (!line[0])
  {
	while(!line[0])
	line = readline(config->banner);
  }
  else
    add_history(line);
    return (line);
}

void shell_loop(t_cmd *config)
{  
  int status;
  status = 1;

  while(status) 
  {
    config->line = read_line(config);

	    cmd_parser(config, config->line);
		cmd_fill(config);
		cmd_prepare(config);
		//ft_clean(config);		
  }
}


char **args_build(t_cmd *config, int i){
char **now;
int 	x;

x = 0;
now = malloc(sizeof(char *) * 100);
now[x] = ft_strdup(config->cmd_line[i]);
x++;
if(config->cmd_args[i])
{
now[x] = ft_strdup(config->cmd_args[i]);
x++;
}
if(config->cmd_value[i])
{
now[x] = ft_strdup(config->cmd_value[i]);
x++;
}
now[x] = NULL;
// printf("%s %s %s %s \n",now [x - 3] ,now[x - 2], now[x - 1], now[x]);
return(now);
}

int cmd_single(t_cmd *config){

	pid_t pid;

	char **tmp;
	tmp = args_build(config, 0);

	pid = fork();
	if(pid == 0) {
      if(execve(ft_pathfinder(config->cmd_line[0], config->envp), tmp, config->envp)){
			printf("error exec.\n");
	}
		exit(EXIT_FAILURE);

	}
	else if(pid > 0) {
		wait(NULL);
	}
	return 1;

}

int cmd_execute(t_cmd *config){

	if(config->npipe > 0){
		if(config->red > 0){	
			printf("red mode on pip  \n");
			if(config->red == 1)// single >
				return (single_right(config));
			if(config->red == 2)// single >>
				return (double_right(config));
			if(config->red == 3)// single <
				return (single_right(config));
			if(config->red == 4)// single <<
				return (single_right(config));								
		}
		printf("pipe mode \n");
		return (pipe_execute(config));
	}
	else {
		if(config->red > 0){
			printf("red mode on single\n");
			return(single_right(config));	
		}
		printf("single mode \n");		
		return(cmd_single(config));
	}
	
	return (0);
}


int cmd_prepare(t_cmd *config)
{
	int i;
	i = 0;
	
  if (config->cmd_line[0] == NULL) {
    return 1;
  }
  while(i < config->builtin_len){
      if (ft_strcmp(config->cmd_line[0], config->builtin_cmd[i]) == 0) {
        return (builtin_func(config->builtin_cmd[i], &config->cmd_args[0]));
    }
	i++;
  }
	return cmd_execute(config);
}

void shell_init(t_cmd *config, char **envp){
	config->envp = envp;
	config->npipe = 0;
	config->builtin_cmd = builtin_str();
	config->builtin_len = len_num_builtins(config->builtin_cmd);
  	config->banner = ft_strcat(getenv("USER"), "@minishell>");
	config->stdout_clone = dup(STDOUT_FILENO);
	config->stdin_clone = dup(STDIN_FILENO);
	config->operator = operator();
	config->last_cmd_position = 0;
	config->red = 0;
	
	
}

int main(int argc, char **argv,char **envp)
{
  (void)argc;
  (void)argv;
  	t_cmd config;
	//t_cmd config;
	shell_init(&config, envp);
	shell_loop(&config);
  return (1);
}