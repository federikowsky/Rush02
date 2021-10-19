#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "utils.h"

int check_input(int argc, char **argv) {
    int i;

    i = -1;
    if (argc == 2) 
    {
        while(argv[1][++i])
            if (argv[1][i] < '0' || argv[1][i] > '9' )
                return 0;
    }
    if (argc == 3)
    {
        while(argv[2][++i])
            if (argv[2][i] < '0' || argv[2][i] > '9' )
                return 0;
    }
    return 1;
}

char* make_string(int argc, char **argv) 
{
    char c;
    int i;
    char *s;
    int fd; 

    if (argc == 2)
        fd = open("numbers.dict", O_RDONLY);
    else 
        fd = open(argv[1], O_RDONLY);
    s = (char *)malloc(sizeof(char) * 10000);
    i = 0;
    while (read(fd, &c, 1))
        s[i++] = c; 
    s[i] = '\0';
    close(fd);
    return s;
}

int main(int argc, char **argv) {
    PointSCL scl;
    t_ull val;
    char *temp;

    scl = NULL;
    temp = make_string(argc, argv);
    node_alloc(&scl, temp);
    if (argc == 2 && ft_len(argv[1]) < 20)
    {
        val = ft_atoi(argv[1]);
        print_nb(val, take_val(scl, nbr_len(val)), scl);
    }
    else if (argc == 3 && ft_len(argv[2]) < 20)
    {
        val = ft_atoi(argv[2]);
        print_nb(val, take_val(scl, nbr_len(val)), scl);
    }
    else if (argc == 2)
        split_string(scl, argv[1]);
    else
        split_string(scl, argv[2]);
    write(1, "\n", 1);
    return 0;
}
