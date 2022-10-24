#include "minishell.h"
int main(void){

  char *txt = "heyru";
  char **split;
  split = ft_split(txt, ' ');
  printf("val %s \n", split[0]);
  printf("val %s \n", split[1]);
  // printf("val %s \n", split[2]);
}