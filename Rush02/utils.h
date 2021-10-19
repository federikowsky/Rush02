#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

typedef unsigned long long t_ull;
typedef struct s_list {
    t_ull nb;
    t_ull lenght;
    char *string;
    struct s_list *next;
}   t_list;

typedef t_list NodoSCL;
typedef NodoSCL* PointSCL;


t_ull nbr_len(t_ull value);
char *find_value(PointSCL scl, t_ull value);
t_ull take_val(PointSCL scl, t_ull len);
void ft_putstr(char *s);
void print_nb(t_ull inval, t_ull dicval, PointSCL scl);
void fill_SCL(PointSCL scl, char *s);
t_ull ft_atoi(char* S);
t_ull ft_len(char *s);
char *get_string(char **s);
void node_alloc(PointSCL *scl, char *s);
void print_nb2(t_ull dicval, t_ull inval, t_ull length, PointSCL scl);
void split_string(PointSCL scl ,char *s);
t_ull lenght_number(char *s);
