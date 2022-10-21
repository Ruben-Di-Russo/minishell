#include "minishell.h"

char **builtin_str(void)
{
    char *cmd;
    char **str;
    cmd = "cd exit help";
    str = ft_split(cmd, (char)SPACE_DELM);
    return (str);    
}

int lsh_num_builtins(char **builtin_str) {
  return sizeof(builtin_str) / sizeof(char *);
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
void ft_argv_print(char **argv)
{
  int i = 0;
  while (argv[i]){
    printf("argv print id %d : %s \n", i, argv[i]);
    i++;
  }
}
int builtin_func(char *cmd, char **args){
  printf("inside : %s \n ", args[0]);
  if (ft_strcmp(cmd, "cd") == 0)
    return (cmd_cd(args));
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
  if (args[1] == NULL) {
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  } 
  else {
    if (chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return 1;
}

int cmd_exit(char **args)
{
  (void)args;
  return 0;
}