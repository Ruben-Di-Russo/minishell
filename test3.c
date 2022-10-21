#include "minishell.h"
char **split_pipe_cmd(char *line)
{
  int position;
  char **tokens;
  char **splited;

  position = 0;
  splited = ft_split(line, (char)PIPE_DELM);
  while (splited[position] != '\0'){
    position++;
  }
  tokens = malloc(position * sizeof(char*));
  position = 0;
  while(splited[position] != '\0'){
    tokens[position] = splited[position];
    position++;
  }
  tokens[position] = 0;
  return tokens;
}
char **split_command_line(char *line)
{
  int position;
  char **tokens;
  char **splited;

  position = 0;
  splited = ft_split(line, (char)SPACE_DELM);
  while (splited[position] != '\0'){
    position++;
  }
  tokens = malloc(position * sizeof(char*));
  position = 0;
  while(splited[position] != '\0'){
    tokens[position] = splited[position];
    position++;
  }
  tokens[position] = 0;
  return tokens;
}
char *demo(char **str){
	int i;
    int count;
    char *line;
    i = 0;
    count = 0;
    while (str[i]){
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


int main(void)
{
char *line = "ls -l | wc -l";
char **tok;
tok = ft_split(line, (char)PIPE_DELM);
char *xx;
xx = demo(tok);
printf("val : %s \n", xx);
/*
//ft_argv_print();
*/
return (0);
}