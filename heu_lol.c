/*
 * source : http://openclassrooms.com/courses/les-listes-doublement-chainees-en-langage-c
 */
#include <stdio.h>
#include "../libraire/libft.h"
/* Macro : supprimer le premier element de la liste */
#define dlist_remove_first(list) dlist_remove_id(list, 1)
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
		p_new->head = NULL;
		p_new->tail = NULL;
	}
	return (p_new);
}

// si on push : le node a deja ete malloc !
void		new_push(t_dlist *list_a, t_dlist *list_b, t_node *node)
{
	ft_putstr("new push : ");
	ft_putnbr(node->data);
	ft_putchar('\n');
	if (list_b->tail == NULL)
	{
		node->prev = NULL;
		list_b->head = node;
		list_b->tail = node;
		ft_putstr("NEW");
	}
	else
	{
		list_b->tail->next = node;
		node->prev = list_b->tail;
		list_b->tail = node;
		ft_putstr("PUSH");
	}
	// append sur t_dlist
	// suppression du node sur la liste ou il est
	// si c'est le dernier node : suppression de la liste
	//
	// connaitre la position du node
	if (node->next == NULL)
	{
		list_a->tail = node->prev;
		list_a->tail->next = NULL;
		ft_putendl("on est a la fin");
	}
	else if (node->prev == NULL)
	{
		list_a->head = node->next;
		list_a->head->prev = NULL;
		ft_putendl("on au debut");
	}
	else
	{
		node->next->prev = node->prev;
		node->prev->next = node->next;
		ft_putendl("otr");
	}
	list_a->length--;
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
t_dlist		*dlist_insert(t_dlist *p_list, int data, int position)
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
void		dlist_delete(t_dlist **p_list)
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

void		dlist_display_inversed(t_dlist *p_list)
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
t_dlist		*dlist_remove_all(t_dlist *p_list, int data)
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
t_dlist		*dlist_remove_id(t_dlist *p_list, int position)
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
size_t		dlist_length(t_dlist *p_list)
{
	size_t ret = 0;
	if (p_list != NULL)
	{
		ret = p_list->length;
	}
	return (ret);
}

/* Rechercher un element selon sa valeur */
t_dlist		*dlist_find(t_dlist *p_list, int data)
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
t_dlist		*dlist_find_all(t_dlist *p_list, int data)
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

t_dlist		*dlist_reverse(t_dlist *p_list)
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

/* trie a bulle  */
int			croissant(int a, int b)
{
	return (a <= b);
}

t_node		*sort_list(t_node *lst, int (*cmp)(int, int))
{
	t_node		*tmp;
	tmp = lst;
	int stop;
	int tmp2;
	stop = 0;
	while (stop != 1)
	{
		stop = 1;
		tmp = lst;
		while (tmp->next)
		{
			if (!cmp(tmp->data, tmp->next->data))
			{
				tmp2 = tmp->data;
				tmp->data = tmp->next->data;
				tmp->next->data = tmp2;
				stop = 0;
			}
			tmp = tmp->next;
		}
		// print
	}
	return (lst);
}
/* fin trie a bulle  */

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
	while (tmp->next)
	{
		if (tmp->data > tmp->next->data)
			tmp = tmp->next;
		else
			return (0);
	}
	return (1);
}

