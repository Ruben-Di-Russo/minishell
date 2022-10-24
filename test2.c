#include "minishell.h"
void exe(char **envp){

    char *args[3];
    char *cmd[1];
    //args[0] = "/bin/ls";
    // cmd[0] = "/bin/ls";
    // args[0] = "-l";
    // args[1] = "parser.c";
	// args[2] = NULL;

    cmd[0] = "/bin/ls";
    args[0] = "ls";
    args[1] = "-l";
    args[2] = NULL;


    if (execve(cmd[0], args, envp))
        printf("error exec 1.\n");

}

int main (int argc, char **argv, char **envp)
{

	exe(envp);
}