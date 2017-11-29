#include <stdio.h>
#include <stdlib.h>


struct slist {
	struct slist *next;
	int n;
};
struct stack {
	struct slist *t;
};

typedef struct stack stack;
typedef struct stack pile;
typedef struct slist slist;

pile *init_pile(void);
int pile_pleine(const pile *p);
int pile_vide(const pile *p);
int sommet_pile(const pile *p);
int empiler(pile *p, int elem);
int depiler(pile *p);

/* Ajouter un element à la tête de la liste */
slist *slist_add_head(slist *list, int elem);

/* Supprimmer l'element elem de la liste list */
slist *slist_remove_head(slist *list);

/* Afficher une liste */
void print_slist(slist *l);


/* Creates and returns a stack with the elements of array */
pile *stack_from_array(const int *array, size_t nmemb);

/* Afficher p, en le dépilant */
void depiler_afficher(pile *p);

int main(void)
{
	pile *p;
	pile *q;
	const int a[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
	const int b[] = {1, 4, 6, 8, 10, 14, 16, 20, 21, 30, 32, 36};

	puts("Sorted stacks!");

	p = stack_from_array(a, sizeof a / sizeof a[0]);
	q = stack_from_array(b, sizeof b / sizeof b[0]);

	puts("D\u00e9piler p...");
	depiler_afficher(p);
	puts("D\u00e9piler q...");
	depiler_afficher(q);

	exit(EXIT_SUCCESS);
}

pile *init_pile(void)
{
	pile *const p = malloc(sizeof(pile));
	if (!p) {
		fputs("Problem with allocating memory.\n", stderr);
		return NULL;
	}
	return p;
}

int pile_pleine(const pile *p)
{
	/* This is just so we can avoid the "unused paramater" warning */
	return 0 && p;
}

int pile_vide(const pile *p)
{
	if (!p || !p->t)
		return 1;
	return 0;
}

int sommet_pile(const pile *p)
{
	/* We assume that p is not an empty stack, i.e., (p && p->t) != 0 */
	return p->t->n;
}

int empiler(pile *p, int elem)
{
	/* Again, we assume that p has already been intitialized. */
	if (pile_pleine(p))
		return 0;
	p->t = slist_add_head(p->t, elem);
	return 1;
}

int depiler(pile *p)
{
	/* Again, we assume that p has already been intitialized. */
	p->t = slist_remove_head(p->t);
	return 1;
}

slist *slist_remove_head(slist *list)
{
	slist *tmp;
	if (!list)
		return NULL;
	tmp = list;
	list = list->next;
	free(tmp);
	return list;
}

slist *slist_add_head(slist *list, int elem)
{
	slist *const tmp = malloc(sizeof(slist));
	if (!tmp) {
		fputs("Problem with allocating memory.\n", stderr);
		return list;
	}
	tmp->n = elem;
	tmp->next = list;
	list = tmp;
	return list;
}

void print_slist(slist *l)
{
	while (l) {
		printf("%4d ", l->n);
		l = l->next;
	}
	fputc('\n', stdout);
	return;
}

pile *stack_from_array(const int *array, size_t nmemb)
{
	pile *p = init_pile();
	while (nmemb--)
		empiler(p, *(array++));
	return p;
}

void depiler_afficher(pile *p)
{
	int i;
	for (i = 0; i < 20; ++i) {
		int x = 123456;
		if (!pile_vide(p))
			x = sommet_pile(p);
		else
			break;
		printf("%4d ", x);
		depiler(p);
	}
	fputc('\n', stdout);
	return;
}
