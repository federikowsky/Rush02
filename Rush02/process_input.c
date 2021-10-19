#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "utils.h"

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