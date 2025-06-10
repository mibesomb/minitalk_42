#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_global {
    int bit_character[8];
    int index;
} t_global;

t_global *data;

void print_character(int *bit_character)
{
    int i;
    char c;

    i = 0;
    c = 0;
    data->index = 0;
    while (i < 8)
    {
        if (bit_character[i] == 1)
            c |= (1 << (7 - i));
        i++;
    }
    write(1, &c, 1);
}

void stocking_bit(int signum)
{
    if (signum == SIGUSR1)
        data->bit_character[data->index] = 1;
    else if (signum == SIGUSR2)
        data->bit_character[data->index] = 0;
    data->index++;
    if (data->index == 8)
        print_character(data->bit_character);
}

int main(int ac)
{
    void *ptr = &stocking_bit;
    data = malloc(sizeof(t_global));
    if (!data)
        return 1;
    data->index = 0;
    printf("%d\n", getpid());
    signal(SIGUSR1, stocking_bit);
    signal(SIGUSR2, stocking_bit);
    while (1)
    {
        pause();
    }
}
