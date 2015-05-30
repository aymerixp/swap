#include "../libraire/libft.h"

typedef struct		s_file
{
	int				data;
	struct s_file	*next;
}					t_file;

void	file_enqueue(t_file **p_file, int data)
{
	t_file *p_new;
	p_new = malloc(sizeof(*p_new));
	if (p_new != NULL)
	{
		p_new->next = NULL;
		p_new->data = data;
		if (*p_file == NULL)
			*p_file = p_new;
		else
		{
			t_file *p_tmp;
			p_tmp = *p_file;
			while (p_tmp->next != NULL)
				p_tmp = p_tmp->next;
			p_tmp->next = p_new;
		}
	}
}

void	print_file(t_file *p_file)
{
	t_file *tmp;

	tmp = p_file;
	while (tmp != NULL)
	{
		ft_putnbr(tmp->data);
		ft_putchar(' ');
		tmp = tmp->next;
	}
}

t_file		*sort(t_file *lst)
{
	t_file *tmp;
	tmp = lst;
	int stop;

	int tmp_swap;
	stop = 0;
	while (stop != 1)
	{
		tmp = lst;
		stop = 1;
		while (tmp->next != NULL)
		{
			if (tmp->data > tmp->next->data)
			{
				tmp_swap = tmp->data;
				tmp->data = tmp->next->data;
				tmp->next->data = tmp_swap;
				stop = 0; /* si on n'est pas rentre dans la condition
				* le trie est termine
				* stop vaut 1
				* donc le while (stop != 1) n'est plus vrai */
			}
			tmp = tmp->next;
		}
	}
	return (lst);
}

t_file	*sa(t_file *lst)
{
	t_file *tmp;
	tmp = lst;

	int tmp_swap;
	while (tmp->next != NULL)
	{
		tmp_swap = tmp->data;
		tmp->data = tmp->next->data;
		tmp->next->data = tmp_swap;
		tmp = tmp->next;
	}
	return (lst);
}

int		main(int ac, char **av)
{
	int i;
	i = 1;
	if (ac <= 1)
	{
		ft_putstr("ERROR : manque les parametres\n");
		return (0);
	}

	t_file *pointeur_file;
	pointeur_file = NULL;
	while (i < ac)
	{
		file_enqueue(&pointeur_file, ft_atoi(av[i]));
		ft_putnbr(ft_atoi(av[i]));
		ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');

	pointeur_file = sa(pointeur_file);
	print_file(pointeur_file);

	return (0);
}
