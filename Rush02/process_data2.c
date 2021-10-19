#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "utils.h"

t_ull lenght_number(char *s)
{
    if (*s == '\n' || *s == '\0')
        return 0;
    if(*s >= '0' && *s <= '9')
        return 1 + lenght_number(s + 1);
    else
        return lenght_number(s + 1);
}

void print_nb2(t_ull dicval, t_ull inval, t_ull length, PointSCL scl)
{
    t_ull number;

    if (inval == 0)
        return ;
    number = inval / take_val(scl, nbr_len(inval));
    if (inval >= 100)
    {
        print_nb(number,take_val(scl, nbr_len(number)), scl);
        ft_putstr(find_value(scl, take_val(scl, length)));
        print_nb2(take_val(scl, nbr_len(inval % dicval)), inval % dicval, length - 3, scl);
    }
    else if (inval >= 20 && inval < 100)
    {
        ft_putstr(find_value(scl, (inval / 10) * 10));
        print_nb2(take_val(scl, nbr_len(inval % dicval)), inval % dicval, length, scl);
    }
    else if (inval > 0 && inval <= 19)
        ft_putstr(find_value(scl, inval));
}

void split_string(PointSCL scl ,char *s)
{
    int len;
    char *temp;
    int i;
    int count;

    len = ft_len(s);
    count = len / 15;
    while (len > 0)
    {
        temp = (char *)malloc(sizeof(char) * (len - (15 * count) + 1));
        i = 0;
        while (i < len - (15 * count))
            temp[i++] = *s++;
        temp[i] = '\0';
        print_nb2(take_val(scl, ft_len(temp)), ft_atoi(temp), len, scl);
        len = len - (len - (15 * count--));
    }
}
//123456789012345678901234548625562530