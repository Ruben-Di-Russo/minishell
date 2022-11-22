#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_cmd
{

    char    **cmd_line;
    char    **cmd_args;
    char    **cmd_value;
    char    **arg_build;
    int     test;

} t_cmd;
char	*ft_strdup(const char *s1);
char **prepare(t_cmd *config, int i);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_pathfinder(char *cmd, char **envp);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (0);
	if (len > ft_strlen(s))
		str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	else
		str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	i = 0;
	while (len > 0 && start <= ft_strlen(s))
	{
		str[i] = s[start];
		i++;
		start++;
		len--;
	}
	str[i] = '\0';
	return (str);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char **prepare(t_cmd *config, int i){
int 	x;

x = 0;
config->arg_build = malloc(sizeof(char *) * 100);
config->arg_build[x] = ft_strdup(config->cmd_line[i]);
x++;
if(config->cmd_args[i])
{
config->arg_build[x] = ft_strdup(config->cmd_args[i]);
x++;
}
if(config->cmd_value[i])
{
config->arg_build[x] = ft_strdup(config->cmd_value[i]);
x++;
}
config->arg_build[x] = NULL;
return(config->arg_build);
}
void ft_argv_print(char **argv, char *type)
{
  int i = 0;
  while (argv[i]){
    printf("%s argv print id %d : %s \n",type, i, argv[i]);
    i++;
  }
}

char	*ft_strdup(const char *s1)
{
	char	*s2;	

	s2 = malloc(strlen(s1) + 1);
	if (!(s2))
		return (0);
	ft_memcpy(s2, s1, strlen(s1) + 1);
	return (s2);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (0);
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!n)
		return (0);
	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static size_t	get_word(const char *s, char c)
{
	size_t	ret;

	ret = 0;
	while (*s)
	{
		if (*s != c)
		{
			++ret;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (ret);
}

char	**ft_split(const char *s, char c)
{
	char	**ret;
	size_t	i;
	size_t	len;

	if (!s)
		return (0);
	i = 0;
	ret = malloc(sizeof(char *) * (get_word(s, c) + 1));
	if (!ret)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				++s;
			ret[i++] = ft_substr(s - len, 0, len);
		}
		else
			++s;
	}
	ret[i] = 0;
	return (ret);
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

int main(int argc, char **argv,char **envp){

    t_cmd prova;
    (void)argc;
    (void)argv;

    int i;
    i = 0;
    prova.cmd_line = malloc(10000);
    prova.cmd_args = malloc(10000);
    prova.cmd_value = malloc(10000);
    prova.cmd_line[i] = ft_strdup("builtin echo");
    prova.cmd_args[i] = ft_strdup("-n");
    prova.cmd_value[i] = ft_strdup("ciao");

    prepare(&prova, i);
    printf("val : %s \n", prova.cmd_line[0]);
    ft_argv_print(prova.arg_build, "build : ");
      if(execve(prova.cmd_line[0], prepare(&prova, 0), envp)){
			printf("error exec.\n");
	}

    return (0);
}