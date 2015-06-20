#include "../libraire/libft.h"
/* Macro : supprimer le premier element de la liste */
#define dlist_remove_first(list) dlist_remove_id(list, 1) // MEN SERT PAS
/* Macro : supprimer le dernier element de la liste */
#define dlist_remove_last(list) dlist_remove_id(list, dlist_length(list))

typedef struct		s_node
{
	int data;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct		s_dlist
{
	size_t length;
	size_t doublon;
	struct s_node	*tail;
	struct s_node	*head;
}					t_dlist;

/* Allouer une nouvelle liste  */
t_dlist		*dlist_new(void)
{
	t_dlist *p_new = malloc(sizeof *p_new);
	if (p_new != NULL)
	{
		p_new->length = 0;
		p_new->doublon = 0;
		p_new->head = NULL;
		p_new->tail = NULL;
	}
	return (p_new);
}

/* Ajout en fin de liste */
t_dlist		*dlist_append(t_dlist *p_list, int data)
{
	if (p_list != NULL) /* On verifie si notre liste a ete allouee */
	{
		t_node *p_new = malloc(sizeof *p_new); /* Creation d'un nouveau node */
		if (p_new != NULL)
		{
			p_new->data = data;
			p_new->next = NULL; /* On fait pointer next vers NULL  */
			if (p_list->tail == NULL) /* Cas ou notre liste est vide (pointeur vers la fin de liste a NULL) */
			{
				p_new->prev = NULL; /* On fait pointer prev vers NULL  */
				p_list->head = p_new; /* On fait pointer la tete de la liste vers le nouvel element */
				p_list->tail = p_new; /* On fait pointer la fin de la liste vers le nouvel element  */
			}
			else /* Cas ou des elements sont deja presents dans notre liste  */
			{
				p_list->tail->next = p_new; /* On relie le dernier element de la liste vers notre nouvel element (debut du chainage)  */
				p_new->prev = p_list->tail; /* On fait pointer prev vers le dernier element de la liste  */
				p_list->tail = p_new; /* On fait pointer la fin de liste vers notre nouvel element (fin du chainage : 3 etapes)  */
			}
			p_list->length++; /* Incrementation de la taille de la liste  */
		}
	}
	return (p_list); /* On retourne notre nouvelle liste  */
}

/* Ajout en debut de liste  */
t_dlist		*dlist_prepend(t_dlist *p_list, int data)
{
	// verif si doublon 
	t_dlist *tmp;
	tmp = p_list;
	t_node *node;
	node = tmp->head;
	while (node != NULL)
	{
		if (node->data == data)
		{
			tmp->doublon++;
			return (p_list);
		}
		node = node->next;
	}
	if (p_list != NULL)
	{
		t_node *p_new = malloc(sizeof *p_new);
		if (p_new != NULL)
		{
			p_new->data = data;
			p_new->prev = NULL;
			if (p_list->tail == NULL)
			{
				p_new->next = NULL;
				p_list->head = p_new;
				p_list->tail = p_new;
			}
			else
			{
				/* Ce qui change : */
				p_list->head->prev = p_new;
				p_new->next = p_list->head;
				p_list->head = p_new;
			}
			p_list->length++;
		}
	}
	return (p_list);
}

/* Inserer un element */
t_dlist		*dlist_insert(t_dlist *p_list, int data, int position) // MEN SERT PAS
{
	if (p_list != NULL)
	{
		t_node *p_temp = p_list->head;
		int i;
		i = 0;
		while (p_temp != NULL && i <= position)
		{
			if (position == i)
			{
				if (p_temp->next == NULL)
				{
					p_list = dlist_append(p_list, data);
				}
				else if (p_temp->prev == NULL)
				{
					p_list = dlist_prepend(p_list, data);
				}
				else
				{
					t_node *p_new = malloc(sizeof *p_new);
					if (p_new != NULL)
					{
						p_new->data = data;
						p_temp->next->prev = p_new;
						p_temp->prev->next = p_new;
						p_new->prev = p_temp->prev;
						p_new->next = p_temp;
						p_list->length++;
					}
				}
			}
			else
			{
				p_temp = p_temp->next;
			}
			i++;
		}
	}
	return (p_list);
}

/* Liberer une liste  */
void		dlist_delete(t_dlist **p_list) // MEN SERT PAS
{
	if (*p_list != NULL)
	{
		t_node *p_temp = (*p_list)->head;
		while (p_temp != NULL)
		{
			t_node *p_del = p_temp;
			p_temp = p_temp->next;
			free(p_del);
		}
		free (*p_list), *p_list = NULL;
	}
}

void		dlist_display(t_dlist *p_list)
{
	if (p_list != NULL)
	{
		t_node *p_temp = p_list->head;
		while (p_temp != NULL)
		{
			ft_putnbr(p_temp->data);
			ft_putstr(" -> ");
			p_temp = p_temp->next;
		}
	}
	ft_putendl("NULL");
}

void		dlist_display_inversed(t_dlist *p_list) // MEN SERT PAS
{
	ft_putstr("NULL");
	if (p_list != NULL)
	{
		t_node *p_temp = p_list->tail;
		while (p_temp != NULL)
		{
			ft_putstr(" <- ");
			ft_putnbr(p_temp->data);
			p_temp = p_temp->prev;
		}
	}
	ft_putchar('\n');
}

/* supprimer un element selon sa valeur  */
t_dlist		*dlist_remove(t_dlist *p_list, int data)
{
	if (p_list != NULL)
	{
		t_node *p_temp = p_list->head;
		int found = 0;
		while (p_temp != NULL && !found)
		{
			if (p_temp->data == data)
			{
				if (p_temp->next == NULL)
				{
					p_list->tail = p_temp->prev;
					p_list->tail->next = NULL;
				}
				else if (p_temp->prev == NULL)
				{
					p_list->head = p_temp->next;
					p_list->head->prev = NULL;
				}
				else
				{
					p_temp->next->prev = p_temp->prev;
					p_temp->prev->next = p_temp->next;
				}
				free(p_temp);
				p_list->length--;
				found = 1;
			}
			else
			{
				p_temp = p_temp->next;
			}
		}
	}
	return (p_list);
}

/* supprimer un ensemble d'elements suivant une meme valeur */
t_dlist		*dlist_remove_all(t_dlist *p_list, int data) // MEN SERT PAS
{
	if (p_list != NULL)
	{
		t_node *p_temp = p_list->head;
		while (p_temp != NULL)
		{
			if (p_temp->data == data)
			{
				if (p_temp->next == NULL)
				{
					p_list->tail = p_temp->prev;
					p_list->tail->next = NULL;
				}
				else if (p_temp->prev == NULL)
				{
					p_list->head = p_temp->next;
					p_list->head->prev = NULL;
				}
				else
				{
					p_temp->next->prev = p_temp->prev;
					p_temp->prev->next = p_temp->next;
				}
				free(p_temp);
				p_list->length--;
			}
			else
			{
				p_temp = p_temp->next;
			}
		}
	}
	return (p_list);
}

/* Supprimer un element selon sa position */
t_dlist		*dlist_remove_id(t_dlist *p_list, int position) // MEN SERT DANS LES MACROS
{
	if (p_list != NULL)
	{
		t_node *p_temp = p_list->head;
		int i;
		i = 1;
		while (p_temp != NULL && i <= position)
		{
			if (position == i)
			{
				if (p_temp->next == NULL)
				{
					p_list->tail = p_temp->prev;
					p_list->tail->next = NULL;
				}
				else if (p_temp->prev == NULL)
				{
					p_list->head = p_temp->next;
					p_list->head->prev = NULL;
				}
				else
				{
					p_temp->next->prev = p_temp->prev;
					p_temp->prev->next = p_temp->next;
				}
				free(p_temp);
				p_list->length--;
			}
			else
			{
				p_temp = p_temp->next;
			}
			i++;
		}
	}
	return (p_list);
}

/* Avoir la taille d'une liste chainee */
size_t		dlist_length(t_dlist *p_list) // MEN SERT DANS LES MACROS
{
	size_t ret = 0;
	if (p_list != NULL)
	{
		ret = p_list->length;
	}
	return (ret);
}

/* Rechercher un element selon sa valeur */
t_dlist		*dlist_find(t_dlist *p_list, int data) // MEN SERT PAS
{
	t_dlist *ret = NULL;
	if (p_list != NULL)
	{
		t_node *p_temp = p_list->head;
		int found = 0;
		while (p_temp != NULL && !found)
		{
			if (p_temp->data == data)
			{
				ret = dlist_new();
				ret = dlist_append(ret, data);
				found = 1;
			}
			else
			{
				p_temp = p_temp->next;
			}
		}
	}
	return (ret);
}

/* Recherche un ensemble d'elements selon une meme valeur */
t_dlist		*dlist_find_all(t_dlist *p_list, int data) // MEN SERT PAS
{
	t_dlist *ret = NULL;
	if (p_list != NULL)
	{
		t_node *p_temp = p_list->head;
		while (p_temp != NULL)
		{
			if (p_temp->data == data)
			{
				if (ret == NULL)
				{
					ret = dlist_new();
				}
				ret = dlist_append(ret, data);
			}
			p_temp = p_temp->next;
		}
	}
	return (ret);
}

t_dlist		*dlist_reverse(t_dlist *p_list) // MEN SERT PAS
{
	t_dlist *ret = NULL;
	if (p_list != NULL)
	{
		t_node *p_temp = p_list->tail;
		ret = dlist_new();
		while (p_temp != NULL)
		{
			ret = dlist_append(ret, p_temp->data);
			p_temp = p_temp->prev;
		}
	}
	return (ret);
}


/* intervertit les 2 premiers elements au sommet de la pile a */
void		sa(t_dlist *p_list_a)
{
	t_dlist *tmp;
	tmp = p_list_a;
	int a;
	int b;
	a = p_list_a->tail->data;
	b = p_list_a->tail->prev->data;
	/* est ce que le premier est plus grand que le deuxieme de la liste ? */
	if (p_list_a->tail->data > p_list_a->tail->prev->data)
	{
		tmp->tail->data = b;
		tmp->tail->prev->data = a;
		//ft_putendl("sa");
		//ft_putstr("yes");
	}
	//ft_putnbr(tmp->tail->data);
}

/* rotate a */
/* le dernier devient le premier */
t_dlist		*rotate(t_dlist *p_list)
{
	t_node *tmp;
	int data_head;
	data_head = p_list->head->data; // va devenir le next

	tmp = p_list->head;
	while (tmp->next != NULL)
	{
		tmp->data = tmp->next->data;
		tmp = tmp->next;
	}
	p_list->tail->data = data_head;
	return (p_list);
}

/* le premier devient le dernier */
t_dlist		*rotate_inverse(t_dlist *p_list)
{
	t_node *tmp;
	int data_tail;
	data_tail = p_list->tail->data;

	tmp = p_list->tail;
	while (tmp->prev != NULL)
	{
		tmp->data = tmp->prev->data;
		tmp = tmp->prev;
	}
	p_list->head->data = data_tail;
	return (p_list);
}

void		push(t_dlist *list_a, t_dlist *list_b)
{
	dlist_prepend(list_b, list_a->tail->data); // ajoute en debut de liste
	if (list_a->head->next == NULL)
	{
		list_a->tail = NULL;
		list_a->head = NULL;
		list_a->length--;
		list_a = NULL;
	}
	else
		dlist_remove_last(list_a);
}

int			verif_order(t_dlist *p_list_a)
{
	t_node *tmp;
	tmp = p_list_a->head;
	if (p_list_a->length == 0)
		return (1);
	while (tmp->next)
	{
		if (tmp->data > tmp->next->data)
			tmp = tmp->next;
		else
			return (0);
	}
	return (1);
}

int		is_croissant(t_dlist *p_list_b)
{
	t_node *tmp;
	tmp = p_list_b->head;
	if (p_list_b->length == 0)
		return (1);
	while (tmp->next)
	{
		if (tmp->data < tmp->next->data)
			tmp = tmp->next;
		else
			return (0);
	}
	return (1);
}

int		is_value_max(t_dlist *p_list)
{
	int i;
	t_node *tmp;
	tmp = p_list->head;
	i = tmp->data;
	while (tmp != NULL)
	{
		if (tmp->data > i)
			i = tmp->data;
		tmp = tmp->next;
	}
	return (i);
}

void		push_swap(t_dlist *p_list_a, t_dlist *p_list_b)
{
	// c'est fini quans p_list_a est decroissant et quand p_list_b est NULL
	t_node *tmp;
	tmp = p_list_a->tail;
	t_node *tmp2;
	tmp2 = p_list_b->head;
	int i = 0;
	while (tmp != NULL)
	{
		// si tail->data < tail->next
		if (p_list_a->length > 2 && p_list_a->head->data < p_list_a->head->next->data)
		{
			color_str("===avant rra :============\n", "33;7");
			ft_putstr("liste a : ");
			dlist_display(p_list_a);
			ft_putstr("liste b : ");
			dlist_display(p_list_b);
			color_str("rra", "44;1");
			p_list_a = rotate(p_list_a); // c'est donc un rra
			color_str("===apres rra :============\n", "33;7");
			ft_putstr("liste a : ");
			dlist_display(p_list_a);
			ft_putstr("liste b : ");
			dlist_display(p_list_b);
		}
		/* est ce que le premier doit devenir le dernier ? */
		if (p_list_a->head->data < p_list_a->tail->data)
		{
			color_str("===avant ra :============\n", "33;7");
			ft_putstr("liste a : ");
			dlist_display(p_list_a);
			ft_putstr("liste b : ");
			dlist_display(p_list_b);
			color_str("ra", "44;1");
			p_list_a = rotate_inverse(p_list_a); // c'est donc un ra
			color_str("===apres ra :============\n", "33;7");
			ft_putstr("liste a : ");
			dlist_display(p_list_a);
			ft_putstr("liste b : ");
			dlist_display(p_list_b);
		}

		if (p_list_a->length > 2 && p_list_a->tail->data > p_list_a->tail->prev->data)
		{
			sa(p_list_a);
			color_str("sa", "44;1");
			ft_putchar(' ');
		}
		else
		{
			// bloquer ici
			// faire une deuxieme fonction swap sans la definition des variables au debut ?
			if (i < 3)
			{
				push(p_list_a, p_list_b);
				ft_putstr("pb ");
			}
		}
		while (tmp2 != NULL)
		{
			if (p_list_b->length > 2 && p_list_b->head->data < p_list_b->head->next->data)
			{
				color_str("===avant rrb :============\n", "32;7");
				ft_putstr("liste a : ");
				dlist_display(p_list_a);
				ft_putstr("liste b : ");
				dlist_display(p_list_b);
				color_str("rrb", "44;1");
				p_list_b = rotate(p_list_b); // c'est donc un rra
				color_str("===apres rrb :============\n", "32;7");
				ft_putstr("liste a : ");
				dlist_display(p_list_a);
				ft_putstr("liste b : ");
				dlist_display(p_list_b);
			}
			if (p_list_b->head->data < p_list_b->tail->data)
			{
				color_str("===avant rb :============\n", "32;7");
				ft_putstr("liste a : ");
				dlist_display(p_list_a);
				ft_putstr("liste b : ");
				dlist_display(p_list_b);
				color_str("rb", "44;1");
				p_list_b = rotate_inverse(p_list_b); // c'est donc un rb
				color_str("===apres rb :============\n", "32;7");
				ft_putstr("liste a : ");
				dlist_display(p_list_a);
				ft_putstr("liste b : ");
				dlist_display(p_list_b);
			}
			if (p_list_b->length > 2 && p_list_b->tail->data > p_list_b->tail->prev->data)
			{
				sa(p_list_b);
				color_str("sb", "44;1");
				ft_putchar(' ');
			}
			else
			{
				push(p_list_b, p_list_a);
				ft_putstr("pa ");
			}

			tmp2 = tmp2->next;
		}
		tmp = tmp->prev;
		i++;
	}

	color_str("=========================\n", "33;7");
	ft_putstr("liste a : ");
	dlist_display(p_list_a);
	ft_putstr("liste b : ");
	dlist_display(p_list_b);


	// il faut tout remettre avant la fin
	tmp = p_list_b->head;
	color_str("remet tout sur la list a\n", "35");
	while (tmp != NULL)
	{
		dlist_append(p_list_a, tmp->data);
		if (tmp->next != NULL)
		{
			dlist_remove(p_list_b, tmp->data);
		}
		else
		{
			p_list_b->tail = NULL;
			p_list_b->head = NULL;
			p_list_b->length--;
			//p_list_b = NULL; // on detruit pas la liste cat on peut en avoir besoin au prochain tour
		}
		ft_putstr("pa ");
		tmp = tmp->next;
	}

	// si b est decroissant 
	// et
	// si a est decroissant
	// si la tete de b est inferieure a la queue de a, on colle
	//if (verif_order(p_list_b) && verif_order(p_list_a) && p_list_b->head->data < p_list_a->tail->data)
	//	ft_putstr("OUIOIUOIUOIUOIU");
	if(p_list_b->length == 0)
	{
		if (verif_order(p_list_a))
		{
			if (p_list_a->doublon != 0)
			{
				ft_putchar('\n');
				color_nbr(p_list_a->doublon, "33;1");
				if (p_list_a->doublon == 1)
					color_str(" doublon a ete fusionne", "33;1");
				else
					color_str(" doublons ont ete fusionnes", "33;1");
			}
			color_str("ORDER OK\n", "32;7");
		} else
		{
			color_str("ORDER KO\n", "31;7");
			push_swap(p_list_a, p_list_b);
		}
	}
}

void		push_swap2(t_dlist *p_list_a, t_dlist *p_list_b)
{
	t_node *tmp_a;
	tmp_a = p_list_a->head;
	t_node *tmp_b;
	tmp_b = p_list_b->head;
	while (!verif_order(p_list_a) && tmp_a != NULL)
	{
		if (p_list_a->length >= 2 && p_list_a->head->data < p_list_a->head->next->data)
		{
			p_list_a = rotate(p_list_a);
			color_str("rra", "44;1");
		}
		if (p_list_a->length >= 2 && p_list_a->head->data < p_list_a->tail->data)
		{
			p_list_a = rotate_inverse(p_list_a);
			color_str("ra", "44;1");
		}
		if (p_list_a->length >= 2 && p_list_a->tail->data > p_list_a->tail->prev->data)
		{
			color_str("sa", "44;1");
			sa(p_list_a);
		}
		else
		{
			dlist_append(p_list_b, p_list_a->tail->data);
			if (p_list_a->head->next == NULL)
			{
				p_list_a->tail = NULL;
				p_list_a->head = NULL;
				p_list_a->length--;
				//p_list_a = NULL;
			}
			else
				dlist_remove_last(p_list_a);
			//push(p_list_a, p_list_b);
			ft_putstr("pb ");
		}
		// si c'est dans l'ordre : on fait next
		// else
		// on recommence depuis head
		//if (verif_order(p_list_a))
			tmp_a = tmp_a->next;
		//else
			//tmp_a = p_list_a->head;
	}

	// verifier si liste_b est bien CROISSANT
	// si oui : on push tout sur a
	if (is_croissant(p_list_b))
	{
		ft_putendl("yes");
	}
	else
	{
		// sinon on trie list_b
		ft_putendl("nik sa mere");
	}

	// verifier si liste_a est bien DECROISSANT
	// si non : on relance un trie
	if (!verif_order(p_list_a))
	{
		tmp_a = p_list_a->head;
		ft_putendl("list a pas decroissante");
		while (tmp_a != NULL)
		{
			if (p_list_a->length >= 2 && p_list_a->tail->data > p_list_a->tail->prev->data)
			{
				color_str("sa", "44;1");
				sa(p_list_a);
			}
			tmp_a = tmp_a->next;
		}
	}

	ft_putchar('\n');
	color_str("is value max", "41;1");
	ft_putnbr(is_value_max(p_list_b));
	ft_putchar('\n');

	// verifier si liste_b est bien CROISSANT
	// si oui : on push tout sur a
	if (is_croissant(p_list_b))
	{
		// est ce que list a est decroissant ?
		if (verif_order(p_list_a))
		{
			ft_putstr("la liste a est decroissante ");
			// on met la liste b sur la liste a
			tmp_b = p_list_b->tail;
			while (tmp_b != NULL)
			{
				dlist_append(p_list_a, p_list_b->tail->data);
				//if (p_list_a->head->next == NULL)
				if (tmp_b->prev == NULL)
				{
					p_list_b->tail = NULL;
					p_list_b->head = NULL;
					p_list_b->length--;
					//p_list_b = NULL; ATTENTION A CETTE LIGNE DE MERDE
				}
				if (tmp_b->prev != NULL)
					dlist_remove_last(p_list_b);
				ft_putnbr(tmp_b->data);
				tmp_b = tmp_b->prev;
				ft_putstr("pa ");
			}
		}
	}
	else
	{
		// sinon on trie list_b
		tmp_b = p_list_b->head;
		while (tmp_b != NULL)
		{
			ft_putnbr(tmp_b->data);
			if (p_list_b->length >= 2 && p_list_b->tail->data > p_list_b->tail->prev->data)
			{
				color_str("sb", "44;1");
				sa(p_list_b);
			}
			tmp_b = tmp_b->next;
		}

		color_str("faut trier b", "41;1");
		return ;
	}

	/* cas particulier : il reste un data sur la liste b
	 * on push a
	 * puis on verif l'ordre de a */
	if (p_list_b->length == 1)
	{
		//push(p_list_b, p_list_a);
		// ft_putstr("pa");
		color_str("cas particuler ", "41;1");
		return ;
		//while (!verif_order(p_list_a) && tmp_a != NULL)
		//return ;
	}

	/* seulement si b >= 2
	 * si a est decroissant
	 * et
	 * si b est croissant 
	 * si la tete de b est inferieure a la queue de a, on colle
	 */
	/*
	if (p_list_b->length >= 2)
	{
		if (verif_order(p_list_a) && verif_order(p_list_b) && p_list_a->tail->data > p_list_b->tail->data)
		{
			tmp_b = p_list_b->head;
			color_str("remet tout sur la list a\n", "35");
			while (tmp_b != NULL)
			{
				dlist_append(p_list_a, tmp_b->data);
				if (tmp_b->next != NULL)
				{
					dlist_remove(p_list_b, tmp_b->data);
				}
				else
				{
					p_list_b->tail = NULL;
					p_list_b->head = NULL;
					p_list_b->length--;
					//p_list_b = NULL; // on detruit pas la liste cat on peut en avoir besoin au prochain tour
				}
				push(p_list_b, p_list_a);
				ft_putstr("pa ");
				tmp_b = tmp_b->next;
			}
			//return ;
		}
	}
	*/

	if (verif_order(p_list_a) && p_list_b->length == 0)
		color_str("ORDER OK\n", "32;7");
	else
	{
		color_str("ORDER KO\n", "31;7");
		push_swap2(p_list_a, p_list_b);
	}
}

void		push_swap3(t_dlist *p_list_a, t_dlist *p_list_b)
{
	t_node *tmp_a;
	tmp_a = p_list_a->head;
	t_node *tmp_b;
	tmp_b = p_list_b->head;
	while (!verif_order(p_list_a) && tmp_a != NULL)
	{
		if (p_list_a->length >= 2 && p_list_a->head->data < p_list_a->head->next->data)
		{
			p_list_a = rotate(p_list_a);
			color_str("rra ", "44;1");
		}
		if (p_list_a->length >= 2 && p_list_a->head->data < p_list_a->tail->data)
		{
			p_list_a = rotate_inverse(p_list_a);
			color_str("ra ", "44;1");
		}
		if (p_list_a->length >= 2 && p_list_a->tail->data > p_list_a->tail->prev->data)
		{
			color_str("sa ", "44;1");
			sa(p_list_a);
		}
		else
		{
			dlist_append(p_list_b, p_list_a->tail->data);
			if (p_list_a->head->next == NULL)
			{
				p_list_a->tail = NULL;
				p_list_a->head = NULL;
				p_list_a->length--;
				p_list_a = NULL;
			}
			else
				dlist_remove_last(p_list_a);
			push(p_list_a, p_list_b);
			ft_putstr("pb ");
		}
		if (!is_croissant(p_list_b))
		{
			ft_putstr("list b pas croissant");
		}
		// sinon on fait les operations sur la liste b comme sur la liste a
		// et a la fin on regarde si c'est dans l'ordre
		// si c'est vide ?
		// on re rentre dans push swap 3 ?
		tmp_a = tmp_a->next;
	}

	// verifier si liste_b est bien CROISSANT
	// si oui : on push tout sur a
	/*
	if (is_croissant(p_list_b))
	{
		ft_putendl("yes");
	}
	else
	{
		// sinon on trie list_b
		ft_putendl("nik sa mere");
	}*/

	// verifier si liste_a est bien DECROISSANT
	// si non : on relance un trie
/*
	if (!verif_order(p_list_a))
	{
		tmp_a = p_list_a->head;
		ft_putendl("list a pas decroissante");
		while (tmp_a != NULL)
		{
			if (p_list_a->length >= 2 && p_list_a->tail->data > p_list_a->tail->prev->data)
			{
				color_str("sa", "44;1");
				sa(p_list_a);
			}
			tmp_a = tmp_a->next;
		}
	}
*/

	/*
	// verifier si liste_b est bien CROISSANT
	// si oui : on push tout sur a
	if (is_croissant(p_list_b))
	{
		// est ce que list a est decroissant ?
		if (verif_order(p_list_a))
		{
			ft_putstr("la liste a est decroissante ");
			// on met la liste b sur la liste a
			tmp_b = p_list_b->tail;
			while (tmp_b != NULL)
			{
				dlist_append(p_list_a, p_list_b->tail->data);
				//if (p_list_a->head->next == NULL)
				if (tmp_b->prev == NULL)
				{
					p_list_b->tail = NULL;
					p_list_b->head = NULL;
					p_list_b->length--;
					//p_list_b = NULL; ATTENTION A CETTE LIGNE DE MERDE
				}
				if (tmp_b->prev != NULL)
					dlist_remove_last(p_list_b);
				ft_putnbr(tmp_b->data);
				tmp_b = tmp_b->prev;
				ft_putstr("pa ");
			}
		}
	}
*/

	/*
	else
	{
		// sinon on trie list_b
		tmp_b = p_list_b->head;
		while (tmp_b != NULL)
		{
			if (p_list_b->length >= 2 && p_list_b->tail->data > p_list_b->tail->prev->data)
			{
				color_str("sb ", "44;1");
				sa(p_list_b);
			}
			tmp_b = tmp_b->next;
		}

		color_str("faut trier b", "41;1");
		ft_putchar('\n');
		return ;
	}*/

	/* cas particulier : il reste un data sur la liste b
	 * on push a
	 * puis on verif l'ordre de a */
	if (p_list_b->length == 1)
	{
		//push(p_list_b, p_list_a);
		// ft_putstr("pa");
		color_str("cas particuler ", "41;1");
		return ;
		//while (!verif_order(p_list_a) && tmp_a != NULL)
		//return ;
	}

	/* seulement si b >= 2
	 * si a est decroissant
	 * et
	 * si b est croissant 
	 * si la tete de b est inferieure a la queue de a, on colle
	 */
	/*
	if (p_list_b->length >= 2)
	{
		if (verif_order(p_list_a) && verif_order(p_list_b) && p_list_a->tail->data > p_list_b->tail->data)
		{
			tmp_b = p_list_b->head;
			color_str("remet tout sur la list a\n", "35");
			while (tmp_b != NULL)
			{
				dlist_append(p_list_a, tmp_b->data);
				if (tmp_b->next != NULL)
				{
					dlist_remove(p_list_b, tmp_b->data);
				}
				else
				{
					p_list_b->tail = NULL;
					p_list_b->head = NULL;
					p_list_b->length--;
					//p_list_b = NULL; // on detruit pas la liste cat on peut en avoir besoin au prochain tour
				}
				push(p_list_b, p_list_a);
				ft_putstr("pa ");
				tmp_b = tmp_b->next;
			}
			//return ;
		}
	}
	*/

	if (verif_order(p_list_a) && p_list_b->length == 0)
		color_str("ORDER OK\n", "32;7");
	else
	{
		ft_putchar('\n');
		ft_putstr("liste a : ");
		dlist_display(p_list_a);
		ft_putstr("liste b : ");
		dlist_display(p_list_b);
		color_str("ORDER KO\n", "31;7");
		push_swap3(p_list_a, p_list_b);
	}
}

void		push_swap4(t_dlist *p_list_a, t_dlist *p_list_b)
{
	// c'est fini quans p_list_a est decroissant et quand p_list_b est NULL
	t_node *tmp;
	tmp = p_list_a->tail;
	while (tmp != NULL)
	{
		/* est ce que le premier doit devenir le dernier ? */
		if (p_list_a->head->data < p_list_a->tail->data)
		{
			p_list_a = rotate_inverse(p_list_a); // c'est donc un ra
			color_str("ra", "44;1");
			ft_putchar(' ');
		}

		if (p_list_a->length > 2 && p_list_a->tail->data > p_list_a->tail->prev->data)
		{
			sa(p_list_a);
			color_str("sa", "44;1");
			ft_putchar(' ');
		}
		else
		{
			push(p_list_a, p_list_b);
			ft_putstr("pb ");
		}
		tmp = tmp->prev;
	}

	tmp = p_list_b->head;
	while (tmp != NULL)
	{
		dlist_append(p_list_a, tmp->data);
		if (tmp->next != NULL)
		{
			dlist_remove(p_list_b, tmp->data);
		}
		else
		{
			p_list_b->tail = NULL;
			p_list_b->head = NULL;
			p_list_b->length--;
		}
		ft_putstr("pa ");
		tmp = tmp->next;
	}

	if(p_list_b->length == 0)
	{
		if (verif_order(p_list_a))
			color_str("ORDER OK\n", "32;7");
		else
		{
			color_str("ORDER KO\n", "31;7");
			push_swap4(p_list_a, p_list_b);
		}
	}
}

int		find_option(char *s, const char c)
{
	while (*s++ != '\0')
	{
		if (*s == c)
			return (1);
	}
	return (0);
}

int		ft_isstringalpha(char *s)
{
	int i;
	i = 0;
	if (s[i] == '-')
		i++;
	else
		return (0);
	while (s[i] != '\0')
	{
		if (!ft_isalpha(s[i]))
			return (0);
		i++;
	}

	return (1);
}

void		test_trier_une_liste(t_dlist *p_list_a, t_dlist *p_list_b)
{
	t_node *tmp_a;
	tmp_a = p_list_a->head;
	while (tmp_a != NULL)
	{
		//ft_putnbr(tmp_a->data);
		//ft_putchar(' ');
		tmp_a = tmp_a->next;
	}
	if (!verif_order(p_list_a))
	{
		if (p_list_a->length >= 2 && p_list_a->head->data < p_list_a->tail->data)
		{
			p_list_a = rotate_inverse(p_list_a); // c'est donc un ra
			color_str("ra", "44;1");
			ft_putchar(' ');
		}
		if (p_list_a->length >= 2 && p_list_a->tail->data > p_list_a->tail->prev->data)
		{
			color_str("sa ", "44;1");
			sa(p_list_a);
		}
		else
		{
			push(p_list_a, p_list_b);
			color_str("pb ", "44;1");
		}
		//ft_putchar('\n');
		test_trier_une_liste(p_list_a, p_list_b);
	}
	// maintenant a est dans l'ordre alors on renvoi tout sur a et on regarde a nouveau si c'est dans l'ordre ?
	t_node *tmp_b;
	tmp_b = p_list_b->head;
	while (tmp_b != NULL)
	{
		dlist_append(p_list_a, tmp_b->data);
		if (tmp_b->next != NULL)
		{
			dlist_remove(p_list_b, tmp_b->data);
		}
		else
		{
			p_list_b->tail = NULL;
			p_list_b->head = NULL;
			p_list_b->length--;
		}
		ft_putstr("pa ");
		tmp_b = tmp_b->next;
	}

	if (p_list_b->length == 1)
	{
		//push(p_list_b, p_list_a);
		// ft_putstr("pa");
		color_str("cas particuler ", "41;1");
		exit (0);
		//while (!verif_order(p_list_a) && tmp_a != NULL)
		//return ;
	}
	if(p_list_b->length == 0)
	{
		if (verif_order(p_list_a))
		{
			color_str("ORDER OK\n", "32;7");
			exit (0);
		}
		else
		{
			color_str("ORDER KO\n", "31;7");
			test_trier_une_liste(p_list_a, p_list_b);
		}
	}
}

// attendu : sa pb pb pb sa pa pa pa
// gcc -Wall -Werror -Wextra propre.c ../libraire/libft.a -o pust_swap && ./a.out 2 1 3 6 5 8
/*
 * ./push_swap `ruby -e "puts (-5000..5000).to_a.reverse.insert(rand(8000) + 1000, 10001).join(' ')"`
 * ./push_swap `ruby -e "puts (-1000..1000).to_a.shuffle.join(' ')"` 
 */
int			main(int ac, char **av)
{
	int i;
	i = 1;
	t_dlist *list_a;
	list_a = dlist_new();
	t_dlist *list_b;
	list_b = dlist_new();
	if (ac == 1)
	{
		ft_putendl("MANQUE LES ARGUMENTS");
		return (0);
	}
	if (ac == 2)
	{
		ft_putendl("MANQUE UN ARGUMENT");
		return (0);
	}

	if (ft_isstringalpha(av[i]))
	{
		ft_putstr("option ok");
		ft_putchar('\n');
		i++;
	}
	//color_str("mettre des options avec les parametres\n", "31;7");

	// est ce que c'est bien des ints ?
	/*
	if (av[2][0] == '-')
	{
		if (find_option(av[2], 'v'))
			color_str("option verbose OK\n", "35;7");
		if (find_option(av[2], 'c'))
			color_str("option color OK\n", "35;7");
		i = i + 2;
	}
	else
		ft_putchar('\n');
	*/

	if (ft_atoi(av[2]) > 2147483647)
		return (0);

	while (i < ac)
	{
		if (ft_atoi(av[i]) > 2147483647)
		{
			ft_putstr("fucking error");
			return (0);
			//exit(0);
		}
		list_a = dlist_prepend(list_a, ft_atoi(av[i++]));
	}

	/*
	 * est ce que je fais une sortie d'erreur si j'ai un doublon avec une option qui les fusionne ?
	 */

	color_str("=============juste apres enregistrement :====", "36;7");
	ft_putchar('\n');
	ft_putstr("liste a : ");
	dlist_display(list_a);
	ft_putstr("liste b : ");
	dlist_display(list_b);

	//if (verif_order(list_a) == 0)
		//push_swap4(list_a, list_b);
		test_trier_une_liste(list_a, list_b);

	color_str("===========fin de push_swap()================", "36;7");

	ft_putchar('\n');
	ft_putstr("liste a : ");
	dlist_display(list_a);
	ft_putstr("liste b : ");
	dlist_display(list_b);
}
