#include <stdlib.h>
#include "../libraire/libft.h"

typedef struct	s_node_list
{
	int			donnee;
	struct s_node_list *next;
	struct s_node_list *prev;
}				t_node_list;

typedef struct	s_double_list
{
	int					count;
	struct s_node_list *first;
	struct s_node_list *last;
}				t_double_list;

t_double_list	*list_create(void)
{
	return malloc(sizeof(t_double_list));
}

void			print_list(t_double_list *list)
{
	t_node_list *tmp_node;
	tmp_node = list->first;
	while (tmp_node != NULL)
	{
		ft_putnbr(tmp_node->donnee);
		tmp_node = tmp_node->next;
	}
}

// Ajout d'un nouvel element
void			list_push(t_double_list *list, int donnee)
{
	t_node_list *node;
	node = malloc(sizeof(node));
	node->donnee = donnee;
	if (list->last == NULL)
	{
		list->first = node;
		list->last = node;
	} else {
		list->last->next = node;
		node->prev = list->last;
		list->last = node;
	}
	list->count++;
}

int		main(int ac, char **av)
{
	t_double_list *pointeur_list;
	pointeur_list = list_create();

	int i;
	i = 1;

	if (ac == 1)
	{
		ft_putstr("ERREUR : manque les arguments");
		return (0);
	}

	while (i < ac)
		list_push(pointeur_list, ft_atoi(av[i++]));

	print_list(pointeur_list);

	return (0);
}
