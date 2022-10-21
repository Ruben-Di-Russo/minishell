#include "minishell.h"


char *read_line(t_config *config)
{
  char *line;
  line = readline(config->banner);
  if (line == NULL)
    return (0);
  else
    add_history(line);
    return (line);
}

// char **split_command_line(char *line)
// {
//   int position;
//   char **tokens;
//   char **splited;

//   position = 0;
//   splited = ft_split(line, (char)SPACE_DELM);
//   while (splited[position] != '\0'){
//     position++;
//   }
//   tokens = malloc(position * sizeof(char*) + 1);
//   position = 0;
//   while(splited[position] != '\0'){
//     tokens[position] = splited[position];
//     position++;
//   }
//   tokens[position] = 0;
//   return tokens;
// }

// char **split_pipe_cmd(char *line)
// {
//   int position;
//   char **tokens;
//   char **splited;

//   position = 0;
//   splited = ft_split(line, (char)PIPE_DELM);
//   while (splited[position] != '\0'){
//     position++;
//   }
//   tokens = malloc(position * sizeof(char*) + 1);
//   position = 0;
//   while(splited[position] != '\0'){
//     tokens[position] = splited[position];
//     position++;
//   }
//   tokens[position] = 0;
//   return tokens;
// }
void shell_loop(t_config *config)
{  
  int status;
  status = 1;

  while(status) 
  {
    config->line = read_line(config);
	pipe_detector(config);
    if(config->n_pipe){
		config->pipe_cmd = ft_split(config->line, (char)PIPE_DELM);
		config->tmp = split_to_line(config->pipe_cmd);
		printf("line : %s \n", config->tmp);
		config->args_cmd = split_command_line(config->tmp);
		printf("arg0 : %s \n", config->args_cmd[0]);
		printf("arg1 : %s \n", config->args_cmd[1]);
		printf("arg2 : %s \n", config->args_cmd[2]);
		printf("arg3 : %s \n", config->args_cmd[3]);
   		status = pipe_execute(config);
	}
	else
	{
    config->args_cmd = split_command_line(config->line);
	printf("arg0 : %s \n", config->args_cmd[0]);
	printf("arg1 : %s \n", config->args_cmd[1]);
	printf("arg2 : %s \n", config->args_cmd[2]);
	printf("arg3 : %s \n", config->args_cmd[3]);
    status = cmd_prepare(config);
	}
    

    //operator_detector(config);
    //config->pipe_cmd = split_pipe_cmd(config->line);
  
    //ft_argv_print(config->pipe_cmd);
    free(config->line);
    //free(args);
  }
}



int cmd_execute(t_config *config){

	pid_t pid;

	pid = fork();

	if(pid == 0) {
		/*
		printf("cmd 1 : %s \n", config->args_cmd[0]);
		printf("args 2 : %s \n", config->args_cmd[1]);
		*/
		//if (execvp(config->args_cmd[0], config->args_cmd) == -1) {
      if(execve(ft_pathfinder(config->args_cmd[0], config->envp), config->args_cmd, config->envp)){
			printf("error exec.\n");
	}
		exit(EXIT_FAILURE);

	}
	else if(pid > 0) {
		/*
		printf("Parent => PID: %d\n", getpid());
		printf("Waiting for child process to finish.\n");
		*/
		wait(NULL);
		/*
		printf("Child process finished.\n");
		*/
	}
	return 1;

}



int cmd_prepare(t_config *config)
{
	int i;
	i = 0;
	//ft_argv_print(config->args_cmd);  	
	
  if (config->args_cmd[0] == NULL) {
    return 1;
  }

  while(i < config->builtin_len){
      if (ft_strcmp(config->args_cmd[0], config->builtin_cmd[i]) == 0) {
        return (builtin_func(config->builtin_cmd[i], config->args_cmd));
    }
	i++;
  }
	return cmd_execute(config);
}

int pipe_detector(t_config *config){
	int i;
	
	i = 0;
	while(config->line[i]){
		if(config->line[i] == PIPE_DELM ){
			config->n_pipe++;
		}
		i++;
	}
	return(config->n_pipe);
}

int operator_detector(t_config *config, char *str){
(void)config;
(void)str;
return (0);
}

int pipe_execute(t_config *config){

    int     ch[2];
    pid_t   child1;
    pid_t   child2;
    pipe(ch);
    child1 = fork();
	/*
	while(i < config->n_pipe)
	{
	*/

    if (child1 == 0)
    {
        //* Child   1
        close(ch[0]);
        config->stdout_clone = dup(STDOUT_FILENO);
		printf("cmd pipe : %s \n", config->args_cmd[0]);
		printf("val : %s \n", ft_pathfinder(config->args_cmd[0], config->envp));
        dup2(ch[1], STDOUT_FILENO);
		if(execve(ft_pathfinder(config->args_cmd[0], config->envp), config->args_cmd, config->envp))
			printf("error exec pipe 1.\n");
		dup2(config->stdout_clone, STDOUT_FILENO);
		close(config->stdout_clone);
		close(ch[1]);
		exit(0);
    }

    child2 = fork();
    if (child2 == 0){
        //* Child   2
        close(ch[1]);
        config->stdin_clone = dup(STDIN_FILENO);
        dup2(ch[0], STDIN_FILENO);
		printf("cmd pipe2 : %s \n", config->args_cmd[2]);
		printf("val : %s \n", ft_pathfinder(config->args_cmd[2], config->envp));
        if(execve(ft_pathfinder(config->args_cmd[2], config->envp), config->args_cmd, config->envp))
            printf("error exec pipe 2.\n");
        dup2(config->stdin_clone, STDIN_FILENO);
        close(config->stdin_clone);
        close(ch[0]);
        exit(0);
    }

    close(ch[0]);
    close(ch[1]);
    wait(NULL);
    wait(NULL);
/*
}
*/
return (1);
}

void shell_init(t_config *config, char **envp){
	config->envp = envp;
	config->builtin_cmd = builtin_str();
	config->builtin_len = len_num_builtins(config->builtin_cmd);
  	config->banner = ft_strcat(getenv("USER"), "@minishell>");
  	config->n_pipe = 0;
	
}

int main(int argc, char **argv,char **envp)
{
  (void)argc;
  (void)argv;
	t_config config;
	shell_init(&config, envp);
	shell_loop(&config);
  return (1);
}