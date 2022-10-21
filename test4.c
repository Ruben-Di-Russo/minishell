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
char *demo(char **str){
    char *line;
    int i, j, count;
    i = 0;
    j = 0;
    count = 0;
    while(str[i]){
        j = 0;
        while(str[i][j]){
            count++;
            j++;
        }
        i++;
    }
    line = malloc( 10000);
    i = 0;
    j = 0;
    count = 0;
    while(str[i]){
        j = 0;
        while(str[i][j]){
            line[count] = str[i][j];
            count++;
            j++;
        }
        i++;
    }
    return (line);
}
int main(void) 
{ 
    char *test;
    char **tok;
    char *x;
    test = "ls - l | wc -e";
    tok = split_pipe_cmd(test);
    x = demo(tok);
    printf("d : %s \n", x);

} 