void		push_swap(t_dlist *p_list_a, t_dlist *p_list_b)
{
	// c'est fini quans p_list_a est decroissant et quand p_list_b est NULL
	t_node *tmp;
	tmp = p_list_a->tail;
	while (tmp != NULL)
	{
		// on utilise sa si la valeur de la tail est inferieure a la valeur precedente
		/*
		   if (p_list_a->tail->data > p_list_a->tail->prev->data)
		   {
		// alors le dernier est plus grand que l'avant dernier
		sa(p_list_a); // on arrange ca
		ft_putendl("sa ");
		}
		*/
		//push(p_list_a, p_list_b);
		/*
		   ft_putstr("liste a : ");
		   dlist_display(p_list_a);
		   ft_putstr("liste b : ");
		   dlist_display(p_list_b);
		   */
		// faire un push de node et pas un push de t_dlist
		// on decalle en pushant sur l'autre liste
		// si on est sur la queue de la liste a on repush tout dans l'autre sens puis on verifie si l'ordre est ok
		//ft_putnbr(tmp->data);
		//ft_putchar('X');
		//ft_putnbr(p_list_a->tail->data);
		//
		/* est ce que le premier doit devenir le dernier ? */
		if (p_list_a->head->data < p_list_a->tail->data)
		{
			color_str("ra", "44;1");
			p_list_a = rotate_inverse(p_list_a); // c'est donc un ra
			ft_putchar('\n');
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
			push(p_list_a, p_list_b);
			ft_putstr("pb ");
		}
		tmp = tmp->prev;
	}

	color_str("=========================\n", "33;7");
	ft_putstr("liste a : ");
	dlist_display(p_list_a);
	ft_putstr("liste b : ");
	dlist_display(p_list_b);

	tmp = p_list_b->head;
	color_str("remet tout sur la list a\n", "35");
	while (tmp != NULL)
	{
		ft_putnbr(tmp->data);
		dlist_append(p_list_a, tmp->data);
		if (tmp->next != NULL)
		{
			color_str("if", "33");
			dlist_remove(p_list_b, tmp->data);
		}
		else
		{
			color_str("else", "33");
			p_list_b->tail = NULL;
			p_list_b->head = NULL;
			p_list_b->length--;
			//p_list_b = NULL; // on detruit pas la liste cat on peut en avoir besoin au prochain tour
		}
		//ft_putstr("pa");
		ft_putstr("pa ");
		tmp = tmp->next;
	}
	//if (p_list_b->head->next == NULL)

	/*
	color_str("===========copie sur la liste b==============\n", "36;7");
	if (p_list_a->tail->data > p_list_a->tail->prev->data)
	{
		ft_putnbr(p_list_a->tail->data);
		ft_putstr(" > ");
		ft_putnbr(p_list_a->tail->prev->data);
	}
	*/
	/*
	push(p_list_a, p_list_b);
	push(p_list_a, p_list_b);
	push(p_list_a, p_list_b);
	push(p_list_a, p_list_b);
	push(p_list_a, p_list_b);
	ft_putchar('\n');
	ft_putstr("liste a : ");
	dlist_display(p_list_a);
	ft_putstr("liste b : ");
	dlist_display(p_list_b);
	push(p_list_b, p_list_a);
	push(p_list_b, p_list_a);
	push(p_list_b, p_list_a);
	push(p_list_b, p_list_a);
	push(p_list_b, p_list_a);
*/

	ft_putstr("ttttttttttttttt");
	ft_putnbr(p_list_b->length);
	ft_putstr("ttttttttttttttt");
	if(p_list_b->length == 0)
	{
		if (verif_order(p_list_a))
			color_str("ORDER OK\n", "32;7");
		else
		{
			color_str("ORDER KO\n", "31;7");
			push_swap(p_list_a, p_list_b);
		}
	}
}

// attendu : sa pb pb pb sa pa pa pa
// gcc -Wall -Werror -Wextra oc_double_linked.c ../libraire/libft.a && ./a.out 2 1 3 6 5 8
int			main(int ac, char **av)
{
	int i;
	i = 1;
	t_dlist *list_a;
	list_a = dlist_new();
	t_dlist *list_b;
	list_b = dlist_new();
	if (ac == 1)
		ft_putendl("MANQUE LES ARGUMENTS");

	while (i < ac)
		list_a = dlist_prepend(list_a, ft_atoi(av[i++]));


	color_str("ATTENTION : VERIFIER QU'IL N'Y A PAS DE DOUBLONS\n", "31;7");

	/*
	ft_putchar('\n');
	ft_putstr("liste a : ");
	dlist_display(list_a);
	ft_putstr("liste b : ");
	dlist_display(list_b);
	new_push(list_a, list_b, list_a->head);
	new_push(list_a, list_b, list_a->head->next);
	new_push(list_a, list_b, list_a->head->next->next);
	new_push(list_a, list_b, list_a->head->next->next->next);
	ft_putstr("------------->");
	ft_putnbr(list_a->head->data);
	*/

	/*
	new_push(list_a, list_b, list_a->head->next->next->next->next);
	new_push(list_a, list_b, list_a->head->next->next->next->next->next);
	*/
	color_str("=============juste apres enregistrement :====", "36;7");
	ft_putchar('\n');
	ft_putstr("liste a : ");
	dlist_display(list_a);
	ft_putstr("liste b : ");
	dlist_display(list_b);

	push_swap(list_a, list_b);
	color_str("===========fin de push_swap()================", "36;7");

	ft_putchar('\n');
	ft_putstr("liste a : ");
	dlist_display(list_a);
	ft_putstr("liste b : ");
	dlist_display(list_b);
}
