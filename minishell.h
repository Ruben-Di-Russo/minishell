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
#include <fcntl.h>

#define SPACE_DELM ' '
#define PIPE_DELM '|'
#define DOUBLE_RIGHT_REDIRECTION '>>'
#define DOUBLE_LEFT_REDIRECTION '<<'

typedef struct s_cmd
{
    char    *line;
    char    **cmd_line;
    char    **cmd_args;
    char    **cmd_value;
    char    **builtin_cmd;
    int     builtin_len;
    char    **envp;
    int     npipe;
    char    *banner;
    char    **cmd_parser;
    int     num_cmd;
    int		stdout_clone;
    int		stdin_clone;
    char    *operator;
    int     red;
    int     last_cmd_position;
    char    *file;

} t_cmd;


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
char    *read_line(t_cmd *config);

int     double_right(t_cmd *config);
int     single_right(t_cmd *config);
char    *operator(void);
int     cmd_execute(t_cmd *config);
char    **cmd_parser(t_cmd *config, char *line);
void    cmd_fill(t_cmd *config );
int     echo_fill(t_cmd *config, char *line, int i);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strchr(const char *s, int c);
int     pipe_execute(t_cmd *config);


int     red_pipe_execute(int file, t_cmd *config);
int	    ft_process_red(t_cmd *config, int i);

int cmd_single(t_cmd *config);

char    **args_build(t_cmd *config, int i);
int	    ft_child_process(t_cmd *config, int i);
void    ft_clean(t_cmd *config);

int     cmd_execute(t_cmd *config);
int     cmd_prepare(t_cmd *config);

int     cmd_cd(char **args);
int     cmd_exit(char **args);

void ft_argv_print(char **argv, char *type);
int len_num_builtins(char **builtin_str);
char **builtin_str(void);
int  builtin_func(char *cmd, char **args);


void shell_init(t_cmd *config, char **envp);
void shell_loop(t_cmd *config);
#endif