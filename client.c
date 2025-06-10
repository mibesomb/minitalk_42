#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ft_strlen(char *string)
{
    int i;

    i = 0;
    while(string[i])
        i++;
    return (i);
}
void send_string(int pid, char *string)
{
    int i;
    int j;
    int size;

    j = 0;
    size = ft_strlen(string);
    while (j < size)
    {
        i = 7;
        while (i >= 0)
        {
            if (((string[j] >> i) & 1) == 1)
                kill(pid, SIGUSR1);
            else if (((string[j] >> i) & 1) == 0)
                kill(pid, SIGUSR2);
            usleep(100);
            i--;
        }
        j++;
    }
}

int main(int ac, char **av)
{
    if (ac != 3)
        return 1;
    int pid;
    pid = atoi(av[1]);
    printf("pid = %d\n", pid);
    printf("av[2] = %s\n", av[2]);
    send_string(pid, av[2]);
    return 0;
}

//if ((string >> i) & 1 == 1) : kill(pid, SIGUSR1) 
//if ((string >> i) & 1 == 0) : kill(pid, SIGUSR2) 

    /*if (kill(pid, SIGUSR1) == -1)
    {
        perror("client");
        return 1;
    }*/