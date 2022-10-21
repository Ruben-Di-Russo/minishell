#ifndef DEMO_H
#define DEMO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <readline/readline.h>
#include <readline/history.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#define SPACE_DELM ' '
#define PIPE_DELM '|'
#define DOUBLE_RIGHT_REDIRECTION ">>"
#define DOUBLE_LEFT_REDIRECTION "<<"


typedef struct s_config
{
    char    **args;
    char    **cmd;
    int     i;
    char    *line;
    char    **tmp1;
} t_config;


char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	    ft_strcmp(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strcat(char *dest, char *src);
char	*ft_strjoin(char const *s1, char const *s2);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_pathfinder(char *cmd, char **envp);
int	    free_matrix(char **matrix);



void ft_argv_print(char **argv);
char *split_to_line(char **str);
#endif