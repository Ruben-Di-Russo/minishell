#include "minishell.h"

char **builtin_str(void)
{
    char *cmd;
    char **str;
    cmd = "cd exit help";
    str = ft_split(cmd, (char)SPACE_DELM);
    return (str);    
}


void  ft_clean(t_cmd *config){
  printf("start cleaning ... \n");
  config->red = 0;
  config->npipe = 0;
  config->last_cmd_position = 0;
  free(config->cmd_line);
  free(config->cmd_args);
  free(config->cmd_value);
  free(config->cmd_parser);
}

char *operator(void)
{
    char *op;
    op = malloc(sizeof(char) * 3 + 1);
    op[0] = '|';
    op[1] = '>';
    op[2] = '<';
    op[3] = '\0';
    return (op);    
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 - *s2 == 0)
		{
			s1++;
			s2++;
		}
		else
		{
			return (*s1 - *s2);
		}
	}
	return (*s1 - *s2);
}
void ft_argv_print(char **argv, char *type)
{
  int i = 0;
  while (argv[i]){
    printf("%s argv print id %d : %s \n",type, i, argv[i]);
    i++;
  }
}
int builtin_func(char *cmd, char **args){
  if (ft_strcmp(cmd, "cd") == 0){
    // printf("%s args \n", args[0]);
    return (cmd_cd(args));
  }
  else if (ft_strcmp(cmd, "exit") == 0)
    return (cmd_exit(args));
  return (0);
}

char	*ft_pathfinder(char *cmd, char **envp)
{
	char	**mypaths;
	char	*pathnoslash;
	char	*pathinenv;
	char	*finalpath;
	int		i;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4) != 0)
		i++;
	pathinenv = envp[i] + 5;
	mypaths = ft_split(pathinenv, ':');
	i = 0;
	while (mypaths[i])
	{
		pathnoslash = ft_strjoin(mypaths[i], "/");
		finalpath = ft_strjoin(pathnoslash, cmd);
		free(pathnoslash);
		if (access(finalpath, F_OK) == 0)
			return (finalpath);
		free(finalpath);
		i++;
	}
	free_matrix(mypaths);
	return (NULL);
}

int	free_matrix(char **matrix)
{
	int	i;

	i = -1;
	if (!matrix)
		return (1);
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
	return (0);
}

char *split_to_line(char **str){
	  int i;
    int count;
    char *line;
    i = 0;
    count = 0;
    while (str[i] != '\0'){
        count += ft_strlen(str[i]);
        i++;
    }
    line = malloc( sizeof(char) * count + 1 );
    i = 0;
    while(str[i]){
        ft_strcat(line, str[i]);
        i++;
    }
    line[count] = '\0';
    return(line); 
}

int len_num_builtins(char **builtin_str) {
  int i;
  i = 0;
  while(builtin_str[i]){
    i++;
  }
  return (i);
}

/*
  Builtin function implementations.
*/
int cmd_cd(char **args)
{
  // printf("val : %s \n", args[1]);
  if (args[0] == NULL) {
    fprintf(stderr, "expected argument to \"cd\"\n");
  } 
  else {
    if (chdir(args[0]) != 0) {
      perror("shell");
    }
  }
  return 1;
}

int cmd_exit(char **args)
{
  printf("exit /n");
  (void)args;
  return 0;
}