#ifndef MINISHELL_H
#define MINISHELL_H

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
#define DOUBLE_RIGHT_REDIRECTION '>>'
#define DOUBLE_LEFT_REDIRECTION '<<'


typedef struct s_config
{
    char    **builtin_cmd;
    char    **args_cmd;
    char    *banner;
    char    *line;
    char    **envp;
    int     builtin_len;
    int     n_pipe;
    char    **pipe_cmd;
    int		stdout_clone;
    int		stdin_clone;
    char    *tmp;
} t_config;


char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	    ft_strcmp(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strcat(char *dest, char *src);
char	*ft_strjoin(char const *s1, char const *s2);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_pathfinder(char *cmd, char **envp);
int	    free_matrix(char **matrix);
char    *read_line(t_config *config);

char    *split_to_line(char **str);
int     pipe_detector(t_config *config);

int     pipe_detector(t_config *config);
int     pipe_execute(t_config *config);

int     cmd_execute(t_config *config);
int     cmd_prepare(t_config *config);

int     cmd_cd(char **args);
int     cmd_exit(char **args);

void ft_argv_print(char **argv);
int lsh_num_builtins(char **builtin_str);
int len_num_builtins(char **builtin_str);
char **builtin_str(void);
int  builtin_func(char *cmd, char **args);


void shell_init(t_config *config, char **envp);
void shell_loop(t_config *config);
#endif