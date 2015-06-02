/*
 * pile = stack
 */
#include <stdlib.h>
#include "../libraire/libft.h"

typedef struct	s_pile
{
	int			donnee;
	struct s_pile *prev;
}				t_pile;

t_pile	*reverse_pile(t_pile	*pile);

// Ajout d'un nouvel element
void pile_push(t_pile **p_pile, int donnee)
{
	t_pile *p_nouveau;
	p_nouveau = malloc(sizeof *p_nouveau);
	if (p_nouveau != NULL)
	{
		p_nouveau->donnee = donnee;
		p_nouveau->prev = *p_pile;
		*p_pile = p_nouveau;
	}
}

// Retrait d'un element
int		pile_pop(t_pile **p_pile)
{
	int ret;
	ret = -1;
	if (p_pile != NULL && *p_pile != NULL)
	{
		t_pile *temporaire;
		temporaire = (*p_pile)->prev;
		ret = (*p_pile)->donnee;
		free(*p_pile);
		*p_pile = NULL;
		*p_pile = temporaire;
	}
	return (ret);
}

// Vidage de la pile
void	pile_clear(t_pile **p_pile)
{
	while (*p_pile != NULL)
	{
		pile_pop(p_pile);
	}
}

// Retourner la valeur du dernier element
int		pile_peek(t_pile *p_pile)
{
	int ret;
	ret = -1;
	if (p_pile != NULL)
	{
		ret = p_pile->donnee;
	}
	return (ret);
}

t_pile	*reverse_pile(t_pile	*pile)
{
	t_pile		*new;
	new = NULL;
	while (pile != NULL)
	{
		t_pile		*prev;
		prev = pile->prev;
		pile->prev = new;
		new = pile;
		pile = prev;
	}
	return (new);
}

void	sa(t_pile *pile)
{
	t_pile *avant_dernier;
	t_pile *dernier;
	avant_dernier = NULL;
	dernier = NULL;
	int tmp_avant_dernier;
	int tmp_dernier;

	while (pile != NULL)
	{
		if (pile->prev == NULL)
		{
			dernier = pile;
			tmp_avant_dernier = avant_dernier->donnee;
			tmp_dernier = dernier->donnee;
			if (tmp_dernier > tmp_avant_dernier)
			{
				dernier->donnee = tmp_avant_dernier;
				avant_dernier->donnee = tmp_dernier;
				ft_putstr(" sa ");
			}
			/*
			ft_putstr("\n =========== \n");
			ft_putstr("avant dernier :");
			ft_putnbr(tmp_avant_dernier);
			ft_putstr("dernier :");
			ft_putnbr(tmp_dernier);
			ft_putstr("\n =========== \n");
			*/
			/*
			if (avant_dernier != NULL && dernier != NULL)
				ft_putstr("OK");
			ft_putstr(" dernier : ");
			*/
		}
		avant_dernier = pile;
		//ft_putnbr(pile->donnee);
		pile = pile->prev;
	}
}

void	print_pile(t_pile *pile)
{
	t_pile *tmp;

	tmp = pile;
	while (tmp != NULL)
	{
		ft_putnbr(tmp->donnee);
		tmp = tmp->prev;
	}
}

// prend le premier element au sommet de a et le met sur b
void	pb(t_pile **pile_a, t_pile **pile_b)
{
	t_pile	*iter;
	int		sauvegarde_donnee;

	iter = *pile_a;
	while (iter->prev->prev != NULL)
		iter = iter->prev;
	sauvegarde_donnee = iter->prev->donnee;
	iter->prev = NULL;
	pile_push(pile_b, sauvegarde_donnee);
}

int		main(int ac, char **av)
{
	t_pile *pointeur_pile;
	t_pile *pile_b;
	pointeur_pile = NULL;
	pile_b = NULL;
	int i;
	i = 1;

	if (ac == 1)
	{
		ft_putstr("ERREUR : manque les arguments");
		return (0);
	}

	while (i < ac)
		pile_push(&pointeur_pile, ft_atoi(av[i++]));

	//pointeur_pile = reverse_pile(pointeur_pile);

	print_pile(pointeur_pile);
	sa(pointeur_pile);
	ft_putchar('\n');
	print_pile(pointeur_pile);
	pb(&pointeur_pile, &pile_b);
	pb(&pointeur_pile, &pile_b);
	pb(&pointeur_pile, &pile_b);
	sa(pointeur_pile);
	ft_putchar('\n');
	ft_putstr("apres pb :");
	print_pile(pointeur_pile);
	ft_putchar('\n');
	print_pile(pile_b);

	return (0);
}
