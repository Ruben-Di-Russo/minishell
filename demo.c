#include "minishell.h"
# include <stdlib.h>

int main(){
    int     channel[2];
    pid_t   child_1;
    pid_t   child_2;

    //*        echo ciao | cat
    //* minishell: cmd_1 | cmd_2


    pipe(channel);

    
    child_1 = fork();
    if (0 == child_1) {
        //* Child   1
        close(channel[0]);
        write(channel[1], "ciao da Simo", sizeof("ciao da Simo"));
        exit(0);
    }
    else
    {
        //* Parent
        child_2 = fork();

        if (0 == child_2) {
            //* Child   2
        char*   str = (char *) malloc(sizeof("ciao da Simo"));
        close(channel[1]);
        read(channel[0], str, sizeof("ciao da Simo"));
        printf("child2 read: %s\n", str);
        exit(0);
        }
        else
        {
            //* Parent
            close(channel[0]);
            close(channel[1]);
            waitpid(child_1, NULL, 0);
            waitpid(child_2, NULL, 0);
            return (0);
        }
    }
}
/*
    int my_fd = open("my_file.txt", O_CREAT | O_READ);



    |       FAS (file aperti di sistema)
    |
    |   name        #fds    fd
    |   stdin,      1       0
    |   my_file.txt, 1       my_fd
    |




    int stdin_clone = dup(0); //* 0 = fd del file special stdout

    |       FAS (file aperti di sistema)
    |
    |   name        #fds    fd
    |   stdin,      2       0, 3
    |   my_file.txt, 1       my_fd
    |

    dup2(0, my_fd); //* close(0); 0 -> my_fd


    |       FAS (file aperti di sistema)
    |
    |   name            #fds    fd
    |   stdout,         1       3
    |   my_file.txt,    2       my_fd
    |

    dup2(0, 3);
    close(3)
*/