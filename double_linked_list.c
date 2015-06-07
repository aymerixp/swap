#include <stdlib.h>
#include "../libraire/libft.h"

typedef struct		s_node
{
	int				donnee;
	struct s_node	*next;
	//struct s_node	*prev;
}					t_node;

/*
typedef struct	s_double
{
	int					count;
	struct s_node *first;
	struct s_node *last;
}				t_double;
*/

/*
void			print_list(t_double_list *list)
{
	t_node_list *tmp_node;
	tmp_node = list->first;
	ft_putnbr(tmp_node->donnee);
	while (tmp_node != NULL)
	{
		ft_putnbr(tmp_node->donnee);
		tmp_node = tmp_node->next;
	}
}
*/

// Ajout d'un nouvel element
/*
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
*/

void	node_enqueue(t_node **p_node, int donnee)
{
	t_node *p_new_node;
	p_new_node = malloc(sizeof(p_new_node));
	if (p_new_node != NULL)
	{
		p_new_node->next = NULL;
		p_new_node->donnee = donnee;
		if (*p_node == NULL)
		{
			*p_node = p_new_node;
		}
		else
		{
			t_node *p_tmp;
			p_tmp = *p_node;
			while (p_tmp->next != NULL)
			{
				p_tmp = p_tmp->next;
			}
			p_tmp->next = p_new_node;
		}
	}
	else
		ft_putstr("fukof");
}

int		main(int ac, char **av)
{
	t_node *pointeur_list;
	pointeur_list = NULL;

	int i;
	i = 1;

	if (ac == 1)
	{
		ft_putstr("ERREUR : manque les arguments");
		return (0);
	}

	while (i < ac)
		node_enqueue(&pointeur_list, ft_atoi(av[i++]));

	//print_list(pointeur_list);

	return (0);
}
