#include "../libraire/libft.h"

typedef struct		s_btree
{
	int				key_value;
	int				indice;
	struct s_btree	*left;
	struct s_btree	*right;
}					t_btree;

void	insert(int key, t_btree **leaf, int indice)
{
	if (*leaf == NULL)
	{
		*leaf = (t_btree*)malloc(sizeof(t_btree));
		(*leaf)->key_value = key;
		(*leaf)->indice = indice;
		(*leaf)->left = NULL;
		(*leaf)->right = NULL;
	}
	else if (key < (*leaf)->key_value)
	{
		insert(key, &(*leaf)->left, indice);
	}
	else if (key > (*leaf)->key_value)
	{
		insert(key, &(*leaf)->right, indice);
	}
}

void	print_arbre(t_btree *p_tree)
{
	t_btree *tmp;

	tmp = p_tree;
	while (tmp != NULL)
	{
		ft_putnbr(tmp->key_value);
		tmp = tmp->left;
		while (tmp != NULL)
		{
			ft_putnbr(tmp->key_value);
			tmp = tmp->right;
		}
	}
}

int		main(int ac, char **av)
{
	t_btree *root;
	root = NULL;

	int i;
	i = 1;
	if (ac <= 1)
	{
		ft_putstr("ERROR : manque les parametres\n");
		return (0);
	}

	while (i < ac)
	{
		insert(ft_atoi(av[i]), &root, i);
		i++;
	}

	print_arbre(root);

	return (0);
}
