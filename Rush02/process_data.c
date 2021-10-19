#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "utils.h"

t_ull nbr_len(t_ull value) 
{
	t_ull count = 0;
	while(value > 0) 
	{
		count++;
		value /= 10;
	}
	return count;
}


char *find_value(PointSCL scl, t_ull value) 
{
    if (scl == NULL)
        return 0;
    if(scl->next == NULL && value == 00)
        return scl->string;
    if (scl->nb == value)
        return scl->string;
    return find_value(scl->next, value);
}

t_ull take_val(PointSCL scl, t_ull len) 
{
    if (scl == NULL)
        return 0;
    if (scl->next == NULL)
        return 00;
    if (len == 2 || len == 1)
        return 10;
    if (scl->lenght <= len && scl->next->lenght > len)
        return scl->nb;
    return take_val(scl->next, len);
}

void ft_putstr(char *s)
{   
    if (*s == '\0')
    {
        write(1, " ", 1);
        return;
    }
    write(1, &(*s), 1);
    ft_putstr(s + 1);
}

void print_nb(t_ull inval, t_ull dicval, PointSCL scl)
{
    t_ull number;

    if (inval == 0)
        return;
    number = inval / dicval;
    if (inval >= 100)
    {
        print_nb(number, take_val(scl, nbr_len(number)), scl);
        ft_putstr(find_value(scl, take_val(scl, nbr_len(inval))));
        print_nb(inval % dicval, take_val(scl, nbr_len(inval % dicval)), scl);
    }
    else if (inval >= 20 && inval < 100)
    {
        ft_putstr(find_value(scl, (inval / 10) * 10));
        print_nb(inval % dicval, take_val(scl, nbr_len(inval % dicval)), scl);
    }
    else if (inval > 0 && inval <= 19)
        ft_putstr(find_value(scl, inval));
}