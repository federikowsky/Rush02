#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "utils.h"


void control_dict(char *string)
{
	int i;

	i = 1;
	while(string[i] != '\0')
	{	
		if(string[i - 1] == '\n' && string[i] == '\n')
			string[i] = '{';
		else if(string[i - 1] == 32 && string[i] == 32)
			string[i] = '{';
        i++;
	}
}

t_ull	ft_atoi(char *S)
{
	t_ull	num;

	num = 0;
	while (*S && (*S >= '0' && *S <= '9'))
	{
		num = num * 10 + (*S - '0');
		S++;
	}
	return num;
}

t_ull	ft_len(char *s)
{
	if (*s == '\n' || *s == '\0')
		return (0);
	if (*s == '{')
		return (0);
	return (1 + ft_len(s + 1));
}

char	*get_string(char **s)
{
	char	*ris;
	int		i;
	int		count;

	i = -1;
    count = 0;
	while (!((**s >= 65 && **s <= 90) || (**s >= 97 && **s <= 122)))
		(*s)++;
	while ((*s)[++i] != '\n' && (*s)[i] != '\0')
	{
		if (((*s)[i] > 64 && (*s)[i] < 91) || ((*s)[i] > 96 && (*s)[i] < 123))
			count++;
	}
	ris = (char *)malloc(sizeof(char) * count + 1);
	i = 0;
	while (**s != '\n' && **s != '\0')
	{
		if ((**s > 64 && **s < 91) || (**s > 96 && **s < 123))
			ris[i++] = **s;
        (*s)++;
	}
    (*s)++;
	ris[i] = '\0';
	return (ris);
}

t_ull lenght_number(char *s)
{
    if (*s == '\n' || *s == '\0')
        return 0;
    if(*s >= '0' && *s <= '9')
        return 1 + lenght_number(s + 1);
    else
        return lenght_number(s + 1);
}

void node_alloc(PointSCL *scl, char *s) {
    PointSCL temp;
    PointSCL dest;
    int i;

    i = 0;
    while (*s != '\0')
    {
        temp = *scl;
        dest = *scl;
        *scl = (PointSCL)malloc(sizeof(NodoSCL));
        if (lenght_number(s) < 20)
            (*scl)->nb = ft_atoi(s);
        else
            (*scl)->nb = 1111111111111111111 + i++;
        (*scl)->lenght = lenght_number(s);
        (*scl)->string = get_string(&s);
        (*scl)->next = NULL;
        if (temp != NULL) 
        {
            while(temp->next != NULL)
                temp = temp->next;
            temp->next = *scl;
            *scl = dest;
        }
    }
}

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

void make_string(int fd, char *s) 
{
    char c;
    int i;

    i = 0;
    while (read(fd, &c, 1))
        s[i++] = c; 
    s[i] = '\0';
}

int main(int argc, char **argv) {
    int fd; 
    PointSCL scl;
    t_ull val;
    char *temp;

    scl = NULL;
    //char *x = "4627462541";
    temp = (char *)malloc(sizeof(char) * 10000);
    fd = open("numbers.dict", O_RDONLY);
    if (fd == -1)
        return 0;
    //val = ft_atoi(x);
    make_string(fd, temp);
    //control_dict(temp);
    node_alloc(&scl, temp);
    split_string(scl, "12345678901234567890123454862556253002");
    close(fd);
    return 0;
}